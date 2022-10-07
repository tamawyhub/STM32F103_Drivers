#include "MAX30100.h"

#include <string.h>

#define FIFO_BUF_SIZE	64
#define FIFO_SAMPLES	16

static int is_bigendian(void)
{
	uint32_t i = 1;

	return ((*(uint8_t*)&i) == 0);
}

static int MAX30100_get_available(const MAX30100* p_max30100, uint8_t* p_samples)
{
	const MAX30100_LL* p_max30100_ll;
	uint8_t l_writeptr;
	uint8_t l_readptr;
	uint8_t l_n_samples;
	uint8_t l_ovf;
	int l_ret;

	if( !p_max30100)
	{
		return MAX30100_FAILED;
	}

	p_max30100_ll = &p_max30100->max30100_itf;

	l_ret = MAX30100_LL_get_writeptr(p_max30100_ll, &l_writeptr);
	if(l_ret != MAX30100_LL_OK)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_get_readptr(p_max30100_ll, &l_readptr);
	if(l_ret != MAX30100_LL_OK)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_get_ovf_counter(p_max30100_ll, &l_ovf);

	if(l_writeptr > l_readptr)
	{
		l_n_samples = l_writeptr - l_readptr;
	}
	else if(l_readptr > l_writeptr)
	{
		l_n_samples = l_readptr - l_writeptr;
	}
	else	/* There's been either an overflow or the buffer is empty */
	{
		//TODO this is incorrect in the case where the buffer is full, but no ovf has occured yet
		
		if(l_ovf > 0)
		{
			l_n_samples = 0x0F;
		}
		else
		{
			l_n_samples = 0x00;
		}
	}

	*p_samples = l_n_samples;

	return MAX30100_OK;

}

int MAX30100_init(MAX30100* p_max30100)
{
	const MAX30100_LL* p_max30100_ll;
	int l_ret;

	if( !p_max30100)
	{
		return MAX30100_FAILED;
	}

	p_max30100_ll = &p_max30100->max30100_itf;
#if 0
	MAX30100_LL_reset(p_max30100_ll);
#endif
	l_ret = MAX30100_LL_temperature_mode(p_max30100_ll, p_max30100->enable_temp);
	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	switch(p_max30100->hr_spo2_mode)
	{
		case MAX30100_MODE_HR:
			l_ret = MAX30100_LL_heart_rate_enable(p_max30100_ll);
			break;
		case MAX30100_MODE_SPO2:
			l_ret = MAX30100_LL_spo2_enable(p_max30100_ll);
			break;
		default:
			l_ret = MAX30100_LL_FAILED;
			break;
	}

	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_set_sample_rate(p_max30100_ll, p_max30100->sr);
	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_set_adc_resolution(p_max30100_ll, p_max30100->res);
	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_set_ir_current(p_max30100_ll, p_max30100->ir_current);
	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_set_red_current(p_max30100_ll, p_max30100->red_current);
	if(l_ret == MAX30100_LL_FAILED)
	{
		return MAX30100_FAILED;
	}

	MAX30100_QUEUE_init(&p_max30100->samples_queue);

	return MAX30100_OK;
}

int MAX30100_acquire_samples(MAX30100* p_max30100, uint8_t* nread)
{
	uint8_t samples_buf[FIFO_BUF_SIZE];
	uint8_t l_n_samples;
	uint8_t l_nread;
	MAX30100_SAMPLE l_sample;
	int l_ret;

	if(!p_max30100)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_get_available(p_max30100, &l_n_samples);
	if(l_ret != MAX30100_OK)
	{
		return MAX30100_FAILED;
	}

	l_nread = l_n_samples << 2;
	if(nread)
	{
		*nread = 0;
	}

	l_ret = MAX30100_LL_read_fifo(&p_max30100->max30100_itf, samples_buf, l_nread);
	if(l_ret != MAX30100_LL_OK)
	{
		return MAX30100_FAILED;
	}

	for(uint8_t indx = 0; indx < l_nread; indx += 4)
	{
		if(is_bigendian())
		{
			//TODO write code for big endian processors
		}
		else
		{
			l_sample.sample_hr = (uint16_t) samples_buf[indx + 1] & 0xFF;
			l_sample.sample_hr |= (uint16_t) samples_buf[indx] << 8;

			l_sample.sample_spo2 = (uint16_t) samples_buf[indx + 3] & 0xFF;
			l_sample.sample_spo2 |= (uint16_t) samples_buf[indx + 2] << 8;
		}

		if(!MAX30100_QUEUE_full(&p_max30100->samples_queue))
		{
			MAX30100_QUEUE_enqueue(&p_max30100->samples_queue, (const void*) &l_sample);
		}
		else
		{
			if(nread)
			{
				*nread = indx >> 2;
			}
			
			l_ret = MAX30100_FAILED;
			break;
		}
	}

	return l_ret;
}

int MAX30100_get_raw_value(MAX30100* p_max30100, MAX30100_SAMPLE* p_raw_sample)
{
	if(!p_max30100 || !p_raw_sample)
	{
		return MAX30100_FAILED;
	}

	if(MAX30100_QUEUE_empty(&p_max30100->samples_queue))
	{
		return MAX30100_EMPTY;
	}

	if(!MAX30100_QUEUE_dequeue(&p_max30100->samples_queue, p_raw_sample))
	{
		return MAX30100_FAILED;
	}

	return MAX30100_OK;
}

int MAX30100_available(const MAX30100* p_max30100)
{
	return MAX30100_QUEUE_get_count(&p_max30100->samples_queue);
}

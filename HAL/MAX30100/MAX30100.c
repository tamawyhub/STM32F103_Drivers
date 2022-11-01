#include "MAX30100.h"
#include "../DEBUG/DEBUG.h"

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
	uint8_t dummy;
	int l_ret;

	if( !p_max30100)
	{
		return MAX30100_FAILED;
	}

	p_max30100_ll = &p_max30100->max30100_itf;
#if 0
	MAX30100_LL_reset(p_max30100_ll);
#endif
	l_ret = MAX30100_LL_get_pending(p_max30100_ll, &dummy);
	l_ret = MAX30100_LL_set_interrupts(p_max30100_ll, p_max30100->interrupts);
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
	
	p_max30100->max30100_filter.iir_filter.iir_alpha = 0.9f;
	p_max30100->max30100_filter.iir_filter.prev_w = 0.0f;
	p_max30100->max30100_filter.bw_filter.alpha1 = 1.367287359973195227e-1f;
	p_max30100->max30100_filter.bw_filter.alpha2 = 0.72654252800536101020f;
	p_max30100->max30100_filter.bw_filter.prev_v = 0.0f;

	memset(&p_max30100->max30100_data, 0, sizeof(MAX30100_DATA));
	p_max30100->max30100_data.sample_time = 10;	/* 100hz */

	return MAX30100_OK;
}

int MAX30100_acquire_samples(MAX30100* p_max30100, uint8_t* nread)
{
	uint8_t samples_buf[FIFO_BUF_SIZE];
	uint8_t l_n_samples;
	uint8_t l_nread;
	uint8_t dummy;
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
	
	l_ret = MAX30100_LL_set_writeptr(&p_max30100->max30100_itf, 0);
	if(l_ret != MAX30100_LL_OK)
	{
		return MAX30100_FAILED;
	}

	l_ret = MAX30100_LL_set_readptr(&p_max30100->max30100_itf, 0);
	if(l_ret != MAX30100_LL_OK)
	{
		return MAX30100_FAILED;
	}
	
	MAX30100_LL_get_pending(&p_max30100->max30100_itf, &dummy);	/* Clear pending interrupts */

	for(uint8_t indx = 0; indx < l_nread; indx += 4)
	{
		if(is_bigendian())
		{
			//TODO write code for big endian processors
		}
		else
		{
			l_sample.sample_hr = (MAX30100_HR) samples_buf[indx + 1] & 0xFF;
			l_sample.sample_hr |= (MAX30100_HR) samples_buf[indx] << 8;

			l_sample.sample_spo2 = (MAX30100_SPO2) samples_buf[indx + 3] & 0xFF;
			l_sample.sample_spo2 |= (MAX30100_SPO2) samples_buf[indx + 2] << 8;
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

int MAX30100_quantatize(MAX30100* p_max30100)
{
	MAX30100_SAMPLE sample;
	int queue_len;

	if(!p_max30100)
	{
		return MAX30100_FAILED;
	}

	queue_len = MAX30100_available(p_max30100);

	for(uint16_t i = 0; i < queue_len; i++)
	{
		if(MAX30100_QUEUE_dequeue(&p_max30100->samples_queue, &sample) != MAX30100_QUEUE_OK)
		{
			return MAX30100_FAILED;
		}

		sample.sample_hr = (sample.sample_hr > MAX30100_BEAT_THRESHOLD) ? 1 : 0;

		if(MAX30100_QUEUE_enqueue(&p_max30100->samples_queue, &sample) != MAX30100_QUEUE_OK)
		{
			return MAX30100_FAILED;
		}
	}

	return MAX30100_OK;
}

int MAX30100_process_hr(MAX30100* p_max30100)
{

	MAX30100_FILTER* p_filter;
	MAX30100_DATA*	p_data;
	MAX30100_SAMPLE* p_prev_sample;
	MAX30100_SAMPLE sample;
	MAX30100_BPM	l_bpm;
	int queue_len;
	int duration;

	if(!p_max30100)
	{
		return MAX30100_FAILED;
	}

	if(!(p_filter = &p_max30100->max30100_filter))
	{
		return MAX30100_FAILED;
	}

	if(!(p_data = &p_max30100->max30100_data))
	{
		return MAX30100_FAILED;
	}

	if(!(p_prev_sample = &p_data->prev_sample))
	{
		return MAX30100_FAILED;
	}

	if(MAX30100_QUEUE_iir_filter(&p_max30100->samples_queue, &p_filter->iir_filter) != MAX30100_QUEUE_OK)
	{
		return MAX30100_FAILED;
	}

	if(MAX30100_QUEUE_meandiff(&p_max30100->samples_queue) != MAX30100_QUEUE_OK)
	{
		return MAX30100_FAILED;
	}

	if(MAX30100_QUEUE_butterworth(&p_max30100->samples_queue, &p_filter->bw_filter) != MAX30100_QUEUE_OK)
	{
		return MAX30100_FAILED;
	}

	if(MAX30100_quantatize(p_max30100) != MAX30100_QUEUE_OK)
	{
		return MAX30100_FAILED;
	}

	queue_len = MAX30100_available(p_max30100);
	l_bpm = p_data->bpm;

	for(uint16_t i = 0; i < queue_len; i++)
	{
		if(MAX30100_QUEUE_dequeue(&p_max30100->samples_queue, &sample) != MAX30100_QUEUE_OK)
		{
			return MAX30100_FAILED;
		}

		if(p_data->timestamp > p_data->prev_timestamp)
		{
			/* Duration is in milliseconds 
			 * For a 100hz sample rate, sample_time = 10
			 */
			duration = (p_data->timestamp - p_data->prev_timestamp) * p_data->sample_time;
		}
		else
		{
			duration = (p_data->prev_timestamp - p_data->timestamp) * p_data->sample_time;
		}

		if((p_data->prev_sample.sample_hr == 1) && (sample.sample_hr == 0))
		{
			p_data->prev_timestamp = p_data->timestamp;

			if(p_data->timestamp)
			{
				if(duration > 250)
					l_bpm = 60000 / duration;
			}
			else
			{
				l_bpm = 0;
			}

		}
		
		p_data->rising = (sample.sample_hr > p_prev_sample->sample_hr);
		/* Min. heart rate = 15BPM */
		if(duration > 4000)
		{
			l_bpm = 0;
		}

		/* Increment timestamp for every iteration */
		p_data->timestamp++;
		memcpy(p_prev_sample, &sample, sizeof(MAX30100_SAMPLE));
	}

	p_data->bpm = l_bpm;

	return MAX30100_OK;
}

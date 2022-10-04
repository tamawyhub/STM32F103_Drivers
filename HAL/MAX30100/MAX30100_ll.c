#include "MAX30100_ll.h"

#include <stdint.h>
#include <stddef.h>

static int MAX30100_LL_write(const MAX30100_LL* p_max30100, MAX30100_REG reg, uint8_t data)
{
	uint8_t write_buff[2];
	int l_ret;

	write_buff[0] = reg;
	write_buff[1] = data;
	l_ret = MAX30100_LL_FAILED;

	if(p_max30100 && I2C_master_write(p_max30100->i2c_device, p_max30100->addr, write_buff, 2, NULL) == I2C_OK)
	{
		l_ret = MAX30100_LL_OK;
	}

	return l_ret;
}

static int MAX30100_LL_read(const MAX30100_LL *p_max30100, MAX30100_REG reg, uint8_t* data)
{

	if( !p_max30100 || I2C_master_transmit(p_max30100->i2c_device, p_max30100->addr, reg) != I2C_OK)
	{
		return MAX30100_LL_FAILED;
	}

	if( !data || I2C_master_receive(p_max30100->i2c_device, p_max30100->addr, data) != I2C_OK)
	{
		return MAX30100_LL_FAILED;
	}

	return MAX30100_LL_OK;
}

int MAX30100_LL_get_partID(const MAX30100_LL* p_max30100, uint8_t* p_partID)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_PART_ID, p_partID);

	return l_ret;
}

int MAX30100_LL_get_pending(const MAX30100_LL* p_max30100, uint8_t* p_interrupts)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_INT_STATUS, p_interrupts);

	return l_ret;
}

int MAX30100_LL_set_interrupts(const MAX30100_LL* p_max30100, uint8_t interrupts)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_INT_ENABLE, interrupts);

	return l_ret;
}

int MAX30100_LL_get_interrupts(const MAX30100_LL* p_max30100, uint8_t* p_interrupts)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_INT_ENABLE, p_interrupts);

	return l_ret;
}

int MAX30100_LL_get_writeptr(const MAX30100_LL* p_max30100, uint8_t* p_ptr)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_FIFO_WR_PTR, p_ptr);

	return l_ret;
}

int MAX30100_LL_set_writeptr(const MAX30100_LL* p_max30100, uint8_t ptr)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_FIFO_WR_PTR, ptr);

	return l_ret;
}

int MAX30100_LL_get_readptr(const MAX30100_LL* p_max30100, uint8_t* p_ptr)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_FIFO_RD_PTR, p_ptr);

	return l_ret;
}

int MAX30100_LL_set_readptr(const MAX30100_LL* p_max30100, uint8_t ptr)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_FIFO_RD_PTR, ptr);

	return l_ret;
}


int MAX30100_LL_get_ovf_counter(const MAX30100_LL* p_max30100, uint8_t* p_cnt)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_FIFO_OVF_CTR, p_cnt);

	return l_ret;
}

int MAX30100_LL_set_ovf_counter(const MAX30100_LL* p_max30100, uint8_t cnt)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_FIFO_OVF_CTR, cnt);

	return l_ret;
}


int MAX30100_LL_get_mode_config(const MAX30100_LL* p_max30100, uint8_t* p_mode)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_MODE_CONF, p_mode);

	return l_ret;
}

int MAX30100_LL_set_mode_config(const MAX30100_LL* p_max30100, uint8_t mode)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_MODE_CONF, mode);

	return l_ret;
}

int MAX30100_LL_standby(const MAX30100_LL* p_max30100, uint8_t enable)
{
	uint8_t l_mode;
	int l_ret;

	l_ret = MAX30100_LL_get_mode_config(p_max30100, &l_mode);
	if(l_ret == MAX30100_LL_OK)
	{
		if(enable)
		{
			l_mode |= MAX30100_LL_STANDBY_MODE;
		}
		else
		{
			l_mode &= ~MAX30100_LL_STANDBY_MODE;
		}

		MAX30100_LL_set_mode_config(p_max30100, l_mode);

		l_mode = 0;
		MAX30100_LL_get_mode_config(p_max30100, &l_mode);
		l_ret = (l_mode & MAX30100_LL_STANDBY_MODE) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
	}

	return l_ret;
}

int MAX30100_LL_reset(const MAX30100_LL* p_max30100)
{
	int l_ret;

	l_ret = MAX30100_LL_set_mode_config(p_max30100, MAX30100_LL_RESET_MODE);

	return l_ret;
}

int MAX30100_LL_temperature_mode(const MAX30100_LL* p_max30100, uint8_t enable)
{
        uint8_t l_mode;
        int l_ret;
        
        l_ret = MAX30100_LL_get_mode_config(p_max30100, &l_mode);
        if(l_ret == MAX30100_LL_OK)
        {
                if(enable)
                {
                        l_mode |= MAX30100_LL_TEMP_EN;
                }       
                else
                {
                        l_mode &= ~MAX30100_LL_TEMP_EN;
                }

                MAX30100_LL_set_mode_config(p_max30100, l_mode);

                l_mode = 0;
                MAX30100_LL_get_mode_config(p_max30100, &l_mode);
                l_ret = (l_mode & MAX30100_LL_TEMP_EN) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
        }

        return l_ret;
}

int MAX30100_LL_heart_rate_enable(const MAX30100_LL* p_max30100)
{
        uint8_t l_mode;
        int l_ret;

        l_ret = MAX30100_LL_get_mode_config(p_max30100, &l_mode);
        if(l_ret == MAX30100_LL_OK)
        {
		l_mode &= ~MAX30100_LL_SPO2_ENABLE;
		l_mode |= MAX30100_LL_HR_ENABLE;
                MAX30100_LL_set_mode_config(p_max30100, l_mode);

                l_mode = 0;
                MAX30100_LL_get_mode_config(p_max30100, &l_mode);
                l_ret = (l_mode & MAX30100_LL_HR_ENABLE) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
        }

        return l_ret;
}

int MAX30100_LL_spo2_enable(const MAX30100_LL* p_max30100)
{
        uint8_t l_mode;
        int l_ret;

        l_ret = MAX30100_LL_get_mode_config(p_max30100, &l_mode);
        if(l_ret == MAX30100_LL_OK)
        {
                l_mode |= MAX30100_LL_SPO2_ENABLE;
                MAX30100_LL_set_mode_config(p_max30100, l_mode);

                l_mode = 0;
                MAX30100_LL_get_mode_config(p_max30100, &l_mode);
                l_ret = (l_mode & MAX30100_LL_SPO2_ENABLE) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
        }

        return l_ret;
}

int MAX30100_LL_get_spo2_config(const MAX30100_LL* p_max30100, uint8_t* p_conf)
{
	int l_ret;

	l_ret = MAX30100_LL_read(p_max30100, MAX30100_SPO2_CONF, p_conf);

	return l_ret;
}


int MAX30100_LL_set_spo2_config(const MAX30100_LL* p_max30100, uint8_t conf)
{
	int l_ret;

	l_ret = MAX30100_LL_write(p_max30100, MAX30100_SPO2_CONF, conf);

	return l_ret;
}

int MAX30100_LL_set_adc_resolution(const MAX30100_LL* p_max30100, MAX30100_LL_RESOLUTION res)
{
	uint8_t l_conf;
	int l_ret;

	l_ret = MAX30100_LL_get_spo2_config(p_max30100, &l_conf);
	if(l_ret == MAX30100_LL_OK)
	{
		if(res < MAX30100_LL_ADC_RES_MAX)
		{
			l_conf &= 0xFC;
			l_conf |= res;
			MAX30100_LL_set_spo2_config(p_max30100, l_conf);
			
			l_conf = 0;
			MAX30100_LL_get_spo2_config(p_max30100, &l_conf);
			l_ret = ((l_conf & 0x03) == (res & 0x03)) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
		}
		else
		{
			l_ret = MAX30100_LL_FAILED;
		}
	}

	return l_ret;
}

int MAX30100_LL_set_sample_rate(const MAX30100_LL* p_max30100, MAX30100_LL_SAMPLE_RATE	rate)
{
        uint8_t l_conf;
        int l_ret;

        l_ret = MAX30100_LL_get_spo2_config(p_max30100, &l_conf);
        if(l_ret == MAX30100_LL_OK)
        {
                if(rate < MAX30100_LL_SAMPLE_RATE_MAX)
                {
                        l_conf &= 0xE3;
                        l_conf |= (rate << 2);
                        MAX30100_LL_set_spo2_config(p_max30100, l_conf);

                        l_conf = 0;
                        MAX30100_LL_get_spo2_config(p_max30100, &l_conf);
                        l_ret = ((l_conf & 0x1C) == ((rate << 2) & 0x1C)) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
                }
                else
                {
                        l_ret = MAX30100_LL_FAILED;
                }
        }

        return l_ret;
}

int MAX30100_LL_get_led_config(const MAX30100_LL* p_max30100, uint8_t* p_led_current)
{
        int l_ret;

        l_ret = MAX30100_LL_read(p_max30100, MAX30100_LED_CONF, p_led_current);

        return l_ret;
}


int MAX30100_LL_set_led_config(const MAX30100_LL* p_max30100, uint8_t led_current)
{
        int l_ret;

        l_ret = MAX30100_LL_write(p_max30100, MAX30100_LED_CONF, led_current);

        return l_ret;
}

int MAX30100_LL_set_ir_current(const MAX30100_LL* p_max30100, uint8_t current)
{
        uint8_t l_conf;
        int l_ret;

        l_ret = MAX30100_LL_get_led_config(p_max30100, &l_conf);
        if(l_ret == MAX30100_LL_OK)
        {
		l_conf &= 0xF0;
                l_conf |= (current & 0x0F);
                MAX30100_LL_set_led_config(p_max30100, l_conf);

                l_conf = 0;
                MAX30100_LL_get_led_config(p_max30100, &l_conf);
                l_ret = ((l_conf & 0x0F) == (current & 0x0F)) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
        }

        return l_ret;
}

int MAX30100_LL_set_red_current(const MAX30100_LL* p_max30100, uint8_t current)
{
        uint8_t l_conf;
        int l_ret;

        l_ret = MAX30100_LL_get_led_config(p_max30100, &l_conf);
        if(l_ret == MAX30100_LL_OK)
        {
                l_conf &= 0x0F;
                l_conf |= (current<<4) & 0xF0;
                MAX30100_LL_set_led_config(p_max30100, l_conf);

                l_conf = 0;
                MAX30100_LL_get_led_config(p_max30100, &l_conf);
                l_ret = ((l_conf & 0xF0) == ((current<<4) & 0xF0)) ? MAX30100_LL_OK : MAX30100_LL_FAILED;
        }

        return l_ret;
}


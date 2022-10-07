#ifndef MAX30100_LL_H
#define MAX30100_LL_H

#include "../MCAL/I2C/I2C_interface.h"

#include <stdint.h>

#define MAX30100_INT_A_FULL 	(1<<7)
#define MAX30100_INT_TEMP_RDY	(1<<6)
#define MAX30100_INT_HR_RDY	(1<<5)
#define MAX30100_INT_SPO2_RDY	(1<<4)
#define MAX30100_INT_PWR_RDY	(1<<0)

#define MAX30100_LL_STANDBY_MODE	(1<<7)
#define MAX30100_LL_RESET_MODE		(1<<6)
#define MAX30100_LL_TEMP_EN		(1<<3)

#define MAX30100_LL_HR_ENABLE		0x02
#define MAX30100_LL_SPO2_ENABLE		0x03

#define MAX30100_LL_ADC_RES_MAX		4
#define MAX30100_LL_SAMPLE_RATE_MAX	8

typedef enum max30100_reg_t
{
	MAX30100_INT_STATUS = 0x00,
	MAX30100_INT_ENABLE,
	MAX30100_FIFO_WR_PTR,
	MAX30100_FIFO_OVF_CTR,
	MAX30100_FIFO_RD_PTR,
	MAX30100_FIFO_DATA,
	MAX30100_MODE_CONF,
	MAX30100_SPO2_CONF,
	MAX30100_LED_CONF = 0x09,
	MAX30100_TEMP_INTG = 0x16,
	MAX30100_TEMP_FRAC,
	MAX30100_REV_ID = 0xFE,
	MAX30100_PART_ID = 0xFF
} MAX30100_REG;

enum max30100_ll_error
{
	MAX30100_LL_OK,
	MAX30100_LL_FAILED
};

typedef uint8_t MAX30100_LL_RESOLUTION;

typedef uint8_t MAX30100_LL_SAMPLE_RATE;

typedef struct max30100_ll
{
	const I2C_CONFIG* i2c_device;
	uint8_t addr;
} MAX30100_LL;


int MAX30100_LL_get_partID(const MAX30100_LL* p_max30100, uint8_t* p_partID);
int MAX30100_LL_get_pending(const MAX30100_LL* p_max30100, uint8_t* p_interrupts);
int MAX30100_LL_set_interrupts(const MAX30100_LL* p_max30100, uint8_t interrupts);
int MAX30100_LL_get_interrupts(const MAX30100_LL* p_max30100, uint8_t* p_interrupts);
int MAX30100_LL_get_writeptr(const MAX30100_LL* p_max30100, uint8_t* p_ptr);
int MAX30100_LL_set_writeptr(const MAX30100_LL* p_max30100, uint8_t ptr);
int MAX30100_LL_get_readptr(const MAX30100_LL* p_max30100, uint8_t* p_ptr);
int MAX30100_LL_set_readptr(const MAX30100_LL* p_max30100, uint8_t ptr);
int MAX30100_LL_get_ovf_counter(const MAX30100_LL* p_max30100, uint8_t* p_cnt);
int MAX30100_LL_set_ovf_counter(const MAX30100_LL* p_max30100, uint8_t cnt);
int MAX30100_LL_standby(const MAX30100_LL* p_max30100, uint8_t enable);
int MAX30100_LL_reset(const MAX30100_LL* p_max30100);
int MAX30100_LL_temperature_mode(const MAX30100_LL* p_max30100, uint8_t enable);
int MAX30100_LL_heart_rate_enable(const MAX30100_LL* p_max30100);
int MAX30100_LL_spo2_enable(const MAX30100_LL* p_max30100);
int MAX30100_LL_set_adc_resolution(const MAX30100_LL* p_max30100, MAX30100_LL_RESOLUTION res);
int MAX30100_LL_set_sample_rate(const MAX30100_LL* p_max30100, MAX30100_LL_SAMPLE_RATE  rate);
int MAX30100_LL_set_ir_current(const MAX30100_LL* p_max30100, uint8_t current);
int MAX30100_LL_set_red_current(const MAX30100_LL* p_max30100, uint8_t current);
int MAX30100_LL_read_fifo(const MAX30100_LL* p_max30100, uint8_t* buf, uint8_t buf_size);

#endif

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include <stdint.h>

typedef enum i2c_enum_t
{
	I2C1,
	I2C2,
	I2C_COUNT,
} I2C_PERIPHS;

typedef enum i2c_errors_t
{
	I2C_OK,
	I2C_BAD_ADDR,
	I2C_INV,
	I2C_NACK,
	I2C_BUS_ERROR,
	I2C_ACK_FAILURE,
	I2C_ARB_LOST,
	I2C_OVR_ERROR,
} I2C_ERRORS;

typedef struct i2c_config_t
{
	uint16_t ccr;
	uint8_t trise;
	uint8_t apb_freq;
	uint8_t slave_addr1;
	uint8_t slave_addr2;	//COMBINED WITH ADDR1 in 10 bit mode
	uint8_t interrupts;
	uint8_t i2c_id;

} I2C_CONFIG;


int I2C_init(I2C_CONFIG* i2c_config);
int I2C_slave_receive(I2C_CONFIG* i2c_config, uint8_t *buf);
int I2C_slave_transmit(I2C_CONFIG* i2c_config, uint8_t byte);
int I2C_master_transmit(I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t byte);
int I2C_master_write(const I2C_CONFIG* i2c_config, uint8_t slave_addr, const void* buff, uint32_t buff_size, uint32_t* p_sent);
int I2C_master_receive(I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t* byte);
int I2C_master_read(const I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t* buf, uint32_t buf_size);

#endif

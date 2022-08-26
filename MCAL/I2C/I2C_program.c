#include "I2C_private.h"
#include "I2C_interface.h"
#include "BIT_MATH.h"

volatile I2C* const I2C_arr[] = {
	I2C1_BASE,
	I2C2_BASE
}

int I2C_init(I2C_CONFIG* i2c_config)
{
	uint8_t l_i2c_id;

	if(i2c_config == NULL)
	{
		return -1;
	}

	l_i2c_id = i2c_config->i2c_id;

	if(l_i2c_id > I2C_COUNT)
	{
		return I2C_INV;
	}

	I2C_arr[l_i2c_id]->cr1 = 0x00;
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 10);	//Ack Enabled
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 6);	//General Call Enabled

	I2C_arr[l_i2c_id]->cr2 = 0x00;
	I2C_arr[l_i2c_id]->cr2 |= (0x08 << 5);

	I2C_arr[l_i2c_id]->oar1 = 0x00;
	
	if(i2c_config->slave_addr1 > 127)
	{
		return I2C_BAD_ADDR;
	}
	I2C_arr[l_i2c_id]->oar1 |= (i2c_config->slave_addr1 << 1) ;

	SET_BIT(I2C_arr[l_i2c_id]->cr1, 0);

	return I2C_OK;
}

int I2C_slave_receive(I2C_CONFIG* i2c_config, uint8_t *buf)
{
	uint8_t l_i2c_id;

	if(i2c_config == NULL || buf == NULL)
	{
		return -1;
	}

	l_i2c_id = i2c_config->i2c_id;
	if(l_i2c_id > I2C_COUNT)
	{
		return I2C_INV;
	}

	while(!GET_BIT(I2C_arr[l_i2c_id]->sr1, 1));

	/*Address received */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->sr2;

	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 6));
	
	/* Byte received */
	
	*buf = I2C_arr[l_i2c_id]->dr;
	
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 4));

	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->cr1 |= 0x00;

	return I2C_OK;
}


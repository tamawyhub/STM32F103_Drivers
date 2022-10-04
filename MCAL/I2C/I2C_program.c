#include "I2C_private.h"
#include "I2C_interface.h"
#include "BIT_MATH.h"
#include "USART/USART_interface.h"

#include <stddef.h>
#include <stdint.h>

volatile I2C* const I2C_arr[] = {
	I2C1_BASE,
	I2C2_BASE
};

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
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 15);
	CLR_BIT(I2C_arr[l_i2c_id]->cr1, 15);

	I2C_arr[l_i2c_id]->cr2 = 0x00;
	if(i2c_config->apb_freq < 2)
	{
		return I2C_INV;
	}
        I2C_arr[l_i2c_id]->cr2 |= i2c_config->apb_freq; //Set FREQ

	I2C_arr[l_i2c_id]->ccr = 0x00;
	I2C_arr[l_i2c_id]->ccr |= i2c_config->ccr;	/* I2C clokc */

	I2C_arr[l_i2c_id]->trise = 0x00;
	I2C_arr[l_i2c_id]->trise |= i2c_config->trise;	/* I2C max. rise time */

	SET_BIT(I2C_arr[l_i2c_id]->cr1, 0);	//Periph Enable
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 10);	//Ack Enabled
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 6);	//General Call Enabled

	if(i2c_config->slave_addr1 > 127)	//Address1 in case of slave mode
	{
		return I2C_BAD_ADDR;
	}
	I2C_arr[l_i2c_id]->oar1 |= (i2c_config->slave_addr1 << 1) ;

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
	
	/* Stop bit */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->cr1 |= 0x00;

	return I2C_OK;
}

int I2C_slave_transmit(I2C_CONFIG* i2c_config, uint8_t byte)
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
	
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 1));

	/* address received */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->sr2;

	I2C_arr[l_i2c_id]->dr = byte;
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 7) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 4));

	/*NAck or Stop  bit */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->cr1 |= 0x00;

	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		return I2C_NACK;
	}
	
	return I2C_OK;
}

int I2C_master_transmit(I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t byte)
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

	if(slave_addr > 127)
        {
                return I2C_BAD_ADDR;
        }
	
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 8);	/* Put in master mode */
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 0));

	/* Start condition sent */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->dr = slave_addr << 1;
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 1) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10)); /* address ACKed/NACKed */

	/* Address sent */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->sr2;

	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
		SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
		return I2C_ACK_FAILURE;
	}

	/* ACK received */
	I2C_arr[l_i2c_id]->dr = byte;
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 2) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10)); /* Waith until ACK/NACK reception */
	
	/* Generate stop cond. */
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);

	/* Data NACKed */
	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
		return I2C_ACK_FAILURE;
	}
		
	return I2C_OK;
}

int I2C_master_write(const I2C_CONFIG* i2c_config, uint8_t slave_addr, const void* buff, uint32_t buff_size, uint32_t* p_sent)
{

	uint8_t l_i2c_id;
	uint32_t l_indx;
	const char* l_buff;
	int l_ret;

        if(i2c_config == NULL || buff == NULL)
        {
                return -1;
        }

        l_i2c_id = i2c_config->i2c_id;
        if(l_i2c_id > I2C_COUNT)
        {
                return I2C_INV;
	}

	if(slave_addr > 127)
        {
                return I2C_BAD_ADDR;
        }

	SET_BIT(I2C_arr[l_i2c_id]->cr1, 8);	/* Put in master mode */
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 0));

	/* Start condition sent */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->dr = slave_addr << 1;
	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 1) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10)); /* address ACKed/NACKed */

	/* Address sent */
	I2C_arr[l_i2c_id]->sr1;
	I2C_arr[l_i2c_id]->sr2;

	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
		SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
		return I2C_ACK_FAILURE;
	}

	/* ACK received */
	l_indx = 0;
	l_buff = buff;
	while(l_indx < buff_size && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		I2C_arr[l_i2c_id]->dr = l_buff[l_indx];
		while(!GET_BIT(I2C_arr[l_i2c_id]->sr1, 7) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10));
		l_indx++;
	}

	/* Generate stop cond. But wait for BTF or AF first*/
	while(!GET_BIT(I2C_arr[l_i2c_id]->sr1, 2) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10));
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);

	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
	{
		/* NACK recieved */
		CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
		l_indx--;
		l_ret = I2C_ACK_FAILURE;
	}
	else
	{
		l_ret = I2C_OK;
	}

	if(p_sent)
	{
		*p_sent = l_indx;
	}

	return l_ret;
}

int I2C_master_receive(I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t* byte)
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

        if(slave_addr > 127)
        {
                return I2C_BAD_ADDR;
        }

        SET_BIT(I2C_arr[l_i2c_id]->cr1, 8);     /* Put in master mode */
        while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 0));

        /* Start condition sent */
        I2C_arr[l_i2c_id]->sr1;
        I2C_arr[l_i2c_id]->dr = (slave_addr << 1) | 0x01;
        while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 1) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10)); /* address ACKed/NACKed */

        /* Address sent */
        I2C_arr[l_i2c_id]->sr1;
        I2C_arr[l_i2c_id]->sr2;

        if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
        {
                CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
                SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
                return I2C_ACK_FAILURE;
        }

	CLR_BIT(I2C_arr[l_i2c_id]->cr1, 10);
	SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);

	while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 6));

	*byte = I2C_arr[l_i2c_id]->dr;

	return I2C_OK;
}

int I2C_master_read(const I2C_CONFIG* i2c_config, uint8_t slave_addr, uint8_t* buf, uint32_t buf_size)
{
	uint8_t l_i2c_id;
	uint32_t indx;

        if(i2c_config == NULL || buf == NULL)
        {
                return -1;
        }

        l_i2c_id = i2c_config->i2c_id;
        if(l_i2c_id > I2C_COUNT)
        {
                return I2C_INV;
        }

        if(slave_addr > 127)
        {
                return I2C_BAD_ADDR;
        }

        SET_BIT(I2C_arr[l_i2c_id]->cr1, 8);     /* Put in master mode */
        while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 0));

        /* Start condition sent */
        I2C_arr[l_i2c_id]->sr1;
        I2C_arr[l_i2c_id]->dr = (slave_addr << 1) | 0x01;
        while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 1) && !GET_BIT(I2C_arr[l_i2c_id]->sr1, 10)); /* address ACKed/NACKed */

        /* Address sent */
        I2C_arr[l_i2c_id]->sr1;
        I2C_arr[l_i2c_id]->sr2;
	
	if(GET_BIT(I2C_arr[l_i2c_id]->sr1, 10))
        {
                CLR_BIT(I2C_arr[l_i2c_id]->sr1, 10);
                SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
                return I2C_ACK_FAILURE;
        }
	
	if(buf_size > 2)
	{
		for(indx = 0; indx < buf_size - 3; indx++)
		{
			while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 6));
			buf[indx] = I2C_arr[l_i2c_id]->dr;
		}
		while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 2));	/* WAIT BTF = 1, STRETCH CLOCK LINE */
		CLR_BIT(I2C_arr[l_i2c_id]->cr1, 10);
		buf[indx] = I2C_arr[l_i2c_id]->dr;
		SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
		buf[indx + 1] = I2C_arr[l_i2c_id]->dr;
		while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 6));
		buf[indx + 2] = I2C_arr[l_i2c_id]->dr;
	}
	else if(buf_size == 2)
	{
		CLR_BIT(I2C_arr[l_i2c_id]->cr1, 10);
		while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 2));
		SET_BIT(I2C_arr[l_i2c_id]->cr1, 9);
		buf[0] = I2C_arr[l_i2c_id]->dr;
		while( !GET_BIT(I2C_arr[l_i2c_id]->sr1, 6));
		buf[1] = I2C_arr[l_i2c_id]->dr;

	}
	else
	{
		return -1;
	}

	return I2C_OK;
}

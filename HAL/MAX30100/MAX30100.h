#ifndef MAX30100_H
#define MAX30100_H

#include "../MCAL/I2C/I2C_interface.h"

typedef struct max30100_t
{
	const I2C_CONFIG* i2c_device;
} MAX30100;

#endif

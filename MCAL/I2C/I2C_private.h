#ifndef I2C_PRIVATE
#define I2C_PRIVATE

#include <stdint.h>

#define I2C1_BASE ((I2C* const) 0x40005400)
#define I2C2_BASE ((I2C* const) 0x40005800)

typedef struct i2c_t
{
	uint32_t cr1;
	uint32_t cr2;
	uint32_t oar1;
	uint32_t oar2;
	uint32_t dr;
	uint32_t sr1;
	uint32_t sr2;
	uint32_t ccr;
	uint32_t trise;
} I2C;


#endif

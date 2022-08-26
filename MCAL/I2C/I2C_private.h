#ifndef I2C_PRIVATE
#define I2C_PRIVATE

#define I2C1_BASE
#define I2C2_BASE

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

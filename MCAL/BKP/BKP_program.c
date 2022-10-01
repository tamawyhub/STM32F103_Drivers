#include "BKP_interface.h"
#include "BKP_private.h"

int BKP_read_data(uint8_t indx, uint16_t* buff)
{
	if(indx > 0 && indx < BKP_DR_COUNT)
	{
		*buff = BKP.bkp_dr[indx];
		return 0;
	}

	return -1;
}

int BKP_write_data(uint8_t indx, uint16_t data)
{
	if(indx > 0 && indx < BKP_DR_COUNT)
	{
		BKP.bkp_dr[indx] = data;
		return 0;
	}

	return -1;
}

void BKP_enable_cco(void)
{
	BKP.bkp_rtccr |= (1<<7);
};

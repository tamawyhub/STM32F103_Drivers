#include "RTC_interface.h"
#include "RTC_private.h"
#include "BIT_MATH.h"

#include <stdint.h>


void RTC_sync(void)
{
	while( !GET_BIT(RTC.rtc_crl, 5));	/* POLL RTOFF */
	CLR_BIT(RTC.rtc_crl, 3);
	while( !GET_BIT(RTC.rtc_crl, 3));
}

void RTC_config_prescaler(uint32_t prescaler)
{
	while( !GET_BIT(RTC.rtc_crl, 5));	/* POLL RTOFF */
	SET_BIT(RTC.rtc_crl, 4);
	RTC.rtc_prll = (uint16_t) prescaler & 0xFFFF;
	RTC.rtc_prlh = (uint16_t) (prescaler >> 16) & 0x0F;
	CLR_BIT(RTC.rtc_crl, 4);
	while( !GET_BIT(RTC.rtc_crl, 5));
}

void RTC_update_cnt(uint32_t sys_cnt)
{
	while( !GET_BIT(RTC.rtc_crl, 5));	/* POLL RTOFF */
	SET_BIT(RTC.rtc_crl, 4);		/* CNF mode */
	RTC.rtc_cntl = (uint16_t) sys_cnt & 0xFFFF;
	RTC.rtc_cnth = (uint16_t) (sys_cnt >> 16) & 0xFFFF;
	CLR_BIT(RTC.rtc_crl, 4);
	while( !GET_BIT(RTC.rtc_crl, 5));
}
	
void RTC_init(RTC_SOURCE src, uint32_t prescaler, uint32_t sys_cnt)
{
	switch(src)
	{
		case RTC_NO_CLOCK:
			break;
		case RTC_LSE:
			SET_BIT(RCC_BDCR, 0);
			while(! GET_BIT(RCC_BDCR, 1));	/* Wait LSERDY */
			SET_BIT(RCC_BDCR, 8);
			break;
		case RTC_LSI:
			SET_BIT(RCC_BDCR, 9);
			break;
		case RTC_HSE:
			SET_BIT(RCC_BDCR, 8);
			SET_BIT(RCC_BDCR, 9);
			break;
	}

	SET_BIT(RCC_BDCR, 15);	/* Enable RTC */

	RTC_sync();
	RTC_config_prescaler(prescaler);
	RTC_update_cnt(sys_cnt);

}

uint32_t RTC_get_systime(void)
{
	uint32_t systime;

	systime = (RTC.rtc_cnth << 16) & 0xFFFF0000;
	systime |= RTC.rtc_cntl;

	return systime;
}

void RTC_poll_secf(void)
{
	while( !GET_BIT(RTC.rtc_crl, 0));
	CLR_BIT(RTC.rtc_crl, 0);
}


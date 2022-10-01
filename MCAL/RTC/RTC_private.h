#ifndef RTC_PRIVATE_H
#define RTC_PRIVATE_H

#include <stdint.h>

#define RTC_BASE 0x40002800
#define RCC_BASE 0x40021000

struct RTC_t
{
	uint32_t rtc_crh;
	uint32_t rtc_crl;
	uint32_t rtc_prlh;
	uint32_t rtc_prll;
	uint32_t rtc_divh;
	uint32_t rtc_divl;
	uint32_t rtc_cnth;
	uint32_t rtc_cntl;
	uint32_t rtc_alrh;
	uint32_t rtc_alrl;
};


#define RTC (*((volatile struct RTC_t*) RTC_BASE))
#define RCC_BDCR (*((volatile uint32_t*) (RCC_BASE + 0x20)))

#endif

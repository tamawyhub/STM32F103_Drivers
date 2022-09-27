#ifndef RTC_INTERFACE_H
#define RTC_INTERFACE_H

#include <stdint.h>

typedef enum rtc_src_t
{
	RTC_NO_CLOCK,
	RTC_LSE,
	RTC_LSI,
	RTC_HSE
} RTC_SOURCE;

void RTC_sync(void);
void RTC_config_prescaler(uint32_t prescaler);
void RTC_update_cnt(uint32_t sys_cnt);
void RTC_init(RTC_SOURCE src, uint32_t prescaler, uint32_t sys_cnt);
uint32_t RTC_get_systime(void);
void RTC_poll_secf(void);

#endif

/*
 * Author: Mohammed Hisham
 * Date: 6 March 2020
 * Version: 1.0
 */

#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

#include <stdint.h>

#define SYSTICK_AHB_DIV_8       0
#define SYSTICK_AHB_DIV_1       1

void SYSTICK_voidEnableTimer(void);
void SYSTICK_voidDisableTimer(void);
void SYSTICK_voidEnableException(void);
void SYSTICK_voidDisableException(void);
void SYSTICK_voidSelectClock(uint8_t Copy_u8Source);
uint8_t SYSTICK_u8ReadFlag(void);
void SYSTICK_voidLoadTimer(uint32_t Copy_u32Value);
uint32_t SYSTICK_u32GetCount(void);
void SYSTICK_voidSetBusyWait(uint32_t Copy_u32Ticks);
void SYSTICK_voidSetIntervalPeriodic(uint32_t Copy_u32Ticks, void (*callback_ptr) (void));
#endif

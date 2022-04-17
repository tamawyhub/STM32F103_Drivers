/*
 * Author: Mohammed Hisham
 * Date: 23 March 2022
 * Version:  1.0
 */


#ifndef TIMx_INTERFACE_H
#define TIMx_INTERFACE_H

#include <stdint.h>


#define TIM2	0
#define TIM3	1
#define TIM4	2
#define TIM5	3

#define TIMx_UPCOUNT_MODE		0
#define TIMx_DOWNCOUNT_MODE		1
#define TIMx_CENTERALIGNED_01		2
#define TIMx_CENTERALIGNED_02		3
#define TIMx_CENTERALIGNED_03		4

/* External Mode 1 Options */

#define EXTERNAL_MODE1_TI1FP1		0
#define EXTERNAL_MODE1_TI2FP2		1
#define EXTERNAL_MODE1_TI1FED		2

#define TIMx_EDGE_RISING		0
#define TIMx_EDGE_FALLING		1

#define TIMx_PSC_0			0
#define TIMx_PSC_2			1
#define TIMx_PSC_4			2
#define TIMx_PSC_8			3

#define TIMx_CHANNEL_1			1
#define TIMx_CHANNEL_2			2
#define TIMx_CHANNEL_3			3
#define TIMx_CHANNEL_4			4

#define TIMx_COMPARE_FROZEN		0
#define TIMx_COMPARE_SET_ACTIVE		1
#define TIMx_COMPARE_SET_INACTIVE	2
#define TIMx_COMPARE_SET_TOGGLE		3

#define TIMx_ACTIVE_HIGH		0
#define TIMx_ACTIVE_LOW			1


void TIMx_voidInitTimer(uint8_t Copy_u8Timer, uint8_t Copy_u8Mode);
void TIMx_voidSetExternalMode1(uint8_t Copy_u8Timer, uint8_t Copy_u8Src, uint8_t Copy_u8Edge);
void TIMx_voidSetExternalMode2(uint8_t Copy_u8Timer, uint8_t Copy_u8Psc, uint8_t Copy_u8Edge);
void TIMx_voidEnableCapture(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8Psc, uint8_t Copy_u8Edge);
void TIMx_voidEnableCompare(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8OCMode, uint8_t Copy_u8Polarity);
void TIMx_voidEnablePWM(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8Polarity);
void TIMx_voidSetCompareValue(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint16_t Copy_u16Value);
uint16_t TIMx_u16GetCaptureValue(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel);
void TIMx_voidWaitCCFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel);
void TIMx_voidClearCCFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel);
uint8_t TIMx_u8GetOVFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel);
void TIMx_voidClearOVFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel);
void TIMx_voidEnableCCInterrupt(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, void (*callback)(void));
void TIMx_voidSetPrescaler(uint8_t Copy_u8Timer, uint16_t Copy_u16Prescaler);
void TIMx_voidSetPreload(uint8_t Copy_u8Timer, uint16_t Copy_u16Preload);
void TIMx_voidSetCounter(uint8_t Copy_u8Timer, uint16_t Copy_u8Val);
void TIMx_voidEnableTimer(uint8_t Copy_u8Timer);
void TIMx_voidDisableTimer(uint8_t Copy_u8Timer);
void TIMx_voidWaitUpdateFlag(uint8_t Copy_u8Timer);
void TIMx_voidEnableUpdateInterrupt(uint8_t Copy_u8Timer, void (*Copy_pISR) (void));
void TIMx_voidDisableUpdateInterrupt(uint8_t Copy_u8Timer);

#endif

/*
 *Author:
 *
 *
 */

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include <stdint.h>

#define EXTI_MODE_RISING	0
#define EXTI_MODE_FALLING	1
#define EXTI_MODE_ON_CHANGE	2

void EXTI_voidEnableLine(uint8_t Copy_u8Line);
void EXTI_voidDisableLine(uint8_t Copy_u8Line);
void EXTI_voidSetTriggerMode(uint8_t Copy_u8Line, uint8_t Copy_u8Mode);
void EXTI_voidClearPending(uint8_t Copy_u8Line);


#endif

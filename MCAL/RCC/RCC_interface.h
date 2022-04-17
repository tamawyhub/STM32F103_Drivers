/*
 * Author: Mohammed Hisham
 * Date: 14 Feb 2022
 * Version: 1.0
 */

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include <stdint.h>

#define RCC_AHB		0
#define RCC_APB1	1
#define RCC_APB2	2

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId);
void RCC_voidDisableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId);

#endif

/*
 * Author: Mohammed Hisham
 * Date: 19 Feb 2022
 * Version: 1.0
 * Note: Applied to External Interrupts ONLY
 */

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include <stdint.h>

/* System Exceptions */

#define MEM_MANAGEMENT_EXCEPTION	0
#define BUS_FAULT_EXCEPTION		1
#define USAGE_FAULT_EXCEPTION		2
#define SVCALL_EXCEPTION		3
#define DEBUG_MONITOR_EXCEPTION		4
#define	PENDSV_EXCEPTION		5
#define SYSTICK_EXCEPTION		6

/* External Intterupts */

#define EXTI0_IRQ       6
#define EXTI1_IRQ       7
#define EXTI2_IRQ       8
#define EXTI3_IRQ       9
#define EXTI4_IRQ       10
#define EXTI9_5_IRQ     23
#define EXTI15_10_IRQ   40

#define ADC1_2_IRQ      18

#define TIM2_IRQ        28
#define TIM3_IRQ        29
#define TIM4_IRQ        30

#define SPI1_IRQ	35
#define SPI2_IRQ	36

#define USART1_IRQ      37
#define USART2_IRQ      38
#define USART3_IRQ      39


void NVIC_voidEnableIRQ(uint8_t Copy_u8IRQ);
void NVIC_voidDisableIRQ(uint8_t Copy_u8IRQ);
void NVIC_voidSetPending(uint8_t Copy_u8IRQ);
void NVIC_voidClearPending(uint8_t Copy_u8IRQ);
uint8_t NVIC_u8GetActiveFlag(uint8_t Copy_u8IRQ);
void NVIC_voidSetIRQPriority(uint8_t Copy_u8IRQ, uint8_t Copy_u8Pri);
void NVIC_voidSetExceptionPriority(uint8_t Copy_u8Exception, uint8_t Copy_u8Pri);

#endif

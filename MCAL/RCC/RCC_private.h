/*
 * Author: Mohammed Hisham
 * Date: 14 Feb 2022
 * Version: 1.0
 */

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Register definitions	*/

#define RCC_CR		*((volatile uint32_t*) 0x40021000)
#define RCC_CFGR	*((volatile uint32_t*) 0x40021004)
#define RCC_CIR		*((volatile uint32_t*) 0x40021008)
#define RCC_APB2RSTR	*((volatile uint32_t*) 0x4002100C)
#define RCC_APB1RSTR	*((volatile uint32_t*) 0x40021010)
#define RCC_AHBENR	*((volatile uint32_t*) 0x40021014)
#define RCC_APB2ENR	*((volatile uint32_t*) 0x40021018)
#define RCC_APB1ENR	*((volatile uint32_t*) 0x4002101C)
#define RCC_BDCR	*((volatile uint32_t*) 0x40021020)
#define RCC_CSR		*((volatile uint32_t*) 0x40021024)

/*RCC_CLOCK_TYPE */

#define RCC_HSI		0
#define RCC_HSE_CLK	1
#define RCC_HSE_XTAL	2
#define RCC_PLL		3

/*RCC_PLL_INPUT */

#define RCC_PLL_HSI_div_2	0
#define RCC_PLL_HSE_DIV_1	1
#define RCC_PLL_HSE_DIV_2	2

#endif

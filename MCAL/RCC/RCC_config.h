/*
 * Author: Mohammed Hisham
 * Date: 14 Feb 2022
 * Version: 1.0
 */

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H


/* Options for RCC_CLOCK_TYPE 
 * RCC_HSE_XTAL
 * RCC_HSE_CLK
 * RCC_HSI
 * RCC_PLL
 */

#define RCC_CLOCK_TYPE	RCC_HSE_XTAL


/* Options for RCC_PLL_INPUT
 * RCC_PLL_HSI_DIV_2
 * RCC_PLL_HSE_DIV_1
 * RCC_PLL_HSE_DIV_2
 */

/* Options for RCC_PLL_MUL
 * From 2 To 16
 */

#if RCC_CLOCK_TYPE == RCC_PLL

#define RCC_PLL_INPUT 	RCC_PLL_HSE_DIV_2
#define RCC_PLL_MUL	16

#endif


#endif

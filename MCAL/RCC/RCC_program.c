/*
 * Author: Mohammed Hisham
 * Date: 14 Feb 2022
 * Version: 1.0
 */

#include "BIT_MATH.h"
#include "RCC/RCC_interface.h"
#include "RCC/RCC_private.h"
#include "RCC/RCC_config.h"


void RCC_voidInitSysClock(void){

#if 	RCC_CLOCK_TYPE == RCC_HSI
	SET_BIT(RCC_CR, 0);
#elif	RCC_CLOCK_TYPE == RCC_HSE_CLK
	SET_BIT(RCC_CR, 16);
	SET_BIT(RCC_CR, 18);
	SET_BIT(RCC_CFGR, 0);
#elif	RCC_CLOCK_TYPE == RCC_HSE_XTAL	
	SET_BIT(RCC_CR, 16);
	SET_BIT(RCC_CFGR, 0);
#elif	RCC_CLOCK_TYPE == RCC_PLL
	#if	RCC_PLL_INPUT == RCC_PLL_HSI_DIV_2
		SET_BIT(RCC_CR, 0);
	#elif	RCC_PLL_INPUT == RCC_PLL_HSE_DIV_1
		SET_BIT(RCC_CR, 16);
		SET_BIT(RCC_CFGR, 16);
	#elif	RCC_PLL_INPUT == RCC_PLL_HSE_DIV_2
		SET_BIT(RCC_CR, 16);
		SET_BIT(RCC_CFGR, 16);
		SET_BIT(RCC_CFGR, 17);
	#else
		#error("Wrong PLL Input Source");
	#endif
	
	#if RCC_PLL_MUL <= 16
		RCC_CFGR |= ((RCC_PLL_MUL - 2) << 18);
	#else
		#error("Wrong PLL multiplier");
	#endif

	SET_BIT(RCC_CFGR, 1);
	SET_BIT(RCC_CR, 24);
#else
	#error("Wrong Clock Type")
#endif

}

void RCC_voidEnableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId){

	if(Copy_u8PerId <= 31){
		switch(Copy_u8BusId){
			case RCC_AHB:
				SET_BIT(RCC_AHBENR, Copy_u8PerId);
				break;
			case RCC_APB1:
				SET_BIT(RCC_APB1ENR, Copy_u8PerId);
				break;
			case RCC_APB2:
				SET_BIT(RCC_APB2ENR, Copy_u8PerId);
				break;
			default:
				/*Return error*/
				break;
		}
	}
	else{
		/*Invalid PerId*/
		/*Return error*/
	}

}

void RCC_voidDisableClock(uint8_t Copy_u8BusId, uint8_t Copy_u8PerId){

	if(Copy_u8PerId <= 31){

		switch(Copy_u8BusId){
			case RCC_AHB:
				CLR_BIT(RCC_AHBENR, Copy_u8PerId);
				break;
			case RCC_APB1:
				CLR_BIT(RCC_APB1ENR, Copy_u8PerId);
				break;
			case RCC_APB2:
				CLR_BIT(RCC_APB2ENR, Copy_u8PerId);
				break;
			default:
				/*return error*/
				break;
		}
	}
	else{
		/*Invalid Periph.*/
		/*return error*/
	}
}

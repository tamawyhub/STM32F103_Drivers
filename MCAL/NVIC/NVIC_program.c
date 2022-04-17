/*
 * Author: Mohammed Hisham
 * Date: 19 Feb 2022
 * Version: 1.0
 */

#include "BIT_MATH.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
#include "NVIC_interface.h"


void NVIC_voidEnableIRQ(uint8_t Copy_u8IRQ){

	if(Copy_u8IRQ <= 31){
		NVIC_ISER0 = 1 << Copy_u8IRQ;
	}
	else if(Copy_u8IRQ <= LAST_IRQ){
		NVIC_ISER1 = 1 << (Copy_u8IRQ - 32);
	}
	else{
		/* return error*/
	}
}

void NVIC_voidDisableIRQ(uint8_t Copy_u8IRQ){

	if(Copy_u8IRQ <= 31){
		NVIC_ICER0 = 1 << Copy_u8IRQ;
	}
	else if(Copy_u8IRQ <= LAST_IRQ){
		NVIC_ICER1 = 1 << (Copy_u8IRQ - 32);
	}
	else{
		/* return error */
	}
}

void NVIC_voidSetPending(uint8_t Copy_u8IRQ){

        if(Copy_u8IRQ <= 31){
                NVIC_ISPR0 = 1 << Copy_u8IRQ;
        }
        else if(Copy_u8IRQ <= LAST_IRQ){
                NVIC_ISPR1 = 1 << (Copy_u8IRQ - 32);
        }
        else{
                /* return error */
        }
}

void NVIC_voidClearPending(uint8_t Copy_u8IRQ){

        if(Copy_u8IRQ <= 31){
                NVIC_ICPR0 = 1 << Copy_u8IRQ;
        }
        else if(Copy_u8IRQ <= LAST_IRQ){
                NVIC_ICPR1 = 1 << (Copy_u8IRQ - 32);
        }
        else{
                /* return error */
        }
}

uint8_t NVIC_u8GetActiveFlag(uint8_t Copy_u8IRQ){

	if(Copy_u8IRQ <= 31){
		return GET_BIT(NVIC_IABR0, Copy_u8IRQ);
	}
	else if(Copy_u8IRQ <= LAST_IRQ){
		return GET_BIT(NVIC_IABR1, Copy_u8IRQ - 32);
	}
	else{
		return 255;
	}
}

void NVIC_voidSetIRQPriority(uint8_t Copy_u8IRQ, uint8_t Copy_u8Pri){
	
	if(Copy_u8IRQ <= LAST_IRQ){
		uint8_t Local_u8SubPriBits = ((SCB_AIRCR & 0x00000700) >> 8);
		if(Local_u8SubPriBits > 3){
			Local_u8SubPriBits =- 3;
		}
		volatile uint8_t* nvic_ipr = (volatile uint8_t*) &NVIC_IPR0;
		uint16_t Local_u16Priority = Copy_u8Pri << (Local_u8SubPriBits + 4);
		if(Local_u16Priority <= 0xFF){
			*(nvic_ipr + Copy_u8IRQ) = Local_u16Priority;
		}
		else{
			/* return error */
		}
	}
	else{
		/* return error */
	}
}

void NVIC_voidSetExceptionPriority(uint8_t Copy_u8Exception, uint8_t Copy_u8Pri){

	if(Copy_u8Exception <= LAST_EXCEPTION){
		uint8_t Local_u8SubPriBits = ((SCB_AIRCR & 0x00000700) >> 8);
                if(Local_u8SubPriBits > 3){
                        Local_u8SubPriBits =- 3;
                }
		
		volatile uint8_t* scb_shprx;
		if(Copy_u8Exception <= USAGE_FAULT_EXCEPTION){
			scb_shprx = (volatile uint8_t*) &SCB_SHPR1;
			*(scb_shprx + Copy_u8Exception) = Copy_u8Pri << (Local_u8SubPriBits + 4);
		}
		else if(Copy_u8Exception == SVCALL_EXCEPTION){
			scb_shprx = (volatile uint8_t*) &SCB_SHPR2;
			*(scb_shprx + 3) = Copy_u8Pri << (Local_u8SubPriBits + 4);
		}
		else if(Copy_u8Exception == PENDSV_EXCEPTION){
			scb_shprx = (volatile uint8_t*) &SCB_SHPR3;
			*(scb_shprx + 2) = Copy_u8Pri << (Local_u8SubPriBits + 4);
		}
		else if(Copy_u8Exception == SYSTICK_EXCEPTION){
			scb_shprx = (volatile uint8_t*) &SCB_SHPR3;
			*(scb_shprx + 3) = Copy_u8Pri << (Local_u8SubPriBits + 4);
		}
	}
	else{
		//return error
	}
}	

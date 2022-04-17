/*
 * Author: 
 *
 *
 */

#include "BIT_MATH.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"


void EXTI_voidEnableLine(uint8_t Copy_u8Line){

	if(Copy_u8Line <= MAX_LINE){
		SET_BIT(EXTI_IMR, Copy_u8Line);
	}
	else{
		/* return error */
	}
}

void EXTI_voidDisableLine(uint8_t Copy_u8Line){

	if(Copy_u8Line <= MAX_LINE){
		CLR_BIT(EXTI_IMR, Copy_u8Line);
	}
	else{
		/* return error */
	}

}

void EXTI_voidSetTriggerMode(uint8_t Copy_u8Line, uint8_t Copy_u8Mode){

	if(Copy_u8Line <= MAX_LINE){
                switch(Copy_u8Mode){
			case EXTI_MODE_RISING:
				SET_BIT(EXTI_RTSR, Copy_u8Line);
				break;
			case EXTI_MODE_FALLING:
				SET_BIT(EXTI_FTSR, Copy_u8Line);
				break;
			case EXTI_MODE_ON_CHANGE:
				SET_BIT(EXTI_RTSR, Copy_u8Line);
				SET_BIT(EXTI_FTSR, Copy_u8Line);
				break;
			default:
				/*return error*/
				break;
		}
        }
        else{
                /* return error */
        }

}

void EXTI_voidClearPending(uint8_t Copy_u8Line){

	if(Copy_u8Line <= MAX_LINE){
                SET_BIT(EXTI_PR, Copy_u8Line);
        }
        else{
                /* return error */
        }

}



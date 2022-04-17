/*
 * Author: Mohammed Hisham
 * Date: 18 Feb 2022
 * Version: 1.0
 */

#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_interface.h"

void GPIO_voidSetPinMode(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8Mode){
	
	switch(Copy_u8Port){
		case GPIOA:
			if(Copy_u8Pin <= 7){
				GPIOA_CRL = (GPIOA_CRL & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else if(Copy_u8Pin <= 15){
				Copy_u8Pin -= 8;
				GPIOA_CRH = (GPIOA_CRH & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else{
				/* return error*/
			}

			break;
		case GPIOB:
			if(Copy_u8Pin <= 7){
				GPIOB_CRL = (GPIOB_CRL & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else if(Copy_u8Pin <= 15){
				Copy_u8Pin -= 8;
				GPIOB_CRH = (GPIOB_CRH & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else{
				/*return error*/
			}
			break;
		case GPIOC:
			if(Copy_u8Pin <= 7){
				GPIOC_CRL = (GPIOC_CRL & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else if(Copy_u8Pin <= 15){
				Copy_u8Pin -= 8;
				GPIOC_CRH = (GPIOC_CRH & ~(0XF << (Copy_u8Pin * 4))) | (Copy_u8Mode << (Copy_u8Pin * 4));
			}
			else{
				/*return error*/
			}
			break;
		default:
			/*return error*/
			break;
	}
}

void GPIO_voidSetPinVal(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8PinVal){
	
	switch(Copy_u8Port){
		case GPIOA:
			GPIOA_ODR = (GPIOA_ODR & ~(0X1 << Copy_u8Pin)) | (Copy_u8PinVal << Copy_u8Pin);
			break;
		case GPIOB:
			GPIOB_ODR = (GPIOB_ODR & ~(0X1 << Copy_u8Pin)) | (Copy_u8PinVal << Copy_u8Pin);
			break;
		case GPIOC:
			GPIOC_ODR = (GPIOC_ODR & ~(0X1 << Copy_u8Pin)) | (Copy_u8PinVal << Copy_u8Pin);
			break;
		default:
			/*return error*/
			break;
	}
}

void GPIO_voidSetPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
			SET_BIT(GPIOA_ODR, Copy_u8Pin);
			break;
		case GPIOB:
			SET_BIT(GPIOB_ODR, Copy_u8Pin);
			break;
		case GPIOC:
			SET_BIT(GPIOC_ODR, Copy_u8Pin);
			break;
		default:
			/* return err */
			break;
	}
}

void GPIO_voidClearPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
			CLR_BIT(GPIOA_ODR, Copy_u8Pin);
			break;
		case GPIOB:
			CLR_BIT(GPIOB_ODR, Copy_u8Pin);
			break;
		case GPIOC:
			CLR_BIT(GPIOC_ODR, Copy_u8Pin);
			break;
		default:
			/* return error */
			break;
	}
}

void GPIO_voidTogglePin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
			TOGGLE_BIT(GPIOA_ODR, Copy_u8Pin);
			break;
		case GPIOB:
			TOGGLE_BIT(GPIOB_ODR, Copy_u8Pin);
			break;
		case GPIOC:
			TOGGLE_BIT(GPIOC_ODR, Copy_u8Pin);
			break;
		default:
			/* return err */
			break;
	}
}

void GPIO_voidSetPinAtomic(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
			GPIOA_BSRR = (1 << Copy_u8Pin);
			break;
		case GPIOB:
			GPIOB_BSRR = (1 << Copy_u8Pin);
			break;
		case GPIOC:
			GPIOC_BSRR = (1 << Copy_u8Pin);
			break;
		default:
			/* return error */
			break;
	}
}

void GPIO_voidClearPinAtomic(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
                        GPIOA_BRR = (1 << Copy_u8Pin);
                        break;
                case GPIOB:
                        GPIOB_BRR = (1 << Copy_u8Pin);
                        break;
                case GPIOC:
                        GPIOC_BRR = (1 << Copy_u8Pin);
                        break;
                default:
                        /* return error */
                        break;
        }
}

uint8_t GPIO_u8ReadPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin){

	switch(Copy_u8Port){
		case GPIOA:
			return GET_BIT(GPIOA_IDR, Copy_u8Pin);
		case GPIOB:
			return GET_BIT(GPIOB_IDR, Copy_u8Pin);
		case GPIOC:
			return GET_BIT(GPIOC_IDR, Copy_u8Pin);
		default:
			return -1;
	}
}


/* AFIO FUNCTIONS */

void AFIO_voidSetEXTIPin(uint8_t Copy_u8EXTI, uint8_t Copy_u8Pin){

	volatile uint32_t* AFIO_EXTICRx = &AFIO_EXTICR1;
	uint8_t Local_u8Index = Copy_u8EXTI >> 2;
	AFIO_EXTICRx[Local_u8Index] &= ~(0xF << ((Copy_u8EXTI % 4) * 4));	//Need Optimization here
	AFIO_EXTICRx[Local_u8Index] |= Copy_u8Pin << ((Copy_u8EXTI % 4) * 4);	//Need Optimization here

}

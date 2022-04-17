/*
 * Author: Mohammed Hisham
 * Date: 23 March 2022
 * Version: 1.0
 */


#include <stdint.h>
#include "BIT_MATH.h"
#include "TIMx_interface.h"
#include "TIMx_private.h"


volatile TIMx_t* Global_pTimers[] = {_TIM2, _TIM3, _TIM4, _TIM5};

typedef void (*TIMx_isr_t) (void);
TIMx_isr_t TIMx_callbacks[4];


void TIMx_voidInitTimer(uint8_t Copy_u8Timer, uint8_t Copy_u8Mode){
	
	volatile TIMx_t *timer = Global_pTimers[Copy_u8Timer];
	switch(Copy_u8Mode){
		case TIMx_UPCOUNT_MODE:
			CLR_BIT(timer->CR1, 5);
			CLR_BIT(timer->CR1, 6);
			CLR_BIT(timer->CR1, 4);
			break;
		case TIMx_DOWNCOUNT_MODE:
			CLR_BIT(timer->CR1, 5);
			CLR_BIT(timer->CR1, 6);
			SET_BIT(timer->CR1, 4);
			break;
		case TIMx_CENTERALIGNED_01:
			SET_BIT(timer->CR1, 5);
			CLR_BIT(timer->CR1, 6);
			break;
		case TIMx_CENTERALIGNED_02:
			CLR_BIT(timer->CR1, 5);
			SET_BIT(timer->CR1, 6);
			break;
		case TIMx_CENTERALIGNED_03:
			SET_BIT(timer->CR1, 5);
			SET_BIT(timer->CR1, 6);
			break;
		default:
			break;
	}
}

void TIMx_voidSetExternalMode1(uint8_t Copy_u8Timer, uint8_t Copy_u8Src, uint8_t Copy_u8Edge){

	switch(Copy_u8Src){
		case EXTERNAL_MODE1_TI1FP1:
			SET_BIT(Global_pTimers[Copy_u8Timer]->CCMR1, 0);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCMR1, 1);
			SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 4);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 5);
			SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 6);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 1);
			Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Edge << 1);
			break;
		case EXTERNAL_MODE1_TI2FP2:
			SET_BIT(Global_pTimers[Copy_u8Timer]->CCMR1, 8);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCMR1, 9);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 4);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 5);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 6);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 5);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Edge << 5);
			break;
		case EXTERNAL_MODE1_TI1FED:
			/* lEFT */
			CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 4);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 5);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 6);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 1);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Edge << 1);
			break;
		default:
			/*return error*/
			break;
	}
	
	Global_pTimers[Copy_u8Timer]->SMCR |= (0x07);

}

void TIMx_voidSetExternalMode2(uint8_t Copy_u8Timer, uint8_t Copy_u8Psc, uint8_t Copy_u8Edge){
	
	CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 15);
	Global_pTimers[Copy_u8Timer]->SMCR |= (Copy_u8Edge << 15);

	CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 12);
	CLR_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 13);
	Global_pTimers[Copy_u8Timer]->SMCR |= (Copy_u8Psc << 12);

	SET_BIT(Global_pTimers[Copy_u8Timer]->SMCR, 14);
}

void TIMx_voidEnableCapture(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8Psc, uint8_t Copy_u8Edge){

	TIMx_t* Local_pTimer = Global_pTimers[Copy_u8Timer];

	switch(Copy_u8Channel){
		case TIMx_CHANNEL_1:
			//Enable Input Channel
			SET_BIT(Local_pTimer->CCMR1, 0);
			CLR_BIT(Local_pTimer->CCMR1, 1);
			//Set Prescaler
			CLR_BIT(Local_pTimer->CCMR1, 2);
			CLR_BIT(Local_pTimer->CCMR1, 3);
			Local_pTimer->CCMR1 |= (Copy_u8Psc << 2);
			//Select Edge
			CLR_BIT(Local_pTimer->CCER, 1);
			Local_pTimer->CCER |= (Copy_u8Edge << 1);
			//Enable Capture
			SET_BIT(Local_pTimer->CCER, 0);
			break;
		case TIMx_CHANNEL_2:
			//Enable Input Channel
                        SET_BIT(Local_pTimer->CCMR1, 8);
                        CLR_BIT(Local_pTimer->CCMR1, 9);
                        //Set Prescaler
                        CLR_BIT(Local_pTimer->CCMR1, 10);
                        CLR_BIT(Local_pTimer->CCMR1, 11);
                        Local_pTimer->CCMR1 |= (Copy_u8Psc << 10);
                        //Select Edge
                        CLR_BIT(Local_pTimer->CCER, 5);
                        Local_pTimer->CCER |= (Copy_u8Edge << 5);
                        //Enable Capture
                        SET_BIT(Local_pTimer->CCER, 4);
                        break;
		case TIMx_CHANNEL_3:
			//Enable Input Channel
                        SET_BIT(Local_pTimer->CCMR2, 0);
                        CLR_BIT(Local_pTimer->CCMR2, 1);
                        //Set Prescaler
                        CLR_BIT(Local_pTimer->CCMR2, 2);
                        CLR_BIT(Local_pTimer->CCMR2, 3);
                        Local_pTimer->CCMR2 |= (Copy_u8Psc << 2);
                        //Select Edge
                        CLR_BIT(Local_pTimer->CCER, 9);
                        Local_pTimer->CCER |= (Copy_u8Edge << 9);
                        //Enable Capture
                        SET_BIT(Local_pTimer->CCER, 8);
                        break;
		case TIMx_CHANNEL_4:
			//Enable Input Channel
                        SET_BIT(Local_pTimer->CCMR2, 8);
                        CLR_BIT(Local_pTimer->CCMR2, 9);
                        //Set Prescaler
                        CLR_BIT(Local_pTimer->CCMR2, 10);
                        CLR_BIT(Local_pTimer->CCMR2, 11);
                        Local_pTimer->CCMR2 |= (Copy_u8Psc << 10);
                        //Select Edge
                        CLR_BIT(Local_pTimer->CCER, 13);
                        Local_pTimer->CCER |= (Copy_u8Edge << 13);
                        //Enable Capture
                        SET_BIT(Local_pTimer->CCER, 12);
                        break;
		default:
			/*return error*/
			break;
	}


}

void TIMx_voidEnableCompare(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8OCMode, uint8_t Copy_u8Polarity){

	switch(Copy_u8Channel){
		case TIMx_CHANNEL_1:
			Global_pTimers[Copy_u8Timer]->CCMR1 &= ~ (0x7F);
			Global_pTimers[Copy_u8Timer]->CCMR1 |= (Copy_u8OCMode << 4);
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 1);
			Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 1);
			SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 0);
			break;
		case TIMx_CHANNEL_2:
			Global_pTimers[Copy_u8Timer]->CCMR1 &= ~ (0x7F << 8);
                        Global_pTimers[Copy_u8Timer]->CCMR1 |= (Copy_u8OCMode << 12);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 5);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 5);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 4);
                        break;
		case TIMx_CHANNEL_3:
			Global_pTimers[Copy_u8Timer]->CCMR2 &= ~ (0x7F);
                        Global_pTimers[Copy_u8Timer]->CCMR2 |= (Copy_u8OCMode << 4);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 9);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 9);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 8);
                        break;
		case TIMx_CHANNEL_4:
			Global_pTimers[Copy_u8Timer]->CCMR2 &= ~ (0x7F << 8);
                        Global_pTimers[Copy_u8Timer]->CCMR2 |= (Copy_u8OCMode << 12);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 13);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 13);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 12);
                        break;
		default:
			/* returne error */
			break;
	}
}

void TIMx_voidEnablePWM(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint8_t Copy_u8Polarity){

	switch(Copy_u8Channel){
		case TIMx_CHANNEL_1:
			Global_pTimers[Copy_u8Timer]->CCMR1 &= ~ (0x3F);
			Global_pTimers[Copy_u8Timer]->CCMR1 |= 0x68;
			CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 1);
			Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 1);
			SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 0);
			break;
		case TIMx_CHANNEL_2:
			Global_pTimers[Copy_u8Timer]->CCMR1 &= ~ (0x3F << 8);
                        Global_pTimers[Copy_u8Timer]->CCMR1 |= (0x68 << 8);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 5);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 5);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 4);
                        break;
		case TIMx_CHANNEL_3:
			Global_pTimers[Copy_u8Timer]->CCMR2 &= ~ (0x3F);
                        Global_pTimers[Copy_u8Timer]->CCMR2 |= 0x68;
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 9);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 9);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 8);
                        break;
		case TIMx_CHANNEL_4:
			Global_pTimers[Copy_u8Timer]->CCMR2 &= ~ (0x3F << 8);
                        Global_pTimers[Copy_u8Timer]->CCMR2 |= (0x68<< 8);
                        CLR_BIT(Global_pTimers[Copy_u8Timer]->CCER, 13);
                        Global_pTimers[Copy_u8Timer]->CCER |= (Copy_u8Polarity << 13);
                        SET_BIT(Global_pTimers[Copy_u8Timer]->CCER, 12);
                        break;
		default:
			/* return error */
			break;
	}

	SET_BIT(Global_pTimers[Copy_u8Timer]->CR1, 7);
}

void TIMx_voidSetCompareValue(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, uint16_t Copy_u16Val){
	
	*(&(Global_pTimers[Copy_u8Timer]->CCR1) + (Copy_u8Channel - 1)) = Copy_u16Val;
	SET_BIT(Global_pTimers[Copy_u8Timer]->EGR, 0);
}

uint16_t TIMx_u16GetCaptureValue(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel){

	return *(&(Global_pTimers[Copy_u8Timer]->CCR1) + (Copy_u8Channel - 1));
}

void TIMx_voidWaitCCFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel){

	while(!GET_BIT(Global_pTimers[Copy_u8Timer]->SR, Copy_u8Channel));
}

void TIMx_voidClearCCFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel){

	CLR_BIT(Global_pTimers[Copy_u8Timer]->SR, Copy_u8Channel);
}

uint8_t TIMx_u8GetOVFlag(uint8_t Copy_u8Timer,uint8_t Copy_u8Channel){

	return GET_BIT(Global_pTimers[Copy_u8Timer]->SR, Copy_u8Channel + 8);
}

void TIMx_voidClearOVFlag(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel){

        CLR_BIT(Global_pTimers[Copy_u8Timer]->SR, Copy_u8Channel + 8);
}

void TIMx_voidEnableCCInterrupt(uint8_t Copy_u8Timer, uint8_t Copy_u8Channel, void (*callback)(void)){

	SET_BIT(Global_pTimers[Copy_u8Timer]->DIER, Copy_u8Channel);
	TIMx_callbacks[Copy_u8Timer] = callback;
}

void TIMx_voidSetPrescaler(uint8_t Copy_u8Timer, uint16_t Copy_u16Prescaler){
	
	Global_pTimers[Copy_u8Timer]->PSC = Copy_u16Prescaler;
	SET_BIT(Global_pTimers[Copy_u8Timer]->EGR, 0);

}

void TIMx_voidSetPreload(uint8_t Copy_u8Timer, uint16_t Copy_u16Preload){

	Global_pTimers[Copy_u8Timer]->ARR = Copy_u16Preload;

}

void TIMx_voidSetCounter(uint8_t Copy_u8Timer, uint16_t Copy_u8Val){

	Global_pTimers[Copy_u8Timer]->CNT = Copy_u8Val;
}

void TIMx_voidEnableTimer(uint8_t Copy_u8Timer){

	SET_BIT(Global_pTimers[Copy_u8Timer]->CR1, 0);
	
}

void TIMx_voidDisableTimer(uint8_t Copy_u8Timer){

	CLR_BIT(Global_pTimers[Copy_u8Timer]->CR1, 0);

}

void TIMx_voidWaitUpdateFlag(uint8_t Copy_u8Timer){

	while(!GET_BIT(Global_pTimers[Copy_u8Timer]->SR, 0));
	CLR_BIT(Global_pTimers[Copy_u8Timer]->SR, 0);

}

void TIMx_voidEnableUpdateInterrupt(uint8_t Copy_u8Timer, void (*Copy_pISR) (void)){

	SET_BIT(Global_pTimers[Copy_u8Timer]->DIER, 0);
	TIMx_callbacks[Copy_u8Timer] = Copy_pISR;

}

void TIMx_voidDisableUpdateInterrupt(uint8_t Copy_u8Timer){

	CLR_BIT(Global_pTimers[Copy_u8Timer]->DIER, 0);

}

void tim2_isr(void){
	
	TIMx_callbacks[TIM2]();
	CLR_BIT(Global_pTimers[TIM2]->SR, 0);
}

void tim3_isr(void){
	TIMx_callbacks[TIM3]();
	CLR_BIT(Global_pTimers[TIM3]->SR, 0);
}

void tim4_isr(void){
        TIMx_callbacks[TIM4]();
        CLR_BIT(Global_pTimers[TIM4]->SR, 0);
}

void tim5_isr(void){
        TIMx_callbacks[TIM5]();
        CLR_BIT(Global_pTimers[TIM5]->SR, 0);
}
	

/*
 * Author: Mohammed Hisham
 * Date: 7 March 2020
 * Version: 1.0
 */


#include "SEVEN_SEGMENT_interface.h"
#include "SEVEN_SEGMENT_config.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/SYSTICK/SYSTICK_interface.h"
#include "../../MCAL/TIMx/TIMx_interface.h"
#include "../../MCAL/NVIC/NVIC_interface.h"


uint8_t ss_digits[SS_NUM_OF_DIGITS];
uint8_t Global_u8CurrentDigit;
const ss_multi_digit_t* Global_ptrDisp;

void SEVEN_SEGMENT_voidConfigurePinsCC(const seven_segment_t* display){

	GPIO_voidSetPinMode(display->segment_a.port, display->segment_a.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_b.port, display->segment_b.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_c.port, display->segment_c.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_d.port, display->segment_d.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_e.port, display->segment_e.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_f.port, display->segment_f.pin, OUTPUT_2MHZ_PUSH_PULL);
	GPIO_voidSetPinMode(display->segment_g.port, display->segment_g.pin, OUTPUT_2MHZ_PUSH_PULL);
}

void SEVEN_SEGMENT_voidConfigurePinsCA(const seven_segment_t* display){
	
	GPIO_voidSetPinMode(display->segment_a.port, display->segment_a.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_b.port, display->segment_b.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_c.port, display->segment_c.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_d.port, display->segment_d.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_e.port, display->segment_e.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_f.port, display->segment_f.pin, OUTPUT_2MHZ_OPEN_DRAIN);
	GPIO_voidSetPinMode(display->segment_g.port, display->segment_g.pin, OUTPUT_2MHZ_OPEN_DRAIN);
}

void SEVEN_SEGMENT_voidDisplayDigitCC(const seven_segment_t* display, uint8_t Copy_u8Digit){

	switch(Copy_u8Digit){
		case 0:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
			GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
			GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
			GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
			GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
			GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
			break;
		case 1:
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
			break;
		case 2:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 3:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 4:
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
			GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 5:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
			GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 6:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 7:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
			break;
		case 8:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
		case 9:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
			break;
	}

}

void SEVEN_SEGMENT_voidDisplayDigitCA(const seven_segment_t* display, uint8_t Copy_u8Digit){

        switch(Copy_u8Digit){
                case 0:
                        GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidClearPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 1:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 2:
			GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidSetPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidClearPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 3:
			GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
		case 4:
			GPIO_voidSetPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 5:
			GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 6:
                        GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
			GPIO_voidSetPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidClearPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 7:
			GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidSetPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidSetPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidSetPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 8:
                        GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidClearPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
                case 9:
			GPIO_voidClearPin(display->segment_a.port, display->segment_a.pin);
                        GPIO_voidClearPin(display->segment_b.port, display->segment_b.pin);
                        GPIO_voidClearPin(display->segment_c.port, display->segment_c.pin);
                        GPIO_voidClearPin(display->segment_d.port, display->segment_d.pin);
                        GPIO_voidSetPin(display->segment_e.port, display->segment_e.pin);
                        GPIO_voidClearPin(display->segment_f.port, display->segment_f.pin);
                        GPIO_voidClearPin(display->segment_g.port, display->segment_g.pin);
                        break;
	}
}

void SEVEN_SEGMENT_voidMultiplexDigits(void){

	seven_segment_t* Local_ptrSegments = Global_ptrDisp->segments;
	pin_t* Local_ptrCommonPins = Global_ptrDisp->common_pins;
	uint8_t Local_u8CurrentDigit;
	if(Local_ptrSegments->type == SEVEN_SEGMENT_CA){
		for(Local_u8CurrentDigit = 0; Local_u8CurrentDigit < SS_NUM_OF_DIGITS; Local_u8CurrentDigit++){
			if(Local_u8CurrentDigit == Global_u8CurrentDigit){
				GPIO_voidClearPin(Local_ptrCommonPins[Local_u8CurrentDigit].port, Local_ptrCommonPins[Local_u8CurrentDigit].pin);
			}
			else{
				GPIO_voidSetPin(Local_ptrCommonPins[Local_u8CurrentDigit].port, Local_ptrCommonPins[Local_u8CurrentDigit].pin);
			}
		}
	}
	else if(Local_ptrSegments->type == SEVEN_SEGMENT_CC){
		for(Local_u8CurrentDigit = 0; Local_u8CurrentDigit < SS_NUM_OF_DIGITS; Local_u8CurrentDigit++){
			if(Local_u8CurrentDigit == Global_u8CurrentDigit){
				GPIO_voidSetPin(Local_ptrCommonPins[Local_u8CurrentDigit].port, Local_ptrCommonPins[Local_u8CurrentDigit].pin);
			}
			else{
				GPIO_voidClearPin(Local_ptrCommonPins[Local_u8CurrentDigit].port, Local_ptrCommonPins[Local_u8CurrentDigit].pin);
			}
		}
	}
	else{
		/* return error */
	}
	SEVEN_SEGMENT_voidDisplayDigit(Local_ptrSegments, ss_digits[Global_u8CurrentDigit]);
	
	Global_u8CurrentDigit = (Global_u8CurrentDigit == SS_NUM_OF_DIGITS)? 0: (Global_u8CurrentDigit + 1);

}

void SEVEN_SEGMENT_voidConfigurePins(const seven_segment_t* Copy_ptrDisp){

	if(Copy_ptrDisp->type == SEVEN_SEGMENT_CC){
		SEVEN_SEGMENT_voidConfigurePinsCC(Copy_ptrDisp);
	}
	else if(Copy_ptrDisp->type == SEVEN_SEGMENT_CA){
		SEVEN_SEGMENT_voidConfigurePinsCA(Copy_ptrDisp);
	}
	else{
		/* return error */
	}
}

void SEVEN_SEGMENT_voidDisplayDigit(const seven_segment_t* Copy_ptrDisp, uint8_t Copy_u8Digit){

	if(Copy_ptrDisp->type == SEVEN_SEGMENT_CC){
		SEVEN_SEGMENT_voidDisplayDigitCC(Copy_ptrDisp, Copy_u8Digit);
	}
	else if(Copy_ptrDisp->type == SEVEN_SEGMENT_CA){
		SEVEN_SEGMENT_voidDisplayDigitCA(Copy_ptrDisp, Copy_u8Digit);
	}
	else{
		//return error
	}
}

void SEVEN_SEGMENT_voidInitMultiDigit(const ss_multi_digit_t* Copy_ptrDisp){

	Global_ptrDisp = Copy_ptrDisp;
	uint8_t Local_u8CurrentPin;
	for(Local_u8CurrentPin = 0; Local_u8CurrentPin < SS_NUM_OF_DIGITS; Local_u8CurrentPin++){
		GPIO_voidSetPinMode(Copy_ptrDisp->common_pins[Local_u8CurrentPin].port, 
				Copy_ptrDisp->common_pins[Local_u8CurrentPin].pin, OUTPUT_2MHZ_OPEN_DRAIN);
	}

#if SEVEN_SEGMENT_CLK_SOURCE == SEVEN_SEGMENT_SYSTICK
	SYSTICK_voidSelectClock(SYSTICK_AHB_DIV_8);
	NVIC_voidSetExceptionPriority(SYSTICK_EXCEPTION, 15);
	SYSTICK_voidSetIntervalPeriodic(5000, SEVEN_SEGMENT_voidMultiplexDigits);
#elif SEVEN_SEGMENT_CLK_SOURCE == SEVEN_SEGMENT_TIM2
	RCC_voidEnableClock(RCC_APB1, 0);
        NVIC_voidEnableIRQ(TIM2_IRQ);
	TIMx_voidInitTimer(TIM2, TIMER_UPCOUNT_MODE);
	TIMx_voidSetPrescaler(TIM2, 7);
	TIMx_voidSetPreload(TIM2, 5000);
	TIMx_voidEnableUpdateInterrupt(TIM2, SEVEN_SEGMENT_voidMultiplexDigits);
	TIMx_voidEnableTimer(TIM2);
#elif SEVEN_SEGMENT_CLK_SOURCE == SEVEN_SEGMENT_TIM3
	RCC_voidEnableClock(RCC_APB1, 1);
        NVIC_voidEnableIRQ(TIM3_IRQ);
	TIMx_voidInitTimer(TIM3, TIMER_UPCOUNT_MODE);
        TIMx_voidSetPrescaler(TIM3, 7);
        TIMx_voidSetPreload(TIM3, 5000);
        TIMx_voidEnableUpdateInterrupt(TIM3, SEVEN_SEGMENT_voidMultiplexDigits);
        TIMx_voidEnableTimer(TIM3);
#elif SEVEN_SEGMENT_CLK_SOURCE == SEVEN_SEGMENT_TIM4
	RCC_voidEnableClock(RCC_APB1, 2);
        NVIC_voidEnableIRQ(TIM4_IRQ);
	TIMx_voidInitTimer(TIM4, TIMER_UPCOUNT_MODE);
        TIMx_voidSetPrescaler(TIM4, 7);
        TIMx_voidSetPreload(TIM4, 5000);
        TIMx_voidEnableUpdateInterrupt(TIM4, SEVEN_SEGMENT_voidMultiplexDigits);
        TIMx_voidEnableTimer(TIM4);
#elif SEVEN_SEGMENT_CLK_SOURCE == SEVEN_SEGMENT_TIM5
	RCC_voidEnableClock(RCC_APB1, 3);
	NVIC_voidEnableIRQ(TIM5_IRQ);
	TIMx_voidInitTimer(TIM5, TIMER_UPCOUNT_MODE);
        TIMx_voidSetPrescaler(TIM5, 7);
        TIMx_voidSetPreload(TIM5, 5000);
        TIMx_voidEnableUpdateInterrupt(TIM5, SEVEN_SEGMENT_voidMultiplexDigits);
        TIMx_voidEnableTimer(TIM5);
#endif
}

void SEVEN_SEGMENT_voidDisplayMultiDigit(uint32_t Copy_u32Val){

	const uint8_t Local_u8Divisor = 10;
	for(uint8_t Local_u8DigitIndx = 0; Local_u8DigitIndx < SS_NUM_OF_DIGITS; Local_u8DigitIndx++){
		ss_digits[Local_u8DigitIndx] = Copy_u32Val % Local_u8Divisor;
		Copy_u32Val /= Local_u8Divisor;
	}

}


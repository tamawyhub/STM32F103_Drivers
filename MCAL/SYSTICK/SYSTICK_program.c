/*
 * Author: Mohammed Hisham
 * Date: 6 March 2020
 * Version: 1.0
 */

#include "SYSTICK_private.h"
#include "SYSTICK_interface.h"
#include "BIT_MATH.h"

void (*callback_func) (void);
uint8_t Global_u8IsSingle;


void SYSTICK_voidEnableTimer(void){
	SET_BIT(STK_CTRL, 0);
}

void SYSTICK_voidDisableTimer(void){
	CLR_BIT(STK_CTRL, 0);
}


void SYSTICK_voidEnableException(void){

	SET_BIT(STK_CTRL, 1);
}

void SYSTICK_voidDisableException(void){

	CLR_BIT(STK_CTRL, 1);
}

void SYSTICK_voidSelectClock(uint8_t Copy_u8Source){

	switch(Copy_u8Source){
		case SYSTICK_AHB_DIV_8:
			CLR_BIT(STK_CTRL, 2);
			break;
		case SYSTICK_AHB_DIV_1:
			SET_BIT(STK_CTRL, 2);
			break;
		default:
			/* return error */
			break;
	}
}

uint8_t SYSTICK_u8ReadFlag(void){

	return GET_BIT(STK_CTRL, 16);
}

void SYSTICK_voidLoadTimer(uint32_t Copy_u32Value){

	STK_LOAD = Copy_u32Value;
}

uint32_t SYSTICK_u32GetCount(void){

	return STK_VAL;
}

void SYSTICK_voidSetBusyWait(uint32_t Copy_u32Ticks){

	STK_LOAD = Copy_u32Ticks;
	SET_BIT(STK_CTRL, 0);
	while(!GET_BIT(STK_CTRL, 16));
	CLR_BIT(STK_CTRL, 0);
	STK_LOAD = 0;
	STK_VAL = 0;
}

void SYSTICK_voidSetIntervalPeriodic(uint32_t Copy_u32Ticks, void (*callback_ptr) (void)){
	
	STK_LOAD = Copy_u32Ticks - 1;
	SET_BIT(STK_CTRL, 1);
	callback_func = callback_ptr;
	SET_BIT(STK_CTRL, 0);
	Global_u8IsSingle = 0;
}

void systick_isr(void){
	uint8_t Local_u8Temp;
	callback_func();
	Local_u8Temp = GET_BIT(STK_CTRL, 16); //Clear flag
}

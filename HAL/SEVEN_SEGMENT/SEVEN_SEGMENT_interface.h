/*
 * Author: Mohammed Hisham
 * Date: 7 March 2020
 * Version: 1.0
 */

#ifndef SEVEN_SEGMENT_INTERFACE_H
#define SEVEN_SEGMENT_INTERFACE_H

#include <stdint.h>

#define SEVEN_SEGMENT_CC	0
#define SEVEN_SEGMENT_CA	1


#include "SEVEN_SEGMENT_config.h"

typedef struct {
	uint8_t port;
	uint8_t pin;
}pin_t;

typedef struct{
	/* 7 SEGMENT PINS */
	pin_t segment_a;
	pin_t segment_b;
	pin_t segment_c;
	pin_t segment_d;
	pin_t segment_e;
	pin_t segment_f;
	pin_t segment_g;

	uint8_t type;
}seven_segment_t;

typedef struct{
	seven_segment_t* segments;
	pin_t* common_pins;
}ss_multi_digit_t;

void SEVEN_SEGMENT_voidConfigurePins(const seven_segment_t* display);
void SEVEN_SEGMENT_voidDisplayDigit(const seven_segment_t* display, uint8_t Copy_u8Digit);
void SEVEN_SEGMENT_voidDisplayChar(const seven_segment_t* display, uint8_t ch);
void SEVEN_SEGMENT_voidInitMultiDigit(const ss_multi_digit_t* disp);
void SEVEN_SEGMENT_voidDisplayMultiDigit(uint32_t Copy_u32Val);

#endif

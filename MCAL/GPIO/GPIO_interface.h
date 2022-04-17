/*
 * Author: Mohammed Hisham
 * Date: 18 Feb 2022
 * Version: 1.0
 */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <stdint.h>

/* GPIO PROTS 	*/

#define GPIOA		0
#define GPIOB		1
#define GPIOC		2

/*GPIO PINS	*/

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4    	4
#define PIN5    	5
#define PIN6    	6
#define PIN7    	7
#define PIN8    	8
#define PIN9    	9
#define PIN10    	10
#define PIN11    	11
#define PIN12    	12
#define PIN13    	13
#define PIN14    	14
#define PIN15    	15

/*GPIO INPUT MODES	*/

#define INPUT_ANALIG			0b0000
#define INPUT_FLOAT			0b0100
#define INPUT_PULLUP			0b1000
#define INPUT_PULLDWN			0b1000

/*GPIO OUTPUT MODES	*/

#define OUTPUT_2MHZ_PUSH_PULL		0b0010
#define OUTPUT_2MHZ_OPEN_DRAIN		0b0110
#define OUTPUT_2MHZ_AF_PUSH_PULL	0b1010
#define OUTPUT_2MHZ_AF_OPEN_DRAIN	0b1110

#define OUTPUT_10MHZ_PUSH_PULL		0b0001
#define OUTPUT_10MHZ_OPEN_DRAIN		0b0101
#define OUTPUT_10MHZ_AF_PUSH_PULL	0b1001
#define OUTPUT_10MHZ_AF_OPEN_DRAIN	0b1101

#define OUTPUT_50MHZ_PUSH_PULL		0b0011
#define OUTPUT_50MHZ_OPEN_DRAIN		0b0111
#define OUTPUT_50MHZ_AF_PUSH_PULL	0b1011
#define OUTPUT_50MHZ_AF_OPEN_DRAIN	0b1111

/*AFIO DEFINES */

#define EXTI0		0
#define EXTI1		1
#define EXTI2   	2
#define EXTI3   	3
#define EXTI4   	4
#define EXTI5   	5
#define EXTI6   	6
#define EXTI7   	7
#define EXTI8  		8
#define EXTI9   	9
#define EXTI10   	10
#define EXTI11   	11
#define EXTI12   	12
#define EXTI13   	13
#define EXTI14   	14
#define EXTI15   	15

#define PAX		0
#define PBX		1
#define PCX		2
#define PDX		3
#define PEX		4
#define PFX		5
#define PGX		6


/* GPIO FUNCTION */

void GPIO_voidSetPinMode(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8PinMode);
void GPIO_voidSetPinVal(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8PinVal);
void GPIO_voidSetPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
void GPIO_voidClearPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
void GPIO_voidTogglePin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
void GPIO_voidSetPinAtomic(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
void GPIO_voidClearPinAtomic(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
uint8_t GPIO_u8ReadPin(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);

/* AFIO FUNCTIONS */

void AFIO_voidSetEXTIPin(uint8_t Copy_u8EXTIx, uint8_t Copy_u8Pin);
#endif

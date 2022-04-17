/*
 * Author: Mohammed Hisham
 * Date: 2 April 2022
 * Version: 1.0
 */

#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#define USART1_BASE	0x40013800
#define USART2_BASE	0x40004400
#define USART3_BASE	0x40044800

typedef struct{

	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
}USART_t;

#define _USART1	(volatile USART_t*) USART1_BASE
#define _USART2 (volatile USART_t*) USART2_BASE
#define _USART3 (volatile USART_t*) USART3_BASE


#endif

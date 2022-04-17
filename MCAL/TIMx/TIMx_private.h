/*
 *Author: Mohammed Hisham
 *Date: 23 March 2022
 *Version: 1.0
 */

#ifndef TIMx_PRIVATE_H
#define TIMx_PRIVATE_H

#define TIM2_BASE	0x40000000
#define TIM3_BASE	0x40000400
#define TIM4_BASE	0x40000800
#define TIM5_BASE	0x40000C00

#include <stdint.h>


typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t reserved1;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t reserved2;
	uint32_t DCR;
	uint32_t DMAR;

}TIMx_t;

#define _TIM2	((volatile TIMx_t*) TIM2_BASE)
#define _TIM3	((volatile TIMx_t*) TIM3_BASE)
#define _TIM4	((volatile TIMx_t*) TIM4_BASE)
#define _TIM5	((volatile TIMx_t*) TIM5_BASE)


#endif

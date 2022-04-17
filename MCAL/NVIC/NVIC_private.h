/*
 * Author: Mohammed Hisham
 * Date: 19 Feb 2022
 * Version: 1.0
 */

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define LAST_EXCEPTION	6
#define LAST_IRQ	59

#define NVIC_BASE	0XE000E100

#define NVIC_ISER0	(*(volatile uint32_t*) (NVIC_BASE + 0x000))
#define NVIC_ISER1	(*(volatile uint32_t*) (NVIC_BASE + 0x004))
#define NVIC_ICER0	(*(volatile uint32_t*) (NVIC_BASE + 0x080))
#define NVIC_ICER1	(*(volatile uint32_t*) (NVIC_BASE + 0x084))
#define NVIC_ISPR0	(*(volatile uint32_t*) (NVIC_BASE + 0x100))
#define NVIC_ISPR1	(*(volatile uint32_t*) (NVIC_BASE + 0x104))
#define NVIC_ICPR0	(*(volatile uint32_t*) (NVIC_BASE + 0x180))
#define NVIC_ICPR1	(*(volatile uint32_t*) (NVIC_BASE + 0x184))
#define NVIC_IABR0	(*(volatile uint32_t*) (NVIC_BASE + 0x200)) //define as const.
#define NVIC_IABR1	(*(volatile uint32_t*) (NVIC_BASE + 0x204)) //define as const.
#define NVIC_IPR0	(*(volatile uint32_t*) (NVIC_BASE + 0x300))
#define NVIC_IPR1       (*(volatile uint32_t*) (NVIC_BASE + 0x304))
#define NVIC_IPR2       (*(volatile uint32_t*) (NVIC_BASE + 0x308))
#define NVIC_IPR3       (*(volatile uint32_t*) (NVIC_BASE + 0x30C))
#define NVIC_IPR4       (*(volatile uint32_t*) (NVIC_BASE + 0x310))
#define NVIC_IPR5       (*(volatile uint32_t*) (NVIC_BASE + 0x314))
#define NVIC_IPR6       (*(volatile uint32_t*) (NVIC_BASE + 0x318))
#define NVIC_IPR7       (*(volatile uint32_t*) (NVIC_BASE + 0x31C))
#define NVIC_IPR8       (*(volatile uint32_t*) (NVIC_BASE + 0x320))
#define NVIC_IPR9       (*(volatile uint32_t*) (NVIC_BASE + 0x324))
#define NVIC_IPR10      (*(volatile uint32_t*) (NVIC_BASE + 0x328))
#define NVIC_IPR11      (*(volatile uint32_t*) (NVIC_BASE + 0x32C))
#define NVIC_IPR12      (*(volatile uint32_t*) (NVIC_BASE + 0x330))
#define NVIC_IPR13	(*(volatile uint32_t*) (NVIC_BASE + 0x334))
#define NVIC_IPR14      (*(volatile uint32_t*) (NVIC_BASE + 0x338))

/*********SCB registers*******/

#define SCB_BASE	0xE000ED00

#define SCB_AIRCR	(*(volatile uint32_t*) (SCB_BASE + 0x0C))
#define SCB_SHPR1	(*(volatile uint32_t*) (SCB_BASE + 0x18))
#define SCB_SHPR2	(*(volatile uint32_t*) (SCB_BASE + 0x1C))
#define SCB_SHPR3	(*(volatile uint32_t*) (SCB_BASE + 0x20))



#endif

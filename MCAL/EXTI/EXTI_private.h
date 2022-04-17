/*
 * Author:
 *
 *
 */

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#define MAX_LINE	18
#define EXTI_BASE	0x40010400

#define EXTI_IMR	(*(volatile uint32_t*) (EXTI_BASE + 0x00))
#define EXTI_EMR	(*(volatile uint32_t*) (EXTI_BASE + 0x04))
#define EXTI_RTSR	(*(volatile uint32_t*) (EXTI_BASE + 0x08))
#define EXTI_FTSR	(*(volatile uint32_t*) (EXTI_BASE + 0x0C))
#define EXTI_SWIER	(*(volatile uint32_t*) (EXTI_BASE + 0x10))
#define EXTI_PR		(*(volatile uint32_t*) (EXTI_BASE + 0x14))

#endif

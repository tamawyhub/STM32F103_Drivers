/*
 * Author: Mohammed Hisham
 * Data: 18 Feb 2022
 * Version: 1.0
 */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define GPIOA_BASE	0X40010800
#define GPIOB_BASE	0X40010C00
#define GPIOC_BASE	0X40011000

#define GPIOX_CRL(BASE)		(*(volatile uint32_t*) (BASE + 0X00))
#define GPIOX_CRH(BASE)		(*(volatile uint32_t*) (BASE + 0X04))
#define GPIOX_IDR(BASE)		(*(volatile uint32_t*) (BASE + 0X08))
#define GPIOX_ODR(BASE)		(*(volatile uint32_t*) (BASE + 0X0C))
#define GPIOX_BSRR(BASE)	(*(volatile uint32_t*) (BASE + 0X10))
#define GPIOX_BRR(BASE)		(*(volatile uint32_t*) (BASE + 0X14))
#define GPIOX_LCKR(BASE)	(*(volatile uint32_t*) (BASE + 0X18))


/*PORTA Regs. */

#define GPIOA_CRL	GPIOX_CRL(GPIOA_BASE)
#define GPIOA_CRH	GPIOX_CRH(GPIOA_BASE)
#define GPIOA_IDR	GPIOX_IDR(GPIOA_BASE)
#define GPIOA_ODR	GPIOX_ODR(GPIOA_BASE)
#define GPIOA_BSRR	GPIOX_BSRR(GPIOA_BASE)
#define GPIOA_BRR	GPIOX_BRR(GPIOA_BASE)
#define GPIOA_LCKR	GPIOX_LCKR(GPIOA_BASE)

/*PORTB Regs. */

#define GPIOB_CRL	GPIOX_CRL(GPIOB_BASE)
#define GPIOB_CRH	GPIOX_CRH(GPIOB_BASE)
#define GPIOB_IDR	GPIOX_IDR(GPIOB_BASE)
#define GPIOB_ODR	GPIOX_ODR(GPIOB_BASE)
#define GPIOB_BSRR	GPIOX_BSRR(GPIOB_BASE)
#define GPIOB_BRR	GPIOX_BRR(GPIOB_BASE)
#define GPIOB_LCKR	GPIOX_LCKR(GPIOB_BASE)

/*PORTC Regs. */

#define GPIOC_CRL	GPIOX_CRL(GPIOC_BASE)
#define GPIOC_CRH	GPIOX_CRH(GPIOC_BASE)
#define GPIOC_IDR	GPIOX_IDR(GPIOC_BASE)
#define GPIOC_ODR	GPIOX_ODR(GPIOC_BASE)
#define GPIOC_BSRR	GPIOX_BSRR(GPIOC_BASE)
#define GPIOC_BRR	GPIOX_BRR(GPIOC_BASE)
#define GPIOC_LCKR	GPIOX_LCKR(GPIOC_BASE)


#define AFIO_BASE	0x40010000

#define AFIO_EVCR	(*(volatile uint32_t*) (AFIO_BASE + 0x00))
#define AFIO_MAPR	(*(volatile uint32_t*) (AFIO_BASE + 0x04))
#define AFIO_EXTICR1	(*(volatile uint32_t*) (AFIO_BASE + 0x08))
#define AFIO_EXTICR2    (*(volatile uint32_t*) (AFIO_BASE + 0x0C))
#define AFIO_EXTICR3    (*(volatile uint32_t*) (AFIO_BASE + 0x10))
#define AFIO_EXTICR4    (*(volatile uint32_t*) (AFIO_BASE + 0x14))
#define AFIO_MAPR2	(*(volatile uint32_t*) (AFIO_BASE + 0x1C))

#endif

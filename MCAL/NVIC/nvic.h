#ifndef  _NVIC_H
#define _NVIC_H

#define SYS_IRQS 16
#define PERIPH_IRQS 60
#define ISR_VEC_SIZE (SYS_IRQS + PERIPH_IRQS)


#define IRQ_POS(X) (SYS_IRQS + X)



//System handlers

void systick_isr(void) __attribute__((weak));

//ISRs

void exti0_isr(void) __attribute__((weak));
void exti1_isr(void) __attribute__((weak));
void exti2_isr(void) __attribute__((weak));
void exti3_isr(void) __attribute__((weak));
void exti4_isr(void) __attribute__((weak));
void exti9_5_isr(void) __attribute__((weak));
void exti15_10_isr(void) __attribute__((weak));

void adc1_2_isr(void) __attribute__((weak));

void tim2_isr(void) __attribute__((weak));
void tim3_isr(void) __attribute__((weak));
void tim4_isr(void) __attribute__((weak));

void spi1_isr(void) __attribute__((weak));
void spi2_isr(void) __attribute__((weak));

void usart1_isr(void) __attribute__((weak));
void usart2_isr(void) __attribute__((weak));
void usart3_isr(void) __attribute__((weak));


#endif

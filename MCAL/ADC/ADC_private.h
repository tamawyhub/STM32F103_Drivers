/*
 *Author: Mohammed Hisham
 *Date: 21 March 2022
 *Version: 1.0
 */

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADC_BASE	0x40012400

#define ADC_SR		((volatile uint32_t*) ADC_BASE + 0x00)
#define ADC_CR1		((volatile uint32_t*) ADC_BASE + 0x40)
#define ADC_CR2		((volatile uint32_t*) ADC_BASE + 0x80)
#define ADC_SMPR1	((volatile uint32_t*) ADC_BASE + 0xC0)
#define ADC_SMPR2	((volatile uint32_t*) ADC_BASE + 0x10)
#define ADC_DR		((volatile uint32_t*) ADC_BASE + 0x4C)


#endif

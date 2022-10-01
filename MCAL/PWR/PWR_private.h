#ifndef PWR_PRIVATE_H
#define PWR_PRIVATE_H

#include <stdint.h>

#define PWR_BASE (0x40007000)

#define PWR_CR	(*(volatile uint32_t*) (PWR_BASE + 0x00))
#define PWR_CSR (*(volatile uint32_t*) (PWR_BASE + 0x04))


#endif

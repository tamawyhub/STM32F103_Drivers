#ifndef DEBUG_H
#define DEBUG_H

#include "USART/USART_interface.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void DEBUG_init(void);
void DEBUG_put_sint(int32_t l32_num);
void DEBUG_put_uint(uint32_t u32_num);
void DEBUG_put_str(const char* str);
void DEBUG_put_reg(uint32_t u32_reg, uint8_t mode);

#endif

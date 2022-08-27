#ifndef DEBUG_H
#define DEBUG_H

#include "USART/USART_interface.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum debug_ports_t
{
	DEBUG_PORT1 = USART1,
	DEBUG_PORT2,
	DEBUG_PORT3,
	DEBUG_PORT_COUNT,
} DEBUG_PORT;

#ifdef DEBUG
void DEBUG_init(uint8_t port);
void DEBUG_putc(uint8_t port, char ch);
void DEBUG_puts(uint8_t port, const char* ch);
void DEBUG_putline(uint8_t port, const char* ch);
void DEBUG_put_sint(uint8_t port, int32_t n);
void DEBUG_put_uint(uint8_t port, uint32_t n);
void DEBUG_put_hex(uint8_t port, uint32_t n);
void DEBUG_put_hex32(uint8_t port, uint32_t n);
void DEBUG_put_bin8(uint8_t port, uint32_t n);
#else
#define DEBUG_init(...)
#define DEBUG_putc(...)
#define DEBUG_puts(...)
#define DEBUG_putline(...)
#define DEBUG_put_sint(...)
#define DEBUG_put_uint(...)
#define DEBUG_put_hex(...)
#define DEBUG_put_hex32(...)
#define DEBUG_put_bin8(...)
#endif

#endif

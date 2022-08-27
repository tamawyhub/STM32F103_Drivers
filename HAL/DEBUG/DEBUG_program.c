#include "DEBUG.h"
#include "RCC/RCC_interface.h"
#include "GPIO/GPIO_interface.h"
#include "USART/USART_interface.h"

#include <string.h>

#define BUF_SIZE 64

#ifdef DEBUG
void DEBUG_init(uint8_t port)
{
	switch(port)
	{
		case DEBUG_PORT1:
			RCC_voidEnableClock(RCC_APB2, 14);
			GPIO_voidSetPinMode(GPIOA, PIN9, OUTPUT_10MHZ_AF_PUSH_PULL);
		       	GPIO_voidSetPinMode(GPIOA, PIN10, INPUT_FLOAT);
			break;
		case DEBUG_PORT2:
			/* TODO */
			break;
		case DEBUG_PORT3:
			/* TODO */
			break;
		default:
			return;
	}

	USART_voidInitSerial(port, 13, USART_TX_RX, USART_8_BITS, USART_STOP_1, USART_NO_PARITY);
}

void DEBUG_putc(uint8_t port, char ch)
{
	if(port < DEBUG_PORT_COUNT)
		USART_voidTransmitByte(port, ch);
}

void DEBUG_puts(uint8_t port, const char* str)
{
	if(port < DEBUG_PORT_COUNT)
		USART_voidTransmitString(port, str);
}

void DEBUG_putline(uint8_t port, const char* str)
{
	if(port < DEBUG_PORT_COUNT)
	{
		USART_voidTransmitString(port, str);
		USART_voidTransmitString(port, "\n\r");
	}
}

void DEBUG_put_sint(uint8_t port, int32_t n)
{
	char buf[BUF_SIZE];

	if(port < DEBUG_PORT_COUNT)
	{
		itoa(n, buf, 10);
		USART_voidTransmitString(port, buf);
		USART_voidTransmitString(port, "\n\r");
	}
}

void DEBUG_put_uint(uint8_t port, uint32_t n)
{
	char buf[BUF_SIZE];

        if(port < DEBUG_PORT_COUNT)
        {
                utoa(n, buf, 10);
                USART_voidTransmitString(port, buf);
		USART_voidTransmitString(port, "\n\r");
        }
}

void DEBUG_put_hex(uint8_t port, uint32_t n)
{
	char buf[BUF_SIZE];

        if(port < DEBUG_PORT_COUNT)
        {
                utoa(n, buf, 16);
                USART_voidTransmitString(port, "0x");
                USART_voidTransmitString(port, buf);
		USART_voidTransmitString(port, "\n\r");
        }
}

void DEBUG_put_hex32(uint8_t port, uint32_t n)
{

	char buf[BUF_SIZE];
	uint8_t i;
	uint8_t len;

        if(port < DEBUG_PORT_COUNT)
        {
                utoa(n, buf, 16);
                USART_voidTransmitString(port, "0x");

		len = strlen(buf);
		for(i = len; i < 8; i++)
		{
			USART_voidTransmitByte(port, '0');
		}

                USART_voidTransmitString(port, buf);
		USART_voidTransmitString(port, "\n\r");
	}
}

void DEBUG_put_bin8(uint8_t port, uint32_t n)
{
	char buf[BUF_SIZE];
	uint8_t i;
	uint8_t len;

        if(port < DEBUG_PORT_COUNT)
        {
                utoa(n, buf, 2);
                USART_voidTransmitString(port, "0b");

		len = strlen(buf);
		for(i = len; i < 8; i++)
		{
			USART_voidTransmitByte(port, '0');
		}
                USART_voidTransmitString(port, buf);
		USART_voidTransmitString(port, "\n\r");
	}
}

#endif

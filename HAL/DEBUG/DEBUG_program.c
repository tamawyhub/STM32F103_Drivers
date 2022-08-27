#include "DEBUG.h"
#include "RCC/RCC_interface.h"
#include "GPIO/GPIO_interface.h"
#include "USART/USART_interface.h"

#define BUF_SIZE 64

void DEBUG_init(void)
{
	RCC_voidEnableClock(RCC_APB2, 14);
	GPIO_voidSetPinMode(GPIOA, PIN9, OUTPUT_10MHZ_AF_PUSH_PULL);
        GPIO_voidSetPinMode(GPIOA, PIN10, INPUT_FLOAT);
	USART_voidInitSerial(USART1, 13, USART_TX_RX, USART_8_BITS, USART_STOP_1, USART_NO_PARITY);
}

void DEBUG_put_str(const char* str)
{
	if(str != NULL)
	{
		USART_voidTransmitString(USART1, str);
		USART_voidTransmitString(USART1, "\n\r");
	}
}

void DEBUG_put_sint(int32_t l32_num)
{
	char buffer[BUF_SIZE];

	itoa(l32_num, buffer, 10);

	buffer[BUF_SIZE - 1] = '\0';
	USART_voidTransmitString(USART1, buffer);
	USART_voidTransmitString(USART1, "\n\r");
}

void DEBUG_put_uint(uint32_t u32_num)
{
	char buffer[BUF_SIZE];

	utoa(u32_num, buffer, 10);

	buffer[BUF_SIZE - 1] = '\0';
	USART_voidTransmitString(USART1, buffer);
	USART_voidTransmitString(USART1, "\n\r");
}

void DEBUG_put_reg(uint32_t u32_reg, uint8_t mode)
{
	char buffer[BUF_SIZE];

	switch(mode)
	{
		case 'x':
			itoa(u32_reg, buffer, 16);
			break;
		case 'b':
			itoa(u32_reg, buffer, 2);
			break;
		default:
			buffer[0] = '\0';
	}

	USART_voidTransmitString(USART1, buffer);
	USART_voidTransmitString(USART1, "\n\r");
}

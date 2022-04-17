/*
 * Author: Mohammed Hisham
 * Date: 2 April 2022
 * Version: 1.0
 */

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#include <stdint.h>
#include "USART_config.h"


#define	USART1			0
#define USART2			1
#define USART3			2


#define USART_8_BITS		0
#define USART_9_BITS		1

#define USART_NO_PARITY		0
#define USART_EVEN_PARITY	2
#define USART_ODD_PARITY	3

#define USART_RX_ONLY		1
#define USART_TX_ONLY		2
#define USART_TX_RX		3

#define USART_STOP_1		0
#define USART_STOP_2		2

#define USART_NO_ERROR		0
#define USART_OVERRUN_ERROR	1
#define USART_NOISE_ERROR	2
#define USART_FRAME_ERROR	3
#define USART_PARITY_ERROR	4


#if (FLOAT_BAUDRATE)
void USART_voidInitSerial(uint8_t Copy_u8USART, float Copy_fDiv, uint8_t Copy_u8Mode, uint8_t Copy_u8Length,
                uint8_t Copy_u8StopBits,  uint8_t Copy_u8Parity);
#else
void USART_voidInitSerial(uint8_t Copy_u8USART, uint16_t Copy_u16Div, uint8_t Copy_u8Mode, uint8_t Copy_u8Length,
                uint8_t Copy_u8StopBits,  uint8_t Copy_u8Parity);
#endif

void USART_voidTransmitByte(uint8_t Copy_u8USART, uint8_t Copy_u8Byte);
void USART_voidTransmitString (uint8_t Copy_u8USART, const char *Copy_pStr);
void USART_voidTransmitData (uint8_t Copy_u8USART, const uint8_t *Copy_pDataPtr, uint32_t Copy_u8DataSize);
int8_t USART_s8ReceiveByte (uint8_t Copy_u8USART, uint8_t *Copy_pByte);
uint8_t USART_u8GetByte(uint8_t Copy_u8USART);
int8_t USART_s8ReceiveData (uint8_t Copy_u8USART, uint8_t *Copy_pBuffer, uint32_t Copy_u32DataSize);
int8_t USART_s8ReceiveString (uint8_t Copy_u8USART, char *Copy_pBuffer);
void USART_voidEnableReceiveInterrupt(uint8_t Copy_u8USART, void (*Copy_pIRQ) (void));
void USART_voidDisableReceiveInterrupt(uint8_t Copy_u8USART);

#endif

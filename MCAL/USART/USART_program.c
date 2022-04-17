/*
 *
 *
 *
 */

#include <stdint.h>
#include <stddef.h>
#include "BIT_MATH.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
#include "../GPIO/GPIO_interface.h"

typedef void (*usart_irq_t) (void);

volatile USART_t* Global_pUSARTArr[] = {_USART1, _USART2, _USART3};
usart_irq_t Global_pIRQs[3];

#if (FLOAT_BAUDRATE)
void USART_voidInitSerial(uint8_t Copy_u8USART, float Copy_fDiv, uint8_t Copy_u8Mode, uint8_t Copy_u8Length, 
		uint8_t Copy_u8StopBits,  uint8_t Copy_u8Parity){
	
	USART_t* Local_pUSART = Global_pUSARTArr[Copy_u8USART];
	uint16_t Local_u16DivMantissa = (uint16_t) Copy_fDiv;
	float Local_fDivFraction = (Copy_fDiv - Local_u16DivMantissa) * 16.0f;
	uint8_t Local_u8DivFraction = (uint8_t) Local_fDivFraction;
	if(Local_fDivFraction - (float) Local_u8DivFraction > 0.5f){
		++Local_u8DivFraction;
	}
	if(Local_u8DivFraction >= 16){
		++Local_u16DivMantissa;
		Local_u8DivFraction = 0;
	}
	Local_pUSART->BRR = (Local_u16DivMantissa << 4) | Local_u8DivFraction;

	Local_pUSART->CR2 |= (Copy_u8StopBits << 12);
	Local_pUSART->CR1 = 0x00;
	Local_pUSART->CR1 |= (Copy_u8Length << 12);
	Local_pUSART->CR1 |= (Copy_u8Parity << 9);
	SET_BIT(Local_pUSART->CR1, 13);
	Local_pUSART->CR1 |= (Copy_u8Mode << 2);

}

#else
void USART_voidInitSerial(uint8_t Copy_u8USART, uint16_t Copy_u16Div, uint8_t Copy_u8Mode, uint8_t Copy_u8Length,
                uint8_t Copy_u8StopBits,  uint8_t Copy_u8Parity){

        USART_t* Local_pUSART = Global_pUSARTArr[Copy_u8USART];
        Local_pUSART->BRR = (Copy_u16Div << 4);

        Local_pUSART->CR2 |= (Copy_u8StopBits << 12);
        Local_pUSART->CR1 = 0x00;
        Local_pUSART->CR1 |= (Copy_u8Length << 12);
        Local_pUSART->CR1 |= (Copy_u8Parity << 9);
        SET_BIT(Local_pUSART->CR1, 13);
        Local_pUSART->CR1 |= (Copy_u8Mode << 2);

}
#endif

void USART_voidTransmitByte(uint8_t Copy_u8USART, uint8_t Copy_u8Byte){

	while(!GET_BIT(Global_pUSARTArr[Copy_u8USART]->SR, 7));
	Global_pUSARTArr[Copy_u8USART]->DR = Copy_u8Byte;
}

void USART_voidTransmitString (uint8_t Copy_u8USART, const char *Copy_pStr)
{
	USART_t *Local_pUSART = Global_pUSARTArr[Copy_u8USART];
	while (*Copy_pStr)
	{
		while (!GET_BIT(Local_pUSART->SR, 7))
		{
			/* Wait until TDR is empty */
		}

		Local_pUSART->DR = *Copy_pStr;
		++Copy_pStr;
	}
}

void USART_voidTransmitData (uint8_t Copy_u8USART, const uint8_t *Copy_pDataPtr, uint32_t Copy_u32DataSize)
{
	USART_t *Local_pUSART = Global_pUSARTArr[Copy_u8USART];
	
	uint32_t Local_u32LoopCounter;
	for(Local_u32LoopCounter = 0; Local_u32LoopCounter < Copy_u32DataSize; Local_u32LoopCounter++)
	{
		while (!GET_BIT(Local_pUSART->SR, 7))
		{
			/* Wait until TDR is empty */
		}

		Local_pUSART->DR = Copy_pDataPtr[Local_u32LoopCounter];
	}
}

int8_t USART_s8ReceiveByte (uint8_t Copy_u8USART, uint8_t *Copy_pByte)
{
	int8_t Local_s8RetVal;

	if (Copy_pByte != NULL)
	{
		USART_t *Local_pUSART = Global_pUSARTArr[Copy_u8USART];

		while (!GET_BIT(Local_pUSART->SR, 5))
		{
			/* Wait until data transferred to RDR */
		}

		if (GET_BIT(Local_pUSART->SR, 3))
		{
			/* Overrun error */
			Local_s8RetVal = USART_OVERRUN_ERROR;
		}
		else if (GET_BIT(Local_pUSART->SR, 2))
		{
			/* Noise error */
			Local_s8RetVal = USART_NOISE_ERROR;
		}
		else if (GET_BIT(Local_pUSART->SR, 1))
		{
			/* Frame error */
			Local_s8RetVal = USART_FRAME_ERROR;
		}
		else if (GET_BIT(Local_pUSART->SR, 0))
		{
			/* Parity error */
			Local_s8RetVal = USART_PARITY_ERROR;
		}
		else
		{
			/* No errors */
			Local_s8RetVal = USART_NO_ERROR;
		}

		*Copy_pByte = Local_pUSART->DR;
	}
	else
	{
		Local_s8RetVal = -1;
	}

	return Local_s8RetVal;
}

uint8_t USART_u8GetByte(uint8_t Copy_u8USART)
{
	uint8_t Local_u8Byte;
	Local_u8Byte = Global_pUSARTArr[Copy_u8USART]->DR;

	return Local_u8Byte;
}

int8_t USART_s8ReceiveData (uint8_t Copy_u8USART, uint8_t *Copy_pBuffer, uint32_t Copy_u32DataSize)
{
	uint32_t Local_u32LoopCounter;
	int8_t Local_s8RetVal;

	for (Local_u32LoopCounter = 0; Local_u32LoopCounter < Copy_u32DataSize; Local_u32LoopCounter++)
	{
		Local_s8RetVal = USART_s8ReceiveByte(Copy_u8USART, Copy_pBuffer + Local_u32LoopCounter);
		if (Local_s8RetVal != USART_NO_ERROR)
		{
			/* Overrun, Noise, Frame or Parity error encountered */
			/* break. Goto return statement */
			break;
		}
	}

	return Local_s8RetVal;
}

int8_t USART_s8ReceiveString (uint8_t Copy_u8USART, char *Copy_pBuffer)
{
	int8_t Local_s8RetVal;

	do
	{
		Local_s8RetVal = USART_s8ReceiveByte(Copy_u8USART, Copy_pBuffer);
		
		if (Local_s8RetVal != USART_NO_ERROR)
		{
			/* Overrun, Noise, Frame or parity error */
			/* break. Goto return statement */
			break;
		}
	}while (*(Copy_pBuffer++) != '\r');
	*Copy_pBuffer = '\0';

	return Local_s8RetVal;
}

void USART_voidEnableReceiveInterrupt(uint8_t Copy_u8USART, usart_irq_t Copy_pIRQ)
{
	SET_BIT(Global_pUSARTArr[Copy_u8USART]->CR1, 5);
	Global_pIRQs[Copy_u8USART] = Copy_pIRQ;
}

void USART_voidDisableReceiveInterrupt(uint8_t Copy_u8USART)
{
	CLR_BIT(Global_pUSARTArr[Copy_u8USART]->CR1, 5);
}

void usart1_isr(void)
{
	Global_pIRQs[0]();
}

void usart2_isr(void)
{
	Global_pIRQs[1]();
}

void usart3_isr(void)
{
	Global_pIRQs[2]();
}

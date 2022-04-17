/*
 *
 *
 *
 */

#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

#include <stdint.h>

#define DMA_NO_INCREMENT		0
#define DMA_PERIPH_INCREMENT		1
#define DMA_MEM_INCREMENT		2
#define DMA_MEM_PERIPH_INCREMENT	3

#define DMA_PRIORITY_LOW		0
#define DMA_PRIORITY_MEDIUM		1
#define DMA_PRIORITY_HIGH		2
#define DMA_PRIORITY_VERY_HIGH		3

#define DMA_READ_PERIPH			0
#define DMA_READ_MEM			1

#define DMA_SIZE_8			0
#define DMA_SIZE_16			1
#define DMA_SIZE_32			2


void DMA_voidSetPeriphAddress(uint8_t Copy_u8Channel, const void* Copy_ptrAddr);
void DMA_voidSetMemAddress(uint8_t Copy_u8Channel, const void* Copy_ptrAddr);
void DMA_voidSetDataLength(uint8_t Copy_u8Channel, uint16_t Copy_u16Len);
void DMA_voidSetPriority(uint8_t Copy_u8Channel, uint8_t Copy_u8Pri);
void DMA_voidSetDirection(uint8_t Copy_u8Channel, uint8_t Copy_u8Dir);
void DMA_voidEnableCircularMode(uint8_t Copy_u8Channel);
void DMA_voidDisableCircularMode(uint8_t Copy_u8Channel);
void DMA_voidSetIncrementMode(uint8_t Copy_u8Channel, uint8_t Copy_u8Mode);
void DMA_voidSetDataSize(uint8_t Copy_u8Channel, uint8_t Copy_u8MemDataSize, uint8_t Copy_u8PeriphDataSize);
void DMA_voidEnableChannel(uint8_t Copy_u8Channel);
void DMA_voidDisableChannel(uint8_t Copy_u8Channel);
void DMA_voidEnableMem2Mem(uint8_t Copy_u8Channel);
void DMA_voidDisableMem2Mem(uint8_t Copy_u8Channel);
void DMA_voidStartTransfer(uint8_t Copy_u8Channel, const void* Copy_ptrSrc, const void* Copy_ptrDest, uint16_t Copy_u16Length);
void DMA_voidWaitDone(uint8_t Copy_u8Channel);
uint8_t DMA_u8GetCompleteFlag(uint8_t Copy_u8Channel);

#endif

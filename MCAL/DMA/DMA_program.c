/*
 *
 *
 *
 */

#include <stdint.h>
#include "BIT_MATH.h"
#include "DMA_private.h"
#include "DMA_interface.h"

void DMA_voidSetPeriphAddress(uint8_t Copy_u8Channel, const void* Copy_ptrAddr){

	if(Copy_u8Channel <= 7){
		DMA.channel[Copy_u8Channel].CPAR = Copy_ptrAddr;
	}
	else{
		/*return error*/
	}

}

void DMA_voidSetMemAddress(uint8_t Copy_u8Channel, const void* Copy_ptrAddr){

	if(Copy_u8Channel <= 7){
		DMA.channel[Copy_u8Channel].CMAR = Copy_ptrAddr;
	}
	else{
		/*return error*/
	}

}

void DMA_voidSetDataLength(uint8_t Copy_u8Channel, uint16_t Copy_u16Len){

	if(Copy_u8Channel <= 7){
		DMA.channel[Copy_u8Channel].CCR &= ~0x01;	//Disable DMA Channel
                DMA.channel[Copy_u8Channel].CNDTR = Copy_u16Len;
        }
        else{
                /*return error*/
        }
}

void DMA_voidSetPriority(uint8_t Copy_u8Channel, uint8_t Copy_u8Pri){

	if(Copy_u8Channel <= 7){
                if(Copy_u8Pri <= 3){
			DMA.channel[Copy_u8Channel].CCR &= ~(0x03<<12);
			DMA.channel[Copy_u8Channel].CCR |= (Copy_u8Pri<<12);
		}
		else{
			/*return error*/
		}
        }
        else{
                /*return error*/
        }

}

void DMA_voidSetDirection(uint8_t Copy_u8Channel, uint8_t Copy_u8Dir){

	if(Copy_u8Channel <= 7){
                if(Copy_u8Dir <= 1){
                        DMA.channel[Copy_u8Channel].CCR &= ~(0x01<<4);
                        DMA.channel[Copy_u8Channel].CCR |= (Copy_u8Dir<<4);
		}
		else{
			/*return error*/
		}
        }
        else{
                /*return error*/
        }

}

void DMA_voidEnableCircularMode(uint8_t Copy_u8Channel){

	if(Copy_u8Channel <= 7){
		DMA.channel[Copy_u8Channel].CCR |= (0X01<<5);
        }
        else{
                /*return error*/
        }
	
}

void DMA_voidDisableCircularMode(uint8_t Copy_u8Channel){

        if(Copy_u8Channel <= 7){
                DMA.channel[Copy_u8Channel].CCR &= ~(0X01<<5);
        }
        else{
                /*return error*/
        }

}

void DMA_voidSetIncrementMode(uint8_t Copy_u8Channel, uint8_t Copy_u8Mode){

	if(Copy_u8Channel <= 7){
                if(Copy_u8Mode <= 3){
                        DMA.channel[Copy_u8Channel].CCR &= ~(0x03<<6);
                        DMA.channel[Copy_u8Channel].CCR |= (Copy_u8Mode<<6);
		}
		else{
			/*return error*/
		}
        }
        else{
                /*return error*/
        }

}

void DMA_voidSetDataSize(uint8_t Copy_u8Channel, uint8_t Copy_u8PeriphDataSize, uint8_t Copy_u8MemDataSize){

	if(Copy_u8Channel <= 7){
                if(Copy_u8PeriphDataSize <= 2){
                        DMA.channel[Copy_u8Channel].CCR &= ~(0x03<<8);
                        DMA.channel[Copy_u8Channel].CCR |= (Copy_u8PeriphDataSize<<8);
		}
		if(Copy_u8MemDataSize <= 2){
			DMA.channel[Copy_u8Channel].CCR &= ~(0x03<<10);
                        DMA.channel[Copy_u8Channel].CCR |= (Copy_u8MemDataSize<<10);
		}
		else{
			/*return error*/
		}
        }
        else{
                /*return error*/
        }

}

void DMA_voidEnableChannel(uint8_t Copy_u8Channel){

	if(Copy_u8Channel <= 7){
                DMA.channel[Copy_u8Channel].CCR |= 0X01;
        }
        else{
                /*return error*/
        }
}

void DMA_voidDisableChannel(uint8_t Copy_u8Channel){

	if(Copy_u8Channel <= 7){
                DMA.channel[Copy_u8Channel].CCR &= ~0X01;
        }
        else{
                /*return error*/
        }
}

void DMA_voidEnableMem2Mem(uint8_t Copy_u8Channel){

	if(Copy_u8Channel <= 7){
                DMA.channel[Copy_u8Channel].CCR |= (0X01<<14);
        }
        else{
                /*return error*/
        }
}

void DMA_voidDisableMem2Mem(uint8_t Copy_u8Channel){

        if(Copy_u8Channel <= 7){
                DMA.channel[Copy_u8Channel].CCR &= ~(0X01<<14);
        }
        else{
                /*return error*/
        }
}

void DMA_voidStartTransfer(uint8_t Copy_u8Channel, const void* Copy_ptrSrc, const void* Copy_ptrDest, uint16_t Copy_u16Length){

	if(Copy_u8Channel <= 7){
		DMA_voidSetPeriphAddress(Copy_u8Channel, Copy_ptrSrc);
		DMA_voidSetMemAddress(Copy_u8Channel, Copy_ptrDest);
		DMA_voidSetDataLength(Copy_u8Channel, Copy_u16Length);
		DMA_voidSetDirection(Copy_u8Channel, DMA_READ_PERIPH);
		DMA_voidDisableCircularMode(Copy_u8Channel);
		DMA_voidEnableChannel(Copy_u8Channel);
	}
	else{
		/*return error*/
	}
}

void DMA_voidWaitDone(uint8_t Copy_u8Channel){

	while(!GET_BIT(DMA.ISR, 1));
}

uint8_t DMA_u8GetCompleteFlag(uint8_t Copy_u8Channel){

	return GET_BIT(DMA.ISR, 1);
}

/*
 * Author: Mohammed Hisham
 * Date: 29 March 2022
 * Version: 1.0
 */

#include <stdint.h>
#include "BIT_MATH.h"
#include "SPI_private.h"
#include "SPI_interface.h"

volatile SPI_t* Global_pSPIArr[2] = {_SPI1, _SPI2};
typedef void (*callback_t) (void);
callback_t Global_pCallbacks[2];

void SPI_voidInitMaster(uint8_t Copy_u8SPI, uint8_t Copy_u8ClockPsc, uint8_t Copy_u8ClockPhase,
		uint8_t Copy_u8ClockPolarity, uint8_t Copy_u8FF, uint8_t Copy_u8FrameSize){

	volatile SPI_t *Local_pSPI = Global_pSPIArr[Copy_u8SPI];

	Local_pSPI->CR1 = 0x00;
	Local_pSPI->CR1 |= Copy_u8ClockPhase;
	Local_pSPI->CR1 |= (Copy_u8ClockPolarity << 1);
	SET_BIT(Local_pSPI->CR1, 2);	//Enable Master Mode
	Local_pSPI->CR1 |= (Copy_u8ClockPsc << 3);
	Local_pSPI->CR1 |= (Copy_u8FF << 7);
	Local_pSPI->CR1 |= (Copy_u8FrameSize << 11);
	SET_BIT(Local_pSPI->CR1, 8);//NSS high
	SET_BIT(Local_pSPI->CR1, 9);//S.W NSS
	SET_BIT(Local_pSPI->CR1, 6);
}

void SPI_voidEnableSlaveSelect(uint8_t Copy_u8SPI){

	//Configure NSS as AF Open Drain Output
	CLR_BIT(Global_pSPIArr[Copy_u8SPI]->CR1, 9);
	SET_BIT(Global_pSPIArr[Copy_u8SPI]->CR2, 2);
}

void SPI_voidInitSlave(uint8_t Copy_u8SPI, uint8_t Copy_u8ClockPhase, uint8_t Copy_u8ClockPolarity, 
		uint8_t Copy_u8FF, uint8_t Copy_u8FrameSize){

	//Slave mode not tested
	volatile SPI_t *Local_pSPI = Global_pSPIArr[Copy_u8SPI];

	Local_pSPI->CR1 = 0x00;
	Local_pSPI->CR1 |= Copy_u8ClockPhase;
	Local_pSPI->CR1 |= (Copy_u8ClockPolarity << 1);
	Local_pSPI->CR1 |= (Copy_u8FF << 7);
	Local_pSPI->CR1 |= (Copy_u8FrameSize << 11);
	SET_BIT(Local_pSPI->CR1, 6);

}

void SPI_voidTransmitData(uint8_t Copy_u8SPI, uint16_t Copy_u16Data, uint8_t Copy_u8IsBlocking){

	while(Copy_u8IsBlocking && !GET_BIT(Global_pSPIArr[Copy_u8SPI]->SR, 1));
	Global_pSPIArr[Copy_u8SPI]->DR = Copy_u16Data;
}

uint16_t SPI_u16ReceiveData(uint8_t Copy_u8SPI){

	while(!GET_BIT(Global_pSPIArr[Copy_u8SPI]->SR, 0));
	return Global_pSPIArr[Copy_u8SPI]->DR;
}


void SPI_voidEnableRXInterrupt(uint8_t Copy_u8SPI, void (*rx_callback) (void)){

	SET_BIT(Global_pSPIArr[Copy_u8SPI]->CR2, 6);
	Global_pCallbacks[Copy_u8SPI] = rx_callback;
}

void SPI_voidDisableRXInterrupt(uint8_t Copy_u8SPI){

	CLR_BIT(Global_pSPIArr[Copy_u8SPI]->CR2, 6);
}

void SPI_voidEnableTXInterrupt(uint8_t Copy_u8SPI, void (*tx_callback) (void)){

        SET_BIT(Global_pSPIArr[Copy_u8SPI]->CR2, 7);
        Global_pCallbacks[Copy_u8SPI] = tx_callback;
}

void SPI_voidDisableTXInterrupt(uint8_t Copy_u8SPI){

        CLR_BIT(Global_pSPIArr[Copy_u8SPI]->CR2, 7);
}


void spi1_isr(void){

	Global_pCallbacks[0]();
}

void spi2_isr(void){
	
	Global_pCallbacks[1]();
}

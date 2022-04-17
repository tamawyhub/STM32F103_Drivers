/*
 * Author: Mohammed Hisham
 * Date: 29 March 2022
 * Version: 1.0
 */


#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#define SPI1	0
#define SPI2	1

#define SPI_CAPTURE_1ST_EDGE	0
#define SPI_CAPTURE_2ND_EDGE	1

#define SPI_IDLE_LOW		0
#define SPI_IDLE_HIGH		1

#define SPI_PSC_DIV_2		0
#define SPI_PSC_DIV_4		1
#define SPI_PSC_DIV_8		2
#define SPI_PSC_DIV_16		3
#define SPI_PSC_DIV_32		4
#define SPI_PSC_DIV_64		5
#define SPI_PSC_DIV_128		6
#define SPI_PSC_DIV_256		7

#define SPI_MSB_FIRST		0
#define SPI_LSB_FIRST		1

#define SPI_FRAME_SIZE_8	0
#define SPI_FRAME_SIZE_16	1

#define SPI_NON_BLOCKING	0
#define SPI_BLOCKING		1


void SPI_voidInitMaster(uint8_t Copy_u8SPI, uint8_t Copy_u8ClockPsc, uint8_t Copy_u8ClockPhase,
                uint8_t Copy_u8ClockPolarity, uint8_t Copy_u8FF, uint8_t Copy_u8FrameSize);
void SPI_voidEnableSlaveSelect(uint8_t Copy_u8SPI);
void SPI_voidInitSlave(uint8_t Copy_u8SPI, uint8_t Copy_u8ClockPhase, uint8_t Copy_u8ClockPolarity, 
		uint8_t Copy_u8FF, uint8_t Copy_u8FrameSize);
void SPI_voidEnableRXInterrupt(uint8_t Copy_u8SPI, void (*rx_callback) (void));
void SPI_voidEnableTXInterrupt(uint8_t Copy_u8SPI, void (*tx_callback) (void));
void SPI_voidDisableRXInterrupt(uint8_t Copy_u8SPI);
void SPI_voidDisableTXInterrupt(uint8_t Copy_u8SPI);
void SPI_voidTransmitData(uint8_t Copy_u8SPI, uint16_t Copy_u16Data, uint8_t Copy_u8IsBlocking);
uint16_t SPI_u16ReceiveData(uint8_t Copy_u8SPI);

#endif

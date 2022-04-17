/*
 * Author: Mohammed Hisham
 * Date: 29 March 2022
 * Version: 1.0
 */

#ifndef SPI_PRIVATE_H
#define spi_private_H

#define SPI1_BASE	0x40013000
#define SPI2_BASE	0x40003800

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SR;
	uint32_t DR;
	uint32_t CRCPR;
	uint32_t RXCRCR;
	uint32_t TXCRCR;
	uint32_t I2SCFGR;
	uint32_t I2SPR;
}SPI_t;

#define _SPI1	(volatile SPI_t*) SPI1_BASE
#define _SPI2	(volatile SPI_t*) SPI2_BASE

#endif

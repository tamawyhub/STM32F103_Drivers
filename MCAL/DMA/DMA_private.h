/*
 * Author: Mohammed Hisham
 * Date: 22 March 2022
 * Version: 1.0
 */

#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

#define DMA_BASE	0x40020000

#define DMA_CHANNELS	7

typedef struct{
	uint32_t CCR;
	uint32_t CNDTR;
	const void* CPAR;
	const void* CMAR;
	uint32_t reserved;
}DMA_channel_t;

typedef struct{
	uint32_t ISR;
	uint32_t IFCR;
	DMA_channel_t channel[DMA_CHANNELS];
}DMA_t;


#define DMA	(*(volatile DMA_t*) DMA_BASE)

#endif

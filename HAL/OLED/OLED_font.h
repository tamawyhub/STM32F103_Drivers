#ifndef _OLED_FONT_H
#define _OLED_FONT_H

#include <stdint.h>

#define FONT_SYMBOLS	96	

typedef struct font
{
	uint16_t font_data_size;
	const uint8_t *font_char_width;
	const uint8_t *font_data;
} FONT;


#endif

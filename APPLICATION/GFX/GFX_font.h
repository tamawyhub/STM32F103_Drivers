#ifndef _GFX_FONT_H
#define _GFX_FONT_H

#include "GFX_config.h"
#include "GFX.h"

#include <stdint.h>

#define FONT_SYMBOLS	96	

typedef struct font
{
	uint16_t font_data_size;
	uint8_t font_char_fixed_size;
	uint8_t font_char_height;
	const uint8_t *font_char_size;
	const uint8_t *font_data;
} FONT;

#if 0
typedef struct GFX_bitmap
{
	uint8_t bitmap_width;
	uint8_t bitmap_height;
	const uint8_t* bitmap_data;
} GFX_BITMAP;
#endif

typedef enum e_fonts
{
#if GFX_FONT_USE_DEFAULT_5X7 == 1
        DEFAULT_5X7,
#endif

#if GFX_FONT_USE_DEFAULT_6X7 == 1
        DEFAULT_6X7,
#endif
#if GFX_FONT_USE_ARIAL_14 == 1
	ARIAL_14,
#endif
#if GFX_FONT_USE_IAIN_5X7 == 1
	IAIN_5X7,
#endif
#if GFX_FONT_USE_SYSTEM_5X7 == 1
	SYSTEM_5X7,
#endif
#if GFX_FONT_USE_STANG_5X7 == 1
	STANG_5X7,
#endif
#if GFX_FONT_USE_WENDY_3X5 == 1
	WENDY_3X5,
#endif
#if GFX_FONT_USE_CP437_8X8 == 1
	CP437_8X8,
#endif
#if GFX_FONT_USE_FONT_8X8 == 1
	FONT_8X8,
#endif
#if GFX_FONT_USE_FIXED_BOLD == 1
	FIXED_BOLD,
#endif
#if GFX_FONT_USE_TIMES_NEW_ROMAN_ITALIC == 1
	TIMES_NEW_ROMAN_ITALIC,
#endif
#if GFX_FONT_USE_COOPER_21 == 1
	COOPER_21,
#endif
        FONTS_USED
} E_FONTS;

int GFX_putc(GFX* gfx, uint8_t font_indx, uint8_t ch);
int GFX_puts(GFX* gfx, uint8_t font_indx, const char* str);

#endif

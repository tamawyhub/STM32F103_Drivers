#ifndef _GFX_H
#define _GFX_H

#include "GFX_font.h"
#include "GFX_config.h"

#include <stdint.h>

typedef struct GFX_cursor
{
	uint16_t xpos;
    uint16_t ypos;
} GFX_CURSOR;

typedef struct gfx_t
{
    char* buffer;
    GFX_CURSOR cursor;
    uint16_t buffer_height;
    uint16_t buffer_width;
} GFX;

typedef enum GFX_erros
{
	GFX_OK,
	GFX_FAILED,
	GFX_IN_BOUNDARY,
	GFX_COL_OUT,
	GFX_LINE_OUT,
} GFX_ERRORS;

void GFX_init(GFX* gfx, char* lcd_buffer, uint16_t width, uint16_t height);
int GFX_putc(GFX* gfx, uint8_t font_indx, uint8_t ch);
int GFX_puts(GFX* gfx, uint8_t font_indx, const char* str);

#endif
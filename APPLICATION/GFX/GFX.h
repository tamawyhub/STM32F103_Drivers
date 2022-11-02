#ifndef _GFX_H
#define _GFX_H

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
int GFX_get_pos(GFX* gfx, GFX_CURSOR* cursor);
int GFX_set_pos(GFX* gfx, GFX_CURSOR* cursor);
int GFX_update_cursor(GFX* gfx, uint16_t height, uint16_t width);
int GFX_check_boundaries(const GFX* gfx, const GFX_CURSOR* cursor);
int GFX_update_buff(GFX* gfx, char* buf, GFX_CURSOR* cursor, uint16_t len);

#endif
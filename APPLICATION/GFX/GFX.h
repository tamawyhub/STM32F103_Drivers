#ifndef _GFX_H
#define _GFX_H

#include <stdint.h>

typedef uint16_t gfx_size_t;

typedef struct GFX_cursor
{
	gfx_size_t xpos;
	gfx_size_t ypos;
} GFX_CURSOR;

typedef struct gfx_t
{
    char* buffer;
    GFX_CURSOR cursor;
    gfx_size_t buffer_height;
    gfx_size_t buffer_width;
} GFX;

typedef enum GFX_erros
{
	GFX_OK,
	GFX_FAILED,
	GFX_IN_BOUNDARY,
	GFX_COL_OUT,
	GFX_LINE_OUT,
} GFX_ERRORS;

void GFX_init(GFX* gfx, char* lcd_buffer, gfx_size_t width, gfx_size_t height);
int GFX_get_pos(GFX* gfx, GFX_CURSOR* cursor);
int GFX_set_pos(GFX* gfx, GFX_CURSOR* cursor);
int GFX_check_boundaries(const GFX* gfx, const GFX_CURSOR* cursor);
int GFX_update_buff(GFX* gfx, char* buf, GFX_CURSOR* cursor, gfx_size_t len);

#endif

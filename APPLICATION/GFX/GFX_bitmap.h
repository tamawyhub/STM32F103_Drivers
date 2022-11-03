#ifndef _GFX_BITMAP_H
#define _GFX_BITMAP_H

#include "GFX.h"

typedef struct GFX_bitmap
{
	gfx_size_t bitmap_width;
	gtx_size_t bitmap_height;
	const uint8_t* bitmap_data;
} GFX_BITMAP;

int GFX_draw_bitmap(const GFX_BITMAP* bitmap, const GFX_CURSOR* cursor);

#endif

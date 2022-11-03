#ifndef _GFX_BITMAP_H
#define _GFX_BITMAP_H

typedef struct GFX_bitmap
{
	uint8_t bitmap_width;
	uint8_t bitmap_height;
	const uint8_t* bitmap_data;
} GFX_BITMAP;

int GFX_draw_bitmap(const GFX_BITMAP* bitmap, const GFX_CURSOR* cursor);

#endif

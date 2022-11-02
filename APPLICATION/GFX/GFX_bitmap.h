#ifndef _GFX_BITMAP_H
#define _GFX_BITMAP_H

#include "GFX.h"

#include <stdint.h>

typedef struct bitmap_t
{
    char* bitmap_buffer;
    uint16_t height;
    uint16_t width;
    uint16_t x_pos;
    uint16_t y_pos;
} GFX_BITMAP;

void GFX_BITMAP_draw_bitmap(GFX* gfx, const GFX_BITMAP* bitmap);

#endif
#include "GFX_bitmap.h"

void GFX_BITMAP_draw_bitmap(GFX* gfx, const GFX_BITMAP* bitmap)
{
    uint16_t l_width, l_height;
    GFX_CURSOR l_cursor;

    if(gfx && bitmap)
    {
        /* Check boundaries */
        if((bitmap->x_pos + bitmap->width) > gfx->buffer_width)
        {
            l_width = gfx->buffer_width - bitmap->x_pos;
        }
        else
        {
            l_width = bitmap->width;
        }

        if((bitmap->y_pos + bitmap->height) > gfx->buffer_height)
        {
            l_height = gfx->buffer_height - bitmap->y_pos;
        }
        else
        {
            l_height = bitmap->height;
        }

        l_cursor.xpos = bitmap->x_pos;
        l_cursor.ypos = bitmap->y_pos;

        GFX_update_cursor(gfx, l_height, l_width);
        GFX_update_buff(gfx, bitmap->bitmap_buffer, &l_cursor, l_width * l_height);
    }
}
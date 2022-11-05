#include "GFX.h"
#include "GFX_font.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

int GFX_get_pos(GFX* gfx, GFX_CURSOR* cursor)
{
	int l_ret = GFX_FAILED;

	if(gfx && cursor)
	{
		memcpy(cursor, &gfx->cursor, sizeof(GFX_CURSOR));
		l_ret = GFX_OK;
	}

	return l_ret;
}

int GFX_set_pos(GFX* gfx, GFX_CURSOR* cursor)
{
	int l_ret = GFX_FAILED;

	if(gfx && cursor && 
		(cursor->xpos < gfx->buffer_width) && (cursor->ypos < gfx->buffer_height))
	{
		memcpy(&gfx->cursor, cursor, sizeof(GFX_CURSOR));
		l_ret = GFX_OK;
	}

	return l_ret;
}

int GFX_update_cursor(GFX* gfx, uint16_t height, uint16_t width)
{
    uint16_t l_ret = GFX_FAILED;

    if(gfx)
    {
        if((gfx->cursor.xpos + width) < gfx->buffer_width)
        {
            gfx->cursor.xpos += width;
        }
        else    /* Wrapp around */
        {
            gfx->cursor.xpos = 0;
        }

        if((gfx->cursor.ypos + height) < gfx->buffer_height)
        {
            gfx->cursor.ypos += height;
        }
        else
        {
            gfx->cursor.ypos = 0;
        }

        l_ret = GFX_OK;
    }

    return l_ret;
}
int GFX_check_boundaries(const GFX* gfx, const GFX_CURSOR* cursor)
{

	if(cursor == NULL || gfx == NULL)
	{
		return GFX_FAILED;
	}

	if(cursor->xpos >= gfx->buffer_width)
	{
		return GFX_COL_OUT;
	}

	if(cursor->ypos >= gfx->buffer_height)
	{
		return GFX_LINE_OUT;
	}

	return GFX_IN_BOUNDARY;
}

int GFX_update_buff(GFX* gfx, const uint8_t* buf, GFX_CURSOR* cursor, gfx_size_t len, GFX_UMETHOD umethod)
{
	gfx_size_t start_pos;
	gfx_size_t end_pos;
	gfx_size_t buffer_size;

	if(gfx == NULL || cursor == NULL || buf == NULL)
	{
		return GFX_FAILED;
	}

	if(len == 0)
	{
		return GFX_OK;
	}
	
	start_pos = cursor->ypos * gfx->buffer_width + cursor->xpos;
	end_pos = start_pos + len;
	buffer_size = gfx->buffer_height * gfx->buffer_width;

	if(end_pos > buffer_size)
	{
		len = buffer_size - start_pos;
	}
	
	if (umethod == GFX_UMETHOD_COPY) memcpy(gfx->buffer + start_pos, buf, len);
	else if (umethod == GFX_UMETHOD_OR)
	{
		for (gfx_size_t i = 0; i < len; i++)
			*(gfx->buffer + (start_pos + i)) |= *(buf + i);
	}
	else return GFX_FAILED;

	return GFX_OK;
}

void GFX_init(GFX* gfx, char* lcd_buffer, gfx_size_t width, gfx_size_t height)
{
	if(gfx && lcd_buffer)
	{
		gfx->buffer = lcd_buffer;
		memset(gfx->buffer, 0, height * width);
		memset(&gfx->cursor, 0, sizeof(GFX_CURSOR));
		gfx->buffer_height = height;
		gfx->buffer_width = width;
	}
}

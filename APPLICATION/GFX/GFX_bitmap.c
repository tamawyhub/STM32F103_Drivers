#include "GFX.h"
#include "GFX_bitmap.h"

int GFX_draw_bitmap(const GFX_BITMAP* bitmap, const GFX_CURSOR* cursor)
{

	GFX_CURSOR l_cursor;
	if(bitmap == NULL)
	{
		return GFX_FAILED;
	}

	if(cursor == NULL)
	{
		GFX_get_pos(&l_cursor);
	}
	else
	{
		memcpy(&l_cursor, cursor, sizeof(GFX_CURSOR));
	}

	for (uint8_t i = 0; i < bitmap->bitmap_height; i++, l_cursor->ypos++)
		GFX_update_buff(bitmap->bitmap_data+i*bitmap_bitmap_width, &l_cursor, bitmap->bitmap_width);
	//GFX_update_disp();

	return GFX_OK;
}

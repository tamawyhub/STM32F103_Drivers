#include "OLED_font.h"
#include "OLED_ascii.h"
#include "OLED.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "../DEBUG/DEBUG.h"

static const FONT font_arr[] = 
{
#if OLED_FONT_USE_DEFAULT_5X7 == 1
	{
		sizeof(font_default_5x7),
		1, 1,
		font_default_5x7_char_size,
		font_default_5x7
	},
#endif

#if OLED_FONT_USE_DEFAULT_6X7 == 1
	{
		sizeof(font_default_6x7),
		1, 1,
		font_default_6x7_char_size,
		font_default_6x7
	},
#endif
#if OLED_FONT_USE_ARIAL_14 == 1
	{
		sizeof(font_arial_14),
		0, 2,
		font_arial_14_char_size,
		font_arial_14
	},
#endif
#if OLED_FONT_USE_IAIN_5X7 == 1
	{
		sizeof(font_iain_5x7),
		0, 1,
		font_iain_5x7_char_size,
		font_iain_5x7
	},
#endif
#if OLED_FONT_USE_SYSTEM_5X7 == 1
	{
		sizeof(font_system_5x7),
		1, 1,
		font_system_5x7_char_size,
		font_system_5x7
	},
#endif
#if OLED_FONT_USE_STANG_5X7 == 1
	{
		sizeof(font_stang_5x7),
		1, 1,
		font_stang_5x7_char_size,
		font_stang_5x7
	},
#endif
#if OLED_FONT_USE_WENDY_3X5 == 1
	{
		sizeof(font_wendy_3x5),
		1, 1,
		font_wendy_3x5_char_size,
		font_wendy_3x5
	},
#endif
#if OLED_FONT_USE_CP437_8X8 == 1
	{
		sizeof(font_cp437_8x8),
		1, 1,
		font_cp437_8x8_char_size,
		font_cp437_8x8
	},
#endif
#if OLED_FONT_USE_FONT_8X8 == 1
	{
		sizeof(font_font_8x8),
		1, 1,
		font_font_8x8_char_size,
		font_font_8x8
	},
#endif
#if OLED_FONT_USE_FIXED_BOLD == 1
	{
		sizeof(font_fixed_bold),
		1, 2,
		font_fixed_bold_char_size,
		font_fixed_bold
	},
#endif
#if OLED_FONT_USE_TIMES_NEW_ROMAN_ITALIC == 1
	{
		sizeof(font_times_new_roman_italic),
		0, 2,
		font_times_new_roman_italic_char_size,
		font_times_new_roman_italic
	},
#endif
#if OLED_FONT_USE_COOPER_21 == 1
	{
		sizeof(font_cooper_21),
		0, 3,
		font_cooper_21_char_size,
		font_cooper_21
	},
#endif
};

static int OLED_find_var_size_char_indx(const FONT* font, uint8_t ch)
{
	uint16_t indx;
	const uint8_t* ch_size;

	if(font == NULL)
	{
		return OLED_FAILED;
	}

	indx = 0;
	ch = ch - 32;
	ch_size = font->font_char_size;
	for(uint16_t i = 0; i < ch && indx < font->font_data_size; i++)
	{
		indx += ch_size[i];
	}

	return indx;
}

static int OLED_putchar(uint8_t font_indx, uint8_t ch)
{
	uint8_t ch_size;
	uint8_t ch_width;
	uint16_t ch_indx;
	OLED_CURSOR l_cursor;
	const FONT* l_font;
	uint8_t reset_cursor;
	
	if(font_indx >= FONTS_USED)
	{
		return OLED_FAILED;
	}

	l_font = &font_arr[font_indx];
	ch_size = l_font->font_char_size[ch - 32];
	ch_width = ch_size / l_font->font_char_height;

	if(ch == '\n')
	{
		OLED_get_pos(&l_cursor);
		l_cursor.ypos += l_font->font_char_height;
		if(OLED_check_boundaries(&l_cursor) == OLED_LINE_OUT)
		{
			l_cursor.ypos = 0;
		}
		return OLED_set_pos(&l_cursor);
	}
	if(ch == '\r')
	{
		OLED_get_pos(&l_cursor);
		l_cursor.xpos = 0;
		return OLED_set_pos(&l_cursor);
	}	
	if(ch == '\t')
	{
		OLED_puts(font_indx, "    ");
		return OLED_OK;
	}

	if(l_font->font_char_fixed_size)
	{
		ch_indx = (ch - 32) * ch_size;
	}
	else
	{
		ch_indx = OLED_find_var_size_char_indx(l_font, ch);
	}

	OLED_get_pos(&l_cursor);
	l_cursor.xpos += ch_width;
	switch(OLED_check_boundaries(&l_cursor))
	{
		case OLED_IN_BOUNDARY:
			reset_cursor = 1;
			break;
		case OLED_COL_OUT:
			l_cursor.xpos = 0;
			l_cursor.ypos += l_font->font_char_height;

			if(OLED_check_boundaries(&l_cursor) == OLED_LINE_OUT)
			{
				l_cursor.ypos = 0;
			}
			reset_cursor = 0;
			break;
		default:
			return OLED_FAILED;
	}
	
	if(reset_cursor)
	{
		OLED_get_pos(&l_cursor);
	}
	for(uint8_t i = 0; i < l_font->font_char_height; i++)
	{
		l_cursor.ypos += i;
		ch_indx += (i * ch_width);
		OLED_update_buff(&(l_font->font_data[ch_indx]), &l_cursor, ch_width);
		l_cursor.ypos -= i;
	}
	
	l_cursor.xpos += ch_width;
	if(OLED_set_pos(&l_cursor) != OLED_OK)
	{
		return OLED_FAILED;
	}

	return OLED_OK;
}

int OLED_putc(uint8_t font_indx, char ch)
{
	if(OLED_putchar(font_indx, (uint8_t) ch) != OLED_OK)
	{
		return OLED_FAILED;
	}

	return OLED_update_disp();
}

int OLED_puts(uint8_t font_indx, const char* str)
{
	int l_ret;
	if(str == NULL)
	{
		return OLED_FAILED;
	}

	while(*str)
	{
		l_ret = OLED_putchar(font_indx, (uint8_t) *str);
		if(l_ret != OLED_OK)
		{
			return OLED_FAILED;
		}
		str++;
	}

	return OLED_update_disp();
}

int OLED_draw_bitmap(const OLED_BITMAP* bitmap, const OLED_CURSOR* cursor)
{

	OLED_CURSOR l_cursor;
	if(bitmap == NULL)
	{
		return OLED_FAILED;
	}

	if(cursor == NULL)
	{
		OLED_get_pos(&l_cursor);
	}
	else
	{
		memcpy(&l_cursor, cursor, sizeof(OLED_CURSOR));
	}

	OLED_update_buff(bitmap->bitmap_data, &l_cursor, (uint16_t) bitmap->bitmap_height * bitmap->bitmap_width);
	OLED_update_disp();

	return OLED_OK;
}

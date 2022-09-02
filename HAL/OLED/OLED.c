#include "OLED.h"
#include "SSD1306/SSD1306_interface.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>


static uint8_t oled_buff[OLED_BUFF_SIZE];
static OLED_CURSOR oled_cursor;

int OLED_update_disp(void)
{
	return SSD1306_write_data(oled_buff, OLED_BUFF_SIZE);
}

int OLED_clear_disp(void)
{

	memset(oled_buff, 0, OLED_BUFF_SIZE);

	return OLED_update_disp();
}

int OLED_set_pos(const OLED_CURSOR* cursor)
{
	int l_ret = -1;

	if((cursor->xpos < OLED_WIDTH) && (cursor->ypos < OLED_HEIGHT))
	{
		memcpy(&oled_cursor, &cursor, sizeof(OLED_CURSOR));
		l_ret = 0;
	}

	return l_ret;
}

void OLED_get_pos(OLED_CURSOR* cursor)
{
	if(cursor != NULL)
	{
		memcpy(&cursor, &oled_cursor, sizeof(OLED_CURSOR));
	}
}

int OLED_init(void)
{
	int l_ret;
	SSD1306_CONFIG oled_driver;

	oled_driver.ssd1306_height = OLED_HEIGHT;
	oled_driver.ssd1306_width = OLED_WIDTH;
#if SSD1306_INTERFACE_MODE == SSD1306_USE_I2C
	oled_driver.ssd1306_addr = OLED_ADDR;
#endif
	l_ret = SSD1306_init(&oled_driver);
	if(l_ret != SSD1306_OK)
	{
		return l_ret;
	}

	l_ret = SSD1306_flip_vertically(OLED_FLIP_VERTICALLY);
	if(l_ret != SSD1306_OK)
	{
		return l_ret;
	}
		
	l_ret = SSD1306_flip_horizontally(OLED_FLIP_HORIZONTALLY);
	if(l_ret != SSD1306_OK)
	{
		return l_ret;
	}

	l_ret = OLED_clear_disp();
	if(l_ret != SSD1306_OK)
	{
		return l_ret;
	}

	oled_cursor.xpos = 0;
	oled_cursor.ypos = 0;

	return 0;
}

int OLED_check_line_boundary(const OLED_CURSOR* cursor)
{
	return (cursor->xpos < OLED_COLS) ? OLED_IN_BOUNDARY : OLED_COL_OUT;
}



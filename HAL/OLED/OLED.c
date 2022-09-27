#include "OLED.h"
#include "SSD1306/SSD1306_interface.h"
#include "SSD1306/SSD1306_config.h"

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
	memset(&oled_cursor, 0, sizeof(OLED_CURSOR));

	return OLED_update_disp();
}

int OLED_set_pos(const OLED_CURSOR* cursor)
{
	int l_ret = OLED_FAILED;

	if((cursor->xpos < OLED_COLS) && (cursor->ypos < OLED_LINES))
	{
		memcpy(&oled_cursor, cursor, sizeof(OLED_CURSOR));
		l_ret = OLED_OK;
	}

	return l_ret;
}

void OLED_get_pos(OLED_CURSOR* cursor)
{
	if(cursor != NULL)
	{
		memcpy(cursor, &oled_cursor, sizeof(OLED_CURSOR));
	}
}

int OLED_check_boundaries(const OLED_CURSOR* cursor)
{
	if(cursor == NULL)
	{
		return OLED_FAILED;
	}

	if(cursor->xpos >= OLED_COLS - 5)
	{
		return OLED_COL_OUT;
	}

	if(cursor->ypos >= OLED_LINES)
	{
		return OLED_LINE_OUT;
	}

	return OLED_IN_BOUNDARY;
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

	return OLED_OK;
}

uint8_t* OLED_get_buff(void)
{
	return oled_buff;
}

int OLED_update_buff(const uint8_t* copy_buff, const OLED_CURSOR* cursor, uint16_t size)
{
	uint16_t start_pos;
	uint16_t end_pos;

	if(copy_buff == NULL || cursor == NULL || size == 0)
	{
		return OLED_FAILED;
	}
	
	start_pos = cursor->ypos * OLED_COLS + cursor->xpos;
	end_pos = start_pos + size;

	if(end_pos > OLED_BUFF_SIZE)
	{
		size = OLED_BUFF_SIZE - start_pos;
	}
	
	memcpy(oled_buff + start_pos, copy_buff, size);

	return OLED_FAILED;
}

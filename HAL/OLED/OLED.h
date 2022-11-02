#ifndef _OLED_H
#define _OLED_H

#if 0
#include "OLED/OLED_config.h"
#include "../HAL/SSD1306/SSD1306_interface.h"

#include <stdint.h>

#define OLED_COLS	OLED_WIDTH
#define OLED_LINES	(OLED_HEIGHT >> 3)
#define OLED_BUFF_SIZE	(OLED_LINES * OLED_COLS)


typedef struct oled_cursor
{
	uint16_t xpos;
       	uint16_t ypos;
} OLED_CURSOR;

typedef enum oled_erros
{
	OLED_OK,
	OLED_FAILED,
	OLED_IN_BOUNDARY,
	OLED_COL_OUT,
	OLED_LINE_OUT,
} OLED_ERRORS;


int OLED_update_disp(void);
int OLED_clear_disp(void);
int OLED_set_pos(const OLED_CURSOR* cursor);
void OLED_get_pos(OLED_CURSOR* cursor);
int OLED_check_boundaries(const OLED_CURSOR* cursor);
int OLED_init(const I2C_CONFIG* i2c_config);
uint8_t* OLED_get_buff(void);
int OLED_update_buff(const uint8_t* copy_buff, const OLED_CURSOR* cursor, uint16_t size);

/* Functions in OLED_font.c */
int OLED_putc(uint8_t font_indx, char ch);
int OLED_puts(uint8_t font_indx, const char* str);
int OLED_draw_bitmap(const OLED_BITMAP* bitmap, const OLED_CURSOR* cursor);

#endif
#endif
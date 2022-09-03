#ifndef _OLED_H
#define _OLED_H


#include "OLED/OLED_config.h"

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

typedef enum e_fonts
{
#if OLED_FONT_USE_DEFAULT_5X7 == 1
        DEFAULT_5X7,
#endif

#if OLED_FONT_USE_DEFAULT_6X7 == 1
        DEFAULT_6X7,
#endif
#if OLED_FONT_USE_ARIAL_14 == 1
	ARIAL_14,
#endif
#if OLED_FONT_USE_IAIN_5X7 == 1
	IAIN_5X7,
#endif
#if OLED_FONT_USE_SYSTEM_5X7 == 1
	SYSTEM_5X7,
#endif
#if OLED_FONT_USE_STANG_5X7 == 1
	STANG_5X7,
#endif
#if OLED_FONT_USE_WENDY_3X5 == 1
	WENDY_3X5,
#endif
#if OLED_FONT_USE_CP437_8X8 == 1
	CP437_8X8,
#endif
#if OLED_FONT_USE_FONT_8X8 == 1
	FONT_8X8,
#endif
        FONTS_USED
} E_FONTS;


int OLED_update_disp(void);
int OLED_clear_disp(void);
int OLED_set_pos(const OLED_CURSOR* cursor);
void OLED_get_pos(OLED_CURSOR* cursor);
int OLED_check_boundaries(const OLED_CURSOR* cursor);
int OLED_init(void);
uint8_t* OLED_get_buff(void);
int OLED_update_buff(const uint8_t* copy_buff, const OLED_CURSOR* cursor, uint16_t size);

/* Functions in OLED_font.c */
int OLED_putc(uint8_t font_indx, char ch);
int OLED_puts(uint8_t font_indx, const char* str);
#endif

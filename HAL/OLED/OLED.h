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
} OLED_ERRORS;

int OLED_update_disp(void);
int OLED_clear_disp(void);
int OLED_set_pos(const OLED_CURSOR* cursor);
void OLED_get_pos(OLED_CURSOR* cursor);
int OLED_init(void);

#endif

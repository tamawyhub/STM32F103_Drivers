#ifndef _SSD1306_PRIVATE_H
#define _SSD1306_PRIVATE_H

#include <stdint.h>

#define SSD1306_MAX_CMD_LEN 3

#define SSD1306_SEGMENTS 128
#define SSD1306_PAGES 8

#define SSD1306_PIXELS (SSD1306_SEGMENTS * SSD1306_PAGES)

#define SSD1306_USE_I2C	1
#define SSD1306_USE_SPI 2



typedef struct command_t
{
	uint8_t cmd_len;
	uint8_t cmd_buf[SSD1306_MAX_CMD_LEN];
} SSD1306_COMMAND;

#endif

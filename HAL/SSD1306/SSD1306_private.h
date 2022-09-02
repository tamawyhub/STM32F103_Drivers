#ifndef _SSD1306_PRIVATE_H
#define _SSD1306_PRIVATE_H

#define SSD1306_MAX_CMD_LEN 3

#define SSD1306_USE_I2C	1
#define SSD1306_USE_SPI 2


typedef struct command_t
{
	uint8_t cmd_len;
	uint8_t cmd_buf[SSD1306_MAX_CMD_LEN];
} COMMAND;

#endif

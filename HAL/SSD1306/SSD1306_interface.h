#ifndef _SSD1306_INTERFACE_H
#define _SSD1306_INTERFACE_H

#include <stdint.h>

#define SSD1306_HEIGHT_64 64
#define SSD1306_HEIGHT_32 32

typedef struct ssd1306_config
{
	uint8_t ssd1306_addr;
	uint8_t ssd1306_height;
	uint8_t ssd1306_width;
} SSD1306_CONFIG;

typedef enum ssd1306_errors
{
	SSD1306_OK = 0,
	SSD1306_INIT_FAILED,
	SSD1306_BAD_DIMENSIONS,
	SSD1306_NOT_FOUND,
	SSD1306_BUF_ERROR,
	SSD1306_CMD_FAILED,
	SSD1306_CMD_INVALID,
	SSD1306_DATA_FAILED,
} SSD1306_ERRORS;

typedef enum ssd1306_addr_modes
{
	SSD1306_HORIZONTAL_ADDR_MODE = 0,
	SSD1306_VERTICAL_ADDR_MODE,
	SSD1306_PAGE_ADDR_MODE,
	SSD1306_INVALID_ADDR_MODE,
} SSD1306_ADDR_MODES;

typedef enum ssd1306_normal_inverse
{
	SSD1306_NORMAL_MODE = 0,
	SSD1306_INVERSE_MODE
} SSD1306_NORMAL_INVERSE_MODES;

int SSD1306_init(const SSD1306_CONFIG* ssd1306_config);
int SSD1306_set_contrast(uint8_t contrast);
int SSD1306_set_mux_ratio(uint8_t ratio);
int SSD1306_set_seq_com(void);
int SSD1306_set_charge_pump_state(uint8_t state);
int SSD1306_set_disp_clock(uint8_t div_ratio, uint8_t freq);
int SSD1306_deactivate_scroll(void);
int SSD1306_set_page_addr_mode_col_start(uint8_t start_addr);
int SSD1306_set_addressing_mode(uint8_t mode);
int SSD1306_set_col_addr(uint8_t col_start_addr, uint8_t col_end_addr);
int SSD1306_set_page_addr(uint8_t start_page, uint8_t end_page);
int SSD1306_use_ram_content(uint8_t mode);
int SSD1306_set_normal_inverse(uint8_t mode);
int SSD1306_disp_on(void);
int SSD1306_disp_off(void);
int SSD1306_flip_vertically(uint8_t flip);
int SSD1306_flip_horizontally(uint8_t flip);
int SSD1306_write_data(const char* data, uint32_t data_size);

#endif

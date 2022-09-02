#include "SSD1306_interface.h"
#include "SSD1306_private.h"
#include "SSD1306_config.h"

#include "../MCAL/I2C/I2C_interface.h"
#include "DEBUG/DEBUG.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

SSD1306_CONFIG ssd1306_config;

#if SSD1306_INTERFACE_MODE == SSD1306_USE_I2C

I2C_CONFIG ssd1306_i2c_config;

static int SSD1306_write_command(SSD1306_COMMAND* cmd)
{
	uint8_t l_cmd_buf[SSD1306_MAX_CMD_LEN + 1];
	int l_ret;

	if(cmd == NULL)
	{
		return SSD1306_BUF_ERROR;
	}

	if(cmd->cmd_len > SSD1306_MAX_CMD_LEN)
	{
		return SSD1306_CMD_FAILED;
	}
	
	l_cmd_buf[0] = 0x00;

	memcpy(l_cmd_buf + 1, cmd->cmd_buf, cmd->cmd_len);

	l_ret = I2C_master_write(&ssd1306_i2c_config, ssd1306_config.ssd1306_addr, l_cmd_buf, cmd->cmd_len + 1, NULL);

	if(l_ret != I2C_OK)
	{
		return SSD1306_CMD_FAILED;
	}

	return SSD1306_OK;
}

int SSD1306_write_data(const char* data, uint32_t data_size)
{
	char l_buff[SSD1306_PIXELS + 1];
	int l_ret;

	if(data == NULL)
	{
		return SSD1306_BUF_ERROR;
	}
	
	if(data_size > SSD1306_PIXELS)
	{
		data_size = SSD1306_PIXELS;	
	}

	l_buff[0] = 0x40;
	memcpy(l_buff + 1, data, data_size);

	l_ret = I2C_master_write(&ssd1306_i2c_config, ssd1306_config.ssd1306_addr, l_buff, data_size + 1, NULL);

	return (l_ret == I2C_OK) ? SSD1306_OK : SSD1306_DATA_FAILED;
}

int SSD1306_init(const SSD1306_CONFIG* p_ssd1306_config)
{
	int l_ret;

	if(p_ssd1306_config == NULL)
	{
		return SSD1306_INIT_FAILED;
	}

	if(p_ssd1306_config->ssd1306_height != SSD1306_HEIGHT_64 && p_ssd1306_config->ssd1306_height != SSD1306_HEIGHT_32)
	{
		return SSD1306_BAD_DIMENSIONS;
	}

	ssd1306_i2c_config.i2c_id = SSD1306_I2C_PORT;
	ssd1306_i2c_config.apb_freq = 8;
	ssd1306_i2c_config.ccr = 0x28;
	ssd1306_i2c_config.trise = 0x09;

	l_ret = I2C_init(&ssd1306_i2c_config);
	if(l_ret != I2C_OK)
	{
		return SSD1306_INIT_FAILED;
	}

	/* Check device */
	l_ret = I2C_master_transmit(&ssd1306_i2c_config, p_ssd1306_config->ssd1306_addr, 0x55);
	if(l_ret != I2C_OK)
	{
		return SSD1306_NOT_FOUND;
	}
	
	memcpy(&ssd1306_config, p_ssd1306_config, sizeof(SSD1306_CONFIG));

	/* Init commands */

	l_ret = 0;
	l_ret |= SSD1306_set_mux_ratio(ssd1306_config.ssd1306_height - 1);
	l_ret |= SSD1306_set_seq_com();
	l_ret |= SSD1306_set_contrast(0xFF);
	l_ret |= SSD1306_set_disp_clock(0x00, 0x0f);
	l_ret |= SSD1306_set_charge_pump_state(1);
	l_ret |= SSD1306_deactivate_scroll();
	l_ret |= SSD1306_set_addressing_mode(SSD1306_HORIZONTAL_ADDR_MODE);
	l_ret |= SSD1306_set_col_addr(0x00, ssd1306_config.ssd1306_width - 1);
	l_ret |= SSD1306_set_page_addr(0x00, (ssd1306_config.ssd1306_height >> 3) - 1);
	l_ret |= SSD1306_set_normal_inverse(SSD1306_NORMAL_MODE);
	l_ret |= SSD1306_use_ram_content(1);
	l_ret |= SSD1306_disp_on();

	if(l_ret != SSD1306_OK)
	{
		return SSD1306_INIT_FAILED;
	}

	return SSD1306_OK;
}

#elif SSD1306_INTERFACE_MODE == SSD1306_USE_SPI
/* TODO */

#else
#error "You should define SSD1306_USE_I2C or SSD1306_USE_SPI"
#endif

int SSD1306_set_contrast(uint8_t contrast)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0x81;
	cmd.cmd_buf[1] = contrast;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_mux_ratio(uint8_t ratio)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0xA8;
	cmd.cmd_buf[1] = ratio & 0x3F;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_seq_com(void)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0xDA;
	cmd.cmd_buf[1] = 0x02;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_charge_pump_state(uint8_t state)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0x8D;
	cmd.cmd_buf[1] = 0x10 | ((state & 0x01) << 2);

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_disp_clock(uint8_t div_ratio, uint8_t freq)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0xD5;
	cmd.cmd_buf[1] = ((freq & 0x0F) << 4) | (div_ratio & 0x0F);

	return SSD1306_write_command(&cmd);
}

int SSD1306_deactivate_scroll(void)
{
	SSD1306_COMMAND cmd;
	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0x2E;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_page_addr_mode_col_start(uint8_t start_addr)
{
	int l_ret;
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0x00 | (start_addr & 0x0F);

	l_ret = SSD1306_write_command(&cmd);

	cmd.cmd_buf[0] = 0x10 | ((start_addr >> 4) & 0x0F);
	
	return (l_ret == SSD1306_OK) && (SSD1306_write_command(&cmd) == SSD1306_OK);
}

int SSD1306_set_addressing_mode(uint8_t mode)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 2;
	cmd.cmd_buf[0] = 0x20;
	if((mode & 0x03) < SSD1306_INVALID_ADDR_MODE)
		cmd.cmd_buf[1] = mode & 0x03;
	else
		return SSD1306_CMD_INVALID;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_col_addr(uint8_t col_start_addr, uint8_t col_end_addr)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 3;
	cmd.cmd_buf[0] = 0x21;
	cmd.cmd_buf[1] = col_start_addr;
	cmd.cmd_buf[2] = col_end_addr;

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_page_addr(uint8_t start_page, uint8_t end_page)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 3;
	cmd.cmd_buf[0] = 0x22;
	cmd.cmd_buf[1] = start_page & 0x07;
	cmd.cmd_buf[2] = end_page & 0x07;

	return SSD1306_write_command(&cmd);
}

int SSD1306_use_ram_content(uint8_t mode)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0xA4 | (!mode & 0x01);

	return SSD1306_write_command(&cmd);
}

int SSD1306_set_normal_inverse(uint8_t mode)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0xA6 | (mode & 0x01);

	return SSD1306_write_command(&cmd);
}


int SSD1306_disp_on(void)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0xAF;

	return SSD1306_write_command(&cmd);
}

int SSD1306_disp_off(void)
{
	SSD1306_COMMAND cmd;

	cmd.cmd_len = 1;
	cmd.cmd_buf[0] = 0xAE;

	return SSD1306_write_command(&cmd);
}




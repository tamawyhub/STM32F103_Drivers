#ifndef __PCD8544_H
#define __PCD8544_H

#include <stdint.h>

#define PCD8544_ROWS        6
#define PCD8544_COLS        84

/* Disp commands */
#define PCD8544_FUNC_SET    0x20
#define PCD8544_DISP_CTRL   0x08
#define PCD8544_SET_Y       0x40
#define PCD8544_SET_X       0x80
#define PCD8544_TEMP_CTRL   0x04
#define PCD8544_BIAS_SYS    0x10
#define PCD8544_SET_VOP     0x80

/*
* 0- RES = {GPIOA, PIN6} -> Example and can be assigned to any GPIO
* 1- CE
* 2- D/C
* 3- DIN
* 4- CLK
*/

typedef uint8_t (*PCD8544_PINS) [2];

typedef struct pcd8544_t
{
    PCD8544_PINS pins;
    uint8_t clock_speed;
    uint8_t spi_itf;
    uint8_t addressing_mode;
    uint8_t mode;
    uint8_t temp_coef;
    uint8_t bias;
    uint8_t vop;
} PCD8544;

enum pcd8544_error_r
{
    PCD8544_OK,
    PCD8544_FAILED
};

enum pcd8544_addressing_mode_t
{
    PCD8544_V_ADDR,
    PCD8544_H_ADDR
};

enum pcd8544_disp_mode
{
    PCD8544_BLANK,
    PCD8544_NORMAL,
    PCD8544_ON,
    PCD8544_INVERSE
};

int PCD8544_init(const PCD8544* pcd8544);
int PCD8544_update(const PCD8544* pcd8544, char* buffer, uint16_t size);

#endif
#include "PCD8544.h"
/* LL drivers*/
#include "../../MCAL/SPI/SPI_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

/* C libraries */
#include <stdint.h>

/* Private functions */
static uint8_t PCD8544_function_set(uint8_t pupd, uint8_t mode, uint8_t extended);
static uint8_t PCD8544_disp_control(uint8_t mode);
static uint8_t PCD8544_set_y(uint8_t addr);
static uint8_t PCD8544_set_x(uint8_t addr);
static uint8_t PCD8544_temp_control(uint8_t temp);
static uint8_t PCD8544_set_bias(uint8_t bias);
static uint8_t PCD8544_set_vop(uint8_t vop);
static void PCD8544_send_command(const PCD8544* pcd8544, uint8_t cmd);
static void PCD8544_send_data(const PCD8544* pcd8544, uint8_t data);
static void PCD8544_reset_set(const PCD8544* pcd8544);
static void PCD8544_reset_clear(const PCD8544* pcd8544);
static void PCD8544_chip_enable_set(const PCD8544* pcd8544);
static void PCD8544_chip_enable_clear(const PCD8544* pcd8544);

int PCD8544_init(const PCD8544* pcd8544)
{
    int l_ret = PCD8544_OK;
    uint8_t cmd;

    if(pcd8544)
    {
        /* RES, CE, D/C, DIN, SCK */
        GPIO_voidSetPinMode(pcd8544->pins[0][0], pcd8544->pins[0][1], OUTPUT_10MHZ_PUSH_PULL);
        GPIO_voidSetPinMode(pcd8544->pins[1][0], pcd8544->pins[1][1], OUTPUT_10MHZ_PUSH_PULL);
        GPIO_voidSetPinMode(pcd8544->pins[2][0], pcd8544->pins[2][1], OUTPUT_10MHZ_PUSH_PULL);
        GPIO_voidSetPinMode(pcd8544->pins[3][0], pcd8544->pins[3][1], OUTPUT_10MHZ_AF_PUSH_PULL);
        GPIO_voidSetPinMode(pcd8544->pins[4][0], pcd8544->pins[4][1], OUTPUT_10MHZ_AF_PUSH_PULL);

        if(pcd8544->spi_itf == SPI1)
        {
            RCC_voidEnableClock(RCC_APB2, 12);
        }
        else if(pcd8544->spi_itf == SPI2)
        {
            RCC_voidEnableClock(RCC_APB1, 14);
        }
        else
        {
            l_ret = PCD8544_FAILED;
        }

        /* Init SPI interface*/

        SPI_voidInitMaster(pcd8544->spi_itf, SPI_PSC_DIV_8, SPI_CAPTURE_2ND_EDGE, SPI_IDLE_HIGH,
            SPI_MSB_FIRST, SPI_FRAME_SIZE_8);

        PCD8544_reset_set(pcd8544);
        PCD8544_chip_enable_set(pcd8544);
        /* Send Init and Config commands */
        PCD8544_reset_clear(pcd8544);
        /* TODO delay */
        for(uint32_t i = 0; i < 100000; i++);
        PCD8544_reset_set(pcd8544);
        /* Power Up */
        cmd = PCD8544_function_set(0, pcd8544->addressing_mode, 1);
        PCD8544_send_command(pcd8544, cmd);

        /* Temp. compensation*/
        cmd = PCD8544_temp_control(0x00);
        PCD8544_send_command(pcd8544, cmd);

        /* Set Bias */
        cmd = PCD8544_set_bias(4);  /* Mux 1:48 */
        PCD8544_send_command(pcd8544, cmd);

        /* Set Vlcd */
        cmd = PCD8544_set_vop(50);  /* 6.06v = 3.06 + Vop * 0.06 */
        PCD8544_send_command(pcd8544, cmd);

        /* Normal command (H = 0)*/
        cmd = PCD8544_function_set(0, pcd8544->addressing_mode, 0);
        PCD8544_send_command(pcd8544, cmd);

        /* Clear DDRAM */
        cmd = PCD8544_disp_control(PCD8544_BLANK);
        PCD8544_send_command(pcd8544, cmd);

        cmd = PCD8544_disp_control(pcd8544->mode);
        PCD8544_send_command(pcd8544, cmd);

        /* Set Y = 0, X = 0 */
        cmd = PCD8544_set_y(0);
        PCD8544_send_command(pcd8544, cmd);
        cmd = PCD8544_set_x(0);
        PCD8544_send_command(pcd8544, cmd);
    }
    else
    {
        l_ret = PCD8544_FAILED;
    }

    return l_ret;
}

int PCD8544_update(const PCD8544* pcd8544, char* buffer, uint16_t size)
{
    int l_ret = PCD8544_FAILED;
    
    if(pcd8544)
    {
        for(uint16_t idx = 0; idx < size; idx++)
        {
            PCD8544_send_data(pcd8544, buffer[idx]);
        }

        l_ret = PCD8544_OK;
    }

    return l_ret;
}
uint8_t PCD8544_function_set(uint8_t pupd, uint8_t mode, uint8_t extended)
{
    uint8_t cmd = PCD8544_FUNC_SET;

    cmd |= (pupd << 2) | (mode << 1) | (extended);

    return cmd;
}

static uint8_t PCD8544_disp_control(uint8_t mode)
{
    uint8_t cmd = PCD8544_DISP_CTRL;

    switch(mode)
    {
        case PCD8544_BLANK:
            break;
        case PCD8544_NORMAL:
            cmd |= (1 << 2);
            break;
        case PCD8544_ON:
            cmd |= 0x01;
            break;
        case PCD8544_INVERSE:
            cmd |= (1 << 2) | 0x01;
            break;
        default:
            cmd = 0x00;
            break;
    }

    return cmd;
}

static uint8_t PCD8544_set_y(uint8_t addr)
{
    uint8_t cmd = 0x00;

    if(addr < PCD8544_ROWS)
    {
        cmd = PCD8544_SET_Y | addr;
    }

    return cmd;
}

static uint8_t PCD8544_set_x(uint8_t addr)
{
    uint8_t cmd = 0x00;

    if(addr < PCD8544_COLS)
    {
        cmd = PCD8544_SET_X | addr;
    }

    return cmd;
}

static uint8_t PCD8544_temp_control(uint8_t temp)
{
    uint8_t cmd = PCD8544_TEMP_CTRL;
    if(temp <= 3)
    {
        cmd |= temp;
    }

    return cmd;
}

static uint8_t PCD8544_set_bias(uint8_t bias)
{
    uint8_t cmd = PCD8544_BIAS_SYS;

    if(bias <= 7)
    {
        cmd |= (~bias);
    }

    return cmd;
}

static uint8_t PCD8544_set_vop(uint8_t vop)
{
    uint8_t cmd = PCD8544_SET_VOP;

    cmd |= vop;

    return cmd;
}

static void PCD8544_send_command(const PCD8544* pcd8544, uint8_t cmd)
{
    if(pcd8544)
    {
        GPIO_voidClearPinAtomic(pcd8544->pins[2][0], pcd8544->pins[2][1]);
        PCD8544_chip_enable_clear(pcd8544);
        SPI_voidTransmitData(pcd8544->spi_itf, cmd, 1);
        PCD8544_chip_enable_set(pcd8544);
        GPIO_voidSetPinAtomic(pcd8544->pins[2][0], pcd8544->pins[2][1]);
    }
}

static void PCD8544_send_data(const PCD8544* pcd8544, uint8_t data)
{
    if(pcd8544)
    {
        GPIO_voidSetPinAtomic(pcd8544->pins[2][0], pcd8544->pins[2][1]);
        PCD8544_chip_enable_clear(pcd8544);
        SPI_voidTransmitData(pcd8544->spi_itf, data, 1);
        PCD8544_chip_enable_set(pcd8544);
    }
}

static void PCD8544_reset_set(const PCD8544* pcd8544)
{
    if(pcd8544)
    {
        GPIO_voidSetPinAtomic(pcd8544->pins[0][0], pcd8544->pins[0][1]);
    }
}

static void PCD8544_reset_clear(const PCD8544* pcd8544)
{
    if(pcd8544)
    {
        GPIO_voidClearPinAtomic(pcd8544->pins[0][0], pcd8544->pins[0][1]);
    }
}


static void PCD8544_chip_enable_set(const PCD8544* pcd8544)
{
    if(pcd8544)
    {
        GPIO_voidSetPinAtomic(pcd8544->pins[1][0], pcd8544->pins[1][1]);
    }
}

static void PCD8544_chip_enable_clear(const PCD8544* pcd8544)
{
    if(pcd8544)
    {
        GPIO_voidClearPinAtomic(pcd8544->pins[1][0], pcd8544->pins[1][1]);
    }
}
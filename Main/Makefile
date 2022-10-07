######################################################################
#  Project
######################################################################


target = main.bin
SRCFILES = main.c ../MCAL/RCC/RCC_program.c ../MCAL/GPIO/GPIO_program.c ../MCAL/NVIC/NVIC_program.c ../MCAL/EXTI/EXTI_program.c ../MCAL/SYSTICK/SYSTICK_program.c ../MCAL/DMA/DMA_program.c ../HAL/SEVEN_SEGMENT/SEVEN_SEGMENT_program.c ../MCAL/TIMx/TIMx_program.c ../MCAL/SPI/SPI_program.c ../MCAL/USART/USART_program.c ../MCAL/I2C/I2C_program.c ../HAL/DEBUG/DEBUG_program.c ../HAL/SSD1306/SSD1306_program.c ../HAL/OLED/OLED.c ../HAL/OLED/OLED_font.c \
	   ../MCAL/PWR/PWR_program.c  ../MCAL/BKP/BKP_program.c ../MCAL/RTC/RTC_program.c ../HAL/MAX30100/MAX30100_ll.c \
	   ../HAL/MAX30100/MAX30100_queue.c ../HAL/MAX30100/MAX30100.c

INCLUDE = ../include
LOAD_SCRIPT = ../stm32f103c8t6.ld

ifeq ($(DBG), 1)
DBGFLAG = -DDEBUG
endif

include ../Makefile.incl

/*
 * Autthor: Mohammed Hisham
 * Date: 6 March 2020
 * Version: 1.0
 */

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H


#define STK_BASE	0xE000E010	

#define STK_CTRL	(*(volatile uint32_t*) (STK_BASE + 0x00))
#define STK_LOAD	(*(volatile uint32_t*) (STK_BASE + 0x04))
#define STK_VAL		(*(volatile uint32_t*) (STK_BASE + 0x08))

#endif

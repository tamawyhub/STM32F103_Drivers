/*
 * Author:	Mohammed Hisham
 * Date:	11 FEB	2022
 * Version:	1.0
 */

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR, BIT) ((VAR) |= (1<<(BIT)))
#define CLR_BIT(VAR, BIT) ((VAR) &= ~(1<<(BIT)))
#define TOGGLE_BIT(VAR, BIT) ((VAR) ^= (1<<(BIT)))
#define GET_BIT(VAR, BIT) (((VAR) >> (BIT)) & 1)

#endif

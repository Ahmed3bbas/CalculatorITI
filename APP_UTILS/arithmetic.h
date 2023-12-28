/*
 * arithmetic.h
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */

#ifndef APP_UTILS_ARITHMETIC_H_
#define APP_UTILS_ARITHMETIC_H_

/* MACROS*/
/*------*/
#define EquationSize						16
#define Invalid 							0
#define NUM_OF_FLOATING 					100.0


/* USER-DEFINED */
/*--------------*/
typedef struct eq
{									/* Eample of INFIX */
	s32 equation[EquationSize];    /* Ex: [300, '+', 500]  */
	u8 	is_operator[EquationSize]; /* Ex: [0  ,  1  , 0  ] */
	u8  iterator;				   /* Ex:  0     1    2   *//* Counter incremented */
}equation_t;


/* FUNCTION DECLERATION*/
/*---------------------*/
equation_t Parse_from_infix_to_postfix(equation_t *InFixEq);
u8 solve_simp_arith_opr(num_t first_num, u8 op, num_t second_num, num_t *resukt);
s8 get_precedence(u8 operator);

#endif /* APP_UTILS_ARITHMETIC_H_ */

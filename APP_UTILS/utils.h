/*
 * utils.h
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */

#ifndef UTILS_H_
#define UTILS_H_

#define YES			1
#define NO			0
/* USER-DEFINED */
/*--------------*/
typedef struct Number
{
	s64 d_part; /*decimal*/
	s16 f_part; /*Floating*/
}num_t;


/* DECLARE GLOBAL VARIABLES*/
/*---------------------*/
extern s8 TopOfOperatingNumbers;

/* FUNCTION DECLERATION*/
/*---------------------*/
u8 push_operating_numbers(num_t *stack, u8 size, num_t data);
u8 pop_operating_numbers(num_t *stack, num_t *data);




#endif /* UTILS_H_ */

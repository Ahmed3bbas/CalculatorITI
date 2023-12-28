/*
 * stack_s32.h
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */

#ifndef LIBS_STACK_S32_H_
#define LIBS_STACK_S32_H_

/* DECLARE GLOBAL VARIABLES*/
/*---------------------*/
extern s8 top;

/* FUNCTION DECLERATION*/
/*---------------------*/
u8 push(s32 *stack, u8 size, s32 data);
u8 pop(s32 *stack, s32 *data);
u8 get_last_element(s32 *stack, s32 *data);

#endif /* LIBS_STACK_S32_H_ */

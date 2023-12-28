/*
 * stack_s32.c
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */
#include "std_data_types.h"
#include "BIT_MATH.h"

#include "stack_s32.h"

/* GLOBAL VARIABLES*/
/*---------------------*/
s8 top = -1;


u8 push(s32 *stack, u8 size, s32 data)
{
	if (top >= size)
		return NOK;
	else
		stack[++top] = data;
	return OK;
}

u8 pop(s32 *stack, s32 *data)
{
	if (top < 0 || data == NULL)
	{
		return NOK;
	}
	else
		*data = stack[top--];
	return OK;
}

u8 get_last_element(s32 *stack, s32 *data)
{
	if (top < 0 || data == NULL)
	{
		return NOK;
	}
	else
		*data = stack[top];
	return OK;
}

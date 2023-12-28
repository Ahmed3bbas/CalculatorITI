/*
 * utils.c
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */

/* Includes */
#include "../LIBS/std_data_types.h"
#include "../LIBS/BIT_MATH.h"

#include "utils.h"

/* GLOBAL VARIABLES*/
/*---------------------*/
s8 TopOfOperatingNumbers = -1;


u8 push_operating_numbers(num_t *stack, u8 size, num_t data)
{
	if (TopOfOperatingNumbers >= size)
		return NOK;
	else
	{
		TopOfOperatingNumbers++;
		stack[TopOfOperatingNumbers].d_part = data.d_part;
		stack[TopOfOperatingNumbers].f_part = data.f_part;
	}
	return OK;
}

u8 pop_operating_numbers(num_t *stack, num_t *data)
{
	if (TopOfOperatingNumbers < 0 || data == NULL)
	{
		return NOK;
	}
	else
	{
		data->d_part = stack[TopOfOperatingNumbers].d_part;
		data->f_part = stack[TopOfOperatingNumbers].f_part;
		TopOfOperatingNumbers--;
	}
	return OK;
}


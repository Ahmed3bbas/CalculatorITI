/*
 * arithmetic.c
 *
 *  Created on: Dec 27, 2023
 *      Author: engah
 */

#include "../LIBS/std_data_types.h"
#include "../LIBS/BIT_MATH.h"
#include "../LIBS/stack_s32.h"
#include "utils.h"

#include "arithmetic.h"
/*
 * Parse_from_infix_to_postfix - convert equation from infix to postfix
 * @InFixEq: it a pointer to equation_t which have infix equation array + is_operator + iterator
 *
 * Return: struct which is equation_t of PostFix after conversation
 * Example :
 * 			input: InFixEq
 * 			{
 * 				equation	:   [15, '+', 13, '*' , 10]
 * 				is_operator	:	[0    1    0   1     0]
 * 				iterator	:	 5
 * 			}
 * 			Output: Postfix
 * 			{
 * 				equation	:   [15, 13, 10,  '*' , '+']
 * 				is_operator	:	[0   0   0     1     1 ]
 * 				iterator	: 	5
 * 			}
 * */
equation_t Parse_from_infix_to_postfix(equation_t *InFixEq)
{
	u8 Local_u8Iterator;
	s8 Local_u8SubIterator;
	s32 operatorsStack[EquationSize];
	s32 Local_s32LastOp = 0;
	u8 op;
	equation_t PostFixEq;


	/*Parsing to convert from infix to postfix*/
	for (Local_u8Iterator = 0; Local_u8Iterator < InFixEq->iterator; Local_u8Iterator++)
	{
		if (InFixEq->is_operator[Local_u8Iterator] == 1)
		{
			/*Operator*/
			op = (u8)InFixEq->equation[Local_u8Iterator];

			/* if stack is empty push operator in stack to check precedence with next operator*/
			if (top < 0)
				push(operatorsStack, EquationSize, op);
			else
			{
				/*get last element in operator stack*/
				get_last_element(operatorsStack, &Local_s32LastOp);

				/*check current operator higher precedence than last element in stack*/
				if (get_precedence(op) > get_precedence(Local_s32LastOp))
				{
					/*if yes push to operator to stack*/
					push(operatorsStack, EquationSize, op);
				}
				else
				{
					/* if no, pop all operators in stack in postfix equation array*/
					/* popping operator with higher precedence firstly */
					Local_u8SubIterator = top;
					do
					{
						pop(operatorsStack, &Local_s32LastOp);
						PostFixEq.equation[PostFixEq.iterator] = Local_s32LastOp;

						/* this is operator not a number */
						PostFixEq.is_operator[PostFixEq.iterator] = 1;
						PostFixEq.iterator++;
						--Local_u8SubIterator;
					}while((Local_u8SubIterator > -1) && (get_precedence(op) < get_precedence(Local_s32LastOp)));

					/* Push current operator to stack */
					/* Note: Done this to check with next infix operator which one is higher precedence */
					push(operatorsStack, EquationSize, op);
				}
			}


		}
		else
		{
			/* Number */
			/* if it is a number push it to postfix equation array */
			PostFixEq.equation[PostFixEq.iterator] = InFixEq->equation[Local_u8Iterator];

			/*This is number not an operator*/
			PostFixEq.is_operator[PostFixEq.iterator] = 0;
			PostFixEq.iterator++;
		}

	}

	/* Lets make stack empty if have any operator by popping all operators */
	if (top > -1)
	{
		for (Local_u8SubIterator = top; Local_u8SubIterator >= 0 ; --Local_u8SubIterator)
		{
			pop(operatorsStack, &Local_s32LastOp);
			PostFixEq.equation[PostFixEq.iterator] = Local_s32LastOp;
			PostFixEq.is_operator[PostFixEq.iterator] = 1;
			PostFixEq.iterator++;
		}
	}
	return PostFixEq;
}

/*
 * solve_simp_arith_opr - solve simple arithmetic operation
 * @first_num	: first number in operation  => struct of num_t
 * 				  which have decimal part and floating part
 * @op			: type of operation + , - , *
 * @second_num	: Second number in operation => struct of num_t
 * 				  which have decimal part and floating part
 * @result		: It is a pointer to result of operation =>
 * 				  struct of num_t which have decimal part and floating part
 * Return		: Error State OK  if operation success
 * 				 			  NOK if Not
 * Example 		:
 * 			input:
 * 			- first_num
 * 				{
 * 					d_part	   : 3
 * 					f_part	   : 2
 * 				}
 * 			- op = '+'
 * 			- second_num
 * 				{
 * 					d_part	   : 2
 * 					f_part	   : 2
 * 				}
 * 			- result
 * 				{
 * 					d_part	   : 0
 * 					f_part	   : 0
 * 				}
 *
 * 			Output:
 * 			result
 * 				{
 * 					d_part	   : 5
 * 					f_part	   : 4
 * 				}
 * */
u8 solve_simp_arith_opr(num_t first_num, u8 op, num_t second_num, num_t *result)
{
	/*Result saved*/
	s64 Local_u16ResDecimalDigits;
	s16 Local_s16ResFloatingDigits;

	switch(op)
	{
		case '+':
			Local_u16ResDecimalDigits = (first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) + (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING));
			Local_s16ResFloatingDigits = ((f32)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) + (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING)))
										-(s64)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) + (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING))))
										* NUM_OF_FLOATING;
			break;
		case '-':

			Local_u16ResDecimalDigits = (first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) - (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING));
			Local_s16ResFloatingDigits = ((f32)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) - (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING)))
										-(s64)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) - (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING))))
										* NUM_OF_FLOATING;
			break;
		case '*':
			Local_u16ResDecimalDigits = (first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) * (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING));
			Local_s16ResFloatingDigits = ((f32)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) * (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING)))
										-(s64)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) * (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING))))
										* NUM_OF_FLOATING;
			break;
		case '/':
			if (second_num.d_part == 0)
			{
				return NOK;
			}
			else
			{
				Local_u16ResDecimalDigits = (first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) / (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING));
				Local_s16ResFloatingDigits = ((f32)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) / (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING)))
											-(s64)((first_num.d_part + (first_num.f_part / NUM_OF_FLOATING)) / (second_num.d_part + ( second_num.f_part / NUM_OF_FLOATING))))
												* NUM_OF_FLOATING;
			}
			break;
		default:
			return NOK;
			break;
	}
	result->d_part = Local_u16ResDecimalDigits;
	result->f_part = Local_s16ResFloatingDigits;
	return OK;
}

/**
 * get_precedence - return precedence of operator
 * @operator	: type of operation + , - , *
 * Return		: Precedence of this operator
 * 				 -1 if Invalid of Operator
 */
s8 get_precedence(u8 operator)
{
	s8 returned_value = -1;
	switch (operator)
	{
		case '*':
				returned_value = 2;
				break;
		case '/':
				returned_value = 2;
				break;
		case '+':
				returned_value = 1;
				break;
		case '-':
				returned_value = 1;
				break;
		default:
				returned_value = -1;
				break;
	}

	return (returned_value);
}


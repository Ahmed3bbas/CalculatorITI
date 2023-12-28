/*
 * Calculator_main.c
 *
 *  Created on: Dec 15, 2023
 *      Author: engah
 */

/* Includes */
#include "LIBS/std_data_types.h"
#include "LIBS/BIT_MATH.h"
#include "LIBS/stack_s32.h"

#include "APP_UTILS/utils.h"
#include "APP_UTILS/arithmetic.h"

#include  "MCAL/DIO/DIO_interface.h"
#include "HAL/KPD/KPD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"


/* MACROS*/
/*------*/
#define SHOW_POSTFIX_INSTEAD_OF_RESULT 		NO /* YES / NO */


/* GLOBAL VARIABLES*/
/*---------------------*/
u8 Global_u8NeedToClearDisplay = 0; /*Flag to clear display*/

s32 num = 0; /*General variable to save numbers*/

equation_t PostFixEq = {{0}, {0}, 0}, InFixEq = {{0}, {0}, 0};


/* FUNCTION DECLERATION*/
/*---------------------*/
void reset(void);


int main(void)
{
	/*
	 *	Local_u8Key							: get pressed key
	 *	Local_u8SetNumberToEquation			: flag to know there is number enter needs to push in equation array
	 *	op 									: operator (+, *, ..)
	 *	Local_u8IsSuccess					: flag to check successful operation
	 *	Is_operator							: array of flags to check if there is operator pressed (Note: you will need to check if equation is right)
	 *	Local_u8Iterator					: General iterator
	 *	first_num 							: first number (first element in operation)
	 *	second_num							: Second number (Second element in operation)
	 * */

	u8 Local_u8Key, Local_u8SetNumberToEquation = 0;
	u8 op = Invalid, Local_u8IsSuccess = 1;
	u8 Local_u8Iterator;

	/*solve equation*/
	num_t first_num, second_num;
	num_t StackOfOperatingNumbers[EquationSize];
	num_t result;

	DIO_voidInit(); /*Define I/O PINS*/
	KPD_voidInit();	/* initialize KeyPad */
	CLCD_void_INIT(); /* initialize CLCD*/

	while(1)
	{
		/* Which Key is pressed? */
		Local_u8Key = KPD_u8GetPressedKey();

		if (Local_u8Key != NOT_PRESSED)
		{
			if (Local_u8Key >= '0' && Local_u8Key <= '9')
			{
				/*Clear Display*/
				if (Global_u8NeedToClearDisplay == 1)
				{
					CLCD_voidClearDisplay();
					reset();
				}
				/*set flag*/
				Local_u8SetNumberToEquation = 1;

				/*Show Number on LCD*/
				CLCD_voidSendCharcter(Local_u8Key);

				/* Full Number */
				num = num * 10;
				num += (Local_u8Key - '0');
			}
			else if (Local_u8Key == '+' || Local_u8Key == '*' || Local_u8Key == '-' || Local_u8Key == '/')
			{
				/*Clear Display*/
				if (Global_u8NeedToClearDisplay == 1)
				{
					CLCD_voidClearDisplay();
					reset();
				}

				/*Set Operator*/
				switch(Local_u8Key)
				{
					case '+': op = '+'; break;
					case '-': op = '-'; break;
					case '*': op = '*'; break;
					case '/': op = '/'; break;
					default: break;
				}

				if (Local_u8SetNumberToEquation != 0)
				{
					/*push number to equation array*/
					InFixEq.equation[InFixEq.iterator] = num;

					/* this is number not an operator */
					InFixEq.is_operator[InFixEq.iterator] = 0;

					/* increase counter that shows the last index of equation array*/
					InFixEq.iterator++;

					/* Rest flag (already pushed number to array)*/
					Local_u8SetNumberToEquation = 0;

					/*Reset num to get the second one*/
					num = 0;
				}

				/*set operator to equation array*/
				InFixEq.equation[InFixEq.iterator] = op;
				/*This is operator not number*/
				InFixEq.is_operator[InFixEq.iterator] = 1;

				InFixEq.iterator++;

				/*Show Operator on LCD*/
				CLCD_voidSendCharcter(Local_u8Key);
			}
			else if (Local_u8Key == '=')
			{
				/*set this flag because when user pressed on number/operator clear display*/
				Global_u8NeedToClearDisplay = 1;

				/*Get last number*/
				if (Local_u8SetNumberToEquation != 0)
				{
					InFixEq.equation[InFixEq.iterator] = num;
					InFixEq.is_operator[InFixEq.iterator] = 0;
					InFixEq.iterator++;
					Local_u8SetNumberToEquation = 0;
				}

				/*Reset num*/
				num = 0;

				/*Move Cursor to next line to show result*/
				CLCD_voidMoveCursor(0,1);


				/* parse equation */
				PostFixEq = Parse_from_infix_to_postfix(&InFixEq);

				/* solve equation */
				for (Local_u8Iterator = 0; Local_u8Iterator < PostFixEq.iterator; ++Local_u8Iterator)
				{
					s32 temp = PostFixEq.equation[Local_u8Iterator];
					if (PostFixEq.is_operator[Local_u8Iterator])
					{
						Local_u8IsSuccess = 0;
						if (pop_operating_numbers(StackOfOperatingNumbers, &second_num) == NOK)
							break;
						if (pop_operating_numbers(StackOfOperatingNumbers, &first_num) == NOK)
						{
							/*This Condition cover if there - or + at first of arithmetic operation*/
							if((temp == '+' || temp == '-') && InFixEq.is_operator[0]) /* Local_u8Iterator < PostFixEq.iterator - 1*/
							{
								first_num.d_part = 0;
								first_num.f_part = 0;
							}
							else
								break;
						}

						if (solve_simp_arith_opr(first_num, (u8)temp, second_num, &result) == OK)
						{
							push_operating_numbers(StackOfOperatingNumbers, EquationSize, result);
							Local_u8IsSuccess = 1;
						}
//						else
//							Local_u8IsSuccess = 0;

					}
					else
					{
						result.d_part = (s64)temp;
						result.f_part = 0;
						push_operating_numbers(StackOfOperatingNumbers, EquationSize, result);
					}
				}

#if SHOW_POSTFIX_INSTEAD_OF_RESULT==YES
				/*Print POSTFIX Equation ON LCD*/
				for (Local_u8Iterator = 0; Local_u8Iterator < PostFixEq.iterator; ++Local_u8Iterator)
				{
					s32 temp = PostFixEq.equation[Local_u8Iterator];
					if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
						CLCD_voidSendCharcter(temp);
					else
						CLCD_voidSendNumber(PostFixEq.equation[Local_u8Iterator]);
				}
#else

				/*Show Results*/
				if (Local_u8IsSuccess == 1)
				{
					/* Get the last result */
					pop_operating_numbers(StackOfOperatingNumbers, &result);

					/* Show in LCD */
					CLCD_voidSendNumber( result.d_part);
					if (result.f_part != 0)
					{
							CLCD_voidSendCharcter('.');

							if (result.f_part < -1)
								result.f_part *= -1;

							CLCD_voidSendNumber(result.f_part);
							result.f_part = 0;
					}

					/*Reset*/
					Local_u8IsSuccess = 0;
				}
				else
				{
					CLCD_voidSendString("INVALID");
				}
#endif
			}
			else if (Local_u8Key == '#')
			{
					reset();
					CLCD_voidClearDisplay(); //CLCD_voidClearLastCharacter();
			}
			else
				CLCD_voidSendCharcter(Local_u8Key);
		}
	}
}

/*
 * reset - Reset all Global vatiables that affect on Operation
 * Return: void
 * */
void reset(void)
{
	PostFixEq.iterator = 0; /*iterator on postfix equation*/
	InFixEq.iterator = 0;        /*Iterator on infix equation*/
	Global_u8NeedToClearDisplay = 0; /*Flag to clear display*/

	num = 0; /*General variable to save numbers*/
	top = -1;
	TopOfOperatingNumbers = -1;
}



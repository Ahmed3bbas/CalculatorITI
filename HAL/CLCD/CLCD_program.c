/*
 * CLCD_program.c
 *
 *  Created on: Dec 10, 2023
 *      Author: engah
 */


#include "../../LIBS/std_data_types.h"
#include "../../LIBS/BIT_MATH.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_private.h"
#include "CLCD_interface.h"


static u8 x = 0;
static u8 y = 0;

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/* RS = 0 ==> COMMAND */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8LOW);

	/* RW = 0 ==> WRITE */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8LOW);

#if (CLCD_MODE==MODE_8)
		/*Send COMMAND*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);
		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(2);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

#elif CLCD_MODE == MODE_4
		/*Send COMMAND*/
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN0,GET_BIT(Copy_u8Command, 4));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN1,GET_BIT(Copy_u8Command, 5));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN2,GET_BIT(Copy_u8Command, 6));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN3,GET_BIT(Copy_u8Command, 7));
		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(1);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

		/*Send COMMAND*/
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN0,GET_BIT(Copy_u8Command, 0));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN1,GET_BIT(Copy_u8Command, 1));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN2,GET_BIT(Copy_u8Command, 2));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN3,GET_BIT(Copy_u8Command, 3));
		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(2);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

	#endif

}

void CLCD_voidSendCharcter(u8 Copy_u8Charcter)
{
		/* RS = 1 ==> DATA */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8HIGH);

		/* RW = 0 ==> WRITE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8LOW);


	#if CLCD_MODE == MODE_8
		/*Send DATA*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Charcter);

		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(2);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

	#elif CLCD_MODE == MODE_4
		/*Send DATA*/
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN0,GET_BIT(Copy_u8Charcter, 4));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN1,GET_BIT(Copy_u8Charcter, 5));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN2,GET_BIT(Copy_u8Charcter, 6));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN3,GET_BIT(Copy_u8Charcter, 7));
		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(1);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

		/*Send DATA*/
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN0,GET_BIT(Copy_u8Charcter, 0));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN1,GET_BIT(Copy_u8Charcter, 1));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN2,GET_BIT(Copy_u8Charcter, 2));
		DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D_PIN3,GET_BIT(Copy_u8Charcter, 3));
		/* ENNABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8HIGH);

		/* DELAY */
		_delay_ms(2);

		/* DISABLE */
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8LOW);

	#endif


		x++;
}


void CLCD_void_INIT(void)
{
	u8 Local_u8FunctionSet, Local_u8Display;
	_delay_ms(30);


	Local_u8FunctionSet = 0b00100000;

	Local_u8FunctionSet |= (CLCD_LINES << DB3); /*2 line*/
	Local_u8FunctionSet |= (CLCD_FONT << DB2); /*Font = 5*7 */
	#if CLCD_MODE==MODE_8

		Local_u8FunctionSet |= (1 << DB4);/*8 bits mode */

	#elif (CLCD_MODE==MODE_4)

		Local_u8FunctionSet |= (0 << DB4);/*4 bits mode */
		CLCD_voidSendCommand(Local_u8FunctionSet>>4);

	#endif
	CLCD_voidSendCommand(Local_u8FunctionSet);

	/*DIPLAY ON/OFF*/
	Local_u8Display = 0b00001000;
	Local_u8Display |= CLCD_DISPLAYMODE << DB2;
	Local_u8Display |= CLCD_CURSERDIPLAY << DB1;
	Local_u8Display |= CLCD_CURSERBLINK << DB0;
	CLCD_voidSendCommand(Local_u8Display);

	/*CLEAR DIPLAY */
	CLCD_voidSendCommand(CLR_COMMAND);
}

void CLCD_voidSendString(char *Copy_pcString)
{
	u8 Local_u8Iterator = 0;
	if (Copy_pcString != NULL)
	{
		while (Copy_pcString[Local_u8Iterator] != '\0')
		{
				CLCD_voidSendCharcter(Copy_pcString[Local_u8Iterator]);
				++Local_u8Iterator;
		}
	}
}

void CLCD_voidClearDisplay(void)
{
	/*CLEAR DIPLAY */
	CLCD_voidSendCommand(CLR_COMMAND);
	x = 0;
	y = 0;
}

void CLCD_voidMoveCursor(u8 Copy_u8X, u8 Copy_u8Y)
{
	/* Addresses of DDRAM start from 127 --to-> 255 */
	u8 Local_u8MoveCommand = Copy_u8Y * (0x40) + Copy_u8X;
	Local_u8MoveCommand |= 0x80; /*0x80 = 127*/
	CLCD_voidSendCommand(Local_u8MoveCommand);
	x = Copy_u8X;
	y = Copy_u8Y;
}


void CLCD_voidSendNumber(s64 Copy_u32Digits)
{
	u8 Local_u8Digits[MAX_INT_DIGITS];
	s8 i = 0;
	if (Copy_u32Digits < 0)
	{
		CLCD_voidSendCharcter('-');
		Copy_u32Digits *= -1;
	}

	if (Copy_u32Digits == 0)
	{
		CLCD_voidSendCharcter('0');
	}

	while (Copy_u32Digits != 0)
	{
		Local_u8Digits[i] = ( Copy_u32Digits % 10 ) + '0';
		Copy_u32Digits /= 10;
		++i;
	}

	--i;

	while(i > -1)
	{
		CLCD_voidSendCharcter(Local_u8Digits[i]);
		--i;
	}
}

void CLCD_voidClearLastCharacter()
{
	CLCD_voidMoveCursor(x - 1, y);
	CLCD_voidSendCharcter(' ');
	CLCD_voidMoveCursor(x - 1, y);
}

void CLCD_voidMoveCursorCGRAM(u8 Copy_u8StartPosition)
{
	/* Addresses of CGRAM start from 64 --to-> 127 */
	u8 Local_u8MoveCommand = Copy_u8StartPosition | (0x40);
	CLCD_voidSendCommand(Local_u8MoveCommand);
}

void CLCD_voidGenerateSpecialCharacter(u8 Copy_u8Index, u8 Copy_u8Pattern[PATTERNSIZE])
{
	u8 Local_u8Iterator = 0;
	u8 Local_u8ActualXPostion = x;
	for (Local_u8Iterator = 0; Local_u8Iterator < PATTERNSIZE; ++Local_u8Iterator)
	{
		/*Move to CGRAM*/
		CLCD_voidMoveCursorCGRAM((Copy_u8Index * PATTERNSIZE) + Local_u8Iterator);
		/* Write to CGRAM*/
		CLCD_voidSendCharcter(Copy_u8Pattern[Local_u8Iterator]);
	}
	/*I Moved cursor to write on CG RAM by moving cursor to write on it
	 * SO I HAVE TO RETURN  TO PREVIOUS POSTION BEFORFE WRITE ON IT*/
	x = Local_u8ActualXPostion;
	CLCD_voidMoveCursor(x, y);
}


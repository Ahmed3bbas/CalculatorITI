/*
 * KPD_program.c
 *
 *  Created on: Dec 11, 2023
 *      Author: engah
 */

#include "../../LIBS/std_data_types.h"
#include "../../LIBS/BIT_MATH.h"

#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"

#include "KPD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"


void KPD_voidInit(void)
{
	/* Activate PULL UP and initiate the columns with 1*/
	DIO_u8SetPortValue(KPD_PORT, DIO_u8ALLHIGH);
}
u8 	 KPD_u8GetPressedKey(void)
{
	u8 Local_u8KPDMappedArr[MARIXSIZE][MARIXSIZE]	= {
														{'7'  , '8'  , '9' , '/'},
														{'4'  , '5'  , '6' , '*'},
														{'1'  , '2'  , '3', '-'},
														{'#', '0', '=', '+'}
													};
	u8 Local_Key = NOT_PRESSED;
	u8 Col = 0, Row = 0;
	u8 Local_u8PinValue;

	for (Col = 0; Col < MARIXSIZE; ++Col)
	{
		DIO_u8SetPinValue(KPD_PORT, Col, DIO_u8LOW);

		for (Row = 0; Row < MARIXSIZE; ++Row)
		{
			DIO_u8GetPinValue(KPD_PORT, Row + 4, &Local_u8PinValue);
			if (Local_u8PinValue == 0)
			{
				Local_Key = Local_u8KPDMappedArr[Row][Col];
				_delay_ms(3);
				while(Local_u8PinValue == 0)
				{
					DIO_u8GetPinValue(KPD_PORT, Row + 4, &Local_u8PinValue);
				}
				return (Local_Key);
			}
		}
		DIO_u8SetPinValue(KPD_PORT, Col, DIO_u8HIGH);
	}
	return (Local_Key);

}

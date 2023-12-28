/*
 * DIO_program.c
 *
 *  Created on: Dec 6, 2023
 *      Author: engah
 */


#include "../../LIBS/std_data_types.h"
#include "../../LIBS/BIT_MATH.h"
#include "DIO_register.h"

#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"


void DIO_voidInit(void)
{
	DDRA = PORTA_DIRECTION;
	DDRB = PORTB_DIRECTION;
	DDRC = PORTC_DIRECTION;
	DDRD = PORTD_DIRECTION;

	PORTA = PORTA_INIT_VALUE;
	PORTB = PORTB_INIT_VALUE;
	PORTC = PORTC_INIT_VALUE;
	PORTD = PORTD_INIT_VALUE;
}

//u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
//{
//	u8 Local_u8_ErrorState = OK;
//	if (Copy_u8Pin < 8)
//	{
//		if(Copy_u8Direction == DIO_u8INPUT)
//		{
//			switch (Copy_u8Port)
//			{
//				case DIO_u8PORTA:
//					CLR_BIT(DDRA, Copy_u8Pin);
//					break;
//				case DIO_u8PORTB:
//					CLR_BIT(DDRB, Copy_u8Pin);
//					break;
//				case DIO_u8PORTC:
//					 CLR_BIT(DDRC, Copy_u8Pin);
//					 break;
//				case DIO_u8PORTD:
//					 CLR_BIT(DDRD, Copy_u8Pin);
//					 break;
//				default:
//					Local_u8_ErrorState = NOK;
//					break;
//			}
//		}
//		else if(Copy_u8Direction == DIO_u8OUTPUT)
//		{
//			switch (Copy_u8Port)
//			{
//				case DIO_u8PORTA:
//					SET_BIT(DDRA, Copy_u8Pin);
//					break;
//				case DIO_u8PORTB:
//					SET_BIT(DDRB, Copy_u8Pin);
//					break;
//				case DIO_u8PORTC:
//					SET_BIT(DDRC, Copy_u8Pin);
//					 break;
//				case DIO_u8PORTD:
//					SET_BIT(DDRD, Copy_u8Pin);
//					 break;
//				default:
//					Local_u8_ErrorState = NOK;
//					break;
//			}
//		}
//		else
//		{
//			Local_u8_ErrorState = NOK;
//		}
//	}
//	else
//	{
//		Local_u8_ErrorState = NOK;
//	}
//
//	return Local_u8_ErrorState;
//}

u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	u8 Local_u8_ErrorState = OK;
		if (Copy_u8Pin < 8)
		{
			if(Copy_u8Value == DIO_u8LOW)
			{
				switch (Copy_u8Port)
				{
					case DIO_u8PORTA:
						CLR_BIT(PORTA, Copy_u8Pin);
						break;
					case DIO_u8PORTB:
						CLR_BIT(PORTB, Copy_u8Pin);
						break;
					case DIO_u8PORTC:
						 CLR_BIT(PORTC, Copy_u8Pin);
						 break;
					case DIO_u8PORTD:
						 CLR_BIT(PORTD, Copy_u8Pin);
						 break;
					default:
						Local_u8_ErrorState = NOK;
						break;
				}
			}
			else if(Copy_u8Value == DIO_u8HIGH)
			{
				switch (Copy_u8Port)
				{
					case DIO_u8PORTA:
						SET_BIT(PORTA, Copy_u8Pin);
						break;
					case DIO_u8PORTB:
						SET_BIT(PORTB, Copy_u8Pin);
						break;
					case DIO_u8PORTC:
						SET_BIT(PORTC, Copy_u8Pin);
						 break;
					case DIO_u8PORTD:
						SET_BIT(PORTD, Copy_u8Pin);
						 break;
					default:
						Local_u8_ErrorState = NOK;
						break;
				}
			}
			else
			{
				Local_u8_ErrorState = NOK;
			}
		}
		else
		{
			Local_u8_ErrorState = NOK;
		}

		return Local_u8_ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_pu8Value)
{
	u8 Local_ErrorState = OK;
	if(Copy_u8Pin < 8 && Copy_pu8Value != NULL)
	{
		switch(Copy_u8Port)
		{
			case DIO_u8PORTA : *Copy_pu8Value = GET_BIT(PINA, Copy_u8Pin); break;
			case DIO_u8PORTB : *Copy_pu8Value = GET_BIT(PINB, Copy_u8Pin); break;
			case DIO_u8PORTC : *Copy_pu8Value = GET_BIT(PINC, Copy_u8Pin); break;
			case DIO_u8PORTD : *Copy_pu8Value = GET_BIT(PIND, Copy_u8Pin); break;
			default 		 : Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NOK;
	}
	return Local_ErrorState;
}


//u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
//{
//	u8 Local_ErrorState = OK;
//	switch(Copy_u8Port)
//	{
//	case DIO_u8PORTA: DDRA = Copy_u8Direction; break;
//	case DIO_u8PORTB: DDRB = Copy_u8Direction; break;
//	case DIO_u8PORTC: DDRC = Copy_u8Direction; break;
//	case DIO_u8PORTD: DDRD = Copy_u8Direction; break;
//	default			: Local_ErrorState = NOK;
//	}
//	return Local_ErrorState;
//}

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 Local_ErrorState = OK;
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA: PORTA = Copy_u8Value; break;
	case DIO_u8PORTB: PORTB = Copy_u8Value; break;
	case DIO_u8PORTC: PORTC = Copy_u8Value; break;
	case DIO_u8PORTD: PORTD = Copy_u8Value; break;
	default			: Local_ErrorState = NOK;
	}
	return Local_ErrorState;
}

u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8* Copy_pu8Value)
{
	u8 Local_ErrorState = OK;
	if(Copy_pu8Value != NULL)
	{
		switch(Copy_u8Port)
		{
			case DIO_u8PORTA : *Copy_pu8Value = PINA ; break;
			case DIO_u8PORTB : *Copy_pu8Value = PINB ; break;
			case DIO_u8PORTC : *Copy_pu8Value = PINC ; break;
			case DIO_u8PORTD : *Copy_pu8Value = PIND ; break;
			default 		 : Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NOK;
	}
	return Local_ErrorState;
}


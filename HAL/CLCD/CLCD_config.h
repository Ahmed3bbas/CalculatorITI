/*
 * CLCD_config.h
 *
 *  Created on: Dec 10, 2023
 *      Author: engah
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


/*	Options:
 *  1- MODE_4
 *  2- MODE_8
*/

#define CLCD_MODE					MODE_4

/*	Options:
 * 	1- DIO_u8PORTA
 * 	2- DIO_u8PORTB
 * 	3- DIO_u8PORTC
 * 	4- DIO_u8PORTD
 * 	*/
#define CLCD_CTRL_PORT				DIO_u8PORTC
#define CLCD_RS_PIN					DIO_u8PIN0
#define CLCD_RW_PIN					DIO_u8PIN1
#define CLCD_E_PIN					DIO_u8PIN2

/*NOTE: control port different from DATA PORT*/
#define CLCD_DATA_PORT				DIO_u8PORTA
#define CLCD_D_PIN0					DIO_u8PIN4
#define CLCD_D_PIN1					DIO_u8PIN5
#define CLCD_D_PIN2					DIO_u8PIN6
#define CLCD_D_PIN3					DIO_u8PIN7


#define CLCD_FONT 					1
#define CLCD_LINES 					1

#define CLCD_DISPLAYMODE 			1 /*Show chars or Not*/
#define CLCD_CURSERDIPLAY			1 /*Show Vertical cursor*/
#define CLCD_CURSERBLINK			0 /*Show horizontal cursor*/


#endif /* CLCD_CONFIG_H_ */

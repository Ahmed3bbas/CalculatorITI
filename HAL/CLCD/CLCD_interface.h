/*
 * CLCD_interface.h
 *
 *  Created on: Dec 10, 2023
 *      Author: engah
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define DB0			0
#define DB1			1
#define DB2			2
#define DB3			3
#define DB4			4
#define DB5			5
#define DB6			6
#define DB7			7

void CLCD_void_INIT(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendCharcter(u8 Copy_u8Charcter);
void CLCD_voidSendString(char *Copy_pcString);
void CLCD_voidClearDisplay(void);
void CLCD_voidMoveCursor(u8 Copy_u8X, u8 Copy_u8Y);
void CLCD_voidSendNumber(s64 Copy_u32Digits);
void CLCD_voidClearLastCharacter();

/* CGRAM */
void CLCD_voidMoveCursorCGRAM(u8 Copy_u8StartPosition);
void CLCD_voidGenerateSpecialCharacter(u8 Copy_u8Index, u8 Copy_u8Pattern[]);

#endif /* CLCD_INTERFACE_H_ */

/*
 * DIO_private.h
 *
 *  Created on: Dec 6, 2023
 *      Author: engah
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#define CONCATENATION(x7, x6, x5, x4, x3, x2, x1, x0)					CONCATENATION_HELPER(x7, x6, x5, x4, x3, x2, x1, x0)
#define CONCATENATION_HELPER(x7, x6, x5, x4, x3, x2, x1, x0)			0b##x7##x6##x5##x4##x3##x2##x1##x0


#define PORTA_DIRECTION				CONCATENATION(PORTA_PIN7_DIRECTION, PORTA_PIN6_DIRECTION, PORTA_PIN5_DIRECTION, PORTA_PIN4_DIRECTION, PORTA_PIN3_DIRECTION, PORTA_PIN2_DIRECTION, PORTA_PIN1_DIRECTION, PORTA_PIN0_DIRECTION)
#define PORTB_DIRECTION				CONCATENATION(PORTB_PIN7_DIRECTION, PORTB_PIN6_DIRECTION, PORTB_PIN5_DIRECTION, PORTB_PIN4_DIRECTION, PORTB_PIN3_DIRECTION, PORTB_PIN2_DIRECTION, PORTB_PIN1_DIRECTION, PORTB_PIN0_DIRECTION)
#define PORTC_DIRECTION				CONCATENATION(PORTC_PIN7_DIRECTION, PORTC_PIN6_DIRECTION, PORTC_PIN5_DIRECTION, PORTC_PIN4_DIRECTION, PORTC_PIN3_DIRECTION, PORTC_PIN2_DIRECTION, PORTC_PIN1_DIRECTION, PORTC_PIN0_DIRECTION)
#define PORTD_DIRECTION				CONCATENATION(PORTD_PIN7_DIRECTION, PORTD_PIN6_DIRECTION, PORTD_PIN5_DIRECTION, PORTD_PIN4_DIRECTION, PORTD_PIN3_DIRECTION, PORTD_PIN2_DIRECTION, PORTD_PIN1_DIRECTION, PORTD_PIN0_DIRECTION)


#define PORTA_INIT_VALUE			CONCATENATION(PORTA_PIN7_INIT_VALUE, PORTA_PIN6_INIT_VALUE, PORTA_PIN5_INIT_VALUE, PORTA_PIN4_INIT_VALUE, PORTA_PIN3_INIT_VALUE, PORTA_PIN2_INIT_VALUE, PORTA_PIN1_INIT_VALUE, PORTA_PIN0_INIT_VALUE)
#define PORTB_INIT_VALUE			CONCATENATION(PORTB_PIN7_INIT_VALUE, PORTB_PIN6_INIT_VALUE, PORTB_PIN5_INIT_VALUE, PORTB_PIN4_INIT_VALUE, PORTB_PIN3_INIT_VALUE, PORTB_PIN2_INIT_VALUE, PORTB_PIN1_INIT_VALUE, PORTB_PIN0_INIT_VALUE)
#define PORTC_INIT_VALUE			CONCATENATION(PORTC_PIN7_INIT_VALUE, PORTC_PIN6_INIT_VALUE, PORTC_PIN5_INIT_VALUE, PORTC_PIN4_INIT_VALUE, PORTC_PIN3_INIT_VALUE, PORTC_PIN2_INIT_VALUE, PORTC_PIN1_INIT_VALUE, PORTC_PIN0_INIT_VALUE)
#define PORTD_INIT_VALUE			CONCATENATION(PORTD_PIN7_INIT_VALUE, PORTD_PIN6_INIT_VALUE, PORTD_PIN5_INIT_VALUE, PORTD_PIN4_INIT_VALUE, PORTD_PIN3_INIT_VALUE, PORTD_PIN2_INIT_VALUE, PORTD_PIN1_INIT_VALUE, PORTD_PIN0_INIT_VALUE)

#endif /* DIO_PRIVATE_H_ */

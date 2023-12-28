/*
 * BIT_MATH.h
 *
 *  Created on: Dec 6, 2023
 *      Author: engah
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG, PSN) (REG |= (1 << PSN))
#define TOGGLE_BIT(REG, PSN) (REG ^= (1 << PSN))
#define CLR_BIT(REG, PSN) (REG &= (~(1 << PSN)))
#define GET_BIT(REG, PSN) ((REG >> PSN) & 0x01)


#endif /* BIT_MATH_H_ */

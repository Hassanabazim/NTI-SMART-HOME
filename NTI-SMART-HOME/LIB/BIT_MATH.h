/*
 * BIT_MATH.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)	REG |= (1<<BIT)
#define CLC_BIT(REG,BIT)   	REG &= ~(1<<BIT)
#define TOG_BIT(REG,BIT)   	REG ^= (1<<BIT)
#define GET_BIT(REG,BIT)   	(REG >> (BIT)) & 1

#endif /* BIT_MATH_H_ */

/*
 * MTIM2_priv.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTIMER2_MTIMER2_PRIV_H_
#define MTIMER2_MTIMER2_PRIV_H_


#define	TCNT2_REG 	(*((volatile u8 *)0x44)) //u16 for accessing High and Low
#define TCCR2_REG 	(*((volatile u8 *)0x45))
#define TIMSK_REG	(*((volatile u8  *)0x59))
#define TIFR_REG	(*((volatile u8  *)0x58))


#define CS20_BIT	0
#define CS21_BIT	1
#define CS22_BIT	2

#define WGM21_BIT	3
#define WGM20_BIT	6


#define TIMER2_NO_CLK				0
#define TIMER2_PRESCALER_1			1
#define TIMER2_PRESCALER_8			2
#define TIMER2_PRESCALER_32			3
#define TIMER2_PRESCALER_64			4
#define TIMER2_PRESCALER_128		5
#define TIMER2_PRESCALER_256		6
#define TIMER2_PRESCALER_1024		7

#define TIMER2_CS_MASK 	0xF8 //0b1111 1000

#define TOIE2_BIT	6
#define OCIE2_BIT	7		//Compare Match Interrupt Enable

#define  TIMER2_MODE_NORMAL				0x00

#define FCPU 16UL

#endif /* MTIM2_MTIM2_PRIV_H_ */

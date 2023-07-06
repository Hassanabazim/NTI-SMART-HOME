/*
 * MTIMER1_priv.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTIMER1_MTIMER1_PRIV_H_
#define MTIMER1_MTIMER1_PRIV_H_

#define TCCR1A_REG		*((volatile u8*)0x4F)	//Timer/Counter Control Register A
#define TCCR1B_REG		*((volatile u8*)0x4E)	//Timer/Counter Control Register B

#define TCNT1_REG		*((volatile u16*)0x4C)	//The Timer/Counter
#define ICR1_REG		*((volatile u16*)0x46)	// Input Capture Register
#define TIMSK_REG		*((volatile u8*)0x59)	//Timer Interrupt Mask Register
#define TIFR_REG		*((volatile u8*)0x58)	//Timer Interrupt Flag Register

// TCCR0_REG

#define WGM10_BIT	0
#define WGM11_BIT	1

// TCCR1B_REG
#define CS00_BIT	0
#define CS01_BIT	1
#define CS02_BIT	2
#define WGM12_BIT	3
#define WGM13_BIT	4
#define ICES1_BIT	6 // edge select
#define ICNC1_BIT	7 // noise canceler

// TIMSK_REG	//to access interrupt
#define TOIE1_BIT	2	//overflow interrupt enable
#define TICIE1_BIT	5	//Input Capture Interrupt Enable

//TIFR_REG
#define TOV1_BIT	0	//Overflow Flag
#define ICF1_BIT	2	//Input Capture Flag

// MASK of CS0
#define MTIMER1_CS_MASK	0xF8  // 0b1111 1000


#define MTIMER1_NO_CLOCK			0
#define MTIMER1_PRESCALLER_1		1
#define MTIMER1_PRESCALLER_8		2
#define MTIMER1_PRESCALLER_64		3
#define MTIMER1_PRESCALLER_256		4
#define MTIMER1_PRESCALLER_1024		5
#define MTIMER1_ECTTCL_FALL_EDGE	6
#define MTIMER1_ECTTCL_RAISs_EDGE	7



#endif /* MTIMER1_MTIMER1_PRIV_H_ */

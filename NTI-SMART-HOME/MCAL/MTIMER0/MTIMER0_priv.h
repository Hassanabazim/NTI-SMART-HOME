/*
 * MTIMER0_priv.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */


#ifndef MTIMER0_MTIMER0_PRIV_H_
#define MTIMER0_MTIMER0_PRIV_H_

//TIMER_REGISTERS
#define TCCR0_REG 	(*((volatile u8*)0x53))
#define TCNT0_REG 	(*((volatile u8*)0x52))
#define OCR0_REG 	(*((volatile u8*)0x5C))
#define TIFR_REG 	(*((volatile u8*)0x58))
#define TIMSK_REG 	(*((volatile u8*)0x59))

//TCCRO_REG
#define CS00_BIT	0
#define CS01_BIT	1
#define CS02_BIT 	2
#define WGM01_BIT	3
#define COM00_BIT	4
#define COM01_BIT	5
#define WGM00_BIT	6
#define FOC0_BIT	7

// TIMSK_REG
#define TOIE0_BIT	0
#define OCIE0_BIT	1

//TIFR_REG
#define TOV0_BIT	0
#define OCF0_BIT 	1


//TIMER MASKING
#define MTIMER0_CS_MASK 0xF8
#define MTIMER0_MODE_MASK 0xB7
#define MTIMER0_WAVE_MASK 0xCF

//PRESCALER Settings
#define MTIMER0_NO_CLK 				0
#define MTIMER0_PRESCALER_1			1
#define MTIMER0_PRESCALER_8			2
#define MTIMER0_PRESCALER_64		3
#define MTIMER0_PRESCALER_256		4
#define MTIMER0_PRESCALER_1024		5
#define MTIMER0_EXTCLK_FALL_EDEG	6
#define MTIMER0_EXTCLK_RISE_EDEG	7

//TIMER MODES
#define MTIMER0_NORMAL_MODE 		0x00
#define MTIMER0_CTC_MODE			0x08
#define MTIMER0_FAST_PWM_MODE       0x48
#define MTIMER0_PHASE_CORRECT_MODE	0x40

//WAVEFORE OC0 OPERATION
#define MTIMER0_OC0_DISCONNECTED	0
#define MTIMER_OC0_TOGGLE			1
#define MTIMER0_OC0_CLEAR			2
#define MTIMER0_OC0_SET				3

//PWM Modes
#define MTIMER_OCO_NONINVERTING  2
#define MTIMER_OCO_INVERTING	 3




#define MTIMER_OCO_SH				4



#endif /* MTIMER0_MTIMER0_PRIV_H_ */

/*
 * MADC_priv.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */
#ifndef ADC_ADC_PRIV_H_
#define ADC_ADC_PRIV_H_

#define   	ADMUX_REG 		*((volatile u8*)0x27)
#define 	ADCSRA_REG  	*((volatile u8*)0x26)
#define 	ADC_REG  		*((volatile u16*)0x24)
#define 	SFIOR_REG  		*((volatile u8*)0x50)

#define CHANNEL_MASK		0xE0
#define PRESCALER_MASK		0xF8
#define VREF_MASK			0x3F

#define LEFT_ADJ  1
#define RIGHT_ADJ 0


// ADNUX Register Pin
#define 	ADLAR  5

//ADCSRA Register Pin

#define 	ADIF	4
#define	 	ADSC   	6
#define		ADEN	7

		

#endif /* ADC_ADC_PRIV_H_ */

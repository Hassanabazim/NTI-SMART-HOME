/*
 * MTWI_priv.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTWI_MTWI_PRIV_H_
#define MTWI_MTWI_PRIV_H_

#define TWDR_REG 	(*((volatile u8*)0x23)) // TWI Data Register
#define TWAR_REG 	(*((volatile u8*)0x22)) //TWI Address Register
#define TWSR_REG 	(*((volatile u8*)0x21)) //TWI Status Register
#define TWBR_REG 	(*((volatile u8*)0x20)) // TWI Bit-Rate Register
#define TWCR_REG 	(*((volatile u8*)0x56)) //TWI Control Register

//TWBR Calculation Equation
#define BIT_RATE	(((FCPU/FSCL) - 16 )/(pow(4,MTWI_PRESCALER) * 2))

//TWCR register pins
#define TWINT_BIT	7	// TWI interrupt flag
#define TWEA_BIT 	6	// TWI ACK Enable
#define TWSTA_BIT	5	// TWI Start condition
#define TWSTO_BIT	4	// TWI Stop condition
#define TWWC_BIT	3	// TWI Collision flag
#define TWEN_BIT	2	// TWI Enable
#define TWIE_BIT	0	//	TWI Interrupt Enable

//TWSR Register pins
#define	TWPS1_BIT	1 // TWI Prescaler BIT
#define TWPS0_BIT 	0 // TWI Prescaler BIT

// TWAR Register Pins
#define TWGCE_BIT	0 // TWI General call Enable

// TWBR Register Prescaler
#define MTWI_PRESCALER_1	0
#define MTWI_PRESCALER_4	1
#define MTWI_PRESCALER_8	2
#define MTWI_PRESCALER_64	3

// TWBR Register Mask
#define MTWI_Prescaler_MASK 0xFC

//TWSR Register Mask
#define MTWI_STATUS_MASK 0xF8

#endif /* MTWI_MTWI_PRIV_H_ */

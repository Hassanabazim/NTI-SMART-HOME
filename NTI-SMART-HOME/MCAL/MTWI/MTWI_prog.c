/*
 * MTWI_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include <math.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MTWI_priv.h"
#include "MTWI_config.h"
#include "MTWI_int.h"


ErrorState_t MTWI_enInit(void)
{
	/* 1. Masking with Prescaler bits */
	TWSR_REG &= MTWI_Prescaler_MASK;

	/* 2. Bit Rate  FCPU = 16 MH, SCL = 400 KHz, prescaler = 1 */
	TWBR_REG = BIT_RATE ;

	/* 2. set Enable Bit */
	SET_BIT(TWCR_REG, TWEN_BIT);

	return SUCCESS;
}

ErrorState_t MTWI_enSendStart(void)
{
	/* 1. clear flag and set the start bit and enable TWI */
	TWCR_REG = (1<<TWINT_BIT)|(1<<TWSTA_BIT)|(1<<TWEN_BIT);

	/* 2. wait until operation is done */
	while (!(TWCR_REG & (1<<TWINT_BIT)));

	return SUCCESS;
}

ErrorState_t MTWI_enSendStop(void)
{
	/* clear Interrupt flag and Set Enable, Stop Bit */
	TWCR_REG = (1<<TWINT_BIT)|(1<<TWEN_BIT)|(1<<TWSTO_BIT);

	return SUCCESS;
}

ErrorState_t MTWI_enSendByte(u8 copy_u8data)
{
	/* 1. insert the data into the TWI Data Register */
	TWDR_REG = copy_u8data;

	/*2. set the Interrupt flag and Enable TWI */
	TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT);

	/* 3. wait until the data transmitted */
	while (!(TWCR_REG & (1<<TWINT_BIT)));

	return SUCCESS;
}

ErrorState_t MTWI_enRecByteACK(u8 *ptrRecValue)
{
	ErrorState_t local_state = SUCCESS;
	if (ptrRecValue == NULL)
	{
		local_state  = NULL_PTR_ERR;
	}
	else
	{
		/* 1. set Interrupt flag and Enable and ACK BITS */
		TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT) | (1<<TWEA_BIT);

		/* 2. wait until the data transmitted */
		while (!(TWCR_REG & (1<<TWINT_BIT)));

		/* 3. receive ACK of Data sent */
		*ptrRecValue = TWDR_REG;
	}
	return local_state;
}

ErrorState_t MTWI_enRecByteNoACK(u8 *ptrNRecValue)
{
	ErrorState_t local_state = SUCCESS;
	if (ptrNRecValue == NULL)
	{
		local_state  = NULL_PTR_ERR;
	}
	else
	{
		/* 1. set Interrupt flag and Enable and ACK BITS */
		TWCR_REG = (1<<TWINT_BIT) | (1<<TWEN_BIT) ;

		/* 2. wait until the data transmitted */
		while (!(TWCR_REG & (1<<TWINT_BIT)));

		/* 3. receive ACK of Data sent */
		*ptrNRecValue = TWDR_REG;

	}
	return local_state;
}

ErrorState_t MTWI_enReadStatus(u8 *ptrStateValue)
{
	ErrorState_t local_state = SUCCESS;
	if (ptrStateValue == NULL)
	{
		local_state  = NULL_PTR_ERR;
	}
	else
	{
		*ptrStateValue = (TWSR_REG & MTWI_STATUS_MASK);
	}

	return local_state;
}

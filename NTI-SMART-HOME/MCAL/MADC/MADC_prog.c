/*
 * MADC_prog.c
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MADC_priv.h"
#include "MADC_config.h"
#include "MADC_int.h"

ErrorState_t MADC_enInit(prescaler_t copy_u8presclaer, vref_t copy_vref)
{	
	/* Enable ADC */
	SET_BIT (ADCSRA_REG,ADEN);
	
	/* Clear the PRESCALER BITS by Masking it */
	ADCSRA_REG &= PRESCALER_MASK;
	/* Set the value of the Prescaler */
	ADCSRA_REG |= copy_u8presclaer;
	
	/* clear the VREF_BITS by Masking it */
	ADMUX_REG &= VREF_MASK;
	/* Set the Value of the Vref */
	ADMUX_REG |= copy_vref;
	
	

	return SUCCESS;	
}

ErrorState_t MADC_enReadChannel(channel_t copy_u8Channel, u16 *ptrValue )
{
	/* Clear the channel BITS by Masking it */
	ADMUX_REG &= CHANNEL_MASK;
	/* Set the value of the Channel */
	ADMUX_REG |= copy_u8Channel;
	
	/* start conversion */
	SET_BIT(ADCSRA_REG,ADSC);
	
	while (!(GET_BIT(ADCSRA_REG,ADIF)));
	SET_BIT(ADCSRA_REG, ADIF);
	
	*ptrValue =  ADC_REG;

	return SUCCESS;
}

/*
 * HTEMP_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MDIO_int.h"
#include "MADC_int.h"
#include "HLM35_priv.h"
#include "HLM35_config.h"
#include "HLM35_int.h"

ErrorState_t HLM35_enInit(void)
{
	/* 1. set Channel 1 of ADC is INPUT */
	MDIO_enSetPinDirection(HLM35_PIN, INPUT);

	/* 2. Initialize the ADC */
	MADC_enInit(prescaler_128, vref_AVCC);

	return SUCCESS;
}

ErrorState_t HLM35_enTempRead(u8 *pTempValue)
{
	ErrorState_t Local_state = SUCCESS;

	/* 1. check if the pointer is NULL or NOT*/
	if (pTempValue != NULL)
	{
		/* 2. get the Digital value from ADC channel */
		u16 LocalADC_value;
		MADC_enReadChannel(HLM35_CHANNEL, &LocalADC_value);

		/* 3. calculate the analog value DAC  */
		u32 Local_u32Readmv = (u32)LocalADC_value * 5000 / 1024;

		/* 4.map the analog value with the LM35 voltage equation */
		*pTempValue = Local_u32Readmv / 10;
	}

	else
	{
		Local_state = NULL_PTR_ERR;
	}

	return Local_state;
}

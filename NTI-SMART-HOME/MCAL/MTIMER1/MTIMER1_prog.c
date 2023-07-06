/*
 * MTIMER1_prg.c
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
#include "MTIMER1_priv.h"
#include "MTIMER1_config.h"
#include "MTIMER1_int.h"
#include <avr/interrupt.h>

/* call back function */
static void (*callbackptr[2])(void) = {NULL, NULL};

ErrorState_t MTIMER1_enInit(void)
{
	/* Normal Mode ON */
	CLC_BIT(TCCR1A_REG,WGM10_BIT);
	CLC_BIT(TCCR1A_REG,WGM11_BIT);
	CLC_BIT(TCCR1B_REG,WGM12_BIT);
	CLC_BIT(TCCR1B_REG,WGM13_BIT);
	return SUCCESS;
}

ErrorState_t MTIMER1_enStart(void)
{
#if(MTIMER1_CLK >= MTIMER1_NO_CLOCK && MTIMER1_CLK <= MTIMER1_ECTTCL_RAISs_EDGE)
	//step 1 : clear bits by applying Mask
	TCCR1B_REG &= MTIMER1_CS_MASK;
	// Step2 : insert bits
	TCCR1B_REG |= MTIMER1_CLK;
#else
#error ("Wrong Timer Clock")
#endif
	return SUCCESS;
}

ErrorState_t MTIMER1_enStop(void)
{
	TCCR1B_REG &= MTIMER1_CS_MASK; // reset first 3bit 000
	return SUCCESS;
}

ErrorState_t MTIMER1_ICU_enInit(void)
{
	MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_RAIS_EDGE_TRIG);
	return SUCCESS;
}
ErrorState_t MTIMER1_enEnableINT(u8 copy_u8Int_ID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8Int_ID)
	{
	case MTIMER1_ICU_INT_ID:
		SET_BIT(TIMSK_REG,TICIE1_BIT);
		break;

	case MTIMER1_OVF_INT_ID:
		SET_BIT(TIMSK_REG,TOIE1_BIT);
		break;
	default:
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;

}
ErrorState_t MTIMER1_enDisableINT(u8 copy_u8Int_ID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8Int_ID)
	{
	case MTIMER1_ICU_INT_ID:
		CLC_BIT(TIMSK_REG,TICIE1_BIT);
		break;
	case MTIMER1_OVF_INT_ID:
		CLC_BIT(TIMSK_REG,TOIE1_BIT);
		break;
	default:
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;

}
ErrorState_t MTIMER1_enSetCallBack(u8 copy_u8Int_ID, void(*ptrfn)(void))
{
	ErrorState_t Local_enState = SUCCESS;

	if(ptrfn != NULL)
	{
		callbackptr[copy_u8Int_ID] = ptrfn ;
	}
	else
	{
		Local_enState = NULL_PTR_ERR;

	}
	return Local_enState;
}

ErrorState_t MTIMER1_ICU_enRead(volatile u16 *ptrReadValue)
{
	ErrorState_t Local_enState=SUCCESS;

	if(ptrReadValue != NULL)
	{
		*ptrReadValue = ICR1_REG;
	}
	else
	{
		Local_enState = NULL_PTR_ERR;
	}
	return Local_enState;
}

ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg)
{
	ErrorState_t Local_enState = SUCCESS;

	switch (copy_u8Trigg)
	{
	case MTIMER1_ICU_FALL_EDGE_TRIG:
		CLC_BIT(TCCR1B_REG,ICES1_BIT);
		break;

	case MTIMER1_ICU_RAIS_EDGE_TRIG:
		SET_BIT(TCCR1B_REG,ICES1_BIT);
		break;

	default:
		Local_enState = OUT_OF_RANG_ERR;
		break;
	}

	return Local_enState;
}

ISR(TIMER1_OVF_vect)
{
	if(callbackptr[MTIMER1_OVF_INT_ID] != NULL)
	{
		callbackptr[MTIMER1_OVF_INT_ID]();	//call fn on higher layer (APP)
	}
}

ISR(TIMER1_CAPT_vect)
{
	if(callbackptr[MTIMER1_ICU_INT_ID] != NULL)
	{
		callbackptr[MTIMER1_ICU_INT_ID]();	//call fn on higher layer (APP)
	}
}

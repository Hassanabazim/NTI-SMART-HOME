/*
 * MTIMER0_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MTIMER0_priv.h"
#include "MTIMER0_config.h"
#include <avr/interrupt.h>
#include "MTIMER0_int.h"

static void (*callBackArr[2])(void) = {NULL, NULL};

static u32 g_32NumOFOverflows = 0;
static u8 g_u8NumOFRemaaingCounts = 0;
static u32 g_32NumOFCmpMatches = 0;

ErrorState_t MTIMER0_enInit(void)
{
#if(MTIMER0_MODE == MTIMER0_NORMAL_MODE || MTIMER0_MODE == MTIMER0_CTC_MODE || MTIMER0_MODE == MTIMER0_FAST_PWM_MODE || MTIMER0_MODE == MTIMER0_PHASE_CORRECT_MODE)
	// Step 1 : clear bits by masking
	TCCR0_REG &= MTIMER0_MODE_MASK;

	// step 2 : set value in bits
	TCCR0_REG |= MTIMER0_MODE;
#else
	#error("WRONG MTIMER0 MODE");
#endif

#if (MTIMER0_OC0_MODE >= MTIMER0_OC0_DISCONNECTED && MTIMER0_0C0_MODE <= MTIMER0_OCO_SET)
	// Step 1 : clear bits by masking
	TCCR0_REG &= MTIMER0_WAVE_MASK ;

	// step 2 : set value in bits
	TCCR0_REG |= MTIMER0_OC0_MODE << MTIMER_OCO_SH;

#else
	#error("WRONG MTIMER0_OCO_MODE");
#endif

	return SUCCESS;
}
ErrorState_t MTIMER0_enStart(void)
{
#if(MTIMER0_CLK >= MTIMER0_NO_CLK && MTIMER0_CLK <= MTIMER0_EXTCLK_RISE_EDEG)
	// Step 1 : clear bits by masking
	TCCR0_REG &= MTIMER0_CS_MASK;
	// step 2 : set value in bits
	TCCR0_REG |= MTIMER0_CLK;
#else
#error ("Wrong TIMER CLK");
#endif
	return SUCCESS;

}
ErrorState_t MTIMER0_enStop(void)
{
	// Step 1 : clear bits by masking WHICH IS (NO CLK)
	TCCR0_REG &= MTIMER0_CS_MASK;

	return SUCCESS;
}

ErrorState_t MTIMER0_enSetCallBack(u8 copy_u8Int_ID,void (*ptrfn)(void))
{
	ErrorState_t Local_state = SUCCESS;
	if (ptrfn == NULL)
	{
		Local_state = NULL_PTR_ERR;
	}

	else
	{
		/* METHED 2
		 * callBackArr[copy_u8Int_ID] = ptrfn;
		 */
		switch (copy_u8Int_ID)
		{
		case MTIMER0_OVF_INT_ID:
			callBackArr[0] = ptrfn;
			break;

		case MTIMER0_COM_INT_ID:
			callBackArr[1] = ptrfn;
			break;
		default :
			Local_state = OUT_OF_RANG_ERR;
			break;
		}
	}
	return Local_state;
}

ErrorState_t MTIMER0_enSetTime(u32 copy_u32delayMS)
{
	u32 Local_u16Arr[5] = {1, 8, 64, 256, 1024};

	// using Prescaler predefined as index to map the corresponding value
	f32 tickTime = (f32)Local_u16Arr[MTIMER0_CLK - 1] / FCPU;
	u32 Local_u32TotalNumberOFCounts = (copy_u32delayMS * 1000) / tickTime;

#if(MTIMER0_MODE == MTIMER0_NORMAL_MODE)
	g_32NumOFOverflows = Local_u32TotalNumberOFCounts / 256;
	g_u8NumOFRemaaingCounts = Local_u32TotalNumberOFCounts % 256;
	if (g_u8NumOFRemaaingCounts != 0)
	{
		//preload the TCNT REG with the fraction part
		TCNT0_REG = 256 - g_u8NumOFRemaaingCounts;
		g_32NumOFOverflows ++;
	}
#elif(MTIMER0_MODE == MTIMER0_CTC_MODE)
	u8 Local_u8OCRValue = 255;
	while (Local_u32TotalNumberOFCounts % Local_u8OCRValue != 0)
	{
		Local_u8OCRValue--;
	}
	OCR0_REG = Local_u8OCRValue;
	g_32NumOFCmpMatches = Local_u32TotalNumberOFCounts / Local_u8OCRValue;

#endif
	return SUCCESS;
}

ErrorState_t MTIMER0_enEnableInt(u8 copy_u8Int_ID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8Int_ID)
	{
	case MTIMER0_OVF_INT_ID:
		SET_BIT(TIMSK_REG, TOIE0_BIT);
		break;

	case MTIMER0_COM_INT_ID:
		SET_BIT(TIMSK_REG, OCIE0_BIT);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
		break;
	}
	return Local_state;
}

ErrorState_t MTIMER0_enDisableInt(u8 copy_u8Int_ID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8Int_ID)
	{
	case MTIMER0_OVF_INT_ID:
		CLC_BIT(TIMSK_REG, TOIE0_BIT);
		break;

	case MTIMER0_COM_INT_ID:
		CLC_BIT(TIMSK_REG, OCIE0_BIT);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
		break;
	}
	return Local_state;
}

ErrorState_t MTIMER0_enSetCompareValue(u8 copy_u8Value)
{

	return SUCCESS;
}

#if (MTIMER0_MODE == MTIMER0_FAST_PWM_MODE)
ErrorState_t MTIMER0_enSetFastPWM(u8 copy_u8Duty)
{
	ErrorState_t Local_state = SUCCESS;
	if (copy_u8Duty >= 0 && copy_u8Duty <= 100)
	{
#if (MTIMER0_OC0_MODE == MTIMER_OCO_NONINVERTING)
		OCR0_REG = abs(((copy_u8Duty * 256 ) / 100) - 1);

#elif(MTIMER0_OC0_MODE ==  MTIMER_OCO_INVERTING)
		OCR0_REG = abs(255 - ((copy_u8Duty*256) / 100));
#else
#error ("WRONG FAST PWM MODE")
#endif
	}

	else
	{
		Local_state = OUT_OF_RANG_ERR;
	}

	return Local_state;
}

#elif(MTIMER0_MODE == MTIMER0_PHASE_CORRECT_MODE)
ErrorState_t MTIMER0_enSetPhaseCorrectPWM(u8 copy_u8Duty)
{
	return SUCCESS;
}

#endif
ISR(TIMER0_OVF_vect)
{
	static u32 Local_u32NumOFCounts = 0;
	//Increment Number of counts ever time ISR happen
	Local_u32NumOFCounts ++;

	// if the number of counts equals to global Required Number
	if (Local_u32NumOFCounts == g_32NumOFOverflows)
	{


		//preload the TCNT REG with the fraction part
		TCNT0_REG = 256 - g_u8NumOFRemaaingCounts;

		//take Action
		if (callBackArr[MTIMER0_OVF_INT_ID]!= NULL)
		{
			callBackArr[MTIMER0_OVF_INT_ID]();
		}
		// reset the number of counts
		Local_u32NumOFCounts = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
	static u32 Local_u32NumOFCounts = 0;
	Local_u32NumOFCounts ++;

	if (Local_u32NumOFCounts == g_32NumOFCmpMatches)
	{
		// reset the number of counts
		Local_u32NumOFCounts = 0;


		//take Action
		if (callBackArr[MTIMER0_COM_INT_ID]!= NULL)
		{
			callBackArr[MTIMER0_COM_INT_ID]();
		}

	}
}

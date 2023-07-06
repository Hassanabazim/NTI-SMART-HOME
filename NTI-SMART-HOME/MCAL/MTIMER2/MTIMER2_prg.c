/*
 * MTIM2_prg.c
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
#include <avr/interrupt.h>
#include "MTIMER2_config.h"
#include "MTIMER2_int.h"
#include "MTIMER2_priv.h"

static volatile void (*g_callBackPtr)(void) = NULL;


ErrorState_t TIMER2_enInit(void){
	CLC_BIT(TCCR2_REG,WGM20_BIT);
	CLC_BIT(TCCR2_REG,WGM21_BIT);

	return SUCCESS;
}
ErrorState_t TIMER2_enstart(void){
#if  ((TIMER2_CLK >= TIMER2_NO_CLK) && (TIMER2_CLK <= TIMER2_PRESCALER_1024))

	//Step 1: Clear Bits by applying mask
	TCCR2_REG &= TIMER2_CS_MASK;

	//Step 2: Insert Value +
	TCCR2_REG |= TIMER2_CLK;

#else
#error("Wrong Timer2 Clock")
#endif
	return SUCCESS;
}

ErrorState_t TIMER2_enstop(void){
	TCCR2_REG =0;
	return SUCCESS;

}
ErrorState_t TIMER2_enEnableInt(void){
	ErrorState_t Local_enstate=SUCCESS;

	SET_BIT(TIMSK_REG,TOIE2_BIT);

	return Local_enstate;
}


ErrorState_t TIMER2_enDisableInt(void){

	ErrorState_t Local_enstate=SUCCESS;

	CLC_BIT(TIMSK_REG,TOIE2_BIT);

	return Local_enstate;

}

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr != NULL)
	{
		(g_callBackPtr)();
	}
}

ErrorState_t TIMER2_enSetCallBack(void(*ptrfn)(void)){

	ErrorState_t Local_enState = SUCCESS;


	if(ptrfn==NULL){
		Local_enState = NULL_PTR_ERR;
	}
	else{
		g_callBackPtr=ptrfn;
	}
	return Local_enState;
}
/*

static u32 g_u32NumOfOverflows=0;
static u32 g_u32NumOfRemainingCounts=0;


ErrorState_t TIMER2_enInit(void){
	CLR_BIT(TCCR2_REG,WGM20_BIT);
	CLR_BIT(TCCR2_REG,WGM21_BIT);

	return SUCCESS;
}
ErrorState_t TIMER2_enEnableInt(void){
	ErrorState_t Local_enstate=SUCCESS;

	SET_BIT(TIMSK_REG,TOIE2_BIT);

	return Local_enstate;
}

ErrorState_t TIMER2_enSet_Time(u32 copy_u32delayMS){

	u32 Local_u32Arr[]={1,8,32,64,128,256,1024};
	f32 Local_f32TickTime = Local_u32Arr[TIMER2_CLK-1]/FCPU;
	u32 Local_u32TotalNumberOfCounts=(copy_u32delayMS*1000)/Local_f32TickTime;

	g_u32NumOfOverflows=Local_u32TotalNumberOfCounts/256;
	g_u32NumOfRemainingCounts = Local_u32TotalNumberOfCounts%256;

	if(g_u32NumOfRemainingCounts!=0){
		TCNT2_REG=256-g_u32NumOfRemainingCounts;
		g_u32NumOfOverflows++;
	}

	return SUCCESS;
}
ErrorState_t TIMER2_enstart(void){
#if  ((TIMER2_CLK >= TIMER2_NO_CLK) && (TIMER2_CLK <= TIMER2_PRESCALER_1024))

	//Step 1: Clear Bits by applying mask
	TCCR2_REG &= TIMER2_CS_MASK;

	//Step 2: Insert Value +
	TCCR2_REG |= TIMER2_CLK;

#else
#error("Wrong Timer2 Clock")
#endif
	return SUCCESS;
}
ErrorState_t TIMER2_enstop(void){
	TCCR2_REG &= TIMER2_CS_MASK;
	return SUCCESS;

}
ErrorState_t TIMER2_enSetCallBack(void(*ptrfn)(void)){

	ErrorState_t Local_enState = SUCCESS;


	if(ptrfn==NULL){
		Local_enState = NULL_PTR_ERR;
	}
	else{
		callBackArr=ptrfn;
	}

	return Local_enState;

}
ISR(TIMER2_OVF_vect){

	static u32 Local_u32NumOfCounts =0; // tb3 el data w el .bss wazefet el startup code
		//Increment Number of Counts every time ISR happens
		Local_u32NumOfCounts++;

		//if Number of Counts equals to global required Number of overflows
		if(Local_u32NumOfCounts == g_u32NumOfOverflows){

			//Reset the local counter for the new period
			Local_u32NumOfCounts = 0;

			//Pre-load TCNT with the fraction part
			TCNT2_REG = 256-g_u32NumOfRemainingCounts;

			//take action
			if (callBackArr!=NULL){
				callBackArr();
			}
		}
}
*/

/*
 * HULTRASONIC_prog.c
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
#include "MGIO_int.h"
#include "MTIMER1_int.h"
#include "HULTRA_priv.h"
#include "HULTRA_config.h"
#include "HULTRA_int.h"
#include <math.h>
#include <avr/delay.h>


static volatile u16 Reading_1 = 0;
static volatile u16 Reading_2 = 0;
static volatile u8 OVF_count = 0;
static volatile StateMachine_t state = STATE1;

ErrorState_t ULTRASONIC_enInit(void)
{
	MDIO_enSetPinDirection(PD6, INPUT);//echo
	MDIO_enSetPinDirection(PD7, OUTPUT);//trigger

	//step 1: Init Timer 1
	MTIMER1_enInit();
	//step 2:Init ICU
	MTIMER1_ICU_enInit();
	return SUCCESS;
}

ErrorState_t ULTRASONIC_enEnable(void)
{
	//step 3:Enable ICU Int
	MTIMER1_enEnableINT(MTIMER1_ICU_INT_ID);
	MTIMER1_enEnableINT(MTIMER1_OVF_INT_ID);

	//step 4:Set Call Back
	MTIMER1_enSetCallBack(MTIMER1_ICU_INT_ID, ICU_HW);
	MTIMER1_enSetCallBack(MTIMER1_OVF_INT_ID, OVF_COUNTS);

	//Start Timer 1
	MTIMER1_enStart();
	//Enable Global Interrupt
	MGIO_enEnable();
	//send trigger
	MDIO_enSetPinValue(PD7,HIGH);
	_delay_us(10);
	MDIO_enSetPinValue(PD7, LOW);

	return SUCCESS;
}

ErrorState_t ULTRASONIC_enRead(u16 *ptrValue)
{
	u32 TimeTicks;

	//Busy Waiting until all Readings are taken
	while(state!= STATE3);
	state=STATE1;

	if(OVF_count == 0)
	{
		TimeTicks = (u32)Reading_2 - (u32)Reading_1;
	}
	else
	{
		TimeTicks=(INT_MAX - (u32)Reading_1) + (OVF_count*INT_MAX) + (u32)Reading_2;
	}

	// microsecond = pre-scaler / FCPU
	f32 TickTime = 1024 / FCPU;

	f32 Time  = TimeTicks * TickTime/1000000.0;

	u16 dis = ceil(SOUND_SPEED *(Time/2));

#if (REAL_KIT == SIM_KIT)
	*ptrValue  = dis / 10;
#endif

	return SUCCESS;
}

void ICU_HW(void)
{
	if(STATE1== state)
	{
		//Change State
		MTIMER1_ICU_enRead(&Reading_1);

		//Change Trigger
		MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_FALL_EDGE_TRIG);
		state=STATE2;
	}
	else if(STATE2 == state)
	{
		//Taking_Reading of the falling edge
		MTIMER1_ICU_enRead(&Reading_2);

		//Change State
		state=STATE3;
		MTIMER1_ICU_enSetTrigger(MTIMER1_ICU_RAIS_EDGE_TRIG);

		//Disable Timer 1
		MTIMER1_enStop();

		//Disable Interrupt
		MTIMER1_enDisableINT(MTIMER1_ICU_INT_ID);
		MTIMER1_enDisableINT(MTIMER1_OVF_INT_ID);
	}
}

void OVF_COUNTS(void)
{
	OVF_count++;
}

/*
 * MTIMER1_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTIMER1_MTIMER1_INT_H_
#define MTIMER1_MTIMER1_INT_H_

#include "ERROR_STATE.h"

#define FCPU 16UL

#define MTIMER1_ICU_FALL_EDGE_TRIG	0
#define MTIMER1_ICU_RAIS_EDGE_TRIG	1

#define MTIMER1_OVF_INT_ID	0
#define MTIMER1_ICU_INT_ID	1


ErrorState_t MTIMER1_enInit(void);				//Timer mode
ErrorState_t MTIMER1_enStart(void);				// Clock
ErrorState_t MTIMER1_enStop(void);
ErrorState_t MTIMER1_ICU_enInit(void);			// 1st Trigger to ISR
ErrorState_t MTIMER1_enEnableINT(u8 copy_u8Int_ID);//Enable Interrupt
ErrorState_t MTIMER1_enDisableINT(u8 copy_u8Int_ID);
ErrorState_t MTIMER1_enSetCallBack(u8 copy_u8Int_ID, void(*ptrfn)(void));
ErrorState_t MTIMER1_ICU_enRead(volatile u16 *ptrReadValue);
ErrorState_t MTIMER1_ICU_enSetTrigger(u8 copy_u8Trigg);

#endif /* MTIMER1_MTIMER1_INT_H_ */

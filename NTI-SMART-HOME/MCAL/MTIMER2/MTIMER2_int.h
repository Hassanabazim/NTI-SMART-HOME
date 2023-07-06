/*
 * MTIM2_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTIMER2_MTIMER2_INT_H_
#define MTIMER2_MTIMER2_INT_H_


ErrorState_t TIMER2_enInit(void);	// Timer Mode
ErrorState_t TIMER2_enstart(void);	//Clock
ErrorState_t TIMER2_enstop(void);
ErrorState_t TIMER2_enSetCallBack(void (*ptrfn)(void));
ErrorState_t TIMER2_enEnableInt(void);
ErrorState_t TIMER2_enDisableInt(void);

#endif /* MTIM2_MTIM2_INT_H_ */

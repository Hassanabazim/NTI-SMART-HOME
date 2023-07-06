/*
 * HULTRASONIC_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HULTRA_HULTRA_INT_H_
#define HULTRA_HULTRA_INT_H_

typedef enum{
	STATE1=1,
	STATE2,
	STATE3
}StateMachine_t;


ErrorState_t ULTRASONIC_enInit(void);
ErrorState_t ULTRASONIC_enEnable(void);
ErrorState_t ULTRASONIC_enRead(u16 *ptrValue);

#endif /* HULTRA_HULTRA_INT_H_ */

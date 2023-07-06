/*
 * HDCMOTOR_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HMOTOR_HMOTOR_INT_H_
#define HMOTOR_HMOTOR_INT_H_


typedef enum {
	Motor_forward,
	Motor_reverse
}Motor_dir;


ErrorState_t HDCMOTOR_enInit(void);
ErrorState_t HDCMOTOR_enSetON(Motor_dir copy_u8dir, u8 copy_u8duty);
ErrorState_t HDCMOTOR_enSetOFF(void);


#endif /* HMOTOR_HMOTOR_INT_H_ */

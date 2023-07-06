/*
 * HLED_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HLED_HLED_INT_H_
#define HLED_HLED_INT_H_


#define	HLED_RED_ID 1
#define HLED_GREN_ID 2
#define HLED_BLUE_ID 3


ErrorState_t HLED_enInit(u8 copyu8_LedID);
ErrorState_t HLED_enSetON(u8 copyu8_LedID);
ErrorState_t HLED_enSetOFF(u8 copyu8_LedID);
ErrorState_t HLED_enToggle(u8 copyu8_LedID);



#endif /* HLED_HLED_INT_H_ */

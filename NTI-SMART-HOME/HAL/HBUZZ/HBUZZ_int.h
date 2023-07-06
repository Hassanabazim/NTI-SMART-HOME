/*
 * HBUZZ_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HBUZZ_HBUZZ_INT_H_
#define HBUZZ_HBUZZ_INT_H_

#define HBUZZ_ID  1

ErrorState_t HBUZZ_enInit(u8 copy_u8BuzzID);
ErrorState_t HBUZZ_enSetON(u8 copy_u8BuzzID);
ErrorState_t HBUZZ_enSetOFF(u8 copy_u8BuzzID);
ErrorState_t HBUZZ_enSetONCE(u8 copy_u8BuzzID);
ErrorState_t HBUZZ_enSetNum(u8 copy_u8BuzzID, u8 copy_u8num);




#endif /* HBUZZ_HBUZZ_INT_H_ */

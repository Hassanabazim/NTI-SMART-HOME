/*
 * HTEMP_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HLM35_HLM35_INT_H_
#define HLM35_HLM35_INT_H_


ErrorState_t HLM35_enInit(void);
ErrorState_t HLM35_enTempRead(u8 *pTempValue);



#endif /* HLM35_HLM35_INT_H_ */

/*
 * HEEPROM_int.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HEEPROM_HEEPROM_INT_H_
#define HEEPROM_HEEPROM_INT_H_


ErrorState_t HEEPROM_enInit(void);
ErrorState_t HEEPROM_enWriteByte(u16 copy_u16adress, u8 copy_u8data);
ErrorState_t HEEPROM_enReadByte(u16 copy_u16adress, u8 *ptrData);





#endif /* HEEPROM_HEEPROM_INT_H_ */

/*
 * MTWI_int.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MTWI_MTWI_INT_H_
#define MTWI_MTWI_INT_H_

/* Master Transmitter Status code */

#define MTWI_MT_START_SUCCESS			0x08
#define MTWI_MT_REPEATED_START_SUCCESS	0x10
#define MTWI_MT_SLA_W_ACK				0x18
#define MTWI_MT_SLA_W_NACK				0x20
#define MTWI_MT_DATA_ACK				0x28
#define MTWI_MT_DATA_NACK				0x30
#define MTWI_MT_ARB_LOST				0x38

/* Master Receiver Status code */

#define MTWI_MR_START_SUCCESS			0x08
#define MTWI_MR_REPEATED_START_SUCCESS	0x10
#define MTWI_MR_SLA_R_ACK				0x40
#define MTWI_MR_SLA_R_NACK				0x48
#define MTWI_MR_DATA_ACK				0x50
#define MTWI_MR_DATA_NACK				0x58
#define MTWI_MR_ARB_LOST				0x38


/*     Master Mode       */
ErrorState_t MTWI_enInit(void);
ErrorState_t MTWI_enSendStart(void);
ErrorState_t MTWI_enSendStop(void);
ErrorState_t MTWI_enSendByte(u8 copy_u8data); // Master transmitter
ErrorState_t MTWI_enRecByteACK(u8 *ptrRecValue); // Master Receiver with ACK
ErrorState_t MTWI_enRecByteNoACK(u8 *ptrNRecValue); //Master Receiver without ACK
ErrorState_t MTWI_enReadStatus(u8 *ptrStateValue);





#endif /* MTWI_MTWI_INT_H_ */

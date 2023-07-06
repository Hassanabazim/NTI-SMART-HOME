/*
 * HEEPROM_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MTWI_int.h"
#include "HEEPROM_priv.h"
#include "HEEPROM_config.h"
#include "HEEPROM_int.h"

ErrorState_t HEEPROM_enInit(void)
{
	/* Initialize the TWI Driver */
	MTWI_enInit();
	return SUCCESS;
}
ErrorState_t HEEPROM_enWriteByte(u16 copy_u16adress, u8 copy_u8data)
{
	u8 status ;
	/* 1. Send start */
	MTWI_enSendStart();

	/* 2. check status */
	MTWI_enReadStatus(&status);

	if (status  != MTWI_MT_START_SUCCESS)
	{
		return FAILARE;
	}

	/* 3. Address (1010 + MSB of Date A10, A9, A8 + W) */
	 // Masking 0700 A10 A9 A8 address_u16 with shifting only -> 7
	u8 _3MSB = ((u8)(copy_u16adress & 0x0700) >> 7);
	// Complete the half of the address wit 1010 EEPROM Address
	MTWI_enSendByte(_3MSB | 0xA0);

	/* 4. check status */
	MTWI_enReadStatus(&status);
	if (status  != MTWI_MT_SLA_W_ACK)
	{
		return FAILARE;
	}

	/* 5. send the rest the address (A7 -- A0) as data */
	MTWI_enSendByte((u8) copy_u16adress);

	/* 6. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MT_DATA_ACK)
	{
		return FAILARE;
	}

	/* 7. send byte to be written */
	MTWI_enSendByte(copy_u8data);

	/* 8. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MT_DATA_ACK)
	{
		return FAILARE;
	}

	/* 9. send stop */
	MTWI_enSendStop();

	return SUCCESS;
}

ErrorState_t HEEPROM_enReadByte(u16 copy_u16adress, u8 *ptrData)
{
	u8 status ;
	/* 1. Send start */
	MTWI_enSendStart();

	/* 2. check status */
	MTWI_enReadStatus(&status);
	if (status  != MTWI_MT_START_SUCCESS)
	{
		return FAILARE;
	}

	/* 3. Address (1010 + MSB of Date A10, A9, A8 + W) */
	u8 _3MSB = ((u8)(copy_u16adress & 0x0700) >> 7);
	MTWI_enSendByte(_3MSB | 0xA0);

	/* 4. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MT_SLA_W_ACK)
	{
		return FAILARE;
	}

	/* 5. send the rest of data as address */
	MTWI_enSendByte((u8) copy_u16adress);

	/* 6. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MT_DATA_ACK)
	{
		return FAILARE;
	}

	/* 7. send repeated start */
	MTWI_enSendStart();

	/* 8. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MR_REPEATED_START_SUCCESS)
	{
		return FAILARE;
	}

	/* 9. send address (1010 + 000 + R )*/
	MTWI_enSendByte((u8)((0xA0)|((copy_u16adress & 0x0700) >> 7) | 0x01));

	/* 10. check status */
	MTWI_enReadStatus(&status);
	if (status != MTWI_MR_SLA_R_ACK)
	{
		return FAILARE;
	}

	/* 11. read data */
	MTWI_enRecByteNoACK(ptrData);

	/* 12. check status */

	MTWI_enReadStatus(&status);
	if (status != MTWI_MR_DATA_NACK)
	{
		return FAILARE;
	}

	/* send stop condition */
	MTWI_enSendStop();

	return SUCCESS;

}

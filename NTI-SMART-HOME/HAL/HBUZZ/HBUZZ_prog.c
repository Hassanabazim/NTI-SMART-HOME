/*
 * HBUZZ_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include <util/delay.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MDIO_int.h"
#include "HBUZZ_priv.h"
#include "HBUZZ_config.h"
#include "HBUZZ_int.h"

ErrorState_t HBUZZ_enInit(u8 copy_u8BuzzID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8BuzzID)
	{
	case HBUZZ_ID:
		MDIO_enSetPinDirection(HBUZZ_PIN, OUTPUT);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HBUZZ_enSetON(u8 copy_u8BuzzID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8BuzzID)
	{
	case HBUZZ_ID:
		MDIO_enSetPinValue(HBUZZ_PIN, HIGH);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HBUZZ_enSetOFF(u8 copy_u8BuzzID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8BuzzID)
	{
	case HBUZZ_ID:
		MDIO_enSetPinValue(HBUZZ_PIN, LOW);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HBUZZ_enSetONCE(u8 copy_u8BuzzID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8BuzzID)
	{
	case HBUZZ_ID:
		MDIO_enSetPinValue(HBUZZ_PIN, HIGH);
		_delay_ms(500);
		MDIO_enSetPinValue(HBUZZ_PIN, LOW);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HBUZZ_enSetNum(u8 copy_u8BuzzID, u8 copy_u8num)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copy_u8BuzzID)
	{
	case HBUZZ_ID:
		for (u8 i = 0; i < copy_u8num; i++)
		{
			MDIO_enSetPinValue(HBUZZ_PIN, HIGH);
			_delay_ms(750);
			MDIO_enSetPinValue(HBUZZ_PIN, LOW);
			_delay_ms(750);

		}
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

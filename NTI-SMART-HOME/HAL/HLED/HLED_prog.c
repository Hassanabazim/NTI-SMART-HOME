/*
 * HLED_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MDIO_int.h"
#include "HLED_priv.h"
#include "HLED_config.h"
#include "HLED_int.h"


ErrorState_t HLED_enInit(u8 copyu8_LedID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copyu8_LedID)
	{
	case HLED_RED_ID:
		MDIO_enSetPinDirection(HLED_RED_PIN, OUTPUT);
		break;

	case HLED_GREN_ID:
		MDIO_enSetPinDirection(HLED_GREN_PIN, OUTPUT);
		break;

	case HLED_BLUE_ID:
		MDIO_enSetPinDirection(HLED_BLUE_PIN, OUTPUT);
		break;

	default:
		Local_state = OUT_OF_RANG_ERR;

	}
	return Local_state;
}

ErrorState_t HLED_enSetON(u8 copyu8_LedID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copyu8_LedID)
	{
	case HLED_RED_ID:
		#if(HLED_RED_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_RED_PIN, HIGH);

		#elif (HLED_RED_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_RED_PIN, LOW);
		#else
			#error ("WRONG LED RED DIRECTION")
		#endif
		break;

	case HLED_GREN_ID:
		#if(HLED_GREN_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_GREN_PIN, HIGH);

		#elif (HLED_GREN_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_GREN_PIN, LOW);
		#else
			#error ("WRONG LED GREEN DIRECTION");
		#endif
		break;

	case HLED_BLUE_ID:
		#if(HLED_BLUE_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_BLUE_PIN, HIGH);

		#elif (HLED_BLUE_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_BLUE_PIN, LOW);
		#else
			#error ("WRONG LED BLUE DIECTION")
		#endif
		break;

		default: Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HLED_enSetOFF(u8 copyu8_LedID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copyu8_LedID)
	{
	case HLED_RED_ID:
		#if(HLED_RED_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_RED_PIN, LOW);

		#elif (HLED_RED_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_RED_PIN, HIGH);
		#else
			#error ("WRONG LED RED DIRECTION")
		#endif
		break;

	case HLED_GREN_ID:
		#if(HLED_GREN_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_GREN_PIN, LOW);

		#elif (HLED_GREN_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_GREN_PIN, HIGH);
		#else
			#error ("WRONG LED GREEN DIRECTION")
		#endif
		break;

	case HLED_BLUE_ID:
		#if(HLED_BLUE_DIR == HLED_DIR_FORWARD)
		MDIO_enSetPinValue(HLED_BLUE_PIN, LOW);

		#elif (HLED_BLUE_DIR == HLED_DIR_REVERSE)
		MDIO_enSetPinValue(HLED_BLUE_PIN, HIGH);
		#else
			#error ("WRONG LED BLUE DIRECTION")
		#endif
		break;

		default:
			Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t HLED_enToggle(u8 copyu8_LedID)
{
	ErrorState_t Local_state = SUCCESS;
	switch (copyu8_LedID)
	{
	case HLED_RED_ID:
		MDIO_enTogglePin(HLED_RED_PIN);
		break;

	case HLED_GREN_ID:
		MDIO_enTogglePin(HLED_GREN_PIN);
		break;

	case HLED_BLUE_ID:
		MDIO_enTogglePin(HLED_BLUE_PIN);
		break;

		default: Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

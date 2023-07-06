/*
 * HMOTOR_prog.c
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */


#include "MTIMER0_int.h"
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MDIO_int.h"
#include "HMOTOR_priv.h"
#include "HMOTOR_config.h"
#include "HMOTOR_int.h"

ErrorState_t HDCMOTOR_enInit(void)
{
	MDIO_enSetPinDirection(HDC_MOTOR_IN1_PIN, OUTPUT);
	MDIO_enSetPinDirection(HDC_MOTOR_IN2_PIN, OUTPUT);
	MDIO_enSetPinDirection(PB3, OUTPUT);

	MTIMER0_enInit();
	MTIMER0_enStart();
	return SUCCESS;
}
ErrorState_t HDCMOTOR_enSetON(Motor_dir copy_u8dir, u8 copy_u8duty)
{
	ErrorState_t Local_state = SUCCESS;

	switch (copy_u8dir)
	{
	case Motor_forward:
		MDIO_enSetPinValue(HDC_MOTOR_IN1_PIN, HIGH);
		MDIO_enSetPinValue(HDC_MOTOR_IN2_PIN, LOW);
		MTIMER0_enSetFastPWM(copy_u8duty);
		break;

	case Motor_reverse:
		MDIO_enSetPinValue(HDC_MOTOR_IN1_PIN, LOW);
		MDIO_enSetPinValue(HDC_MOTOR_IN2_PIN, HIGH);
		MTIMER0_enSetFastPWM(copy_u8duty);
		break;

	default:
		Local_state = OUT_OF_RANG_ERR;
		break;
	}


	return Local_state;
}
ErrorState_t HDCMOTOR_enSetOFF(void)
{
	MTIMER0_enSetFastPWM(0);
	MTIMER0_enStop();

	return SUCCESS;
}

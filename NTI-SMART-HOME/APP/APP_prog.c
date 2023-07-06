/*
 *
 * 		NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *      Authors: 1- Hassan Abdelazim Abdelsalam
 *	    		 2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "MGIO_int.h"
#include "MDIO_int.h"
#include "MTIMER0_int.h"
#include "MTIMER1_int.h"
#include "MTIMER2_int.h"
#include "MADC_int.h"
#include "MTWI_int.h"
#include "HLCD_int.h"
#include "HKEYPAD_int.h"
#include "HMOTOR_int.h"
#include "HLM35_int.h"
#include "HBUZZ_int.h"
#include "HLED_int.h"
#include "HULTRA_int.h"
#include "HEEPROM_int.h"
#include "APP_priv.h"
#include "APP_config.h"
#include "APP_int.h"
#include <util/delay.h>
#include <stdlib.h>

void login_system(void);
void temp_system(void);
void Delay_2_min(void);

static u16 tick_delay_2_min = 0;
static u8 multiple_wrong = 0, eeprom_index = 0, SAVED_PASS = 0;

void APP_voidInit(void)
{
	/* Initialization HAL && RELAY */
	MDIO_enSetPinDirection(PC6, OUTPUT);
	HLED_enInit(HLED_RED_ID);
	HLED_enInit(HLED_GREN_ID);
	HLED_enInit(HLED_BLUE_ID);
	HBUZZ_enInit(HBUZZ_ID);
	HKEYPAD_enInit();
	HLM35_enInit();
	HDCMOTOR_enInit();
	HLCD_enInit();
	HEEPROM_enInit();
	ULTRASONIC_enInit();

	/* Initialization & Set Up TIMER2 */
	TIMER2_enSetCallBack(Delay_2_min);
	MGIO_enEnable();
	TIMER2_enInit();
}

void APP_voidStart(void)
{
	/* Application Start */
	HLCD_enGoToXY(1, 0);
	HLCD_enSendString("NTI SMART HOME");
	_delay_ms(500);
	HLCD_enCLearDisplay();
	while (1)
	{
		login_system();
	}
}

void login_system(void)
{
	u8 key = HKEYPAD_NO_KEY_PRESSED ;
	u8 data, wrong_pass = 0,  userArr_index = 0;
	u16 distance;

	/* The First Login Password */
	if (SAVED_PASS == 0)
	{
		HLCD_enSendString("CREATE PASSWORD ");
		HLCD_enGoToXY(2,0);
		HLCD_enSendString("PASS:");
		/* write a system password into EEPROM till i pressed Enter Key */
		while (key != '%')
		{
			HKEYPAD_enGetPressedKey(&key);
			if (key != HKEYPAD_NO_KEY_PRESSED && key != '%')
			{
				HLCD_enSendData('*');
				HEEPROM_enWriteByte(eeprom_index, key);
				eeprom_index++;
			}
		}
		HLCD_enCLearDisplay();
		HLCD_enSendString("PASSWORD CREATED");
		SAVED_PASS=1;
	}

	else if (SAVED_PASS == 1)
	{
		temp_system();
		HLCD_enCLearDisplay();
		ULTRASONIC_enEnable();
		ULTRASONIC_enRead(&distance);
		HLCD_enSendString("DISTANCE = ");
		HLCD_enSendIntNum(distance);
		HLCD_enGoToXY(1, 14);
		HLCD_enSendString("CM");
		u8 *user_pass = (u8*)malloc(11 * sizeof(u8));

		if ((distance >= 0) && (distance <= 15))
		{
			HLCD_enGoToXY(2, 0);
			HLCD_enSendString("PASS:");

			/* Get PW from Keypad and store it in Array till ENTER PRESSED*/
			while (key != '%')
			{
				HKEYPAD_enGetPressedKey(&key);
				if (key != HKEYPAD_NO_KEY_PRESSED && key != '%')
				{
					HLCD_enSendData('*');
					user_pass[userArr_index] = key ;
					userArr_index ++;
				}
			}
			/* When ENTER PRESSED compare each byte with bytes in EEPROM
			 * if the user pass bigger than sys pass return wrong pass*/
			if (userArr_index > eeprom_index)
			{
				wrong_pass = 1;
			}
			/* if user pass less or equal sys pass checks byte by byte*/
			for (u8 i = 0; i < eeprom_index && wrong_pass == 0; i++)
			{
				HEEPROM_enReadByte(i, &data);
				if (user_pass[i] != data)
				{
					wrong_pass = 1;
				}
			}
			/* PASSWORD is correct, open door & see Dashboard
			 * 	1: LEDS ON 		2: LEDS OFF 	3: EXIT */
			if (wrong_pass == 0)
			{
				HLCD_enCLearDisplay();
				HLCD_enSendString("WELCOME AHMED");
				MDIO_enSetPinValue(PC6, HIGH);
				_delay_ms(1000);
				HLCD_enCLearDisplay();
				MDIO_enSetPinValue(PC6, LOW);
				HLCD_enGoToXY(1, 0);
				HLCD_enSendString("1:LEDS ON 2:OFF");
				HLCD_enGoToXY(2, 0);
				HLCD_enSendString("3:EXIT");
				do{
					HKEYPAD_enGetPressedKey(&key);
					if (key != HKEYPAD_NO_KEY_PRESSED)
					{
						HLCD_enGoToXY(2, 11);
						HLCD_enSendData(key);
						if (key == '1')
						{
							HLED_enSetON(HLED_RED_ID);
							HLED_enSetON(HLED_GREN_ID);
							HLED_enSetON(HLED_BLUE_ID);
						}
						else if (key == '2')
						{
							HLED_enSetOFF(HLED_RED_ID);
							HLED_enSetOFF(HLED_GREN_ID);
							HLED_enSetOFF(HLED_BLUE_ID);
						}
						else if(key =='3')
						{
							multiple_wrong = 0;
							MDIO_enSetPinValue(PC6, HIGH);
							_delay_ms(1000);
							MDIO_enSetPinValue(PC6, LOW);
							HLCD_enCLearDisplay();
							free(user_pass);
							break;
						}
					}
				}while(key != '1' || key != '2' || key != '3');
			}
			/* PASSWORD is Incorrect, BUZZ ALERT ONCE */
			else
			{
				multiple_wrong ++;
				free(user_pass);
				HBUZZ_enSetONCE(HBUZZ_ID);
				HLCD_enCLearDisplay();
				HLCD_enGoToXY(1, 0);
				HLCD_enSendString("WRONG PASSWORD");
				HLCD_enGoToXY(2,0);
				HLCD_enSendString("PLEASE TRY AGAIN");
				_delay_ms(500);
				HLCD_enCLearDisplay();

				/* PASSWORD Incorrect THREE times, locked for 2 min */
				while(multiple_wrong == 3)
				{
					TIMER2_enEnableInt();
					HLCD_enGoToXY(1,0);
					HLCD_enSendString("LOCKED FOR 2 MIN!");
					TIMER2_enstart();
				}
				HLCD_enCLearDisplay();
			}// else
		}//  if (distance in range)
		else
		{
			HLCD_enGoToXY(2, 0);
			HLCD_enSendString("SYSTEM OUT RANGE");
		}
	} //else if (saved == 1)
}

void temp_system(void)
{
	u8 temp ;
	HLM35_enTempRead(&temp);

	if (temp <= 25)
	{
		HDCMOTOR_enSetOFF();
	}
	else if (temp > 25 && temp < 30 )
	{
		HDCMOTOR_enSetON(Motor_forward, 50);
	}
	else if (temp >= 30)
	{
		HDCMOTOR_enSetON(Motor_reverse, 100);
	}
}

void Delay_2_min(void)
{
	tick_delay_2_min++;
	if(tick_delay_2_min> (980 * 2))
	{
		multiple_wrong=0;
		tick_delay_2_min=0;
		TIMER2_enstop();
		TIMER2_enDisableInt();
	}
}

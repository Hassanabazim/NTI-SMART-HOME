/*
 * MDIO_prog.c
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATE.h"
#include "MDIO_priv.h"
#include "MDIO_config.h"
#include "MDIO_int.h"


ErrorState_t MDIO_enSetPinDirection(Pin_t copy_enPin, Direction_t copy_enDirection)
{
	ErrorState_t Local_state = SUCCESS;

	u8 Local_u8port = copy_enPin / 10;
	u8 Local_u8pin = copy_enPin % 10 ;

	switch (Local_u8port)
	{
	case PORTA:
		switch(copy_enDirection)
		{
		case INPUT:
			CLC_BIT(DDRA_REG,Local_u8pin);
			break;
		case OUTPUT:
			SET_BIT(DDRA_REG, Local_u8pin);
			break;
		default:
			Local_state = OUT_OF_RANG_ERR;
		}
		break;

		case PORTB:
			switch(copy_enDirection)
			{
			case INPUT:
				CLC_BIT(DDRB_REG,Local_u8pin);
				break;
			case OUTPUT:
				SET_BIT(DDRB_REG, Local_u8pin);
				break;
			default:
				Local_state = OUT_OF_RANG_ERR;
			}
			break;

			case PORTC:
				switch(copy_enDirection)
				{
				case INPUT:
					CLC_BIT(DDRC_REG,Local_u8pin);
					break;
				case OUTPUT:
					SET_BIT(DDRC_REG, Local_u8pin);
					break;
				default:
					Local_state = OUT_OF_RANG_ERR;

				}
				break;

				case PORTD:
					switch(copy_enDirection)
					{
					case INPUT:
						CLC_BIT(DDRD_REG,Local_u8pin);
						break;
					case OUTPUT:
						SET_BIT(DDRD_REG, Local_u8pin);
						break;
					}
					break;

					default:
						Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t MDIO_enSetPinValue(Pin_t copy_enPin, Value_t copy_enValue)
{
	ErrorState_t Local_state = SUCCESS;

	u8 Local_u8port = copy_enPin / 10;
	u8 Local_u8pin = copy_enPin %10 ;

	switch (Local_u8port)
	{
	case PORTA:
		switch(copy_enValue)
		{
		case LOW:
			CLC_BIT(PORTA_REG,Local_u8pin);
			break;
		case HIGH:
			SET_BIT(PORTA_REG,Local_u8pin);
			break;
		default:
			Local_state = OUT_OF_RANG_ERR;
		}
		break;

		case PORTB:
			switch(copy_enValue)
			{
			case LOW:
				CLC_BIT(PORTB_REG,Local_u8pin);
				break;
			case HIGH:
				SET_BIT(PORTB_REG,Local_u8pin);
				break;
			default:
				Local_state = OUT_OF_RANG_ERR;
			}
			break;

			case PORTC:
				switch(copy_enValue)
				{
				case LOW:
					CLC_BIT(PORTC_REG,Local_u8pin);
					break;
				case HIGH:
					SET_BIT(PORTC_REG, Local_u8pin);
					break;
				default:
					Local_state = OUT_OF_RANG_ERR;
				}
				break;

				case PORTD:
					switch(copy_enValue)
					{
					case LOW:
						CLC_BIT(PORTD_REG,Local_u8pin);
						break;
					case HIGH:
						SET_BIT(PORTD_REG, Local_u8pin);
						break;
					default:
						Local_state = OUT_OF_RANG_ERR;
					}
					break;

					default :
						Local_state = OUT_OF_RANG_ERR;
	}

	return Local_state;
}

ErrorState_t MDIO_enSetPortDirection(Port_t copy_enPort, u8 enValue)
{
	ErrorState_t Local_state = SUCCESS;

	switch (copy_enPort)
	{
	case PORTA:
		DDRA_REG = enValue;
		break;

	case PORTB:
		DDRB_REG = enValue;
		break;

	case PORTC:
		DDRC_REG = enValue;
		break;

	case PORTD:
		DDRD_REG = enValue;
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t MDIO_enSetPortValue(Port_t copy_enPort, u8 enValue)
{
	ErrorState_t Local_state = SUCCESS;

	switch (copy_enPort)
	{
	case PORTA:
		PORTA_REG = enValue;
		break;

	case PORTB:
		PORTB_REG = enValue;
		break;

	case PORTC:
		PORTC_REG = enValue;
		break;

	case PORTD:
		PORTD_REG = enValue;
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state;
}

ErrorState_t MDIO_enTogglePin(Pin_t copy_enPin)
{
	ErrorState_t Local_state = SUCCESS;

	u8 Local_u8port = copy_enPin / 10;
	u8 Local_u8pin = copy_enPin %10 ;

	switch (Local_u8port)
	{
	case PORTA:
		TOG_BIT(PORTA_REG,Local_u8pin);
		break;

	case PORTB:
		TOG_BIT(PORTB_REG,Local_u8pin);
		break;

	case PORTC:
		TOG_BIT(PORTC_REG,Local_u8pin);
		break;

	case PORTD:
		TOG_BIT(PORTD_REG,Local_u8pin);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}

	return Local_state;
}

ErrorState_t MDIO_enGetPinValue(Pin_t copy_enPin, Value_t *ptrPinValue)
{
	ErrorState_t Local_state = SUCCESS;

	u8 Local_u8port = copy_enPin / 10;
	u8 Local_u8pin = copy_enPin %10 ;

	switch (Local_u8port)
	{
	case PORTA:
		*ptrPinValue = GET_BIT(PINA_REG,Local_u8pin);
		break;

	case PORTB:
		*ptrPinValue = GET_BIT(PINB_REG,Local_u8pin);
		break;

	case PORTC:
		*ptrPinValue = GET_BIT(PINC_REG,Local_u8pin);
		break;

	case PORTD:
		*ptrPinValue = GET_BIT(PIND_REG,Local_u8pin);
		break;

	default :
		Local_state = OUT_OF_RANG_ERR;
	}
	return Local_state ;
}

ErrorState_t MDIO_enGetPortValue(Port_t copy_enPort, u8 *ptrPortValue)
{
	ErrorState_t Local_state = SUCCESS;

	if (ptrPortValue == NULL)
	{
		Local_state = NULL_PTR_ERR;
	}
	else
	{
		switch (copy_enPort)
		{
		case PORTA:
			*ptrPortValue = PINA_REG;
			break;

		case PORTB:
			*ptrPortValue = PINB_REG;
			break;

		case PORTC:
			*ptrPortValue = PINC_REG;
			break;

		case PORTD:
			*ptrPortValue = PIND_REG;
			break;

		default:
			Local_state = OUT_OF_RANG_ERR;
		}
	}

	return Local_state;
}

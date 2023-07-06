/*
 * MDIO_int.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef MDIO_MDIO_INT_H_
#define MDIO_MDIO_INT_H_

typedef enum {
	PA0 = 10, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
	PB0 = 20, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
	PC0 = 30, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
	PD0 = 40, PD1, PD2, PD3, PD4, PD5, PD6, PD7
}Pin_t;

typedef enum {
	PORTA = 1,
	PORTB,
	PORTC,
	PORTD
}Port_t;

typedef enum {
	LOW,
	HIGH
}Value_t;

typedef enum {
	INPUT,
	OUTPUT
}Direction_t;

ErrorState_t MDIO_enSetPinDirection(Pin_t copy_enPin, Direction_t copy_enDirection);
ErrorState_t MDIO_enSetPinValue(Pin_t copy_enPin, Value_t copy_enValue);
ErrorState_t MDIO_enSetPortDirection(Port_t copy_enPort, u8 enValue);
ErrorState_t MDIO_enSetPortValue(Port_t copy_enPort, u8 enValue);
ErrorState_t MDIO_enTogglePin(Pin_t copy_enPin);
ErrorState_t MDIO_enGetPinValue(Pin_t copy_enPin, Value_t *ptrPinValue);
ErrorState_t MDIO_enGetPortValue(Port_t copy_enPort, u8 *ptrPortValue);



#endif /* MDIO_MDIO_INT_H_ */

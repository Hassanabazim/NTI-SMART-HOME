/*
 * HLCD_config.h
 *
 *  NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */

#ifndef HLCD_HLCD_CONFIG_H_
#define HLCD_HLCD_CONFIG_H_

#define HLCD_MODE   _4BIT_

#define HLCD_RS_PIN   PA1
#define HLCD_EN_PIN   PA2
#define HLCD_RW_PIN


#define HLCD_D4_PIN   PA3
#define HLCD_D5_PIN   PA4
#define HLCD_D6_PIN   PA5
#define HLCD_D7_PIN   PA6

#if(HLCD_MODE == _8BIT_)
#define HLCD_D0_PIN	  PB0
#define HLCD_D1_PIN	  PB1
#define HLCD_D2_PIN	  PB2
#define HLCD_D3_PIN	  PB3
#endif

#endif /* HLCD_HLCD_CONFIG_H_ */

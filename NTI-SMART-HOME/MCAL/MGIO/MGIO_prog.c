/*
 * MGIO_prog.c
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
#include "MGIO_priv.h"
#include "MGIO_config.h"
#include "MGIO_int.h"


ErrorState_t MGIO_enEnable(void)
{
	//SET_BIT(SREG_REG,I_BIT);
	asm("SEI");
	return SUCCESS;
}
ErrorState_t MGIO_enDisable(void)
{
	//CLC_BIT(SREG_REG,I_BIT);
		asm("CLI");
		return SUCCESS;
}

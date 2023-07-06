/*
 * MADC_int.h
 *
 * NTI GRADUATION PROJECT "SMART HOME SYSTEM "
 *
 *  	 Authors: 1- Hassan Abdelazim Abdelsalam
 *	    	 	  2- Abdelrahman Dardeer
 *
 */
#ifndef ADC_ADC_INT_H_
#define ADC_ADC_INT_H_

typedef enum{
	prescaler_2 = 1,
	prescaler_4,
	prescaler_8,
	prescaler_16,
	prescaler_32,
	prescaler_64,
	prescaler_128,
}prescaler_t;

typedef enum{
	vref_AREF,
	vref_AVCC,
	vref_Internal = 3,
}vref_t	;
typedef enum
{
	channel_0,
	channel_1,
	channel_2,
	channel_3,
	channel_4,
	channel_5,
	channel_6,
	channel_7,
}channel_t;

ErrorState_t MADC_enInit(prescaler_t copy_u8presclaer, vref_t copy_vref);
ErrorState_t MADC_enReadChannel(channel_t copy_u8Channel, u16 *ptrValue );

#endif /* ADC_ADC_INT_H_ */

#ifndef _ADC_H
#define _ADC_H

#include "main.h"
#include "MN101AF50D.h"


typedef struct{
	uint_8 Seat_temp_Error:2;
	uint_8 Fan_temp_Error:2;
	uint_8 Water_temp_Error:2;
	uint_8 Moto_Error:2;
}Error_flag;

typedef struct{
	uint_8 num;
	void (*delay_us)(uint_16 n);
	uint_16(*ReadADC)(uint_8 channel);
	Error_flag Error; 
}ADC_Config;

extern ADC_Config adc_set;

void Fun_temp_deal(ADC_Config *p, uint_8 channel);

#endif


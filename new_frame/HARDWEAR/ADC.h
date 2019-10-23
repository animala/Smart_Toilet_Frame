#ifndef _ADC_H
#define _ADC_H

#include "main.h"
#include "MN101AF50D.h"

#define Seat_temp_channel    0x07
#define Wind_temp_channel    0x06
#define Light_temp_channel   0x05
#define Motor_temp_channel   0x04



typedef struct{
	uint_8 num;
	void (*Delay_us)(uint_16 n);
	uint_16(*ReadADC)(uint_8 channel);
	uint_8 Err; 
}ADC_Config;

extern ADC_Config adc_set;



void AD_fun_Init(ADC_Config *p);
void Fun_temp_deal(ADC_Config *p, uint_8 channel);
void Seat_temp_deal(ADC_Config *p);
void Fan_Temp_Deal(ADC_Config *p);
void Get_All_AD(ADC_Config *p);
void All_Temp_Deal(ADC_Config *p);

#endif


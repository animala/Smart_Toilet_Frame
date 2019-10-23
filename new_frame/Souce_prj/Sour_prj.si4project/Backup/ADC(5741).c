#include "ADC.h"

/***********************************************
函数名称：ReadADC
功能描述：
输入参数：
返回参数：
************************************************/
uint_16 ReadADC(uint_8 ADCchannel)
{
	signed int ADC;
	ANCTR1 = ADCchannel;					//select channel
	delay_us(5);								//delay
	ANCTR2 = 0x80;							//START
	while((ANCTR2&0x80) == 0x80);				
	ADC = (uint_16)ANBUF1 << 2;
	ADC = ADC + (ANBUF0 >> 6);
	return ADC; 
}

void Fun_temp_deal(ADC_Config *p, uint_8 channel)
{
	p->ReadADC = ReadADC;
	p->delay_us(channel);

}



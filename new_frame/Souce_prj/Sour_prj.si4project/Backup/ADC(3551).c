#include "ADC.h"




//**********************
//
//  风温表
//
//*********************
const uint Wind_temp_table[]=
{		
	745,	//0°
	736,
	727,
	718,
	709,
	700,
	691,
	682,
	672,
	663,
	653,
	644,
	634,
	625,
	615,
	605,
	595,
	586,
	576,
	566,
	557,
	547,
	538,
	528,
	518,
	509,
	499,
	490,
	480,
	471,
	461,
	452,
	443,
	434,
	425,
	416,
	407,
	398,
	390,
	381,
	373,
	365,
	356,
	348,
	341,
	333,
	325,
	318,
	311,
	303,
	296,
	289,
	283,
	276,
	269,
	263,
	257,
	251,
	245,
	239,
	233,
	227,
	222,
	216,
	211,
	206,
	201,
	196,
	191,
	187,
	182,  //70°
};



//***********************************************
//函数名称：ReadADC
//功能描述：获取AD值，移植的时候更换这个AD值即可
//输入参数：通道口
//返回参数：该通道口的AD值
//************************************************/
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

//***********************************************
//函数名称：ReadADC
//功能描述：获取AD值，移植的时候更换这个AD值即可
//输入参数：通道口
//返回参数：该通道口的AD值
//************************************************/
void AD_fun_Init(ADC_Config *p)
{
	p->ReadADC = ReadADC;
	p->Delay_us = delay_us;	

}

//**********************************
//
//  把AD值处理，对每个AD检测都进行处理
//
//**********************************
uint_16 Temp_deal_fun(ADC_Config *p, uint_8 channel)
{
	static uint_8 AdcCount = 0;	
	static uint_16 AdcBuf[5];
 	uint_16	AdcBufMax;
	uint_16	AdcBufMin;
	uint_16	AdcBufSum;
	uint_16	AdcBufVale;
	uint_8  i;

	AdcBuf[AdcCount] = p->ReadADC(channel);	//处理一个通道的AD值
	AdcCount++;
	if(AdcCount >= 5)  //取5次AD值
	{
		AdcCount = 0;
		AdcBufSum = 0;
		AdcBufMax = AdcBuf[0];
		AdcBufMin = AdcBuf[0];   //清0
		for(i=0; i<5; i++)		//遍历获取最大值和最小值，同时求和
		{
			if(AdcBufMax < AdcBuf[i])
			{
				AdcBufMax = AdcBuf[i];
			}
			if(AdcBufMin > AdcBuf[i])
			{
				AdcBufMin = AdcBuf[i];
			}
			AdcBufSum += AdcBuf[i];	    
		}
		AdcBufVale = (AdcBufSum - AdcBufMax - AdcBufMin) / 3;  //求平均  去掉最大去掉最小求平均
	}
	return AdcBufVale;   //返回处理好的AD值
}

//**********************************
//
//  座温处理函数 
//
//**********************************

void Seat_temp_deal(ADC_Config *p, Status_uion *p)
{
	uint_16 ADtemp;
	uint_8	JieNengTemp;
	ADtemp = Temp_deal_fun(p, Seat_temp_channel);  //取出处理好的座温温度AD值
	if((ADtemp < 30) || (ADtemp > 994))   		 // 短路或者断路
	{
		p->Err |= 0x80;   // 一个字节的 bit 7 bit6 为座温错误位  bit7 位硬件断路开路错误  bit6 为高温错误
	}
	else
	{
		p->Err &= 0x7f;
	}
		Seat.temperature = 0;
	
	while(ADtemp < Wind_temp_table[Seat.temperature])  //获取实际温度值
	{
		Seat.temperature++;
	}
	
	if(Seat.temperature >= 55)					//座温过高
	{
		p->Err |= 0x40;
	}
	else
	{
		p->Err &= 0xbf;
	}

	if((p->Err != 0) && (MachineTest.Flag==0))  //有错误报警
	{
		if(p->Mode_select != 0)
		{
			p->Mode_select = 0;
			work.step = 0;
			work.enable_f = 1;  //还需要再加其他标志位清0	
		}
		if(Status.penkou_f == 1)
		{
			Status.penkou_f = 0;
			penkou.step = 0;
		}
		WaterOut;
	}

	if(Status.PcbTest_f == 0)
	{
		if((Status.power_f)&&(p->Err == 0))
		{
			//------根据环境温度设置节能温度比较值
			if(Entironment.temperature < 10)
			{
				JieNengTemp = 36;
			}
			else if(Entironment.temperature < 15)
			{
				JieNengTemp = 34;
			}
			else if(Entironment.temperature < 20)
			{
				JieNengTemp = 32; 			
			}
			else if(Entironment.temperature < 25)
			{
				JieNengTemp = 30; 			
			}
			else
			{
				JieNengTemp = 25;
			}
			if(Seat.temperature <= JieNengTemp)
			{
				SeatHeat_set;						//--- turn on		
			}
			else if(Seat.temperature >= JieNengTemp+1)
			{
				SeatHeat_clr;							//----turn off
			}
			Seat.Heat_f = 1;
		}

	}
		
}















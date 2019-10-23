#include "ADC.h"

#include "TM1629.h"


ADC_Config adc_set;


//**********************
//
//  ���±�
//
//*********************
const uint Wind_temp_table[]=
{			
	 745,  //0��
	 342,
	 332,
	 323,
	 314,
	 305,
	 296,
	 287,
	 279,
	 271,
	 263,
	 255,
	 248,
	 240,
	 233,
	 226,
	 219,
	 212,
	 206,
	 200,
	 194,
	 188,
	 182,
	 177,
	 171,
	 166,
	 161,
	 156,
	 151,
	 146,
	 142,
	 137,
	 133,
	 129,
	 125,
	 121,
	 117,
	 113,
	 110,
	 106,
	 103,
	 100,
	 97,
	 94,
	 91,
	 88,
	 85,
	 83,
	 80,
	 78,
	 75,
	 73,
	 71,
	 69,
	 67,
	 65,
	 63,
	 61,
	 59,
	 57,
	 56,
	 54,
	 52,
	 51,
	 49,
	 48,
	 46,
	 45,
	 44,
	 43,
	 41,
	 40,
	 39,
	 38,
	 37,
	 36,//75��
};

//**********************
//
//  ���±�
//
//*********************
const uint Seat_temp_table[]=
{		
	745,	//0��
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
	182,  //70��
};

uint_16 temp_save[5];    //�����ADֵ����Ӧÿ��ͨ����

uint_8 AD_addr[4] = 
{
	0x07,   //����
	0x06,	//����
	0x05,	//��
	0x04	//���
};


//***********************************************
//�������ƣ�ReadADC
//������������ȡADֵ����ֲ��ʱ��������ADֵ����
//���������ͨ����
//���ز�������ͨ���ڵ�ADֵ
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
//�������ƣ�ReadADC
//������������ȡADֵ����ֲ��ʱ��������ADֵ����
//���������ͨ����
//���ز�������ͨ���ڵ�ADֵ
//************************************************/
void AD_fun_Init(ADC_Config *p)
{
	p->ReadADC = ReadADC;
	p->Delay_us = delay_us;	

}

//**********************************
//
//  ��ADֵ������ÿ��AD��ⶼ���д���
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

	AdcBuf[AdcCount] = p->ReadADC(channel);	//����һ��ͨ����ADֵ
	AdcCount++;
	if(AdcCount >= 5)  //ȡ5��ADֵ
	{
		AdcCount = 0;
		AdcBufSum = 0;
		AdcBufMax = AdcBuf[0];
		AdcBufMin = AdcBuf[0];   //��0
		for(i=0; i<5; i++)		//������ȡ���ֵ����Сֵ��ͬʱ���
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
		AdcBufVale = (AdcBufSum - AdcBufMax - AdcBufMin) / 3;  //��ƽ��  ȥ�����ȥ����С��ƽ��
		return AdcBufVale;   //���ش���õ�ADֵ
	}
	
}

//**********************************
//
//  ��ADֵ������������AD������겢����
//
//**********************************

void Get_All_AD(ADC_Config *p)
{
	static uint_8 AdcCount = 0; 
	static uint_16 AdcBuf[5];
	uint_16 AdcBufMax;
	uint_16 AdcBufMin;
	uint_16 AdcBufSum;
	uint_16 AdcBufVale;
	uint_8	i;
	uint_8 j,k;		
	for(j=0; j<4; j++)  //�������е�AD���ͨ��
	{
		for(k=0; k<6; k++)
		{
			AdcBuf[k] = p->ReadADC(AD_addr[j]); // �Ѷ�Ӧ��ͨ���Ž�ȥ
			if(k == 5)  //ȡ5��ADֵ
			{
				AdcCount = 0;
				AdcBufSum = 0;
				AdcBufMax = AdcBuf[0];
				AdcBufMin = AdcBuf[0];	 //��0
				for(i=0; i<5; i++)		//������ȡ���ֵ����Сֵ��ͬʱ���
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
				AdcBufVale = (AdcBufSum - AdcBufMax - AdcBufMin) / 3;  //��ƽ��	ȥ�����ȥ����С��ƽ��			
			}
		}
		temp_save[j] = AdcBufVale;   //����ADֵ
	}
}


//**********************************
//
//  ���´����� 
//
//**********************************

void Seat_temp_deal(ADC_Config *p)
{
	uint_16 ADtemp;
	uint_8	JieNengTemp;
	//ADtemp = Temp_deal_fun(p, Seat_temp_channel);  //ȡ������õ������¶�ADֵ
	ADtemp = temp_save[0];
	if((ADtemp < 30) || (ADtemp > 994))   		 // ��·���߶�·
	{
		p->Err |= 0x80;   // һ���ֽڵ� bit 7 bit6 Ϊ���´���λ  bit7 λӲ����·��·����  bit6 Ϊ���´���
	}
	else
	{
		p->Err &= 0x7f;	
		Seat.temperature = 0;
		while(ADtemp < Seat_temp_table[Seat.temperature])  //��ȡʵ���¶�ֵ
		{
			Seat.temperature++;
		}
		
		if(Seat.temperature >= 55)					//���¹���
		{
			p->Err |= 0x40;
		}
		else
		{
			p->Err &= 0xbf;
		}
	}
	if((p->Err != 0) && (MachineTest.Flag==0))  //�д��󱨾�
	{
		if(Status.Mode_select != 0)
		{
			Status.Mode_select = 0;
			work.step = 0;
			work.enable_f = 1;  //����Ҫ�ټ�������־λ��0	
		}
		if(Status.penkou_f == 1)
		{
			Status.penkou_f = 0;
			penkou.step = 0;
		}
		WaterOut;
	}	
	Seat_temp_display(Seat.temperature, p->Err);
	if(Status.PcbTest_f == 0)
	{
		if((Status.power_f)&&(p->Err == 0))
		{
			//------���ݻ����¶����ý����¶ȱȽ�ֵ
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
				SeatHeat_set;							//--- turn on		
			}
			else if(Seat.temperature >= JieNengTemp+1)
			{
				SeatHeat_clr;							//----turn off
			}
			Seat.Heat_f = 1;
		}
	}		
}


//**********************************
//
// 		���´����� 
//
//**********************************

void Fan_Temp_Deal(ADC_Config *p)
{
	uint_16 ADtemp;
	ADtemp = temp_save[1];
	
	if((ADtemp < 10) || (ADtemp>1000))
	{
		p->Err |= 0x20;   // һ���ֽڵ� bit 5 bit4 Ϊ���´���λ  bit5 λӲ����·��·����  bit4 Ϊ���´���
	}
	else
	{
		p->Err &= 0xdf;	

		Drying.temperature = 0;
		
		while(ADtemp < Wind_temp_table[Drying.temperature])
		{
			Drying.temperature++;
		}
		if(Drying.temperature >= 65)					//���¹���
		{
			p->Err |= 0x10;					//���±���
		}
		else
		{
			p->Err &= 0xef;
		}		
	}	
	Room_temp_display(Drying.temperature, p->Err);
}



//***********************
//
//	�¶���ش�����
//
//************************
void All_Temp_Deal(ADC_Config *p)
{
	Get_All_AD(p);
	Seat_temp_deal(p);
	Fan_Temp_Deal(p);

}




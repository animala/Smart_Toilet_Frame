#include "TM1629.h"

TM1629B_CB TM1629B;
TM1629_Fun TM_1629;


bits_uion Bits_set;


//����ʱ��ṹ�壬���Լ���ʱ
extern timer_uion timer; 
/************�����Ƕ˿�ÿһλ��Ӧ�����******************/
#define PORT      Bits_set.num


//���ֶ�Ӧ�ı��
const uint_8 Num_table[16] = {
			0xFC,	//0
			0xA1,	//1
			0x7A,	//2
			0xF2,	//3
			0xA6,	//4
			0xD6,	//5
			0xDE,	//6
			0xB0,	//7
			0xFE,	//8
			0xF6,	//9
			0xBE,	//A
			0xCE,	//b
			0x5C,	//c
			0xEA,	//d
			0x5E,	//E
			0x1E,	//F
};

const uint_8 water_gear_table[5] = {
	
			0x00,
			0x01,
			0x03,
			0x0b,
			0x0f
};

const uint_8 seat_gear_table[5] = {

			0x00,
			0x08,
			0x0c,
			0x0e,
			0x0f
};



//���µ�Stb��Sck��Sda Ϊ��ֲ��Ҫ�޸ĵĵط�
//��ͬ�ĵ�Ƭ���˿�����ߵͷ�ʽ��һ��
//���ֻҪ�޸�����ļ���ʹ��

/*****************************/
//	 Stb���� 
//  1 �����  0�����
/******************************/
void Stb_Set(uint_8 cmd)
{
	if(cmd == 1)
	{
		TM1629BStbOn;
	}
	else
	{
		TM1629BStbOff;
	}
}

//*****************************
//	 Sck����
//  1 �����  0�����
/******************************/
void Sck_Set(uint_8 cmd)
{
	if(cmd == 1)
	{
		TM1629BSckOn;
	}
	else
	{
		TM1629BSckOff;
	}
}

/*****************************/
//	 Sda����
//  1 �����  0�����
/******************************/
void Sda_Set(uint_8 cmd)
{
	if(cmd == 1)
	{
		TM1629BSdaOn;
	}
	else
	{
		TM1629BSdaOff;
	}
}

/*****************************/
//	 Sda�˿����÷���
//  1 ���  0����
/******************************/
void Sda_Dir_Set(uint_8 cmd)
{
	if(cmd == 1)
	{
		TM1629BSdaDirOut;
	}
	else
	{
		TM1629BSdaDirIn;
	}
}
/*****************************/
//	 Sda��ȡ
/******************************/
uint_8 TM1629_Sda_Read(void)
{
	return TM1629BSdaRead;
}

/************************************/
//
// ����Ϊ�ײ���������
//
/*************************************/



//************************************
//
// 1629��ȡ�ֽں���������1629�ṹ��
//
/*************************************/
uint_8 TM1629_Read_Byte(TM1629_Fun *p)
{
	uint_8	i = 0;
	uint_8	data = 0;
	p->TM1629_Sda_Dir_Set(0);  //set in
	p->delay_us(5);
	for(i=0;i<8;i++)
	{
		p->TM1629_Sck_Set(0);
		p->delay_us(5);
		data = data >> 1;
		if(p->TM1629_Sda_Read() == 0x08)
		{
			data |= 0x80;
		}
		else 
		{
			data &= 0x7f;
		}
		p->TM1629_Sck_Set(1);
		p->delay_us(5);
	}
	p->TM1629_Sda_Dir_Set(1);  //set out
	return data;
}

//************************************
//
// 1629д�ֽں���������1629�ṹ��,������
//
/*************************************/
void TM1629_Write_Byte(TM1629_Fun *p, uint_8 data)
{
	uint_8	i;
	p->TM1629_Sck_Set(0);
	p->delay_us(5);
	for(i=8; i>0; i--)
	{
		if(data & 0x01)
		{
			p->TM1629_Sda_Set(1);
		}
		else 
		{
			p->TM1629_Sda_Set(0);
		}
		data = (data >> 1);   			//right shift
		p->delay_us(5);
		p->TM1629_Sck_Set(1);
		p->delay_us(5);
		p->TM1629_Sck_Set(0);
		p->delay_us(5);
	}	
}

/******************************
//TM1629_Fun *p ����ṹ��
//��ʾBUFFER����
//BUFFER����
//DisChoice:��ʾ�ػ��Լ�����
******************************/
void TM1629_Display(TM1629_Fun *p, uint_8 *DisBuffer, uint_8 BufferSize, uint_8 DisChioce)
{
	uint_8	i;
	if(TM1629B.DisFlag)
	{
		TM1629B.DisFlag=0;	
		p->TM1629_Stb_Set(0);
		TM1629_Write_Byte(p,DisMode);		//set mode
		p->TM1629_Stb_Set(1);	
		p->delay_us(5);
		p->TM1629_Stb_Set(0);
		TM1629_Write_Byte(p,SetWrite);		//set atuomatic add one	
		p->TM1629_Stb_Set(1);
		p->delay_us(5);
		p->TM1629_Stb_Set(0);
		p->delay_us(5);
		TM1629_Write_Byte(p,SetAddress);   //set start address
		for(i=0; i<BufferSize; i++)
		{
			TM1629_Write_Byte(p,DisBuffer[i]);	
		}
		p->TM1629_Stb_Set(1);
		p->delay_us(5);
		p->TM1629_Stb_Set(0);
		TM1629_Write_Byte(p,DisChioce);		//display turn on
		p->TM1629_Stb_Set(1);
	}
}

/************************************/
//
//1629��ʼ��
//
/**************************************/
void TM1629_Init(TM1629_Fun *p)
{
	uint_8	i;	
	p->delay_us = delay_us;
	p->TM1629_Stb_Set = Stb_Set;
	p->TM1629_Sck_Set = Sck_Set;
	p->TM1629_Sda_Set = Sda_Set;
	p->TM1629_Sda_Dir_Set = Sda_Dir_Set;
	
	TM1629B.DisFlag = 1;
	for(i=0;i<LedDisBufSize;i++)
	{
		TM1629B.DisBuf[i]=0x00;
	}
	TM1629_Display(p,TM1629B.DisBuf,LedDisBufSize,SetDisOn);
}


/************************************/
//
// ����Ϊ��ʾ���ݺ���
//
/*************************************/

/******************************
//num : Ҫ��ʾ������,������ͼ����ʾ
//select���ڼ����������ʾ
//dir: ����߻����ұߵ������
******************************/
void Display_Num(uint_8 num, uint_8 select, uint_8 dir)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = Num_table[num];  //����˿�ֱ���������ֶ�Ӧ��8λ��ֵ
	//���¾��Ƕ���ߺ��ұߵ�����ܽ���λ�����Ӷ���ʾ����
	temp = Bits_set.num;
	for(i = 0; i < 7; i++)
	{
		if ((temp >> (7 - i)) & 0x01 != 0)
			TM1629B.DisBuf[2 * i + dir] |= 0x01 << select;
		else
			TM1629B.DisBuf[2 * i + dir] &= ~(0x01 << select);
	}
}

/******************************
//
//ˮ�µ�λ������
//
******************************/
void Water_Gear_display(uint_8 num)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = water_gear_table[num];	//����˿�ֱ���������ֶ�Ӧ��8λ��ֵ
	//���¾��Ƕ���ߺ��ұߵ�����ܽ���λ�����Ӷ���ʾ����
	temp = Bits_set.num;
	for(i = 0; i < 4; i++)
	{
		if ((temp >> i) & 0x01 != 0)
			TM1629B.DisBuf[6 - i * 2] |= 0x01 << 0;
		else
			TM1629B.DisBuf[6 - i * 2] &= ~(0x01 << 0);
	}
}


/******************************
//
//���µ�λ������
//
******************************/
void Seat_Gear_display(uint_8 num)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = seat_gear_table[num];	//����˿�ֱ���������ֶ�Ӧ��8λ��ֵ
	//���¾��Ƕ���ߺ��ұߵ�����ܽ���λ�����Ӷ���ʾ����
	temp = Bits_set.num;
	for(i = 0; i < 4; i++)
	{
		if ((temp >> (3 - i)) & 0x01 != 0)
			TM1629B.DisBuf[8 + i * 2] |= 0x01 << 0;
		else
			TM1629B.DisBuf[8 + i * 2] &= ~(0x01 << 0);
	}
}


/******************************
//	ͼ����ʾ����
//dir : 1 buffe[15] 0 buffe[14] 
//cmd : 1 ��ʾ  0 �ر�
//select���ڼ���ͼ����ʾ
******************************/
void Display_Icon(int_8 dir, uint_8 select, uint_8 cmd )
{
	if(cmd == 1)
	TM1629B.DisBuf[14 + dir] |= 0x01 << select;
	else
	TM1629B.DisBuf[14 + dir] &= ~(0x01 << select);	
}


/*****************************************************************************************
//	��ʾ��λ�����¶�
//select: ѡ���������������ʾ����Ϊÿ����������������ģ�����ֻȡ��һ������ܵ�λ�ü��ɣ�
//dir:    ��߻����ұߵ������
//temp��  ��ʾ���¶�ֵ
//���� ��4��5��dir 0 �ػ��� 6��7 dir 1 ���� 0 1 2 3 dir 1  ˮ�� 6 7 dir 1 ���� 3 2 dir0  ���� 2 3 dir 1 
******************************************************************************************/
void Display_Temp(uint_8 select, uint_8 temp, uint_8 dir)
{
	uint_8 Temp_H = 0;
	uint_8 Temp_L = 0;
	
	Temp_H = temp / 10;  	//ȡ10λ
	Temp_L = temp % 10;		//ȡ��λ
		
	//��������������ܴ���
	if((select == 3) && (dir == 0))
	{
		//��ʮλ��ѡ��ĵ�һ�������
		Display_Num(Temp_H, select, dir);
		//�Ѹ�λ��ѡ��ĵ�2�������
		Display_Num(Temp_L, select-1, dir);	
	}
	else
	{
		//��ʮλ��ѡ��ĵ�һ�������
		Display_Num(Temp_H, select, dir);
		//�Ѹ�λ��ѡ��ĵ�2�������
		Display_Num(Temp_L, select+1, dir);
	}
}

//����ͼ��
void ON_Icon(uint_8 num)
{
	Display_Icon(0,4,num);
	Display_Icon(0,5,num);
}
//��Դͼ��
void Power_Icon(uint_8 num)
{
	Display_Icon(0,6,num);
}
//����ͼ��
void Energy_Icon(uint_8 num)
{
	Display_Icon(0,1,num);
}
//�ػ�ͼ��
void Off_Icon(uint_8 num)
{
	Display_Icon(0,7,num);
	Display_Icon(0,3,num);
}
//ð��
void Colon_Icon(uint_8 num)
{
	Display_Icon(0,2,num);
}
//ˮ�º͡�C��ʾ
void Warter_Temp(uint_8 num)
{
	Display_Icon(1,0,num);
	Display_Icon(1,1,num);
	Display_Icon(-8,1,num);
}
//���º͡�C��ʾ
void Room_Temp(uint_8 num)
{
	Display_Icon(1,2,num);
	Display_Icon(1,3,num);
	Display_Icon(-10,1,num);
}
//���º͡�C��ʾ
void Seat_Temp(uint_8 num)
{
	Display_Icon(1,4,num);
	Display_Icon(1,5,num);
	Display_Icon(-14,1,num);
}

//�����������ʾ
void All_show_num(uint_8 num)
{
	uint_8 i = 2;
	uint_8 j = 0;
	for(; i < 8; i++)
	{
		Display_Num(num,i,0);  //������������ֻ��2��ʼ
	}
	for(; j < 8; j++)
	{
		Display_Num(num,j,1);  //�����ұ�����ܴ�0��ʼ
	}
}
//ȫ��Ļ��ʾ
void Display_all(uint_8 num)
{
	uint_8 i;
	if(num == 1)
	{
		for(i=0;i<LedDisBufSize;i++)
		{
			TM1629B.DisBuf[i]=0xff;
		}
	}
	else
	{
		for(i=0;i<LedDisBufSize;i++)
		{
			TM1629B.DisBuf[i]=0x00;
		}
	}
}

/***********************/
//
// �ѵ�λͼ���������ʾ
//
/*********************/
void Display_Icon_fun(Status_uion *S)
{

	Water_Gear_display(S->Icon.water_gear+1);  //��ʾˮ�µ�λ
	Seat_Gear_display(S->Icon.seat_gear+1);     //��ʾ���µ�λ
	Energy_Icon(S->Icon.energy_disp);      //����ͼ��
	Power_Icon(S->Icon.power_disp);       //��Դͼ��
	
}



/*****************************************************************************************
//	��ʾ���Լ����
//���룺���
//���ܣ���ȫ����˸3�Σ�Ȼ��ÿһ��ͼ����һ��ʾ����������ͬʱ��ʾ0 - 9
******************************************************************************************/

void Check_Func_deal(uint_8 id)
{		
		uint_8 Value[33] = {0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,3,4,1,2,3,4,0,1,2,3,4,5,6,7,8,9};
		Auto_Chaeck Icon_index[33] ={
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��
			&Display_all,		//ȫ��ȫ��		
			&ON_Icon, 			//ONͼ��
			&Power_Icon, 		//��Դͼ��	
			&Energy_Icon, 		//����ͼ��
			&Off_Icon, 			//offͼ��
			&Colon_Icon, 		//ð��
			&Warter_Temp, 		//ˮ�¡���C
			&Room_Temp, 		//���¡���C
			&Seat_Temp,			//���¡���C
			&Water_Gear_display, 		//ˮ�µȼ�
			&Water_Gear_display, 		//ˮ�µȼ�
			&Water_Gear_display, 		//ˮ�µȼ�
			&Water_Gear_display, 		//ˮ�µȼ�
			&Seat_Gear_display,			//���µȼ�
			&Seat_Gear_display,			//���µȼ�
			&Seat_Gear_display,			//���µȼ�
			&Seat_Gear_display,			//���µȼ�
			&All_show_num,		//�����������ʾ
		};
		if(id > 23)
		{	
			Auto_Chaeck Show = Icon_index[23];
			(*Show)(Value[id]);
		}		
		else
		{
			Auto_Chaeck Show = Icon_index[id];
		    (*Show)(Value[id]);
		}
		
		TM1629B.DisFlag = 1;
}




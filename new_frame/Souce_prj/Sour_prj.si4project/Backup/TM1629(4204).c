#include "TM1629.h"

TM1629B_CB TM1629B;
TM1629_Fun TM_1629;


bits_uion Bits_set;


//引用时间结构体，给自检延时
extern timer_uion timer; 
/************以下是端口每一位对应数码管******************/
#define PORT      Bits_set.num


//数字对应的表格
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



//以下的Stb、Sck、Sda 为移植需要修改的地方
//不同的单片机端口输出高低方式不一样
//因此只要修改下面的即可使用

/*****************************/
//	 Stb设置 
//  1 输出高  0输出低
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
//	 Sck设置
//  1 输出高  0输出低
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
//	 Sda设置
//  1 输出高  0输出低
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
//	 Sda端口设置方向
//  1 输出  0输入
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
//	 Sda读取
/******************************/
uint_8 TM1629_Sda_Read(void)
{
	return TM1629BSdaRead;
}

/************************************/
//
// 以下为底层驱动函数
//
/*************************************/



//************************************
//
// 1629读取字节函数，输入1629结构体
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
// 1629写字节函数，输入1629结构体,和数据
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
//TM1629_Fun *p 传入结构体
//显示BUFFER内容
//BUFFER长度
//DisChoice:显示关或开以及亮度
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
//1629初始化
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
// 以下为显示内容函数
//
/*************************************/

/******************************
//num : 要显示的数字,不包括图标显示
//select：第几个数码管显示
//dir: 在左边还是右边的数码管
******************************/
void Display_Num(uint_8 num, uint_8 select, uint_8 dir)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = Num_table[num];  //这里端口直接输入数字对应的8位的值
	//以下就是对左边和右边的数码管进行位操作从而显示数字
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
//水温档位批处理
//
******************************/
void Water_Gear_display(uint_8 num)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = water_gear_table[num];	//这里端口直接输入数字对应的8位的值
	//以下就是对左边和右边的数码管进行位操作从而显示数字
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
//座温档位批处理
//
******************************/
void Seat_Gear_display(uint_8 num)
{
	uint_8 temp = 0;
	uint_8 i = 0;
	TM1629B.DisFlag = 1; 
	PORT = seat_gear_table[num];	//这里端口直接输入数字对应的8位的值
	//以下就是对左边和右边的数码管进行位操作从而显示数字
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
//	图标显示操作
//dir : 1 buffe[15] 0 buffe[14] 
//cmd : 1 显示  0 关闭
//select：第几个图标显示
******************************/
void Display_Icon(int_8 dir, uint_8 select, uint_8 cmd )
{
	if(cmd == 1)
	TM1629B.DisBuf[14 + dir] |= 0x01 << select;
	else
	TM1629B.DisBuf[14 + dir] &= ~(0x01 << select);	
}


/*****************************************************************************************
//	显示两位数字温度
//select: 选择哪两个数码管显示（因为每两个数码管是连续的，所以只取第一个数码管的位置即可）
//dir:    左边还是右边的数码管
//temp：  显示的温度值
//开机 ：4，5，dir 0 关机： 6，7 dir 1 数字 0 1 2 3 dir 1  水温 6 7 dir 1 室温 3 2 dir0  座温 2 3 dir 1 
******************************************************************************************/
void Display_Temp(uint_8 select, uint_8 temp, uint_8 dir)
{
	uint_8 Temp_H = 0;
	uint_8 Temp_L = 0;
	
	Temp_H = temp / 10;  	//取10位
	Temp_L = temp % 10;		//取个位
		
	//单独对室温数码管处理
	if((select == 3) && (dir == 0))
	{
		//把十位放选择的第一个数码管
		Display_Num(Temp_H, select, dir);
		//把个位放选择的第2个数码管
		Display_Num(Temp_L, select-1, dir);	
	}
	else
	{
		//把十位放选择的第一个数码管
		Display_Num(Temp_H, select, dir);
		//把个位放选择的第2个数码管
		Display_Num(Temp_L, select+1, dir);
	}
}

//开机图标
void ON_Icon(uint_8 num)
{
	Display_Icon(0,4,num);
	Display_Icon(0,5,num);
}
//电源图标
void Power_Icon(uint_8 num)
{
	Display_Icon(0,6,num);
}
//节能图标
void Energy_Icon(uint_8 num)
{
	Display_Icon(0,1,num);
}
//关机图标
void Off_Icon(uint_8 num)
{
	Display_Icon(0,7,num);
	Display_Icon(0,3,num);
}
//冒号
void Colon_Icon(uint_8 num)
{
	Display_Icon(0,2,num);
}
//水温和°C显示
void Warter_Temp(uint_8 num)
{
	Display_Icon(1,0,num);
	Display_Icon(1,1,num);
	Display_Icon(-8,1,num);
}
//室温和°C显示
void Room_Temp(uint_8 num)
{
	Display_Icon(1,2,num);
	Display_Icon(1,3,num);
	Display_Icon(-10,1,num);
}
//座温和°C显示
void Seat_Temp(uint_8 num)
{
	Display_Icon(1,4,num);
	Display_Icon(1,5,num);
	Display_Icon(-14,1,num);
}

//所有数码管显示
void All_show_num(uint_8 num)
{
	uint_8 i = 2;
	uint_8 j = 0;
	for(; i < 8; i++)
	{
		Display_Num(num,i,0);  //处理左边数码管只从2开始
	}
	for(; j < 8; j++)
	{
		Display_Num(num,j,1);  //处理右边数码管从0开始
	}
}
//全屏幕显示
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
// 把档位图标放这里显示
//
/*********************/
void Display_Icon_fun(Status_uion *S)
{

	Water_Gear_display(S->Icon.water_gear+1);  //显示水温档位
	Seat_Gear_display(S->Icon.seat_gear+1);     //显示座温档位
	Energy_Icon(S->Icon.energy_disp);      //节能图标
	Power_Icon(S->Icon.power_disp);       //电源图标
	
}



/*****************************************************************************************
//	显示屏自检程序
//输入：标号
//功能：先全部闪烁3次，然后每一个图标逐一显示，最后数码管同时显示0 - 9
******************************************************************************************/

void Check_Func_deal(uint_8 id)
{		
		uint_8 Value[33] = {0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,3,4,1,2,3,4,0,1,2,3,4,5,6,7,8,9};
		Auto_Chaeck Icon_index[33] ={
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭
			&Display_all,		//全亮全灭		
			&ON_Icon, 			//ON图标
			&Power_Icon, 		//电源图标	
			&Energy_Icon, 		//节能图标
			&Off_Icon, 			//off图标
			&Colon_Icon, 		//冒号
			&Warter_Temp, 		//水温、°C
			&Room_Temp, 		//室温、°C
			&Seat_Temp,			//座温、°C
			&Water_Gear_display, 		//水温等级
			&Water_Gear_display, 		//水温等级
			&Water_Gear_display, 		//水温等级
			&Water_Gear_display, 		//水温等级
			&Seat_Gear_display,			//座温等级
			&Seat_Gear_display,			//座温等级
			&Seat_Gear_display,			//座温等级
			&Seat_Gear_display,			//座温等级
			&All_show_num,		//所有数码管显示
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




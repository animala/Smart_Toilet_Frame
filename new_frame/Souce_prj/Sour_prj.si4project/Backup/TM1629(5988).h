#ifndef _TM1629_H
#define _TM1629_H

#include "MN101AF50D.h"
#include "main.h"

//----------TM1629B 驱动接口
#define	TM1629BStbOn		P2OUT|=(1<<2)        
#define	TM1629BStbOff		(P2OUT&=~(1<<2))

#define	TM1629BSckOn		P2OUT|=(1<<0)        
#define	TM1629BSckOff		(P2OUT&=~(1<<0))

#define	TM1629BSdaOn		P2OUT|=(1<<1)        
#define	TM1629BSdaOff		(P2OUT&=~(1<<1))
#define	TM1629BSdaDirOut	P2DIR|=(1<<1)        
#define	TM1629BSdaDirIn		P2DIR&=(~(1<<1))
#define	TM1629BSdaRead		(P2IN&0x02)	
#define	TM1629BSdaVale		0x02
//------------显示屏命令字
#define SetWrite		0x40	//---地址增量模式写数据
#define SetAddressFix	0x44	//---地址固定模式写数据
#define	SetRead			0x42	//---读按键命令
#define	DisMode			0x03	//---显示模式设置(7位10段)
#define SetDisOn		0x8f  	//---显示控制命令 open
#define SetDisOff		0x87  	//---显示控制命令 close
#define SetAddress		0xc0	//---设置显示数据地址：00H~0DH
#define	LedDisBufSize	16
//-----------------------------
//---------按键定义
#define	Nokey			0x00	//--无按键	
#define	KeyStop			0x40	//--停止
#define	KeyNvXing		0x04 	  //--女用
#define	KeyTunBu		0x80	//--男用
#define	KeyDring		0x08	//--风温

#define	KeyDengSW		0x84	//------灯控开关
#define	KeyAutoWashSW	0x88	//------自动冲水开关
#define	KeyChuChouSW	0x0c	//------除臭开关
#define	KeyInitSW		0x48	//------EEPROM初始化

#define ON 1
#define OFF 0


//声明一个结构体，成员是一个占1位的变量
typedef struct{
		uint_8 bit0:1;			//声明一个结构体位域，代表右边显示的数码管com
		uint_8 bit1:1;
		uint_8 bit2:1;
		uint_8 bit3:1;
		uint_8 bit4:1;
		uint_8 bit5:1;
		uint_8 bit6:1;
		uint_8 bit7:1;
}Bits;
//声明一个联合体，包含一个变量 和 8个1位变量的结构体
typedef union{
	uint_8 num;
	Bits bit;
}bits_uion;
//-------------------------数据结构
typedef struct{
	uint_8	DisBuf[16];
	uint_8	KeyBuf[5];
	uint_8	flag:1;
	uint_8	DisFlag;
	uint_8	DisFlashFlag;
	//-----------	uint_8	YesCount;
	uint_8	KeyData;
	uint_16	YesCount;
	uint_8	NoCount;
	uint_8	KeyDataBuf;	
	uint_8	KeyDown_f:1;
	uint_8	KeyLongDown_f:1;
	uint_8	KeyUp_f:1;
	uint_8	Updata_f:1;
	uint_8  Disp_Check_f:1;    //自检标志位
	uint_8  Disp_Check_Count;   //自检延时时间
	
	}TM1629B_CB;

extern TM1629B_CB TM1629B;
/************驱动功能结构****************************/
typedef struct{
	void(*delay_us)(uint_16 t);
	void(*TM1629_Stb_Set)(uint_8 cmd);	
	void(*TM1629_Sck_Set)(uint_8 cmd);	
	void(*TM1629_Sda_Set)(uint_8 cmd);	
	void(*TM1629_Sda_Dir_Set)(uint_8 cmd);
	uint_8(*TM1629_Sda_Read)(void);	 
}TM1629_Fun;
extern TM1629_Fun TM_1629;

//声明一个指针函数类型，用于自检程序调用
typedef void (*Auto_Chaeck)(uint_8 cmd);


uint_8 TM1629_Read_Byte(TM1629_Fun *p);
void TM1629_Write_Byte(TM1629_Fun *p, uint_8 data);
void TM1629_Display(TM1629_Fun *p, uint_8 *DisBuffer, uint_8 BufferSizer, uint_8 DisChioce);
void Display_Num(uint_8 num, uint_8 select, uint_8 dir);
void TM1629_ReadKey(TM1629_Fun *p);
void TM1629_Init(TM1629_Fun *p);
void Display_Icon(int_8 dir, uint_8 cmd, uint_8 select);
void Water_Gear_display(uint_8 num);
void Display_Temp(uint_8 select, uint_8 temp, uint_8 dir);
void Digital_Check(void);
void All_show_num(uint_8 num);
void Check_Func_deal(uint_8 id);
void Seat_Gear_display(uint_8 num);
void Display_Icon_fun(Status_uion *S);
void ON_Icon(uint_8 num);
void Display_Icon_select(uint_8 num);
void Room_temp_display(uint_8 temp, uint_8 err);
void Seat_temp_display(uint_8 temp, uint_8 err);
void flash_num(void);


#endif

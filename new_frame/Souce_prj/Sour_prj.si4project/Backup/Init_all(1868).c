
#include "MN101AF50D.h"
#include "math.h"
#include "main.h"

#include "Init_all.h"
#include "Pump_pwm.h"
/*********************************************************/
//	IO口初始化
//所有的IO口初始化
/*********************************************************/
void IO_Init(void)
{
		/*----------pa口设置-------
	pa0增压泵
	pa1进水阀
	pa2烘干加热
	pa3座圈加热
	pa4电极检测
	pa5光敏电阻
	pa6风温
	pa7座温传感器
	---------------------------*/
	PAPLU=0x00;				//---------Pull up PA3 PA6, resistor
	PAOUT=0x0e;				//--------setPA1, pA2 pA3 is high
	PADIR=0x0f;				//---------set  PA1 is output
	//----------------------adc
	PAIMD = 0xf0; 			//--------- Set   PA4 PA5,pa6 pa7  adin 
	ANCTR0 = 0x20; 			//----------Ftad=Fs/8=Fpll/16=16*1000000/16	  Tad=1/Ftad=1us		
	ANCTR0 = 0x88; 			//sample hold time is Tad*8. Conversion clock fs/2.ladder resistance is On.
	ANCTR2=0;				//stop AD
	//---------------------------------------------------------
	/*----------p0口设置-----
	P00	Tdo		编程端口
	p01 tsck	编程端口
	p02 IN		Rx0		即热模块接收
	p03 Out		Tx0		即热模块输出
	p04	In		IR		红外接收
	p05	Out		BUZZWE	
	p06	In		入座感应		
	冲水检测
	---------------------------*/
	P0PLUD=0x00;			
	P0OUT=0x00;	
	P0DIR=0x28;				
	/*----------p垴y设帜邢-
	p20	out		DIS_CLK
	p21	out		DIS_DIO
	p22	out		DIS_STB
	p23	IN		过零
	p24	IN		水位检测
	p27	rest    MCU复位
	---------------------------*/
	P2PLU=0x00;			
	P2OUT=0xff;	
	P2DIR=0x87;				//set P20,P21 p22is input
	/*----------p5口设置-----
	p50	Out		K2
	p51	Out		1A		
	p52	Out		1B
	p53	Out		1C
	p54	Out		1D
	p55	Out		PUMPB
	p56	Out		自动冲水
	p57	Out		暖风风机
	---------------------------*/
	P5PLUD=0x00;
	P5OUT=0x00;                 
	P5DIR=0xff;
	/*----------p6口设置-----
	p62	Out		2D	
	p63	Out		2C
	p64	Out		2B
	p65	Out		2A
	p66	Out		旋钮CLK
	p67	Out		旋钮DATA
	---------------------------*/
	P6PLU=0x00; 				
	P6OUT=0x00;    //set p62 is high
	P6DIR=0xff;	//
	/*----------p7口设置---
	p70	out		key1
	p71	out		除臭风机
	p72	out		冲水板信号
	p73	out		IIC_SClk
	p74	out		IIC_SDA
	p75	out		WiFi-Tx		
	p76	In		WiFi-Rx
	p77	out		夜灯
	---------------------------*/
	P7PLUD=0x00; 				
	P7OUT=0x00;                 
	P7DIR=0xbf;	
	/*----------p8口设置---
	p80	out	Co3
	p81	out	C02
	p82	In	C01
	p83	out	3A
	p84	out	3B
	p85	out	回音
	p86	out	3C
	p87	out	3D
	---------------------------*/
	P8PLUD=0x00; 			
	P8OUT=0x00;                 
	P8DIR=0xfb;					
	/*----------p9口设置-----
	p90	out	即热模块电源控制
	p91	out	Wifi电源控制
	p94	out	PUMPA
	---------------------------*/
	P9PLUD=0x00;					//
	P9OUT=0x00;					// is high
	P9DIR=0xff;					//All  is output
}

//*********************************************************/
//
//  结构体成员的初始化
//
//*********************************************************/
void State_init(void)
{

	Water.DangWei = 3;				//-----水温档位
	Water.DangWei = 0;
	Water.StopHotDelay = 0;
	Water.Hot_f = 0;
	Water.WaterIn_f = 0;			//-----进水	
	Water.TempDeal_time = 0;
	
	Seat.DangWei = 3;				//-----座温档位
	Seat.Heat_f = 0;
	Seat.Flag = 0;
	
	Drying.DangWei = 1;
	
	TunBu.pressure = 3;
	TunBu.PGLevel = 3;
	
	NvXing.pressure = 3;
	NvXing.PGLevel = 3;	
	Enfant.Dring_f = 0;
	
	Entironment.time = 0;
	Entironment.temperature = 25;
	
	SoftPowerDeal.Delay = T10Min;
	SoftPowerDeal.Softpower_f = 1;
	
	Status.power_f = 1;			//-----开机
	Status.seat_f = 0;				//---入座标志位清0
	Status.tunbu_f = 0;				
	Status.nvxing_f = 0;
	Status.enfant_f = 0;	
	Status.dring_f = 0;
	Status.ShuiWenSet_f = 1;
	Status.ZuoWenSet_f = 0;
	Status.jieneng_f = 1;
	Status.auto_f = 1;
	Status.PowerEnd_f = 0;
	Status.QiBeng_f = 0;
	Status.test_f = 0;
	Status.PcbTest_f = 0;
	Status.dengkong_f = 1;
	Status.chuchou_e = 1;	
	/*----新框架设定---*/
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	Status.Auto_clear = 0;
	Status.Icon.water_press_gear = 0;
	Status.Icon.seat_gear = 0;
	Status.Icon.energy_disp = 0;	
	
	MachineTest.Flag = 0;
	MachineTest.Step = 0;
	MachineTest.CheckWifiSignal_f = 0;
	chongshui.delay1 = 0;
	
//	LightInduce.Timer=T10Min;

	LiquidDeal.Flag = 0;	
	LiquidDeal.Frist_f = 1;	
	LiquidDeal.Stop_f = 0;
	LiquidDeal.ADDLiquidCount = 1;
	LiquidDeal.Auto_f = 1;	
	
	work.LianXu_f = 0;
	work.LianXuBuf = 0;	
	work.Start_f = 0;

	CoverSeat.SeatDirStatus = 0;
	CoverSeat.CoverDirStatus = 0;
	CoverSeat.SeatOpen_f = 0;
	CoverSeat.CoverOpen_f = 0;

	//CO3_set_auto;
//	WifiPowerOn;	
	
	buz_set(1,30,30);
}

void Sys_Init(void)
{	
	/*******************sys set**************************************/
	asm (" and 0b00001111,PSW \n"); 	/* Disable all maskable interrupts */

	/************
		CPUM = 0x10;		//--- Set normal mode 
							//--- Set fs=fosc*1 
		MEMCTR = 0xCB;		//--- Set special register area 3 wait cycles 
							//--- Set interrupt vector base 
							//--- Set single chip mode 
	
		OSCCNT=0x13;		//----bit5~~bit7 选择分频比，无分频。 			
							//---bit4, 高速震荡做外围功能，1:禁用，0:使用
							//---bit3,bit2 预留
							//---bit1,	=1选择外部高速震荡。 =0选择内部高速震荡
							//---bit0	=1高速震荡入口，=1P25/P26做为普通IO口
		RCCNT=0x81; 	//----bit7	=1
							//---bit6 to bit2 预留 
							//---bit1	选择内部高速震荡频率 =1 16MH	 =0 20M
							//---bit0	=1禁止内部高速  =0 使能内部高速
		OSCSCNT=0x00;		//----bit7 to bit 1 预留
							//---BIT0  =1低速震荡入口   =0 P90/P91 做为普通IO口
	
		OSCLOCK=0x01;		//----bit7 to bit 1 预留	
							//---bit0 =1 锁存OSCCNT/OSCSCNT	=0 允许修改OSCCNT/OSCSCNT
	
		
		PLLCNT=0x10;		//----bit7 to bit 4   输入频率倍频。 
							//---bit3 to bit 2 预留
		PLLCNT = PLLCNT | 0x01; 			//-- PLL ON 
		delay(200); 
		PLLCNT = PLLCNT | 0x02; 			//--- Start PLL clock 
	*************/					
	
	
		/*-----------------------------------------------
		Buzzer setting
		-----------------------------------------------*/
		DLYCTR = 0x00;					/*	选择蜂鸣器频率  */		
		P0DIR |= 0x20;					/* Set P53 output */
		P0OMD1|=0x20;					//----选择蜂鸣器输出引脚		P05
		DLYCTR = DLYCTR | 0x80 ;		//----- Buzzer output ON 
		//	DLYCTR = DLYCTR & 0x7f ;		//----- Buzzer output ON	
		aftersound_clr;
		//	DLYCTR = DLYCTR & 0x7f ;		//----- Buzzer output ON	
		/*-----------------------------------------------
		Timer0 setting
		时钟源选择PLL/32
		Fpll选择16M
	
		计算定时时间公式如下
		(1/(fpll/32))*25=50u
		**********************************************/
		//TM0MD = TM0MD | 0x01; 	//---- Select the clock source to prescaler 
		//CK0MD = 0x04; 			//---- Select the clock source to fosc/32 
		//TM0OC = 25;				//---- Set the compare register 
		//TM0ICR = TM0ICR | 0x82;	//---- Enable the interrupt, Interrupt level 2 
		//TM0MD|=0x08;				//---- Start  the counter 
		/*-----------------------------------------------
		Timer1 setting
		时钟源选择FPLL/32
		Fpll选择16M
		计算定时时间公式如下
		(1/(fpll/32))*125=250u
		则中断时间为(124+1)*2.0=250U
		-----------定时器-----------------------200U-----*/
		TM1BC=0;
		TM1MD = TM1MD | 0x01;					// Select the clock source to prescaler 
		CK1MD = 0x04;							// Select the clock source to fpll/64 
		TM1OC = 49; 							//--200u
		TM1ICR = TM1ICR | 0x82; 				// Enable the interrupt, Interrupt level 3 
		TM1MD = TM1MD | 0x08;					// Start the counter 
		/*-----------------------------------------------
		Timer 2 setting
		//-----Timer=(1/(fpll/32))*(TM2OC+1)
		//-----Timer=(1/(8/32))*(249+1)
		//-----Timer=1000
		-----------------------------------------------*/
	
		TM3BC=0;
		TM3MD = TM3MD | 0x01;					// Select the clock source to prescaler 
		CK3MD = 0x04;							// Select the clock source to fpll/64 
		TM3OC = 249;							//-1000u	
		TM3ICR = TM3ICR | 0x82; 				// Enable the interrupt, Interrupt level 3 
		TM3MD = TM3MD | 0x08;					// Start the counter 
	
		//------------------------- 	
		PERIILR=0x00;
		IRQEXPEN=0x00;				
		IRQEXPDT=0x00;
		PWM_Init();      //气泵PWM初始化
		//Uart0_init();
		//Uart1_init();	
		asm (" or 0b01110000,PSW \n");			// Enable the interrupt 

}




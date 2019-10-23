
#include "MN101AF50D.h"
#include "math.h"
#include "main.h"

#include "Init_all.h"
#include "Pump_pwm.h"
/*********************************************************/
//	IO�ڳ�ʼ��
//���е�IO�ڳ�ʼ��
/*********************************************************/
void IO_Init(void)
{
		/*----------pa������-------
	pa0��ѹ��
	pa1��ˮ��
	pa2��ɼ���
	pa3��Ȧ����
	pa4�缫���
	pa5��������
	pa6����
	pa7���´�����
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
	/*----------p0������-----
	P00	Tdo		��̶˿�
	p01 tsck	��̶˿�
	p02 IN		Rx0		����ģ�����
	p03 Out		Tx0		����ģ�����
	p04	In		IR		�������
	p05	Out		BUZZWE	
	p06	In		������Ӧ		
	��ˮ���
	---------------------------*/
	P0PLUD=0x00;			
	P0OUT=0x00;	
	P0DIR=0x28;				
	/*----------p��y������-
	p20	out		DIS_CLK
	p21	out		DIS_DIO
	p22	out		DIS_STB
	p23	IN		����
	p24	IN		ˮλ���
	p27	rest    MCU��λ
	---------------------------*/
	P2PLU=0x00;			
	P2OUT=0xff;	
	P2DIR=0x87;				//set P20,P21 p22is input
	/*----------p5������-----
	p50	Out		K2
	p51	Out		1A		
	p52	Out		1B
	p53	Out		1C
	p54	Out		1D
	p55	Out		PUMPB
	p56	Out		�Զ���ˮ
	p57	Out		ů����
	---------------------------*/
	P5PLUD=0x00;
	P5OUT=0x00;                 
	P5DIR=0xff;
	/*----------p6������-----
	p62	Out		2D	
	p63	Out		2C
	p64	Out		2B
	p65	Out		2A
	p66	Out		��ťCLK
	p67	Out		��ťDATA
	---------------------------*/
	P6PLU=0x00; 				
	P6OUT=0x00;    //set p62 is high
	P6DIR=0xff;	//
	/*----------p7������---
	p70	out		key1
	p71	out		�������
	p72	out		��ˮ���ź�
	p73	out		IIC_SClk
	p74	out		IIC_SDA
	p75	out		WiFi-Tx		
	p76	In		WiFi-Rx
	p77	out		ҹ��
	---------------------------*/
	P7PLUD=0x00; 				
	P7OUT=0x00;                 
	P7DIR=0xbf;	
	/*----------p8������---
	p80	out	Co3
	p81	out	C02
	p82	In	C01
	p83	out	3A
	p84	out	3B
	p85	out	����
	p86	out	3C
	p87	out	3D
	---------------------------*/
	P8PLUD=0x00; 			
	P8OUT=0x00;                 
	P8DIR=0xfb;					
	/*----------p9������-----
	p90	out	����ģ���Դ����
	p91	out	Wifi��Դ����
	p94	out	PUMPA
	---------------------------*/
	P9PLUD=0x00;					//
	P9OUT=0x00;					// is high
	P9DIR=0xff;					//All  is output
}

//*********************************************************/
//
//  �ṹ���Ա�ĳ�ʼ��
//
//*********************************************************/
void State_init(void)
{

	Water.DangWei = 3;				//-----ˮ�µ�λ
	Water.DangWei = 0;
	Water.StopHotDelay = 0;
	Water.Hot_f = 0;
	Water.WaterIn_f = 0;			//-----��ˮ	
	Water.TempDeal_time = 0;
	
	Seat.DangWei = 3;				//-----���µ�λ
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
	
	Status.power_f = 1;			//-----����
	Status.seat_f = 0;				//---������־λ��0
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
	/*----�¿���趨---*/
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
	
		OSCCNT=0x13;		//----bit5~~bit7 ѡ���Ƶ�ȣ��޷�Ƶ�� 			
							//---bit4, ����������Χ���ܣ�1:���ã�0:ʹ��
							//---bit3,bit2 Ԥ��
							//---bit1,	=1ѡ���ⲿ�����𵴡� =0ѡ���ڲ�������
							//---bit0	=1��������ڣ�=1P25/P26��Ϊ��ͨIO��
		RCCNT=0x81; 	//----bit7	=1
							//---bit6 to bit2 Ԥ�� 
							//---bit1	ѡ���ڲ�������Ƶ�� =1 16MH	 =0 20M
							//---bit0	=1��ֹ�ڲ�����  =0 ʹ���ڲ�����
		OSCSCNT=0x00;		//----bit7 to bit 1 Ԥ��
							//---BIT0  =1���������   =0 P90/P91 ��Ϊ��ͨIO��
	
		OSCLOCK=0x01;		//----bit7 to bit 1 Ԥ��	
							//---bit0 =1 ����OSCCNT/OSCSCNT	=0 �����޸�OSCCNT/OSCSCNT
	
		
		PLLCNT=0x10;		//----bit7 to bit 4   ����Ƶ�ʱ�Ƶ�� 
							//---bit3 to bit 2 Ԥ��
		PLLCNT = PLLCNT | 0x01; 			//-- PLL ON 
		delay(200); 
		PLLCNT = PLLCNT | 0x02; 			//--- Start PLL clock 
	*************/					
	
	
		/*-----------------------------------------------
		Buzzer setting
		-----------------------------------------------*/
		DLYCTR = 0x00;					/*	ѡ�������Ƶ��  */		
		P0DIR |= 0x20;					/* Set P53 output */
		P0OMD1|=0x20;					//----ѡ��������������		P05
		DLYCTR = DLYCTR | 0x80 ;		//----- Buzzer output ON 
		//	DLYCTR = DLYCTR & 0x7f ;		//----- Buzzer output ON	
		aftersound_clr;
		//	DLYCTR = DLYCTR & 0x7f ;		//----- Buzzer output ON	
		/*-----------------------------------------------
		Timer0 setting
		ʱ��Դѡ��PLL/32
		Fpllѡ��16M
	
		���㶨ʱʱ�乫ʽ����
		(1/(fpll/32))*25=50u
		**********************************************/
		//TM0MD = TM0MD | 0x01; 	//---- Select the clock source to prescaler 
		//CK0MD = 0x04; 			//---- Select the clock source to fosc/32 
		//TM0OC = 25;				//---- Set the compare register 
		//TM0ICR = TM0ICR | 0x82;	//---- Enable the interrupt, Interrupt level 2 
		//TM0MD|=0x08;				//---- Start  the counter 
		/*-----------------------------------------------
		Timer1 setting
		ʱ��Դѡ��FPLL/32
		Fpllѡ��16M
		���㶨ʱʱ�乫ʽ����
		(1/(fpll/32))*125=250u
		���ж�ʱ��Ϊ(124+1)*2.0=250U
		-----------��ʱ��-----------------------200U-----*/
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
		PWM_Init();      //����PWM��ʼ��
		//Uart0_init();
		//Uart1_init();	
		asm (" or 0b01110000,PSW \n");			// Enable the interrupt 

}




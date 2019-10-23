
#include "MN101AF50D.h"
#include "math.h"
#include "main.h"

#include "Init_all.h"
/*********************************************************/
//IOÏ¢ôøã·ûù
//?öÇÊÀ?IOÏ¢îÜ?ìı?õó??
/*********************************************************/
void IO_Init(void)
{
	/*----------paÏ¢?öÇ-------
	pa0ñò??
	pa1?â©?
	pa2ûôÊÎÊ¥?
	pa3ñ¨ÏêÊ¥?
	pa4????
	pa5ÎÃÚÂ?ğæ
	pa6??
	pa7ñ¨??ÊïĞï
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
	/*----------p0Ï¢?öÇ-----
	P00	Tdo		?ïïÓ®Ï¢
	p01 tsck	?ïïÓ®Ï¢
	p02 IN		Rx0		??Ù¼?ïÈâ¥
	p03 Out		Tx0		??Ù¼??õó
	p04	In		IR		?èâïÈâ¥
	p05	Out		BUZZWE	
	p06	In		ìıñ¨Êï?		
	?â©??
	---------------------------*/
	P0PLUD=0x00;			
	P0OUT=0x00;	
	P0DIR=0x28;				
	/*----------P2Ï¢?öÇ-
	p20	out		DIS_CLK
	p21	out		DIS_DIO
	p22	out		DIS_STB
	p23	IN		?ÖÃ
	p24	IN		â©êÈ??
	p27	rest    MCU?êÈ
	---------------------------*/
	P2PLU=0x00;			
	P2OUT=0xff;	
	P2DIR=0x87;				//set P20,P21 p22is input
	/*----------p5Ï¢?öÇ-----
	p50	Out		K2
	p51	Out		1A		
	p52	Out		1B
	p53	Out		1C
	p54	Out		1D
	p55	Out		PUMPB
	p56	Out		í»??â©
	p57	Out		Ñì??Ïõ
	---------------------------*/
	P5PLUD=0x00;
	P5OUT=0x00;                 
	P5DIR=0xff;
	/*----------p6Ï¢?öÇ-----
	p62	Out		2D	
	p63	Out		2C
	p64	Out		2B
	p65	Out		2A
	p66	Out		àÁ?CLK
	p67	Out		àÁ?DATA
	---------------------------*/
	P6PLU=0x00; 				
	P6OUT=0x00;    //set p62 is high
	P6DIR=0xff;	//
	/*----------p7Ï¢?öÇ---
	p70	out		key1
	p71	out		ğ¶ö«?Ïõ
	p72	out		?â©÷ùãá?
	p73	out		IIC_SClk
	p74	out		IIC_SDA
	p75	out		WiFi-Tx		
	p76	In		WiFi-Rx
	p77	out		å¨?
	---------------------------*/
	P7PLUD=0x00; 				
	P7OUT=0x00;                 
	P7DIR=0xbf;	
	/*----------p8Ï¢?öÇ---
	p80	out	Co3
	p81	out	C02
	p82	In	C01
	p83	out	3A
	p84	out	3B
	p85	out	üŞëå
	p86	out	3C
	p87	out	3D
	---------------------------*/
	P8PLUD=0x00; 			
	P8OUT=0x00;                 
	P8DIR=0xfb;					
	/*----------p9Ï¢?öÇ-----
	p90	out	??Ù¼??ê¹Íóğ¤
	p91	out	Wifi?ê¹Íóğ¤
	p94	out	PUMPA
	---------------------------*/
	P9PLUD=0x00;					//
	P9OUT=0x00;					// is high
	P9DIR=0xff;					//All  is output
}

/*********************************************************/
//
//ÊÀ???????ò¤êÈ£¬?Õáôøã·ûù
//
/*********************************************************/
void State_init(void)
{

	Water.DangWei = 3;				//-----Ë®ÎÂµµÎ»
	Water.DangWei = 0;
	Water.StopHotDelay = 0;
	Water.Hot_f = 0;
	Water.WaterIn_f = 0;			//-----½øË®	
	Water.TempDeal_time = 0;
	
	Seat.DangWei = 3;				//-----×ùÎÂµµÎ»
	Seat.Heat_f = 0;
	Seat.Flag = 0;
	
	Drying.DangWei = 3;
	
	TunBu.pressure = 3;
	TunBu.PGLevel = 3;
	
	NvXing.pressure = 3;
	NvXing.PGLevel = 3;	
	Enfant.Dring_f = 0;
	
	Entironment.time = 0;
	Entironment.temperature = 25;
	
	SoftPowerDeal.Delay = T10Min;
	SoftPowerDeal.Softpower_f = 1;
	
	Status.power_f = 1;			//-----¿ª»ú
	Status.seat_f = 0;				//---¼ĞÙÅ×ú°¯	
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
	/*----ĞÂ¿ò¼ÜÉè¶¨---*/
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	Status.Auto_clear = 0;
	Status.Icon.water_gear = 0;
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
	CPUM = 0x10; 		//--- Set normal mode 
						//--- Set fs=fosc*1 
	MEMCTR = 0xCB; 		//--- Set special register area 3 wait cycles 
						//--- Set interrupt vector base 
						//--- Set single chip mode 

	OSCCNT=0x13;		//----bit5~~bit7 ??İÂ?İï£¬ÙéİÂ?¡£				
						//---bit4, ÍÔáÜòè?ñ®èâ?ÍíÒö£¬1:Ğ×éÄ£¬0:ŞÅéÄ
						//---bit3,bit2 ?×º
						//---bit1,	=1??èâİ»ÍÔáÜòè?¡£ =0???İ»ÍÔáÜòè?
						//---bit0	=1ÍÔáÜòè?ìıÏ¢£¬=0 P25/P26ñ®?ÜÅ÷×IOÏ¢
	RCCNT=0x81;		//----bit7	=1
						//---bit6 to bit2 ?×º 
						//---bit1	???İ»ÍÔáÜòè??áã =1 16MH   =0 20M
						//---bit0	=1Ğ×ò­?İ»ÍÔáÜ  =0 ŞÅÒö?İ»ÍÔáÜ
	OSCSCNT=0x00;		//----bit7 to bit 1 ?×º
						//---BIT0  =1î¸áÜòè?ìıÏ¢   =0 P90/P91 ñ®?ÜÅ÷×IOÏ¢

	OSCLOCK=0x01;		//----bit7 to bit 1 ?×º	
						//---bit0 =1 ?ğíOSCCNT/OSCSCNT   =0 ëÃ?áóËÇOSCCNT/OSCSCNT

	
	PLLCNT=0x10;		//----bit7 to bit 4   ?ìı?áãÛÃ?¡£ 
						//---bit3 to bit 2 ?×º
	PLLCNT = PLLCNT | 0x01; 			//-- PLL ON 
	delay(200);	
	PLLCNT = PLLCNT | 0x02; 			//--- Start PLL clock 
*************/					


	/*-----------------------------------------------
	Buzzer setting
	-----------------------------------------------*/
	DLYCTR = 0x00; 					/*  ??Üğ?Ğï?áã  */		
	P0DIR |= 0x20; 					/* Set P53 output */
	P0OMD1|=0x20;					//----??Üğ?Ğï?õóìÚÊÅ		P05
	DLYCTR = DLYCTR | 0x80 ; 		//----- Buzzer output ON 
	//	DLYCTR = DLYCTR & 0x7f ; 		//----- Buzzer output ON 	
	aftersound_clr;
	//	DLYCTR = DLYCTR & 0x7f ; 		//----- Buzzer output ON 	
	/*-----------------------------------------------
	Timer0 setting
	íÂ?PWM?õó
    PA0?õópwm

     -------------------------------------------*/

	 
 	TM0MD&=~0X08;   //TM0MD = TM0MD&£¨0xf7£© bit3(TM0EN) = 0 to stop timer counting
    PAOMD|=0X00;   				//	PAOMD&=~0X01 ûú PA0MD |= 0x01  îÜ??£º  PAOMD&=~0X01 ÜÁ?ØßìéêÈ?~0x01 ßÓ?ı¨ÜÁò¥ê«?îÜ?Üô?£¬ó¦bit0 ìéïÒãÀ0 
	                                           // Ó£ãÀ ûä 0x01 îÜ?£¬?æÔÒöÜÁ?ĞìöâêÈÜô?£¬Ó£ÜôÒöÜÁ? bit0 ìéïÒãÀ0 £¬åıÍıê«?ãÀ1 £¬ûäÖõ0x01 Ñá?ãÀ
	PADIR|=0X01;	//PA0 output
//	TM0MD|=0X10;    //bit 6 5 4 = 0 0 1 to select pwm mode
//	TM0MD&=0X9F;    
	TM0MD|=0X11;    // bit 0 = 1 to enable prescaler output to the clock source
//	TM0MD&=0XF9;    
	CK0MD=0X03;        //FS/2 = 4MHZ
	TM0OC=0X40;       //4M/256 = 31.25Khz
	PAOUT&=~0X01;    // ÜÁò¥ĞìöâêÈÜô?£¬ÜÁ?bit0 ?0  ?õóî¸?øÁ
	TM0MD|=0X08;      // Start the counter 
	/*-----------------------------------------------
	Timer1 setting
	??ê¹??FPLL/32
	Fpll??16M
	?ß©ïÒ???ÍëãÒåıù»
    fpll = 8M
	Timer=(1/(fpll/32))*(TM2OC+1)
	?ñé????(49+1)*4=200Us
	-----------ïÒ?Ğï-----------------------200U-----*/
	TM1BC=0;
	TM1MD = TM1MD | 0x01; 					// Select the clock source to prescaler 
	CK1MD = 0x04; 							// Select the clock source to fpll/64 
//	TM1OC = 25;							//--100u
	TM1OC = 49;								//--200u
	TM1ICR = TM1ICR | 0x82; 				// Enable the interrupt, Interrupt level 3 
	TM1MD |= 0x08; 					// Start the counter 
	//asm (" or 0b01110000,PSW \n"); 			// Enable the interrupt 
	/*-----------------------------------------------
	Timer 2 setting
    //-----8M/32 = 250Khz  = 4us
	//-----Timer=(1/(fpll/32))*(TM2OC+1)
	//-----Timer=(1/(8/32))*(249+1)
	//-----Timer=1000us = 1ms
	-----------------------------------------------*/

	TM3BC=0;
	TM3MD = TM3MD | 0x01; 					// Select the clock source to prescaler 
	CK3MD = 0x04; 							// Select the clock source to fpll/64 
	TM3OC = 249;							//-1000u

	TM3ICR |= 0x83; 				// Enable the interrupt, Interrupt level 3 
	TM3MD = TM3MD | 0x08; 					// Start the counter 

	//-------------------------		
	PERIILR=0x00;
	IRQEXPEN=0x00;				
	IRQEXPDT=0x00;
//	Uart0_init();
//	Uart1_init();	
	asm (" or 0b01110000,PSW \n"); 			// Enable the interrupt 
}




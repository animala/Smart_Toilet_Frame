/* MN101C/E/L SERIES C SAMPLE PROGRAM */


#include "Init_all.h"

#include "Moto_deal.h"
//#include "main.h"

#include "TM1629.h"

buzzer_uion buzzer;
timer_uion timer;
Status_uion Status;
Water_uion Water;
Seat_uion Seat;
Drying_uion Drying;
TunBu_uion TunBu;
NvXing_uion NvXing;
SoftPowerDeal_CB SoftPowerDeal;
Entironment_CB Entironment;
Enfant_uion Enfant;	
MachineTest_CB MachineTest;
chongshui_uion chongshui;
LiquidDeal_CB LiquidDeal;
work_uion work;
CoverSeat_uion CoverSeat;
Error_uion Error;

extern TM1629B_CB TM1629B;

extern TM1629_Fun TM_1629;


void delay_us(uint_16 n)
{
	while(n>0)
		n--;
}




void State_init(void);
void Sys_Init(void);
void State_init(void);
void IO_Init(void);

/*********************************************************/
//	DLYCTR  =  DLYCTR | 0x80 ; 		//----- Buzzer output ON 
//	DLYCTR  =  DLYCTR & 0x7f ; 		//----- Buzzer output ON 
/*******************************************************/
void  buz_set(uint_8 loop,uint_8 delay_H,uint_8 delay_L)
{
	buzzer.ring_times = loop;
	buzzer.ring_time_set = delay_H;
	buzzer.stop_time_set = delay_L;
	buzzer.task_count = 0;
}
//--
//-------------------------------------------
void buz_task(void)
{
	if(buzzer.ring_times != 0)
	{
		if(buzzer.task_count == 0)
		{
			buzzer.ring_time = buzzer.ring_time_set;
			++buzzer.task_count;
       	} 
		else if(buzzer.task_count == 1) 
		{
			//	P5OUT| = 0x04;
			aftersound_set;
			if(--buzzer.ring_time == 0)
			++buzzer.task_count;
       	}
    		else if(buzzer.task_count == 2) 
       	{
			buzzer.stop_time = buzzer.stop_time_set;
			++buzzer.task_count;
		} 
		else if(buzzer.task_count == 3) 
		{
			aftersound_clr;
			//	P5OUT& = ~0x04;   
			if(--buzzer.stop_time == 0)
			{
				if(buzzer.ring_times != 0xff)			//-----Í£Ö¹?½Ğ
				--buzzer.ring_times;
				buzzer.task_count = 0;
           		}
		}
	}
	else 
	{
		buzzer.task_count = 0;
		aftersound_clr;
	}		
}


/*********************************************************/
void Timing(void)			//	//10ms  Ò»´Î
{
	timer.count_10ms++;
	/*if(IR.TFDelay>0)
	{
		IR.TFDelay--;
	}*/	
	if(Drying.ADjustTime>0)
	{
		Drying.ADjustTime--;
	}
//	if(SendData.TF>0)
//	{
//		SendData.TF--;
//	}
	if(CoverSeat.SpaceTime>0)
	{
		CoverSeat.SpaceTime--;
	}
	if((timer.count_10ms%10)==0)
	{
		timer.t_100ms_f=1;				//  100 ms 
	}
	if((timer.count_10ms%50)==0)
	{
		timer.t_500ms_f=1;				//  500 ms 
	}
	if(timer.count_10ms>=100)
	{
		timer.t_1s_f=1;
		timer.count_10ms=0;				//  1s
		if(SoftPowerDeal.Delay>0)
		{
			SoftPowerDeal.Delay--;
		}
		if(Drying.HotStartTime>0)
		{
			Drying.HotStartTime--;
		}
		if(LiquidDeal.SetOff1Min>0)
		{
			LiquidDeal.SetOff1Min--;
		}
	/*	if(LightInduce.Timer>0)
		{
			LightInduce.Timer--;
		}*/
		if(Entironment.time>0)
		{
			Entironment.time--;
		}
		if(Seat.SeatOnTimer>0)
		{
			Seat.SeatOnTimer--;
		}
		if(CoverSeat.delay>0)
		{
			CoverSeat.delay--;
		}
		if(work.Start_f)
		{
			if(work.time>0)
			{
				work.time--;
			}
			else
			{
				work.Start_f=0;
			}
		}
	}
}



void main(void)
{
	uint_8 i = 0;
	uint_8 j = 0;
	State_init();
	Sys_Init();
	IO_Init();
	TM1629_Init(&TM_1629);
	motor_select[0] = &MotorA;
	motor_select[1] = &MotorB;
	Status.Mode_select = 1;
	Status.Pres_select = 1;
	while(1)
	{
		if(timer.t_10ms_f == 1)				
		{
			timer.t_10ms_f = 0;
			Timing();	
			
			Power_up_reset(motor_select);  //å¯¹æ‰€æœ‰ç”µæœºè¿›è¡Œä¸Šç”µå¤ä½?

			if(Status.PowerEnd_f == 1)
			{
			//	if(timer.t_1s_f)
			//	{
			//		j++;
			//	}
			//	if(j == 3)
			//	{
					//Motor_set_position(&MotorB,&Status);   //è¿™ä¸ªæ˜¯è®¾å®šç”µæœºåˆ°è¾¾çš„ä½ç½®
					Reciprocate_fun(&MotorB,&Status);   //å¾€å¤è¿åŠ?
			//	}
				/*if(j == 5)
				{
					j = 5;
				//	Reciprocate_fun(&MotorB,&Status);   //å¾€å¤è¿åŠ?
				}*/
				
			}

			TM1629_Display(&TM_1629,TM1629B.DisBuf,LedDisBufSize,SetDisOn);
			if(timer.t_500ms_f == 1)
			{
				timer.t_500ms_f = 0;				
				i++;
				if(i>32)
				{
					i = 0;
				}
				Check_Func_deal(i);			
			}
			buz_task();
		}					
	}
}


//************************************************
/*-----------------------------------------------
Timer 0 interrupt
-----------------------------------------------*/
#pragma _interrupt INT_TM0
void INT_TM0(void)					//50us    

{

	

}


/*-----------------------------------------------
Timer 1 interrupt
-----------------------------------------------*/
#pragma _interrupt INT_TM1
void INT_TM1(void)					//200us  
{

	/*IR_receive();
	FG_receive();
	SendFG_Data();*/
	
	
}
#pragma _interrupt INT_TM3
void INT_TM3(void)					//1000us  
{
	timer.count_1ms++;
	
	Motor_Control(&MotorA,Motor_ShuntValve);  //·ÖË®·§µç»ú									
	if((timer.count_1ms%2)==0)
	{			
		Motor_Control(&MotorB,Motor_SprayBoom);   //Åç¸Ëµç»ú¿ØÖÆ´¦Àí
	}
	if(timer.count_1ms>=10)
	{	
		timer.count_1ms=0;
		timer.t_10ms_f=1;
	}
}





/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

/* MN101C/E/L SERIES C SAMPLE PROGRAM */


#include "Init_all.h"

#include "Moto_deal.h"
//#include "main.h"
#include "IR.h"
#include "TM1629.h"
#include "Function_deal.h"

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
IR_uion IR;
fangwu_uion fangwu;


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
				if(buzzer.ring_times != 0xff)			//-----停止?叫
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
void Timing(void)			//	//10ms  一次
{
	timer.count_10ms++;
	if(IR.TFDelay>0)
	{
		IR.TFDelay--;
	}	
	if(Drying.ADjustTime>0)
	{
		Drying.ADjustTime--;
	}
/*	if(SendData.TF>0)
	{
		SendData.TF--;
	}*/
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
	TM1629_Init(&TM_1629);     //TM1629初始化
	motor_select[0] = &MotorA;  //把分水电机结构体赋值给 motor_select[0]
	motor_select[1] = &MotorB;	//把喷杆电机结构体赋值给 motor_select[1]

	while(1)
	{
		if(timer.t_10ms_f == 1)				
		{
			timer.t_10ms_f = 0;
			Timing();	

		
			Power_up_reset(motor_select);  //所有电机上电复位
			
			if(Status.PowerEnd_f == 1 && Status.seat_f == 1)  //电机复位完成以及有人入座
			{		
				IR_Opration();   //IR接收处理	
				Motor_A_B_C_program(motor_select,&Status);   //电机工作流程处理函数
			}	
			Zuo_Check();  		//入座处理

			ChuChouDeal();   	//除臭处理

			ChongShuiBanDeal();  //冲水板冲水处理
			
			Display_Temp(0,work.time,1);			//显示倒计时，测试用
			Display_Temp(2,Status.Icon.water_yeild,1);	//显示水量，测试用
			
			Display_Icon_fun(&Status);  //图标显示处理		
			
			if(timer.t_100ms_f == 1)   //100ms刷新
			{
				timer.t_100ms_f = 0;								
				TM1629_Display(&TM_1629,TM1629B.DisBuf,LedDisBufSize,SetDisOn);    //1629显示刷新
			}
			buz_task();  //蜂鸣器处理
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
	IR_receive();				//红外接收
	/*FG_receive();
	SendFG_Data();*/
		
}
#pragma _interrupt INT_TM3
void INT_TM3(void)					//1000us  
{
	timer.count_1ms++;
	
	Motor_Control(&MotorA);  //分水阀电机									
	if((timer.count_1ms%2)==0)
	{			
		Motor_Control(&MotorB);   //喷杆电机控制处理
	}
	if(timer.count_1ms>=10)
	{	
		timer.count_1ms=0;
		timer.t_10ms_f=1;
	}
}





/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

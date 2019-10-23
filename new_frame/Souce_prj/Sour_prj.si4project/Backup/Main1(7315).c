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
/********************************************/
//
//入座检测~
//
/******************************************/
void Zuo_Check(void)
{
	//if(Status.power_f)
	//{
		if(ZhaoZuo_pin == 0)  //检测到入座
		{
			Seat.count1++;
			Seat.count2 = 0;
			if(Seat.count1 > 10)
			{
				//------------100MS着座有效
				Entironment.time = T30Min;
				CoverSeat.delay = T5Min;
				CoverSeat.enable_f = 1;
				Status.chuchou_f = 1;		//-----着座除臭使能
				Status.jieneng_e = 0;		//关闭节能
				Seat.Flag |= 0x01;
				if(Status.seat_f == 0)
				{
					Status.seat_f = 1;
					Status.power_f = 1;		//入座标志位置1
					//SpeedinessHeatPowerOn;
					//WifiPowerOn;
					//CO2_clr_seat;
					Status.fangwu_f = 1;	//防污标志位置1
					fangwu.step = 0;		
					penkou.step = 0;		//喷口步骤清 0
					//penkou.enable_f=0;
					Status.penkou_f = 0;		
					buz_set(1,30,30);	
				}
				if(Seat.count1 > 1000)		//---------入座10S自动冲水开启
				{
					Seat.count1 = 1000;	
					if(Seat.first_f == 0)
					{
						Seat.first_f = 1;
						if(Status.auto_f == 1)
						{
							Status.chongshui_e = 1; 
						}
					}				
				}		
			}
		}
		else
		{
			//------------离座2S有效
			Seat.count2++;
			Seat.SeatOnTimer = T2Min;
			
			if(Seat.count2 > 200)		//--400*10=4000MS
			{
				Seat.count1 = 0;
				Drying.swash_f = 0;
				Status.chuchou_e = 1;
				Seat.Flag |= 0x02;
				if(Status.seat_f)			//-----
				{
					Status.seat_f = 0;	
					LiquidDeal.WaterWash_f = 0;
					LiquidDeal.SetOff1Min = T1Min;
					//CO2_set_seat;
					Seat.first_f = 0;
					Status.stop_f = 1;
					Status.tunbu_f = 0;
					Status.nvxing_f = 0;
					Status.enfant_f = 0;
					work.LianXu_f = 0;
					work.LianXuBuf = 0;
					Enfant.Dring_f = 0;	
					work.step = 0;
					if(Status.dring_f)
					{
						Status.dring_f = 0;	
						Drying.step = 0;
					}
					Status.ShuiYaAnMo_f = 0;
					Status.reciprocate_f = 0;
					Status.dring_wf_f = 0;
					Status.ZuoYu_f = 0;
					Status.LengReAnMo_f = 0;
					if(penkou.enable_f)
					{
						penkou.step=0;
						Status.penkou_f = 0;
					}					
				}
			}
			//----------离座6S自动冲水
			if(Seat.count2 > 600)		
			{
				if(MachineTest.Flag == 0)
				{
					if(Status.auto_f)
					{
						if(Status.chongshui_e)
						{
							Status.chongshui_e = 0;
							Status.chongshui_f = 1;
							Status.chongshuiban_f = 1;
						}
					}
				}
			}
			//---离座1钟关除臭
			if(Seat.count2 > 6000)		
			{
				Status.chuchou_f = 0;	
			}

			//----------离座10分钟进入节能模式
			if(Seat.count2 > 60000)			//----10*60*1000/10		
			{
				if(Status.jieneng_f)
				{
					Status.jieneng_e = 1;
				}
				Seat.count2 = 60000;
			}
		}
	//}
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
			Zuo_Check();  //入座处理

			ChuChouDeal();   //除臭处理

			ChongShuiBanDeal();  //冲水板冲水处理
			
			Display_Temp(0,work.time,1);
			Display_Icon_fun(&Status);  //图标显示处理			
			if(timer.t_100ms_f == 1)  
			{
				timer.t_100ms_f = 0;								
				TM1629_Display(&TM_1629,TM1629B.DisBuf,LedDisBufSize,SetDisOn);    //1629显示刷新
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
	IR_receive();				//红外接收
	/*FG_receive();
	SendFG_Data();*/
		
}
#pragma _interrupt INT_TM3
void INT_TM3(void)					//1000us  
{
	timer.count_1ms++;
	
	Motor_Control(&MotorA,Motor_ShuntValve);  //分水阀电机									
	if((timer.count_1ms%2)==0)
	{			
		Motor_Control(&MotorB,Motor_SprayBoom);   //喷杆电机控制处理
	}
	if(timer.count_1ms>=10)
	{	
		timer.count_1ms=0;
		timer.t_10ms_f=1;
	}
}





/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/

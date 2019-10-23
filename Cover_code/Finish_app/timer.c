
#include "R_main.h"	

void DelayUs(uint_8  Loop)
{
	uint_8 i;
	for(i=0;i<Loop;i++)
	{
		NOP();
	}
}
void timer_manage(void)
{
	timer.sing10ms_f=0;
	timer.sing10ms++;
	if(SendData.TF>0)
	{
		SendData.TF--;
	}
	if(Status.LevelOffTime>0)
	{
		Status.LevelOffTime--;	
	}


	if(SeatCircle.Enable_f)
	{
		if(SeatCircle.DelayTime<300)		//----
		{
			SeatCircle.DelayTime++;
		}
		
	}

	if(SeatCover.Enable_f)
	{
		if(SeatCover.DelayTime<300)		//----
		{
			SeatCover.DelayTime++;
		}
		
	}

	//----------------------------
	
	if((timer.sing10ms%10)==0)			//--- 100ms	
	{
		timer.sing100ms_f=1;

		if(Status.RunTime>0)
		{
			Status.RunTime--;
		}
		else
		{
			SeatCircle.OpenDirStatus=0;
			SeatCover.OpenDirStatus=0;	
		}
	}
	if(timer.sing10ms>=100)	
	{
		timer.sing10ms=0;
	}
}


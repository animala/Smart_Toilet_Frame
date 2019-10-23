#include "R_main.h"



void Raminitial(void)
{
	uint_8 i;
	SeatCircle.DirUp_f1=0;
	SeatCircle.DirDown_f=0;
	SeatCircle.LockDieCount=0;
	SeatCover.DirUp_f=0;
	SeatCover.DirDown_f=0;
	SeatCircle.LockDieCount=0;
	PcbTest.Flag=0;
	SeatCircle.Enable_f = 0;


	Seat.PositionMin=SeatPositionMin;
	Seat.PositionMax=SeatPositionMin+SeatPositionAddMax;	
	Seat.PositionCount=5;
	for(i=0;i<5;i++)
	{
		Seat.PositionMinBUfferr[i]=SeatPositionMin;
	}
	Cover.PositionMin=CoverPositionMin;
	Cover.PositionMax=CoverPositionMin+CoverPositionAddMax;
	Cover.PositionCount=5;	
	for(i=0;i<5;i++)
	{
		Cover.PositionMinBUfferr[i]=CoverPositionMin;
	}	
	SeatCover.PositionIndex=CoverPositionMin+CoverPositionAdd1;
	SeatCircle.PositionIndex=SeatPositionMin+SeatPositionAdd1;
	SeatCover.OpenDirStatus=0;
	SeatCircle.OpenDirStatus=0;
	Status.SeatOpen_f=0;
	Status.CoverOpen_f=0;

	
//	Status.LevelOffTime=0;
//	Seat_Stop();
//	Cover_Stop();
//	SendDataDeal();

	SeatCover.OpenDirStatus=2;		//-----开机先关盖	

	
}


void CircleCoverControl(void)
{
	QuanControl;
	GaiControl;
}




void PcbTestProgrom(void)
{
	if(PcbTest.CoverLedDir)
	{
	}
	else
	{
	}

	if(PcbTest.SeatLedDir)
	{
	}
	else
	{
	}
}



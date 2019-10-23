#include "R_main.h"

/*******************************************************/
void SeatCircleMotorStop(void)
{
	MotIns3Off;
	MotIns4Off;
	MB_EN_OFF;
}

void SeatCircleMotorUp(uint_16 Duty)
{
	//------座圈上翻
	SeatCircle.Enable_f=1;
	SeatCircle.OpenDir_f=1;	
	TDR01=Duty*8;
	MotIns4Off;	
	NOP();
	NOP();
	MotIns3On;
	NOP();
	NOP();
	MB_EN_ON;
}
void SeatCircleMotorDown(uint_16 Duty)
{
	//------座圈下翻
	SeatCircle.Enable_f=1;
	SeatCircle.OpenDir_f=0;	
	TDR01=Duty*8;
	MotIns3Off;
	NOP();
	NOP();
	MotIns4On;
	NOP();
	NOP();
	MB_EN_ON;
}
void	SeatCirclebrake(void)
{
	//-----------杀车功能
	MotIns3On;
	MotIns4On;
	MB_EN_ON;
}

void Seat_Stop(void)
{
	SeatCircleMotorStop();	
	SeatCircle.DirUp_f1=0;
	SeatCircle.DirDown_f=0;
	SeatCircle.Enable_f=0;
	SeatCircle.OpenDir_f=0;
	SeatCircle.OpenDirStatus=0;
}


//============================================座盖
void SeatCoverMotorStop(void)
{
	MotIns1Off;
	MotIns2Off;
	MA_EN_OFF;
}

void SeatCoverMotorUp(uint_16 Duty)
{
	//------座盖上翻
	SeatCover.Enable_f=1;
	SeatCover.OpenDir_f=1;	
	TDR01=Duty*8;
	MotIns2Off;	
	NOP();
	NOP();
	MotIns1On;
	NOP();
	NOP();
	MA_EN_ON;
}
void SeatCoverMotorDown(uint_16 Duty)
{
	//------座盖下翻
	SeatCover.Enable_f=1;
	SeatCover.OpenDir_f=0;	
	TDR01=Duty*8;
	MotIns1Off;
	NOP();
	NOP();
	MotIns2On;
	NOP();
	NOP();
	MA_EN_ON;
}
void	SeatCoverbrake(void)		//-----刹车功能
{
	MotIns1On;
	MotIns2On;
	MA_EN_ON;
}

void	Cover_Stop(void)
{
	SeatCoverMotorStop();	
	SeatCover.DirUp_f=0;
	SeatCover.DirDown_f=0;
	SeatCover.Enable_f=0;
	SeatCover.OpenDir_f=0;
	SeatCover.OpenDirStatus=0;
}
//==================================================
uint_16	ReadADC(uint_8	ADCchannel)
{
	ADS = ADCchannel;
	R_ADC_Start();
	R_ADC_Set_OperationOn();
	NOP();
	NOP();
	while(ADCS == 1);
	NOP();
	NOP();
	R_ADC_Get_Result();
	R_ADC_Stop();
	return ADC.adc_vale_buf; 
}
//------------------------------

void SeatPosition(void)
{
	uint_8	i;
	uint_16	AdcMax,AdcMin,AdcSum,AdcAverage;
	uint_16	SeatCirclePositionTemp;
	
	SeatCircle.AdcBuf[SeatCircle.AdcCount]=ReadADC(_13_AD_INPUT_CHANNEL_19);
	SeatCircle.AdcCount++;
	if(SeatCircle.AdcCount>=5)
	{
		SeatCircle.AdcCount=0;
		AdcSum=0;
		AdcMax=SeatCircle.AdcBuf[0];
		AdcMin=SeatCircle.AdcBuf[0];
		for(i=0;i<5;i++)
		{
			if(AdcMax<SeatCircle.AdcBuf[i])
			{
				AdcMax=SeatCircle.AdcBuf[i];
			}
			if(AdcMin>SeatCircle.AdcBuf[i])
			{
				AdcMin=SeatCircle.AdcBuf[i];
			}
			AdcSum+=SeatCircle.AdcBuf[i];	
		}
		AdcAverage=(AdcSum-AdcMin-AdcMax)/3;

		if(PcbTest.Flag)
		{
			if(AdcAverage>512)
			{
				PcbTest.SeatLedDir=1;
			}
			else
			{
				PcbTest.SeatLedDir=0;
			}
		}
		else
		{
			if(SeatCircle.Enable_f==0)
			{
				if(AdcAverage>(Seat.PositionMin+SeatPositionAddMax-150))				
				{
					if(Status.SeatOpen_f==0)
					{
						Status.SeatOpen_f=1;
						if(Seat.PositionCount>0);
						{
							Seat.PositionCount--;
						}
					}
				}
				else if(AdcAverage<Seat.PositionMin+150)	
				{
					Status.SeatOpen_f=0;
				}
			}
			//---------------------手动干扰座圈方向。
			if((SeatCircle.Enable_f==0)&&(Status.LevelOffTime==0))
			{p
				//if((AdcAverage>SeatPositionMin+30)&&(AdcAverage<SeatPositionMax-10))
				if((AdcAverage>Seat.PositionMin+30)&&(AdcAverage<Seat.PositionMin+SeatPositionAddMax-10))	
				{
					if(AdcAverage>(SeatCircle.PositionIndex+10))
					{
						//-----90%占空比上翻
						SeatCircle.Duty=90;
						SeatCircleMotorUp(90);
					}
					else  if(AdcAverage<(SeatCircle.PositionIndex-10))
					{
						//-----50%占空比下翻
						SeatCircle.Duty=50;
						SeatCircleMotorDown(50);
					}
				}
			}
			//---------------------根据转动方向和转速设置PWM
			if(SeatCircle.Enable_f)
			{
				Status.LevelOffTime=50;
				//------上翻
				if(SeatCircle.OpenDir_f)
				{
					//--------------判断上翻速度SeatCirclePositionTemp↑速度↑
					if(AdcAverage<SeatCircle.PositionIndex)
					{
						SeatCirclePositionTemp=0;
					}
					else
					{
						SeatCirclePositionTemp=AdcAverage-SeatCircle.PositionIndex;
					}
					//-------------不同位置控制速度
					if(AdcAverage<(Seat.PositionMin+SeatPositionAdd1))
					{
						SeatCircle.Duty=95;
						SeatCircleMotorUp(SeatCircle.Duty);
					}
					else if(AdcAverage<(Seat.PositionMin+SeatPositionAdd2))
					{
						SeatCircle.Duty=90;
						SeatCircleMotorUp(SeatCircle.Duty);
					}
					else if(AdcAverage<(Seat.PositionMin+SeatPositionAdd3))
					{
						SeatCircle.Duty=85;
						SeatCircleMotorUp(SeatCircle.Duty);
					}
					else if(AdcAverage<(Seat.PositionMin+SeatPositionAdd4))
					{
						SeatCircle.Duty=80;
						SeatCircleMotorUp(SeatCircle.Duty);	
					}
					else if(AdcAverage<(Seat.PositionMin+SeatPositionAdd5))
					{
						SeatCircle.DirUp_f1=1;
						if(SeatCirclePositionTemp>8)
						{
							SeatCircle.Duty=70;
							SeatCircleMotorUp(SeatCircle.Duty);	
						}
						else if(SeatCirclePositionTemp>5)
						{
							SeatCircle.Duty=75;
							SeatCircleMotorUp(SeatCircle.Duty);
						}
						else
						{
							SeatCircle.Duty=80;
							SeatCircleMotorUp(SeatCircle.Duty);
						}
					}
					else
					{
						if(SeatCirclePositionTemp<=2)
						{
							SeatCircleMotorStop();
							DelayUs(20);
						}
						else
						{
							SeatCirclebrake();			
						}				
					}
					
				}
				else
				{
					//--------------下盖
					//--------------判断下盖速度SeatCirclePositionTemp↑速度↑
					if(AdcAverage>SeatCircle.PositionIndex)
					{
						SeatCirclePositionTemp=0;
					}
					else
					{
						SeatCirclePositionTemp=SeatCircle.PositionIndex-AdcAverage;
					}
					//---------------------------------
					if(AdcAverage>=Seat.PositionMin+SeatPositionAdd5)
					{
						SeatCircle.Duty=50;
						SeatCircleMotorDown(SeatCircle.Duty);
					}
					else if(AdcAverage>=Seat.PositionMin+SeatPositionAdd4)
					{
						SeatCircle.Duty=25;
						SeatCircleMotorDown(SeatCircle.Duty);
					}
					else if(AdcAverage>=Seat.PositionMin+SeatPositionAdd3)
					{
						SeatCircle.Duty=10;
						SeatCircleMotorDown(SeatCircle.Duty);
					}
					else if(AdcAverage>=Seat.PositionMin-30)					
					{
						if(SeatCirclePositionTemp>=1)	
						{
							SeatCirclebrake();
						}
						else
						{
							SeatCircleMotorStop();
						}
					}
					else
					{
						if(SeatCirclePositionTemp<2)	
						{
							Seat_Stop();
							Status.SeatOpen_f=0;
						}
						else
						{
							SeatCirclebrake();
						}
					}
				}			
				//----------------------------------------	
				if(SeatCirclePositionTemp<2)
				{
					SeatCircle.LockDieCount++;
					if(SeatCircle.LockDieCount>6)		//-----卡死1S
					{
						Seat_Stop();					
						SeatCircle.OpenDir_f=0;
						SeatCircle.LockDieCount=0;
						Status.LevelOffTime=20;

						if(AdcAverage>(Seat.PositionMin+SeatPositionAddMax-200))				
						{
							if(Status.SeatOpen_f==0)
							{
								Status.SeatOpen_f=1;
								if(Seat.PositionCount>0)
								{
									Seat.PositionCount--;
								}
							}
						}
						else if(AdcAverage<Seat.PositionMin+200)	
						{
							Status.SeatOpen_f=0;
						}
						else
						{
							SeatCircle.OpenDirStatus=0;
							SeatCover.OpenDirStatus=0;
						}					
					}	
				}
				else
				{
					SeatCircle.LockDieCount=0;
				}
				//--------------
				SeatCircle.PositionIndex=AdcAverage;	
			}

			else
			{
				if((AdcAverage>(SeatCircle.PositionIndex+10))||(AdcAverage<(SeatCircle.PositionIndex-10)))
				{
					SeatCircle.PositionIndex=AdcAverage;
				}
				if(Seat.PositionCount>0)
				{
					if(AdcAverage<(SeatPositionMin+100))
					{
						Seat.PositionMinBUfferr[Seat.PositionCount]=AdcAverage;
					}
				}
				else
				{
					Seat.PositionMin=(Seat.PositionMinBUfferr[0]+
									Seat.PositionMinBUfferr[1]+
									Seat.PositionMinBUfferr[2]+
									Seat.PositionMinBUfferr[3]+
									Seat.PositionMinBUfferr[4])/5;
				}
				
				SeatCircleMotorStop();
				SeatCircle.LockDieCount=0;
				SeatCircle.DelayTime=0;
			}	
		}			
	}
}
//------------------------------------
/*******************************************
自动校准电位器最大最小值
根据转速调节PWM值
转速为零座盖卡死或达到最小最大位置停止电极输出
******************************************/
void CoverPosition(void)
{
	uint_8	i;
	uint_16	AdcMax,AdcMin,AdcSum,AdcAverage;
	uint_16	SeatCoverPositionTemp;
	
	SeatCover.AdcBuf[SeatCover.AdcCount]=ReadADC(_10_AD_INPUT_CHANNEL_16);
	SeatCover.AdcCount++;
	if(SeatCover.AdcCount>=5)
	{
		SeatCover.AdcCount=0;
		AdcSum=0;
		AdcMax=SeatCover.AdcBuf[0];
		AdcMin=SeatCover.AdcBuf[0];
		for(i=0;i<5;i++)
		{
			if(AdcMax<SeatCover.AdcBuf[i])
			{
				AdcMax=SeatCover.AdcBuf[i];
			}
			if(AdcMin>SeatCover.AdcBuf[i])
			{
				AdcMin=SeatCover.AdcBuf[i];
			}
			AdcSum+=SeatCover.AdcBuf[i];	
		}
		AdcAverage=(AdcSum-AdcMin-AdcMax)/3;	

		if(PcbTest.Flag)
		{
			if(AdcAverage>512)
			{
				PcbTest.CoverLedDir=1;
			}
			else
			{
				PcbTest.CoverLedDir=0;
			}
		}
		else
		{
		if(SeatCover.Enable_f==0)
		{
			//if(AdcAverage>CoverPostionMax-30)
			if(AdcAverage>(Cover.PositionMin+CoverPositionAddMax-100))	
			{
				if(Status.CoverOpen_f==0)
				{
					Status.CoverOpen_f=1;
					if(Cover.PositionCount>0);
					Cover.PositionCount--;
				}
				
			}
			//else if(AdcAverage<CoverPositionMin+30)
			else if(AdcAverage<Cover.PositionMin+100)
			{
				Status.CoverOpen_f=0;
			}
		}
		
		
		//-----------------手动干扰座盖方向
		if((SeatCover.Enable_f==0)&&(Status.LevelOffTime==0))
		{
			//if((AdcAverage>CoverPositionMin+30)&&(AdcAverage<CoverPostionMax-150))
			if((AdcAverage>Cover.PositionMin+30)&&(AdcAverage<(Cover.PositionMin+CoverPositionAddMax-150)))	
			{
				if(AdcAverage>(SeatCover.PositionIndex+5))
				{
					SeatCover.Duty=95;					
					SeatCoverMotorUp(SeatCover.Duty);
				}
				else  if(AdcAverage<(SeatCover.PositionIndex-5))
				{
					SeatCover.Duty=50;					
					SeatCoverMotorDown(SeatCover.Duty);
				}
			}
		}
		//---------------------根据转动方向和转速设置PWM
		if(SeatCover.Enable_f)
		{
			Status.LevelOffTime=50;
			//----------------上翻
			if(SeatCover.OpenDir_f)
			{
				//--------------判断上翻速度SeatCoverPositionTemp↑速度↑
				if(AdcAverage<SeatCover.PositionIndex)
				{
					SeatCoverPositionTemp=0;
				}
				else
				{
					SeatCoverPositionTemp=AdcAverage-SeatCover.PositionIndex;
				}
				//-------------不同位置控制速度
				if(AdcAverage<(Cover.PositionMin+CoverPositionAdd1))
				{
					SeatCover.Duty=90;					
					SeatCoverMotorUp(SeatCover.Duty);
				}
				else if(AdcAverage<(Cover.PositionMin+CoverPositionAdd2))
				{
					SeatCover.Duty=80;					
					SeatCoverMotorUp(SeatCover.Duty);
				}
				else if(AdcAverage<(Cover.PositionMin+CoverPositionAdd3))
				{
					SeatCover.Duty=75;					
					SeatCoverMotorUp(SeatCover.Duty);
				}	
				else if(AdcAverage<(Cover.PositionMin+CoverPositionAdd4))		
				{
					SeatCover.Duty=75;					
					SeatCoverMotorUp(SeatCover.Duty);
				}
				else if(AdcAverage<(Cover.PositionMin+CoverPositionAdd5-10))
				{

					SeatCover.DirUp_f=1;
					if(SeatCoverPositionTemp>8)
					{
						SeatCover.Duty=65;					
						SeatCoverMotorUp(SeatCover.Duty);
					}
					else
					{
						SeatCover.Duty=70;					
						SeatCoverMotorUp(SeatCover.Duty);
					}
				}
				else

				{
					SeatCover.DirUp_f=0;
					SeatCover.DirDown_f=0;
					if(SeatCover.BuShang_f)
					{
						SeatCover.BuShangTime++;
						if(SeatCover.BuShangTime<8)
						{
							SeatCover.Duty=20;					
							SeatCoverMotorUp(SeatCover.Duty);
						}
						else
						{
							Status.CoverOpen_f=1;
							Cover_Stop();
							SeatCover.BuShang_f=0;
						}		
		
					}
					else
					{				
						if(SeatCoverPositionTemp<2)
						{
							SeatCoverMotorStop();
							SeatCover.BuShangTime=0;
							SeatCover.BuShang_f=1;
							DelayUs(20);
						}
						else
						{
							
							SeatCover.BuShangTime=0;
							SeatCoverbrake();						
						}
					}
				}
			}

			//----------------下盖
			else
			{
				if(AdcAverage>SeatCover.PositionIndex)
				{
					SeatCoverPositionTemp=0;
				}
				else
				{
					SeatCoverPositionTemp=SeatCover.PositionIndex-AdcAverage;
				}
				if(AdcAverage>=(Cover.PositionMin+CoverPositionAdd5-50))	
				{		
					SeatCover.Duty=75;					
					SeatCoverMotorDown(SeatCover.Duty);
				}
				else if(AdcAverage>=(Cover.PositionMin+CoverPositionAdd4-50))		
				{		
					SeatCover.Duty=15;					
					SeatCoverMotorDown(SeatCover.Duty);
				}			
				else if(AdcAverage>=(Cover.PositionMin+(CoverPositionAdd4-100)))
				{
					SeatCover.Duty=5;					
					SeatCoverMotorDown(SeatCover.Duty);
				}
				else
				{
					if(SeatCoverPositionTemp>=1)
					{
						SeatCoverbrake();
					}
					else
					{
						SeatCoverMotorStop();
					}
				}
				if(AdcAverage<Cover.PositionMin+200)
				{
					Status.CoverOpen_f=0;
					SeatCover.OpenDirStatus=0;
				}
				
			}
			if(SeatCoverPositionTemp<6)
			{
				SeatCover.LockDieCount++;
				if(SeatCover.LockDieCount>6)		//-----卡死1S
				{
					Cover_Stop();
										
					SeatCover.OpenDir_f=0;
					SeatCover.LockDieCount=0;
					Status.LevelOffTime=20;	

					if(AdcAverage>(Cover.PositionMin+CoverPositionAddMax-100))	
					{
						if(Status.CoverOpen_f==0)
						{
							Status.CoverOpen_f=1;
							if(Cover.PositionCount>0);
							Cover.PositionCount--;
						}
				
					}
					//else if(AdcAverage<CoverPositionMin+30)
					else if(AdcAverage<Cover.PositionMin+100)
					{
						Status.CoverOpen_f=0;
					}
					else
					{
						SeatCircle.OpenDirStatus=0;
						SeatCover.OpenDirStatus=0;
					}

				}	
			}
			else
			{
				SeatCover.LockDieCount=0;
			}
			//--------------
			SeatCover.PositionIndex=AdcAverage;	

			if(0)
			//if(SeatCover.DelayTime>=300)
			{
				SeatCover.DelayTime=0;
				SeatCover.Enable_f=0;
				Cover_Stop();
			}
		}

		else
		{
			if((AdcAverage>(SeatCover.PositionIndex+5))||(AdcAverage<(SeatCover.PositionIndex-5)))
			{
				SeatCover.PositionIndex=AdcAverage;	
			}
			if(Cover.PositionCount>0)
			{
				if(AdcAverage<(CoverPositionMin+100))
				{
					Cover.PositionMinBUfferr[Cover.PositionCount]=AdcAverage;
				}
			}
			else
			{
				Cover.PositionMin=(Cover.PositionMinBUfferr[0]+
								Cover.PositionMinBUfferr[1]+
								Cover.PositionMinBUfferr[2]+
								Cover.PositionMinBUfferr[3]+
								Cover.PositionMinBUfferr[4])/5;
			}
			SeatCoverMotorStop();
			SeatCover.LockDieCount=0;
			SeatCover.DelayTime=0;
		}	
		}
	}
}

//-----------------------10ms检测一次
void ReadADCDeal(void)
{
	switch(Status.AdcChoice)
	{
		case 0:
			CoverPosition();
			Status.AdcChoice++;
			break;
		case 1:
			SeatPosition();	
			Status.AdcChoice=0;
			break;
		default:
			Status.AdcChoice=0;
			break;
	}
}

void CoverCircleDeal(void)
{
//-------------------------------------
	if(SeatCover.OpenDirStatus==1)
	{
		if((Status.CoverOpen_f==0)&&(SeatCircle.OpenDirStatus==0))
		{
			//----------翻盖	
			if(SeatCover.Enable_f==0)
			{			
				SeatCover.OpenOrClose_f=1;		//----open
				SeatCover.Duty=99;
				SeatCoverMotorUp(SeatCover.Duty);
			}
		}
		else
		{
			SeatCover.OpenDirStatus=0;
		}
	}
	else  if(SeatCover.OpenDirStatus==2)
	{
		if(SeatCircle.Enable_f==0)
		{
			if(Status.SeatOpen_f)
			{
			//---------先关圈
				SeatCircle.OpenOrClose_f=0;		//----close
				
				SeatCircle.Duty=90;
				SeatCircleMotorDown(SeatCircle.Duty);
			
			}		
			else
			{
				//------再关盖
				if((Status.CoverOpen_f)&&(SeatCircle.OpenDirStatus==0))
				{
					if(SeatCover.Enable_f==0)
					{
						SeatCover.OpenOrClose_f=0;			//----close
						SeatCover.Duty=99;
						SeatCoverMotorDown(SeatCover.Duty);
					}
				}
				else
				{
					SeatCover.OpenDirStatus=0;				
				}
			}
		}
	}
	else
	{
		SeatCover.OpenDirStatus=0;
	}

	
	//--------------
	if(SeatCover.OpenDirStatus==0)
	{
		if(SeatCircle.OpenDirStatus==1)
		{
			if(Status.CoverOpen_f)
			{
				//-----------翻圈
				if(Status.SeatOpen_f==0)
				{
					if(SeatCircle.Enable_f==0)
					{			
						SeatCircle.OpenOrClose_f=1;			//----open
						SeatCircle.Duty=99;
						SeatCircleMotorUp(SeatCircle.Duty);
					}
				}
				else
				{
					SeatCircle.OpenDirStatus=0;
				}
			}
			else
			{
				//---------先翻盖
				if(Status.CoverOpen_f==0)
				{
					if(SeatCover.Enable_f==0)
					{				
						SeatCover.OpenOrClose_f=1;			//----open
						SeatCover.Duty=99;
						SeatCoverMotorUp(SeatCover.Duty);
					}
				}
			}
		}
		else if(SeatCircle.OpenDirStatus==2)
		{
			if(Status.CoverOpen_f)
			{
				//-----------关圈
				if(Status.SeatOpen_f)
				{
					if(SeatCircle.Enable_f==0)
					{
						SeatCircle.OpenOrClose_f=0;			//----close
						SeatCircle.Duty=90;
						SeatCircleMotorDown(SeatCircle.Duty);
					}
				}
				else
				{
					SeatCircle.OpenDirStatus=0;
				}
			}			
		}
		else
		{
			SeatCircle.OpenDirStatus=0;
		}
	}
}




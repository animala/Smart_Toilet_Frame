


#include "main.h"
#include "MN101AF50D.h"
#include "math.h"


#include "WifiDeal.h"
#include "Init.h"


uint_8	WifiTxBuf[WifiTXBufMax];
uint_8	WifiRxBuf[WifiRXBufMax];
uint_8	ReturnStatusBuffer[ReturnStatusSize];
uint_8	ReturnStatusBufferBack[ReturnStatusSize];


WifiSendRepDeal_CB WifiSendRepDeal;
WifiRegisterSign_CB WifiRegisterSign;
WifiStatus_CB WifiStatus;


//---------清除所有清洗功能和烘干功能
void CloseAllFunction(void)
{
	if(Status.tunbu_f||Status.nvxing_f||Status.enfant_f)
	{
		work.step=0;
		Status.tunbu_f=0;
		Status.nvxing_f=0;
		Status.enfant_f=0;
	}
	if(Status.dring_f)
	{
		Drying.step=0;
		Status.dring_f=0;
	}
	Enfant.Dring_f=0;
	Status.QingXiQieHuan_f=0;
	Status.ShuiYaAnMo_f=0;
	Status.reciprocate_f=0;
	Status.dring_wf_f=0;
	Status.ZuoYu_f=0;
	Status.LengReAnMo_f=0;
	work.Start_f=0;
//	Status.dengkong_f=0;
	Drying.swash_f=0;
	work.LianXu_f=0;
	work.LianXuBuf=0;
	if(Status.penkou_f)
	{
		penkou.step=0;
		Status.penkou_f=0;
	}
}

//-------------关闭加液功能
void CloseLiquid(void)
{
//	if((LiquidDeal.Flag)&&(LiquidDeal.SetOff1Min==0))
	if(LiquidDeal.Flag)
	{
		LiquidDeal.Frist_f=0;		//-----笆∠状渭右箳0S气泡时间
		if(LiquidDeal.Start_f)
		{					
			LiquidDeal.Start_f=0;
			LiquidDeal.Step=0;
			LiquidDeal.Enable_f=1;
			LiquidDeal.Frist_f=0;
			LiquidDeal.Stop_f=1;
		}
		if(LiquidDeal.SetOff1Min==0)
		{
			LiquidDeal.WaterWash_f=0;
		}
		LiquidDeal.Flag=0;
	}
}

void PenKouEnable(void)
{
	if((Status.power_f)&&(Error.value==0)&&(Status.seat_f==0)&&(work.enable_f==0))
	{
		if(Status.penkou_f==0)
		{
			penkou.step=0;
			Status.penkou_f=1;
			penkou.enable_f=1;
			Status.stop_f=1;	
			Status.tunbu_f=0;
			Status.nvxing_f=0;
			Status.dring_f=0;
			work.step=0;
			Status.ShuiYaAnMo_f=0;
			Status.reciprocate_f=0;
			Status.dring_wf_f=0;
			Status.ZuoYu_f=0;
			Status.LengReAnMo_f=0;
			Status.ShuiYaAnMo_f=0;
			CloseLiquid();
		}
	}
}


void TunBuWashEnable(void)
{
	if(Status.tunbu_f==0)
	{
		Status.stop_f=0;
		Status.tunbu_f=1;
		if(Status.nvxing_f)
		{
			Status.QingXiQieHuan_f=1;
			Status.nvxing_f=0;
		}		
		Status.enfant_f=0;
		Enfant.Dring_f=0;					
		Status.TunBuShuiYaTiaoJie_f=1;
		Status.NvXingShuiYaTiaoJie_f=0;
		Status.EnfantShuiYaTiaoJie_f=0;
		work.enable_f=1;
		work.step=0;
		if(Status.dring_f)
		{
			Status.dring_f=0;
			Drying.step=0;
		}	
		Status.ZuoYu_f=0;
		Status.LengReAnMo_f=0;
		Status.ShuiYaAnMo_f=0;
		Status.reciprocate_f=0;
		Status.fangwu_f=0;
		Drying.swash_f=0;
		Water.WashTimer=T1Min;			
	}
	work.LianXu_f=0;
	work.LianXuBuf=0;
}
void NvXingWashEnable(void)
{
	if(Status.nvxing_f==0)
	{
		Status.stop_f=0;
		if(Status.tunbu_f)
		{
			Status.QingXiQieHuan_f=1;
			Status.tunbu_f=0;
		}					
		Status.nvxing_f=1;
		Status.enfant_f=0;
		Enfant.Dring_f=0;
		Status.TunBuShuiYaTiaoJie_f=0;
		Status.NvXingShuiYaTiaoJie_f=1;	
		Status.EnfantShuiYaTiaoJie_f=0;
		work.enable_f=1;
		work.step=0;
		if(Status.dring_f)
		{
			Status.dring_f=0;
			Drying.step=0;
		}	
		Status.ZuoYu_f=0;
		Status.LengReAnMo_f=0;
		Status.ShuiYaAnMo_f=0;
		Status.reciprocate_f=0;
		Status.fangwu_f=0;
		Drying.swash_f=0;
		Water.WashTimer=T1Min;
	}
	else
	{
		Status.ZuoYu_f=0;
	}
	work.LianXu_f=0;
	work.LianXuBuf=0;
}

void DringWorkEnable(void)
{
	if(Status.dring_f==0)
	{
		Status.stop_f=0;
		Status.tunbu_f=0;
		Status.nvxing_f=0;
		Status.enfant_f=0;
		Enfant.Dring_f=0;
		Status.QingXiQieHuan_f=0;
		//---work.enable_f=1;
		work.step=0;
		Status.dring_f=1;
		Drying.enable_f=1;
		Status.DringTiaoJie_f=1;
		Drying.step=0;
		Status.ZuoYu_f=0;
		Status.LengReAnMo_f=0;
		Status.ShuiYaAnMo_f=0;
		Status.reciprocate_f=0;
		Drying.WorkingTimer=T4Min;
	}
	work.LianXu_f=0;
	work.LianXuBuf=0;
}

void EnfantWashEnable(void)
{
		if(Status.enfant_f==0)
		{
			Status.stop_f=0;
			if(Status.tunbu_f|Status.nvxing_f)
			{
				Status.QingXiQieHuan_f=1;
				Status.tunbu_f=0;
				Status.nvxing_f=0;
			}					
			Status.enfant_f=1;
			Enfant.Dring_f=1;
			//-------------档位灯显示选择
			Status.TunBuShuiYaTiaoJie_f=0;
			Status.NvXingShuiYaTiaoJie_f=0;
			Status.EnfantShuiYaTiaoJie_f=1;
			Status.DringTiaoJie_f=0;
			Status.ZuoWenSet_f=0;
			Status.ShuiWenSet_f=0;
			//-----------
			work.enable_f=1;
			work.step=0;
			Status.dring_f=0;
			Drying.step=0;					
			Status.ZuoYu_f=0;
			Status.LengReAnMo_f=0;
			Status.ShuiYaAnMo_f=0;
			Status.reciprocate_f=0;
			Status.fangwu_f=0;
			Drying.swash_f=0;
			Water.WashTimer=T1Min;
			Drying.WorkingTimer=T4Min;
		}
}

void	Uart1_init(void)		//初始化UART1
{
	TMAMD1=0x08;		//计数器A开始计数，选择时钟源fpll=8m
	TMAMD2=0x40;		//预分频器开
	TMAOC=103;			//频率=((8*100000)/(103+1))/8=9600
//	TMAOC=52;			//频率=((8*100000)/(103+1))/8=9600
	SC1SEL=0x0f;		//---选择串口1时钟原  以及选择A，B系统  
	
	P7ODC=P7ODC|0x60;		//-----设定p75,P76为开路	
	P7DIR|=0x20;			//----P75
	P7DIR&=~0x40;			//----P76	
	SC1MD0=0x10;
//SC1MD1说明	//bit7=0 RX输入数据
				//bit6=0,SBTN 设置为端口，
				//bit5=1,串行输入				
				//bit4=1，串行数据输出
				//bit3=1，分频
				//bit2=1，主时钟
				//bit1=0，选择8分频
				//bit0=1，全双工
	SC1MD1=0x3d;	
	SC1MD2=0x88;	//8位数据1位停止位  无奇偶效验
	SC1MD3=0x0f;
	SC1TICR=SC1TICR|0X02;		//--允许串口1发送中断
	SC1RICR=SC1RICR|0X02;		//--允许串口1接收中断
	SC1STR=0x40;				//----串口1接收准备
}
//-----------------------------------

/*******************************************************************************
//      功能:       接受应答包
//      输入参数:   无
//      输出参数:   无
//      返回值:     无
//      设定头地址为0x55
//----checksum效验data1+data2+data3

*******************************************************************************/
void WifiRx(void)
{
	uint_8 i;	
       uint_8 checksum;
	if(WifiSendRepDeal.Rx_f)
	{
		WifiSendRepDeal.Rx_ok_f=0;
		WifiSendRepDeal.Rx_error_f=0;
		if((WifiRxBuf[0]==Uart1_Rx_Head1)  &&(WifiRxBuf[1]==Uart1_Rx_Head1))
		{
			WifiSendRepDeal.Tx_size=WifiRxBuf[2];
			checksum=0;
			checksum=WifiSendRepDeal.Rx_55_sum;
			WifiSendRepDeal.Rx_55_sum=0;
			for(i=2;i<(WifiSendRepDeal.Tx_size+2);i++)
			{
				checksum+=WifiRxBuf[i];
			}
			if(checksum==WifiRxBuf[WifiSendRepDeal.Tx_size+2])
			{
				WifiSendRepDeal.Rx_ok_f=1;
				WifiSendRepDeal.Rx_f=0;
				WifiSendRepDeal.Rx_count=0;
				WifiSendRepDeal.Rx_num=0;
				MachineTest.CheckWifiSignal_f=1;
			}
			else
			{
				WifiSendRepDeal.Rx_error_count++;
				if(WifiSendRepDeal.Rx_error_count>7)
				{
					WifiSendRepDeal.Rx_error_count=0;
				}
				WifiSendRepDeal.Rx_error_f=1;
				WifiSendRepDeal.Rx_f=0;
				WifiSendRepDeal.Rx_count=0;
				WifiSendRepDeal.Rx_num=0;
			}
		}
		else
		{
			WifiSendRepDeal.Rx_error_f=1;
			WifiSendRepDeal.Rx_f=0;
			WifiSendRepDeal.Rx_count=0;
			WifiSendRepDeal.Rx_num=0;
		}		
        }	
	else
	{
		if(WifiSendRepDeal.Rx_error_f==1)
		{
			WifiSendRepDeal.Rx_error_f=0;
			WifiSendRepDeal.Rxtime=0;
			WifiSendRepDeal.Rx_count=0;
			WifiSendRepDeal.Rx_num=0;
			WifiSendRepDeal.Rx_ok_f=0;
		}
	
		WifiSendRepDeal.Rxtime++;
		if(WifiSendRepDeal.Rxtime>10)
		{
			WifiSendRepDeal.Rxtime=0;
			WifiSendRepDeal.Rx_count=0;
			WifiSendRepDeal.Rx_num=0;
			WifiSendRepDeal.Rx_ok_f=0;
		}
	}
}

//-----------------------------------------
void GetModeCommData(void)
{
	if(WifiRxBuf[AddressJieNeng]==1)
	{
		Status.jieneng_f=1;
	}
	else
	{
		Status.jieneng_f=0;
	}
	if(WifiRxBuf[Addressdengkong]==1)
	{
		if(Status.dengkong_f==0)
		{
			Status.dengkong_f=1;
			LightInduce.Timer=T10Min;
		}
	}
	else
	{
		Status.dengkong_f=0;
	}

	//---------------------------------
	if(WifiRxBuf[AddressSeatTemp]==32)
	{
		Seat.DangWei=1;
	}
	else if(WifiRxBuf[AddressSeatTemp]==34)
	{
		Seat.DangWei=2;
	}
	else if(WifiRxBuf[AddressSeatTemp]==36)
	{
		Seat.DangWei=3;
	}
	else if(WifiRxBuf[AddressSeatTemp]==38)
	{
		Seat.DangWei=4;
	}	
	else if(WifiRxBuf[AddressSeatTemp]==40)
	{
		Seat.DangWei=5;
	}
	else
	{
		Seat.DangWei=0;
	}
	//--------------------------
	if(WifiRxBuf[AddressPenKou]==1)
	{
		PenKouEnable();
	}
	else
	{
		if(Status.penkou_f)
		{
			penkou.step=0;
			Status.penkou_f=0;
		}

	}

/**
	if(WifiRxBuf[AddressAutoEnable])
	{
		Status.chongshui_f=1;
		Status.chongshuiban_f=1;
		Status.chongshui_e=0;
	}
**/	

	if(WifiRxBuf[AddressFaPao])
	{
		if((Status.power_f)&&(Error.value==0)&&(Status.seat_f==0)&&(work.enable_f==0))
		{
			if(LiquidDeal.Enable_f==0)
			{
				LiquidDeal.Flag=1;	
				LiquidDeal.SetOff1Min=0;
				//LiquidDeal.Frist_f=1;	
				LiquidDeal.Stop_f=0;
			}
		}
	}
	else
	{
		CloseLiquid();

	}
	
}


/*********************************************
电源板发送数据格式				
数据格式=0x55+data1+data2+data3+checksum				
checksum=data1+data2+data3				
data1:表示应答信号				
data2:表示AD高位.				
data3:表示AD低位.				
*********************************************/
void	WifiRxprogram(void)
{
//	unsigned char	i;
	//接受到正确数据	
	if(WifiSendRepDeal.Rx_ok_f)
	{
		WifiSendRepDeal.Rxtime=0;
		WifiSendRepDeal.Rx_ok_f=0;
		//-------------------------模式选择
		switch(WifiRxBuf[AddressConrrol])
		{
			case ComdDataAndControl:
				//-----------------------------查询机器状态
				if((WifiRxBuf[4]==0x10)&&( WifiRxBuf[5]==0x01) )
				{
					WifiRegisterSign.repeater_f=1;					
				}
				//-----------------------------关机
				if((WifiRxBuf[4]==0x10)&&( WifiRxBuf[5]==0x03) )
				{
					buz_set(1,20,20);
					Status.power_f=OFF;
					CloseAllFunction();
					CloseLiquid();
					WifiRegisterSign.repeater_f=1;					
				}
				//-----------------------------开机
				else if((WifiRxBuf[4]==0x10)&&( WifiRxBuf[5]==0x02) )
				{
					buz_set(1,20,20);
					Status.power_f=ON;
					CloseAllFunction();
					CloseLiquid();
					WifiRegisterSign.repeater_f=1;
				}
				//-----------------------------停止
				else if((WifiRxBuf[4]==0x20)&&( WifiRxBuf[5]==0x04) )
				{
					buz_set(1,20,20);
					if((Status.tunbu_f==0)&&(Status.nvxing_f==0)&&(Status.enfant_f==0)&&(Status.dring_f==0)
						&&(LiquidDeal.Flag==0))
					{
						Status.chuchou_e=0;
					}
					CloseAllFunction();
					CloseLiquid();
					WifiRegisterSign.repeater_f=1;
				}

				else if((WifiRxBuf[4]==0x30)&&( WifiRxBuf[5]==0x01) )
				{
					buz_set(1,20,20);
					//--------------接收数据处理
					switch(WifiRxBuf[AddressMode])
					{
						case 0:
							//------没有开启清洗功能
							GetModeCommData();
							//-------------------
							
							WifiRegisterSign.repeater_f=1;
							break;
						case 1:
							//-------臀部清洗
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								TunBuWashEnable();
								if(WifiRxBuf[AddressWaterTemp]==32)
								{
									Water.DangWei=1;
								}
								else if(WifiRxBuf[AddressWaterTemp]==34)
								{
									Water.DangWei=2;
								}
								else if(WifiRxBuf[AddressWaterTemp]==36)
								{
									Water.DangWei=3;
								}
								else if(WifiRxBuf[AddressWaterTemp]==38)
								{
									Water.DangWei=4;
								}
								else if(WifiRxBuf[AddressWaterTemp]==40)
								{
									Water.DangWei=5;
								}
								else
								{
									Water.DangWei=0;
								}
								TunBu.pressure=WifiRxBuf[AddressWaterPressure];
								TunBu.PGLevel=WifiRxBuf[AddressPGLevel];
								if(WifiRxBuf[AddressWashTimerSet]==1)
								{
									Water.WashTimer=WifiRxBuf[AddressWashTimer];
									work.time=WifiRxBuf[AddressWashTimer];
								}
								Status.ShuiYaAnMo_f=WifiRxBuf[AddressShuiYaAnMo];
								Status.reciprocate_f=WifiRxBuf[AddressYiDongAnMo];
								Status.LengReAnMo_f=WifiRxBuf[AddressLengReSpa];
								//Drying.DangWei=WifiRxBuf[AddressDringLevel];
								//Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
								GetModeCommData();	
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}							
							break;
						case 2:
							//-------女性清洗
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								NvXingWashEnable();
								if(WifiRxBuf[AddressWaterTemp]==32)
								{
									Water.DangWei=1;
								}
								else if(WifiRxBuf[AddressWaterTemp]==34)
								{
									Water.DangWei=2;
								}
								else if(WifiRxBuf[AddressWaterTemp]==36)
								{
									Water.DangWei=3;
								}
								else if(WifiRxBuf[AddressWaterTemp]==38)
								{
									Water.DangWei=4;
								}
								else if(WifiRxBuf[AddressWaterTemp]==40)
								{
									Water.DangWei=5;
								}
								else if(WifiRxBuf[AddressWaterTemp]==41)
								{
									Status.ZuoYu_f=1;
								}
								else
									
								{
									Water.DangWei=0;
								}
								
								NvXing.pressure=WifiRxBuf[AddressWaterPressure];
								NvXing.PGLevel=WifiRxBuf[AddressPGLevel];
								if(WifiRxBuf[AddressWashTimerSet]==1)
								{
									Water.WashTimer=WifiRxBuf[AddressWashTimer];
									work.time=WifiRxBuf[AddressWashTimer];
								}
								Status.ShuiYaAnMo_f=WifiRxBuf[AddressShuiYaAnMo];
								Status.reciprocate_f=WifiRxBuf[AddressYiDongAnMo];
								Status.ZuoYu_f=WifiRxBuf[AddressLengReSpa];		//----男用冷热SPA，女用经期特护
							//	Status.LengReAnMo_f=WifiRxBuf[AddressLengReSpa];
								//Drying.DangWei=WifiRxBuf[AddressDringLevel];
								//Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
								GetModeCommData();
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}
							break;
						case 3:
							//-------烘干
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								DringWorkEnable();
								Drying.DangWei=WifiRxBuf[AddressDringLevel];
								if(WifiRxBuf[AddressDringTimerSet]==1)
								{
									Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
									work.time=WifiRxBuf[AddressDringTimer];	
								}
								GetModeCommData();
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}
							break;
						case 4:
							//---------儿童清洗
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								if(work.LianXuBuf==1)
								{
									if(WifiRxBuf[AddressWashTimerSet]==1)
									{
										EnfantWashEnable();
										work.LianXu_f=1;
										work.LianXuBuf=1;
									}
									else
									{
										//-----在转入到烘干模式后设置了智控功能
										//-----不重复开启清洗功能	
									
									}
								}
								else
								{
									EnfantWashEnable();
									work.LianXu_f=1;
									work.LianXuBuf=1;
								}
								//Water.DangWei=WifiRxBuf[AddressWaterTemp];
								//TunBu.pressure=WifiRxBuf[AddressWaterPressure];
								//NvXing.PGLevel=WifiRxBuf[AddressPGLevel];
								if(WifiRxBuf[AddressWashTimerSet]==1)
								{
									Water.WashTimer=WifiRxBuf[AddressWashTimer];
									work.time=WifiRxBuf[AddressWashTimer];
								}
								//Status.ShuiYaAnMo_f=WifiRxBuf[AddressShuiYaAnMo];
								//Status.reciprocate_f=WifiRxBuf[AddressYiDongAnMo];
								///Status.LengReAnMo_f=WifiRxBuf[AddressLengReSpa];
								//Drying.DangWei=WifiRxBuf[AddressDringLevel];
								if(WifiRxBuf[AddressDringTimerSet]==1)
								{
									Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
									//work.time=WifiRxBuf[AddressDringTimer];	
								}
								GetModeCommData();
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}
							break;
						case 5:
							//----------男用全自动
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								if(work.LianXuBuf==2)
								{
									if(WifiRxBuf[AddressWashTimerSet]==1)
									{
										TunBuWashEnable();
										work.LianXu_f=1;
										work.LianXuBuf=2;
									}
									else
									{
										//-----在转入到烘干模式后设置了智控功能
										//-----不重复开启清洗功能	
									
									}
								}
								else
								{
									TunBuWashEnable();
									work.LianXu_f=1;
									work.LianXuBuf=2;
								}
								if(WifiRxBuf[AddressWaterTemp]==32)
								{
									Water.DangWei=1;
								}
								else if(WifiRxBuf[AddressWaterTemp]==34)
								{
									Water.DangWei=2;
								}
								else if(WifiRxBuf[AddressWaterTemp]==36)
								{
									Water.DangWei=3;
								}
								else if(WifiRxBuf[AddressWaterTemp]==38)
								{
									Water.DangWei=4;
								}
								else if(WifiRxBuf[AddressWaterTemp]==40)
								{
									Water.DangWei=5;
								}
								else
								{
									Water.DangWei=0;
								}
								TunBu.pressure=WifiRxBuf[AddressWaterPressure];
								//TunBu.PGLevel=WifiRxBuf[AddressPGLevel];
								TunBu.PGLevel=3;
								if(WifiRxBuf[AddressWashTimerSet]==1)
								{
									Water.WashTimer=WifiRxBuf[AddressWashTimer];
									work.time=WifiRxBuf[AddressWashTimer];
								}
								Status.ShuiYaAnMo_f=WifiRxBuf[AddressShuiYaAnMo];
								Status.reciprocate_f=WifiRxBuf[AddressYiDongAnMo];
								Status.LengReAnMo_f=WifiRxBuf[AddressLengReSpa];
								Drying.DangWei=WifiRxBuf[AddressDringLevel];
								if(WifiRxBuf[AddressDringTimerSet]==1)
								{
									Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
									//work.time=WifiRxBuf[AddressDringTimer];	
								}
								GetModeCommData();	
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}

							break;
						case 6:
							//---------女用全自动
							if((Status.power_f)&&(Status.seat_f)&&(Error.value==0))
							{
								if(work.LianXuBuf==4)
								{
									if(WifiRxBuf[AddressWashTimerSet]==1)
									{
										NvXingWashEnable();
										work.LianXu_f=1;
										work.LianXuBuf=4;
									}
									else
									{
										//-----在转入到烘干模式后设置了智控功能
										//-----不重复开启清洗功能	
									
									}
								}
								else
								{
									NvXingWashEnable();
									work.LianXu_f=1;
									work.LianXuBuf=4;
								}
								if(WifiRxBuf[AddressWaterTemp]==32)
								{
									Water.DangWei=1;
								}
								else if(WifiRxBuf[AddressWaterTemp]==34)
								{
									Water.DangWei=2;
								}
								else if(WifiRxBuf[AddressWaterTemp]==36)
								{
									Water.DangWei=3;
								}
								else if(WifiRxBuf[AddressWaterTemp]==38)
								{
									Water.DangWei=4;
								}
								else if(WifiRxBuf[AddressWaterTemp]==40)
								{
									Water.DangWei=5;
								}
								else
								{
									Water.DangWei=0;
								}
								
								NvXing.pressure=WifiRxBuf[AddressWaterPressure];
								NvXing.PGLevel=WifiRxBuf[AddressPGLevel];
								if(WifiRxBuf[AddressWashTimerSet]==1)
								{
									Water.WashTimer=WifiRxBuf[AddressWashTimer];
									work.time=WifiRxBuf[AddressWashTimer];
								}
								Status.ShuiYaAnMo_f=WifiRxBuf[AddressShuiYaAnMo];
								Status.reciprocate_f=WifiRxBuf[AddressYiDongAnMo];
								Status.LengReAnMo_f=WifiRxBuf[AddressLengReSpa];
								Drying.DangWei=WifiRxBuf[AddressDringLevel];
								if(WifiRxBuf[AddressDringTimerSet]==1)
								{
									Drying.WorkingTimer=WifiRxBuf[AddressDringTimer];
									//work.time=WifiRxBuf[AddressDringTimer];	
								}
								GetModeCommData();	
								WifiRegisterSign.repeater_f=1;
							}
							else
							{
								WifiRegisterSign.wuxiao_f=1;
							}
							break;
						case 7:
							//-------冲水
							Status.chongshui_f=1;
							Status.chongshuiban_f=1;
							Status.chongshui_e=0;
							GetModeCommData();	
							WifiRegisterSign.repeater_f=1;
							break;
						default:
							break;

					}
				}

				break;
				//------------------确认帧
			case ComdAffirm:
				get_Return_status_buffer_back();
				WifiRegisterSign.wifi_zijian_f=0;
				WifiRegisterSign.WifiSet_T_f=0;
				WifiRegisterSign.save_f=0;
				WifiRegisterSign.repeater1_f=0;
				WifiRegisterSign.repeater1_count=0;
				WifiRegisterSign.repeater2_f=0;
				WifiRegisterSign.repeater2_count=0;
				WifiRegisterSign.alram_timer1=Timer500ms;
				break;
				//-----------------------停止故障报警
			case ComdStopAlarm:
				WifiRegisterSign.alramstop_f=1;			
				break;
				//----------------------查询设备
			case ComdSeeAboutEdition:
				WifiRegisterSign.shebeibanben_f=1;
				break;
				//---------------------劥檠璞赣Υ飈
			case ComdEditionResponsion:
				
				WifiRegisterSign.shebeibanben_f=1;
				break;

				//---------------网络状态应答				
			case ComdSeeAboutNetworkRep:
				WifiRegisterSign.wifi_zhuangtai_f=1;
				WifiRegisterSign.wifiStatuse=WifiRxBuf[4];
				if(WifiRegisterSign.wifiStatuse>1)
				{
					WifiRegisterSign.wifiSetTime=0;
				}



				/**
				if((WifiRxBuf[4]==0x00)			//-----通讯正常
				{
					WifiStatus.wifi_f=1;
					WifiRegisterSign.wifiStatuse=0;
					
					//digital.digital_L3=1;
				}
				if( WifiRxBuf[4]==0x01)			//-------AP无法连接	
				{
					WifiRegisterSign.wifiStatuse=1;	
				}
				if( WifiRxBuf[4]==0x02)			//-------服务器无法连接
				{
					WifiRegisterSign.wifiStatuse=2;
				}
				if( WifiRxBuf[4]==0x03)			//------设置状态
				{
					WifiStatus.wifi_f=1;
					WifiRegisterSign.wifiStatuse=3;
				}
				********/
				break;				
			default:
				WifiRegisterSign.wuxiao_f=1;
				break;
			}
		WifiSendRepDeal.Rx_f=0;
	}
}

void	GetHeadData(void)
{
	WifiTxBuf[0]=Uart1_Rx_Head1;
	WifiTxBuf[1]=Uart1_Rx_Head2;
}


//---------------------------wifi 设置
void wifi_zijian_send(void)
{
	uint_8	i;
	WifiRegisterSign.repeater1_timer=Timer500ms;
	WifiRegisterSign.repeater2_timer=Timer1min;
	GetHeadData();
	WifiTxBuf[2]=0x02;
	WifiTxBuf[3]=ComdModuleTest;
	WifiTxBuf[4]=0x00;
	for(i=2;i<4;i++)
	WifiTxBuf[4]=WifiTxBuf[4]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];	
}
void	wifi_set_send(void)
{
	uint_8	i;
	WifiRegisterSign.repeater1_timer=Timer500ms;
	WifiRegisterSign.repeater2_timer=Timer1min;
	GetHeadData();        
	WifiTxBuf[AddressFrameLong]=0x02;
	WifiTxBuf[3]=ComdConfigureNetwork;
	WifiTxBuf[4]=0x00;
	for(i=2;i<4;i++)
	WifiTxBuf[4]=WifiTxBuf[4]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4;	
	WifiSendRepDeal.Tx_num=1;	        
      	TXBUF1=WifiTxBuf[0];
}

//--------------------------应答命令
void wifi_Repeater_R(void)
{
	unsigned char	i;
	WifiRegisterSign.repeater1_timer=Timer500ms;
	WifiRegisterSign.repeater2_timer=Timer1min;
	WifiRegisterSign.repeater_f=0;
	//--------------------------------增加状态表?	Get_Return_status_buffer();
	Get_Return_status_buffer();	
	GetHeadData();
	WifiTxBuf[2]=2+ReturnStatusSize;
	WifiTxBuf[3]=ComdStatusAndAlarm;
	for(i=0;i<ReturnStatusSize;i++)
	{
		WifiTxBuf[4+i]=ReturnStatusBuffer[i];
	}
	WifiTxBuf[4+ReturnStatusSize]=0x00;
	for(i=2;i<4+ReturnStatusSize;i++)
	WifiTxBuf[4+ReturnStatusSize]=WifiTxBuf[4+ReturnStatusSize]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4+ReturnStatusSize;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];		
}
//-------------------------------
void wifi_Repeater1_R(void)
{
	uint_8	i;
	//--------------------------------增加状态表?	Get_Return_status_buffer();
	Get_Return_status_buffer();
	GetHeadData();
	WifiTxBuf[2]=2+ReturnStatusSize;
	WifiTxBuf[3]=ComdReport;
	for(i=0;i<ReturnStatusSize;i++)
	{
		WifiTxBuf[4+i]=ReturnStatusBuffer[i];
	}
	WifiTxBuf[4+ReturnStatusSize]=0x00;
	for(i=2;i<4+ReturnStatusSize;i++)
	WifiTxBuf[4+ReturnStatusSize]=WifiTxBuf[4+ReturnStatusSize]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4+ReturnStatusSize;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];
}
//-------------------------------------
void wifi_Repeater2_R(void)
{
	unsigned char	i;
	//--------------------------------增加状态表?	Get_Return_status_buffer();
	Get_Return_status_buffer();
	GetHeadData();
	WifiTxBuf[2]=4+ReturnStatusSize;
	WifiTxBuf[3]=ComdReport;
	WifiTxBuf[4]=0x7d;
	WifiTxBuf[5]=0x01;
	for(i=0;i<ReturnStatusSize;i++)
	{
		WifiTxBuf[6+i]=ReturnStatusBuffer[i];
	}
	WifiTxBuf[6+ReturnStatusSize]=0x00;
	for(i=2;i<6+ReturnStatusSize;i++)
	WifiTxBuf[6+ReturnStatusSize]=WifiTxBuf[6+ReturnStatusSize]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=6+ReturnStatusSize;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];	

}



void wifi_AckYingDa(void)
{
	unsigned char	i;
	WifiRegisterSign.ACK_f=0;
	WifiRegisterSign.repeater1_timer=Timer500ms;
	WifiRegisterSign.repeater2_timer=Timer1min;
	GetHeadData();
	WifiTxBuf[2]=2;
	WifiTxBuf[3]=ComdAffirm;
//------------------------
	WifiTxBuf[4]=0;
	for(i=2;i<4;i++)
	WifiTxBuf[4]=WifiTxBuf[4]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];
}

//---------------------------wifi 状态查询
void	wifi_status_chaxun_t(void)
{
	unsigned char	i;
	WifiRegisterSign.repeater1_timer=Timer500ms;
	WifiRegisterSign.repeater2_timer=Timer1min;
	GetHeadData();
	WifiTxBuf[2]=0x02;
	WifiTxBuf[3]=ComdSeeAboutNetwork;	
	WifiTxBuf[4]=0x00;
	for(i=2;i<4;i++)
	WifiTxBuf[4]=WifiTxBuf[4]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];	
}
//--------------------------所有错误命令都认为是无效命令
void	wifi_wuxiao_R(void)
{
	unsigned char	i;
	WifiRegisterSign.wuxiao_f=0;
	GetHeadData();
	WifiTxBuf[2]=0x02;
	WifiTxBuf[3]=ComdInefficacy;
	WifiTxBuf[4]=0x00;
	for(i=2;i<4;i++)
	WifiTxBuf[4]=WifiTxBuf[4]+WifiTxBuf[i];
	WifiSendRepDeal.Tx_count=4;	
	WifiSendRepDeal.Tx_num=1;	
	TXBUF1=WifiTxBuf[0];		
}
void	WifiSend(void)
{
//-------------------------wifi自检模式
	if(WifiRegisterSign.wifi_zijian_f)
	{
		if(WifiRegisterSign.repeater_timer==0)
		{
			WifiRegisterSign.send_count++;
			if(WifiRegisterSign.send_count<6)
			{
				//WifiRegisterSign.repeater_timer=Timer1000ms;
				WifiRegisterSign.repeater_timer=Timer200ms;	
				wifi_zijian_send();
			}
			else
			{
				WifiRegisterSign.send_count=0;
				WifiRegisterSign.wifi_zijian_f=0;
			}
		}
	}
	//-------------------------wifi模式设置
	else if(WifiRegisterSign.WifiSet_T_f)
	{
		if(WifiRegisterSign.repeater_timer==0)
		{
			WifiRegisterSign.send_count++;
			if(WifiRegisterSign.send_count<6)
			{
				WifiRegisterSign.repeater_timer=Timer1000ms;
				wifi_set_send();
			}
			else
			{
				WifiRegisterSign.send_count=0;
                                WifiRegisterSign.WifiSet_T_f=0;
			}
		}
	}
	//--------------------ACK确认
	else if(WifiRegisterSign.ACK_f)
	{
		wifi_AckYingDa();
	}
	//---------------------应答
	else if(WifiRegisterSign.repeater_f)
	{
		wifi_Repeater_R();
	}
	//-------------------无晓	
	else if(WifiRegisterSign.wuxiao_f)
	{
		wifi_wuxiao_R();
	}	
	//--------------------1分钟应答
	else if(WifiRegisterSign.repeater2_timer==0)
	{
		WifiRegisterSign.repeater1_timer=WifiRegisterSign.shebeihuibao_time;	
		WifiRegisterSign.repeater2_timer=Timer1min;
		compare_status_buffer();
		if(WifiRegisterSign.repeater2_f)
		{
			if(WifiRegisterSign.repeater2_count<3)
			{
        			WifiRegisterSign.repeater2_count++;  
				WifiRegisterSign.repeater2_timer=2;	
				wifi_Repeater2_R();
			}
			else
			{
				//WifiRegisterSign.repeater1_count=2;
				get_Return_status_buffer_back();
				WifiRegisterSign.repeater2_f=0;
       			WifiRegisterSign.repeater2_count=0;
			}
		}
		//--------------空闲状态下 1分钟查询一次网络
		else
		{
			wifi_status_chaxun_t();
		}
	}
//---------------------1秒钟应答
	if(WifiRegisterSign.repeater1_timer==0)
	{
		compare_status_buffer();
		if(WifiRegisterSign.repeater1_f)
		{
			WifiRegisterSign.repeater1_f=0;
			if(WifiRegisterSign.repeater1_count<3)
			{
        			WifiRegisterSign.repeater1_count++;  
				WifiRegisterSign.repeater1_timer=2;			//200MS
				wifi_Repeater1_R();
			}
			else
			{
				get_Return_status_buffer_back();
				WifiRegisterSign.repeater1_f=0;
       			WifiRegisterSign.repeater1_count=0;
			}
		}
	}
	else
	{
		if(WifiRegisterSign.repeater1_timer==0)
		{
			WifiRegisterSign.repeater1_timer=WifiRegisterSign.shebeihuibao_time;
			if(ReturnStatusBuffer[0]>=3)
			{
				wifi_Repeater1_R();
			}
			compare_status_buffer();
			get_Return_status_buffer_back();
			if(WifiRegisterSign.repeater1_f)
			{
				if(WifiRegisterSign.repeater1_count<3)
				{
  	     				 WifiRegisterSign.repeater1_count++;  
					WifiRegisterSign.repeater1_timer=Timer500ms;	
					wifi_Repeater1_R();
				}
				else
				{
					get_Return_status_buffer_back();
					WifiRegisterSign.repeater1_f=0;
       				WifiRegisterSign.repeater1_count=0;
				}
			}
		}
	}
	/**
	//-----------------
	if(WifiRegisterSign.repeater1_timer==0)
	{
		WifiRegisterSign.repeater1_timer=Timer500ms;	
		wifi_Repeater1_R();
	}
	**/
	//----------------

	
	Get_Return_status_buffer();
}	
//------------------------------------
void get_Return_status_buffer_back(void)
{
	unsigned char	i;	
	for(i=0;i<ReturnStatusSize;i++)
	{
		ReturnStatusBufferBack[i]=ReturnStatusBuffer[i];
	}
}

void compare_status_buffer(void)
{
	unsigned char	i;
	WifiRegisterSign.repeater1_f=0;
	WifiRegisterSign.repeater2_f=0;
	for(i=0;i<ReturnStatusSize;i++)
	{
		if(ReturnStatusBufferBack[i]!=ReturnStatusBuffer[i])
		{
			WifiRegisterSign.repeater1_f=1;
			WifiRegisterSign.repeater2_f=1;
		}
	}
	if(WifiRegisterSign.repeater1_f==0)
	{
		WifiRegisterSign.repeater1_count=0;	
		WifiRegisterSign.repeater2_count=0;	
	}
}

void Get_Return_status_buffer(void)
{
		//---------------模式
		if(Status.tunbu_f)
		{
			if(work.LianXu_f)
			{
				ReturnStatusBuffer[0]=5;		
			}
			else 
			{
				ReturnStatusBuffer[0]=1;
			}
		}
		else if(Status.nvxing_f)
		{
			if(work.LianXu_f)
			{
				ReturnStatusBuffer[0]=6;		
			}
			else 
			{
				ReturnStatusBuffer[0]=2;
			}
		}
		else if(Status.enfant_f)
		{
			ReturnStatusBuffer[0]=4;
		}
		else if(Status.dring_f)
		{
			ReturnStatusBuffer[0]=3;			

		}
		else
		{
			ReturnStatusBuffer[0]=0;
		}
		//-----水温档位		
//		ReturnStatusBuffer[1]=Water.DangWei;	
		if(Status.ZuoYu_f)
		{
			ReturnStatusBuffer[1]=41;
		}
		else
		{	
			if(Water.DangWei==1)
			{
				ReturnStatusBuffer[1]=32;
			}
			else if(Water.DangWei==2)
			{
				ReturnStatusBuffer[1]=34;
			}			
			else if(Water.DangWei==3)
			{
				ReturnStatusBuffer[1]=36;
			}
			else if(Water.DangWei==4)
			{
				ReturnStatusBuffer[1]=38;
			}
			else if(Water.DangWei==5)
			{
				ReturnStatusBuffer[1]=40;
			}
			else if(Status.ZuoYu_f)
			{
				ReturnStatusBuffer[1]=41;
			}
			else
			{
				ReturnStatusBuffer[1]=0;
			}
		}
		//-----水压
		if(Status.tunbu_f)
		{
			ReturnStatusBuffer[2]=TunBu.pressure;
			ReturnStatusBuffer[3]=TunBu.PGLevel;
			ReturnStatusBuffer[4]=0;
			ReturnStatusBuffer[5]=Water.WashTimer;
		}
		if(Status.nvxing_f)
		{
			ReturnStatusBuffer[2]=NvXing.pressure;
			ReturnStatusBuffer[3]=NvXing.PGLevel;
			ReturnStatusBuffer[4]=0;
			ReturnStatusBuffer[5]=Water.WashTimer;
		}
		if(Status.enfant_f)
		{
			ReturnStatusBuffer[2]=1;			//-----最小水压
			ReturnStatusBuffer[3]=5;			//-----最大位移
			ReturnStatusBuffer[4]=0;			//-----
			ReturnStatusBuffer[5]=Water.WashTimer;    //-----设置总时间
		}
		
		ReturnStatusBuffer[6]=Status.ShuiYaAnMo_f;
		ReturnStatusBuffer[7]=Status.reciprocate_f;
		ReturnStatusBuffer[8]=Status.LengReAnMo_f;
		ReturnStatusBuffer[9]=Drying.DangWei;
		ReturnStatusBuffer[10]=0;
		ReturnStatusBuffer[11]=Drying.WorkingTimer;
		//-------------------
		ReturnStatusBuffer[12]=0;
		if(Status.dengkong_f)
		{
			ReturnStatusBuffer[12]|=0x02;
		}
		else
		{
			ReturnStatusBuffer[12]&=~0x02;
		}
		if(LiquidDeal.Enable_f)
		{
			ReturnStatusBuffer[12]|=0x04;
		}
		else
		{
			ReturnStatusBuffer[12]&=~0x04;
		}
		if(Status.jieneng_f)
		{
			ReturnStatusBuffer[12]|=0x08;
		}
		else
		{
			ReturnStatusBuffer[12]&=~0x08;
		}
		//------------------
		ReturnStatusBuffer[13]=0;
		//ReturnStatusBuffer[14]=Seat.DangWei;

		if(Seat.DangWei==1)
		{
			ReturnStatusBuffer[14]=32;
		}
		else if(Seat.DangWei==2)
		{
			ReturnStatusBuffer[14]=34;
		}
		else if(Seat.DangWei==3)
		{
			ReturnStatusBuffer[14]=36;
		}
		else if(Seat.DangWei==4)
		{
			ReturnStatusBuffer[14]=38;
		}
		else if(Seat.DangWei==5)
		{
			ReturnStatusBuffer[14]=40;
		}
		else
		{
			ReturnStatusBuffer[14]=0;
		}
	
		ReturnStatusBuffer[15]=Status.penkou_f;

		if(Status.chongshui_f||Status.chongshuiban_f)
		{
			ReturnStatusBuffer[16]=1;
		}
		else
		{
			ReturnStatusBuffer[16]=0;
		}
		//--------------------------
		if(Status.power_f)
		{
			ReturnStatusBuffer[17]=0x01;	
		}
		else
		{
			ReturnStatusBuffer[17]=0x00;
		}
		if(Status.seat_f)
		{
			ReturnStatusBuffer[17]|=0x02;	
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x02;
		}	
		if(Status.tunbu_f)
		{
			ReturnStatusBuffer[17]|=0x04;	
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x04;			
		}	
		if(Status.nvxing_f)
		{
			ReturnStatusBuffer[17]|=0x08;	
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x08;
		}	
		if(Status.dring_f)
		{
			ReturnStatusBuffer[17]|=0x10;	
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x10;
		}	
		if(LiquidDeal.Level_f)
		{
			ReturnStatusBuffer[17]|=0x20;	
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x20;
		}	

		if(work.LianXu_f)
		{
			ReturnStatusBuffer[17]|=0x40;
		}
		else
		{
			ReturnStatusBuffer[17]&=~0x40;
		}

		//---------------
		ReturnStatusBuffer[18]=work.time;
		ReturnStatusBuffer[19]=0x00;
		ReturnStatusBuffer[20]=Error.value;


		
		
}
//-------------------------------------------------
void WifiTiming(void)
{
	WifiRegisterSign.TimerCount++;	
	if(WifiRegisterSign.repeater_timer>0)
	{
		WifiRegisterSign.repeater_timer--;
	}
	if((WifiRegisterSign.TimerCount%10)==0)
	{
		if(WifiRegisterSign.repeater1_timer>0)
		{
			WifiRegisterSign.repeater1_timer--;
		}
	}
	if((WifiRegisterSign.TimerCount%50)==0)
	{
		if(WifiRegisterSign.repeater2_timer>0)
		{
			WifiRegisterSign.repeater2_timer--;
		}
	}
	if(WifiRegisterSign.TimerCount>=100)
	{
		WifiRegisterSign.TimerCount=0;
		if(WifiRegisterSign.wifiSetTime>0)
		{
			WifiRegisterSign.wifiSetTime--;
		}
	}
}






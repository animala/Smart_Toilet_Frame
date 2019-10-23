#include "Function_deal.h"
#include "TM1629.h"

const uint_8 DryingDutyTable[8][6]=
{
   //--30-40-50-60
   //--36-43-nu-50
   {0,40,42,45,47,47},		//<3
   {0,35,37,39,42,42},		//<3~8
   {0,30,32,33,37,37},		//<8~13   ---有问题
   {0,26,30,30,34,34},		//<13~18
   {0,21,22,26,30,32},		//<18~23
   {0,32,41,55,54,27},		//<23~28
   {0,33,40,48,52,22},		//<28~33
   {0,6,6,10,10,16},		//>33		
};




//    功能函数
//**********************/

void Close_all_function(void)
{
	Status.Icon.power_disp = 0;  //关闭电源图标
	Status.Icon.energy_disp = 0;	//关闭节能
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	work.step = 0;
	Status.reciprocate_f = 0;
	if(Status.dring_f == 1)
	{
		Drying.enable_f = 0;
		Drying.HotEndTime = T10S;  
		Drying.step = 0;
	}	
}

void TunBuWashEnable(void)
{
	if(Status.Mode_select == 0)  //如果是第一次选择臀洗功能
	{
		Status.Mode_select = 1;   //1为臀洗
		Status.Pres_select = 3;   //默认水压是3档
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 1)) //如果不是第一次进入这个功能且正在进行另外的功能
	{
		Status.Mode_select = 1;    //进入臀洗
		Status.Pres_select = 3;   //默认水压是3档
		Status.QingXiQieHuan_f = 1;  //清洗切换
	}
	work.enable_f = 1;    		//使能工作
	work.step = 0;   			//步骤清0
	if(Status.dring_f == 1)   //如果使能了烘干
	{
		Status.dring_f = 0;   //关闭烘干
		Drying.step = 0;
	}	
	Status.LengReAnMo_f = 0;
	Status.ShuiYaAnMo_f = 0;
	Status.reciprocate_f = 0;
	Status.fangwu_f = 0;
	Drying.swash_f = 0;
	Water.WashTimer = T1Min;
}


void NvXingWashEnable(void)
{
	if(Status.Mode_select == 0)  //如果是第一次选择妇洗功能
	{
		Status.Mode_select = 2;   //2为妇洗
		Status.Pres_select = 3;   //默认水压是3档
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 2)) //如果不是第一次进入这个功能且正在进行另外的功能
	{
		Status.Mode_select = 2;    //进入妇洗
		Status.Pres_select = 3;   //默认水压是3档
		Status.QingXiQieHuan_f = 1;  //清洗切换
	}
	work.enable_f = 1;    		//使能工作
	work.step = 0;   			//步骤清0
	if(Status.dring_f == 1)   //如果使能了烘干
	{
		Status.dring_f = 0;   //关闭烘干
		Drying.step = 0;
	}	
	Status.LengReAnMo_f = 0;
	Status.ShuiYaAnMo_f = 0;
	Status.reciprocate_f = 0;
	Status.fangwu_f = 0;
	Drying.swash_f = 0;
	Water.WashTimer = T1Min;
}

void DringWorkEnable(void)
{
	if(Status.dring_f == 0)    //如果是在功能清洗状态下
	{
		Status.stop_f = 0;
		Status.Mode_select = 0;  //关闭功能清洗
		Enfant.Dring_f = 0;   	//儿童烘干清0
		Status.QingXiQieHuan_f = 0;  //清洗切换归0
	
		work.step = 0;
		Status.dring_f = 1;
		Drying.enable_f = 1;
		Drying.step = 0;
		Status.ZuoYu_f = 0;
		Status.LengReAnMo_f = 0;
		Status.ShuiYaAnMo_f = 0;
		Status.reciprocate_f = 0;
		Drying.WorkingTimer = T4Min;
	}
	work.LianXu_f = 0;
	work.LianXuBuf = 0;
}


void ChuChouDeal(void)
{	
	if(Status.test_f==0)
	{
		if(Status.power_f == 1)
		{
			if(Status.chuchou_e&&Status.chuchou_f&&(Status.dring_f==0)&&(Status.PowerEnd_f==1))
			{
				ChuChou_set;
			}
			else
			{
				ChuChou_clr;
			}
		}
		else
		{
			ChuChou_clr;
		}	
	}
}


//---------------------------冲水板冲水处理
void ChongShuiBanDeal	(void)
{
	if(Status.chongshuiban_f)	
	{		
		WaterWashBoardSet;
		chongshui.delay1++;
		if(chongshui.delay1 > 200)		//----200*10ms=2000ms
		{
			chongshui.delay1 = 0;
			Status.chongshuiban_f = 0;
		}
	}
	else
	{
		WaterWashBoardClr;
	}
}

//***************************************/
//	void Wash_deal(uint_8 select)
//	
//	喷杆调节参数
//
//***************************************/
void Wash_deal(uint_8 select)
{

	if(PenGan.PGmove_f == 0 && Status.Mode_select != 0 && Status.reciprocate_f == 0)
	{
		PenGan.PGmove_f = 1;	//喷杆调节使能
		Status.PG_gear = Status.Pres_select;  //先把功能选择档位赋值给档位，再对档位进行操作	
		
		if((select & 0x20) == 0x20)  //位置调节 +
		{
			Status.PG_gear++;		//喷杆位置+
		}
		if((select & 0x10) == 0x10)  //位置调节 -
		{
			Status.PG_gear--;		//喷杆位置-
		}
	}
	
}

//***************************************/
//void Water_change(uint_8 select)
//	
//	水压调节参数
//
//***************************************/
void Water_change(uint_8 select)  
{
	if(Water.pressure_f == 0 && Status.Mode_select != 0)	
	{
		Water.pressure_f = 1;
		Status.Water_gear = select;		//直接把水压值赋值给执行变量
	}
}


//***************************************/
//void Gear_deal(uint_8 select)
//	档位参数选择函数
//
//***************************************/
uint_8 Gear_deal(uint_8 select)
{
	uint_8 temp = 0;
	temp = select & 0x0f;
}


//********************************************/
//
//入座检测~
//
//******************************************/
void Zuo_Check(void)
{
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
			if(Status.seat_f == 1)			//-----
			{
				Status.seat_f = 0;	
				LiquidDeal.WaterWash_f = 0;
				LiquidDeal.SetOff1Min = T1Min;
				//CO2_set_seat;
				Seat.first_f = 0;
				Status.stop_f = 1;
				Status.Mode_select = 0;
				work.LianXu_f = 0;
				work.LianXuBuf = 0;
				work.step = 0;			
				if(Status.dring_f == 1)   //正在烘干的情况下离座
				{
					Status.dring_f = 0;
					Drying.enable_f = 0;
					Drying.step = 0;
					Drying.HotEndTime = T10S;
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
}



//***********************************
//	FanTempDeal
//**********************************/
void FanSetDeal(void)			///---------风温设定温度处理
{
	if(Drying.enable_f == 1)    //烘干使能
	{
		if((Status.dring_f == 1)&&(Status.power_f == 1))  //上电完毕，烘干状态置1
		{
			if(Status.PG_zero_f == 1)   //喷杆收缩到位
			{
				Status.Dry_zero_f=0;
				
				switch(Drying.step)
				{
					case 0:
						HotFan_set;	     //先开风扇，再加热			
						Drying.DutyPwm = 0;
						Drying.time = 0;
						if(Status.auto_f& (Drying.swash_f==0))  //如果使能了自动冲水功能
						{
							if(Status.chongshui_e == 1)
							{
								Drying.swash_f=1;
								Status.chongshui_f=1;
								Status.chongshuiban_f=1;
								Status.chongshui_e=0;
							}
						}
						
						Drying.step++;
						break;
					case 1:
						Drying.time++;
						if(Drying.time>10)
						{
							Drying.time=0;
							Drying.step++;
						}
						break;
					case 	2:
						work.time = Drying.WorkingTimer;
						work.Start_f = 1;
						//--------------默认开始加热温度在环境温度25度下开始加热
						Drying.DutyPwm=DryingDutyTable[Entironment.Index][Drying.DangWei];
							
						Drying.step++;
						break;
					case 	3:
						if(work.time==0)
						{
							work.Start_f=0;
							Status.dring_f=0;
							Drying.DutyPwm=0;
							FanHeat_clr;
							Drying.step=0;
						}					
						break;
					default:
						Status.dring_f=0;
						HotFan_clr;
						FanHeat_clr;
						Drying.step=0;
						break;
				}
				//-----------------等待100ms开始加热				

				//-------------------1S	
				if(Status.Mode_select == 3)   //这里单独对某个模式进行进行PWM控制操作，这里先设定为儿童模式
				{
					Drying.DutyPwm = 35;			//----45
				}
				else
				{
					Drying.DutyPwm = DryingDutyTable[Entironment.Index][Status.Icon.wind_gear];   //档位处理
					Display_Temp(6, Status.Icon.wind_gear, 1);      //显示档位
				}
			}	
		}
	}
	else   //结束烘干步骤
	{
		Drying.DutyPwm = 0;
		FanHeat_clr;         //先关闭加热，再关风扇		 
		if(Drying.HotEndTime == 0)
		{
			HotFan_clr;
			Status.dring_f = 0;  //烘干标志位清0
		}
		else
		{
			HotFan_set;	
		}
	}
}
//*******************************************
//
//		烘干PWM执行函数
//
//******************************************
void DringPwmDeal(void)
{
	if(Status.PcbTest_f == 0)
	{
		Drying.DutyCount++;
		if(Drying.DutyCount > DryingDutySzie)
		{
			Drying.DutyCount = 0;
		}
		if(Drying.DutyCount < Drying.DutyPwm)
		{
			FanHeat_set;
		}
		else
		{
			FanHeat_clr;
		}
	}
}







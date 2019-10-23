#include "Function_deal.h"

//    功能函数
/**********************/

void Close_all_function(void)
{
	Status.Icon.power_disp = 0;  //关闭电源图标
	Status.Icon.energy_disp = 0;	//关闭节能
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	work.step = 0;
	Status.reciprocate_f = 0;
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
















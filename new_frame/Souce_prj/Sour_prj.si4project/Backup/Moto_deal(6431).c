#include "Moto_deal.h"


Motor_uion MotorA;
Motor_uion MotorB;
Motor_uion *motor_select[2];

PenGan_uion PenGan;
penkou_uion penkou;

#define arrySize(x)  (sizeof(x) / sizeof(x[0]))
	
//----------------喷杆电机 P5.4.3.2.1 ABCD
uint_8 StepMotor_B[8] = {0x10,0x18,0x08,0x0c,0x04,0x06,0x02,0x12};

//----------------烘干电机接口 p6.5,4,3,2
uint_8 StepMotor_C[8] = {0x20,0x30,0x10,0x18,0x08,0x0c,0x04,0x24};

//-------水路分配电机   P8.7.6.4.3 ABCD
uint_8 StepMotor_A[8] = {0x80,0xc0,0x40,0x50,0x10,0x18,0x08,0x88};


const uint_16 PengGang[2][6]={
//{1170,1296,1422,1548,1674,1800},							//臀部清洗喷杆位置 0归位 1,2,3,4,5档
{1200,1494,1557,1622,1686,1750},
{1200,1494,1557,1622,1686,1750},						 	//女性清洗喷杆位置 0归位 1,2,3,4,5档
};
//水压设定范围
const uint_16 WaterPressure[2][6]={
{2000,2050,2050,2100,2280,2360},					//臀部清洗喷杆位置 0归位 1,2,3,4,5档
{800,750,750,600,410,0},						 	//女性清洗喷杆位置 0归位 1,2,3,4,5档
};


//------------------------水路分配器
#define 	CskMin			0
#define		CskZJ			4
#define		CskAddLiquid	9
#define 	CskMax			10

const uint_16 CSK_table[]=
{
	0,		//-------0	最小位置
	225,	//-------1	女性3
	450,	//-------2	女性2
	765,	//-------3	女性1
	1339,	//-------4	自洁口
	2025,	//-------5	男用1
	2340,	//-------6	男用2
	2565,	//-------7	男用3
	2790,	//-------8	男用MAX
	3364,	//-------9	加液口
	3544,	//-------10	最大行程
};


#define 	SSMin		0
#define 	SSRestIndex	1
#define 	SSMax		2

const uint_16 SS_table[]=
{
	100,				// 0
	150,				//100,				// 堵转
	1900,				//3332,			// 2					//--复位	
};




//----------------------------
//--端口设置结构体初始化
//--Motor_sum 电机总数
//----------------------------
Port_set p_set[Motor_sum]  =  {	
	{
	    StepMotor_A_IO,  		//初始化的IO口	分水电机
		StepMotorAStop,			//初始化输出0
		StepMotor_A,			//初始化电机的相位
		CSK_table,				//对应电机的位置选择
		WaterPressure			//水压选择
	},
	{
	    StepMotor_B_IO, 		//初始化的IO口	喷杆电机			
		StepMotorBStop,
		StepMotor_B,
		SS_table,
		PengGang				//喷杆位置
	}
};


//--------------步进电机控制指针函数原型------------
//
//-输入： 步进电机控制结构体 Motor_uion，步进电机选择 motor
//
//-输出： 无
//---------------------------------------------------
void Motor_Control(Motor_uion *p,uint_8 motor)
{
	
	if(p->enable_f == 1)						//电机运行标志
	{
		if(p->Index != p->SumCountSet)			 //如果步进电机的当前位置不等于目标设定的位置
		{			
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;					//电机IO口初始化0
			GPIO_OUT(p->pInit->port) |=  p->pInit->phase[p->XiangWei];		//再把电机的相位赋值给IO口			
			if(p->cw_f  ==  1)			//如果正转标志位置1						
			{
				if(p->XiangWei < 7)			//步进电机相位++				
				p->XiangWei++;
				else						//超过相位范围则重新赋值
				p->XiangWei = 0;
				p->Index++;
			}
			else						//步进电机反转
			{
				if(p->XiangWei > 0)			//相位自减
				{
					p->XiangWei--;
				}
				else						//溢出重新赋值
				{
					p->XiangWei = 7;
				}
				if(p->Index > 0)
				{
					p->Index--;
				}
			}
		}
		else								//步进电机到位
		{
			p->enable_f = 0;				//电机失能
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;   //电机IO输出停止
			p->end_f  =  1;				//到位
		}
	}
	else
	{
		if(Status.PcbTest_f == 0)	//如果PCB自检完成后
		{
			GPIO_OUT(p->pInit->port) &=  p->pInit->stop;	//IO输出0								
			p->XiangWei  =  0; //相位清0
		}
	}
}


/********************************/
//	根据选择电机标号获取数组最大的数值
// 0 分水电机   1 喷杆电机
/********************************/
uint_16 Slt_Table(uint_8 num)
{
	uint_16 temp;
	if(num == 0)
	{
		temp = arrySize(CSK_table) - 1;
	}
	else
	{
		temp = arrySize(SS_table) - 1; 
	}
	return temp;
}

/********************************************/
//		步进电机上电复位
//Motor_uion:传入步进电机结构体 
//count：步进电机的个数，本项目只有分水电机和喷杆电机
//**t:  取地址的地址->*(Motor[0])->Motor[0] = MortorB => *MortorB  got it!
//分水电机复位的步骤是先复位，再转到自洁口
//喷杆电机复位则是直接缩到起始点
/*********************************************/
void Power_up_reset(Motor_uion **t)
{
	//循环，初始化电机	
	uint_8 i = 0;
	Motor_uion *p = *t;	  //这里定义一个可变电机结构体，用来存放传进来的电机结构体
	//程序放在10ms中执行
	if(Status.PowerEnd_f == 0)   //上电标志位
	{
		if(timer.t_1s_f == 1)    //10秒计时
		{
			timer.init++;	
			timer.t_1s_f = 0;
		}		
		if(timer.init > 10)
		{
			timer.init = 10;   
		}	
		for (i = 0; i < 2; i++)
		{		
			switch(p->State)
			{
				case 0:							
				p->pInit = &p_set[i];		//初始化电机接口结构体的端口、相位等														
				p->cw_f = 0;							//统一反转  （根据硬件搭配不同，有些电机是复位是反转  这里需要注意）
				p->Index = p->pInit->position[Slt_Table(i)]; 	//当前位置设置为最大
				p->SumCountSet = p->pInit->position[0];		//目标位置设置最小 实现伸缩回位置
				p->State++;
				p->end_f = 0;			
				p->enable_f = 1;		//使能标志位置1													
				break;	
				case 1:
				if(p->end_f == 1 )	//转到目标位置之后														
				{
					if(i == 0)	//对分水电机继续操作
					{
						p->enable_f = 0;
						p->end_f = 0;										
						p->DelayTime = 0;
						p->State++;				
					}
					else		//喷杆电机完成复位
					{
						p->end_f = 0;										
						p->enable_f = 0;
						p->Compelet_flag = 0x01;
						p->select = 1;             //步进电机选择1为喷杆电机
					}
				}
				break;
				case 2:	//这里是让分水电机停止运行100ms
					p->DelayTime++;
					if(p->DelayTime >= 10)
					{
						p->DelayTime = 0;
						p->State++;	
					}
				break;
				case 3:
					//这里给定需要转到的位置				
					p->cw_f = 1;							//正转				
					p->SumCountSet = p->pInit->position[CskZJ]; 	//目标位置设置为自洁口
					p->enable_f = 1;					//使能，开始转动
					p->State++;	
				break;
				case 4:
					if(p->end_f == 1)	//转到目标位置之后														
					{	
						p->end_f = 0;	
						p->enable_f = 0;
						p->Compelet_flag = 0x10;
						p->select = 0;    //步进电机选择位0 为分水电机
					}
				break;
			}
			p++;   //电机结构体+1  //两次循环完成后 P是等于2；
		}		
		if(((p-1)->Compelet_flag || (p-2)->Compelet_flag == 0x11) && (timer.init==10))   //两个电机复位完成以及到达10秒
		{
			Status.PowerEnd_f = 1;				//上电复位完成标志位置1
			(p-1)->Compelet_flag = 0;			//各电机完成标志位置1
			(p-2)->Compelet_flag = 0;
			Status.PG_zero_f=1;		
			Status.Dry_zero_f=1;		
			buz_set(1,30,30);				//叮一下
		}
	}
}

/******************************************/
//	根据选择的模式确定水压
//	模式有 儿童模式、臀部、女性
//  可按需要添加相应功能的水压
/*****************************************/

uint_16 Func_WarterPressure(uint_8 select)
{
	

}


uint_8 k = 0;

/***********************************************/
//步进电机设定位置距离，根据功能不同来设定
//Motor_uion *t 步进电机结构体，distance 目标位置
//
/***********************************************/
void Motor_set_position(Motor_uion *t, uint_8 distance)
{

	k = p_set[0].f_position[1][1];

	/*if(t->Index == t->SumCountSet)
	{
		t->enable_f = 0;
		t->end_f = 1;
	}
	else
	{
		t->enable_f = 0;
		t->end_f = 1;
	}*/


}






/************************
  步进电机驱动工作函数	
***********************/
void	Motor_A_B_C_program(void)
{
//	if(work.enable_f&Status.Dry_zero_f)
/*	if(work.enable_f)	
	{
		if(LiquidDeal.Enable_f == 0)		
		{
			if(Status.tunbu_f||Status.nvxing_f||Status.enfant_f)
			{
			//-------------------功能处理
				if (Status.auto_f && (Status.test_f == 0))
				{
					Status.chongshui_e = 1;
				}	
				Status.PG_zero_f = 0;
				DealCSKandSS();
			}
			else
			{
				DealCSKandSS_end();
			}
		}
	}
	else
	{
		if((Status.tunbu_f == 0)&&(Status.nvxing_f == 0)&&(Status.dring_f == 0))
		Status.stop_f = 0;
	}	*/
}






void DringPwmDeal(void)
{
	if(Status.PcbTest_f == 0)
	{
		Drying.DutyCount++;
		if(Drying.DutyCount>DryingDutySzie)
		{
			Drying.DutyCount = 0;
		}
		if(Drying.DutyCount<Drying.DutyPwm)
		{
			FanHeat_set;
		}
		else
		{
			FanHeat_clr;
		}
	}
}












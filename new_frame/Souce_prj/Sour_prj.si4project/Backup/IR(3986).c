#include "IR.h"

#define	IR_DataSize		6
#define	User_DataSize	5

unsigned char	IR_databuffer[IR_DataSize];
unsigned char	User_databuffer[User_DataSize];



/********************************************************/
//
//  红外接收代码，放在定时器中断中
// 一帧分为 引导码 + 起始码 + 功能数据 + 校验和  共6字节（不包括引导码）
// 0 ： 由 640us低电平 + 480us 高电平组成     1 ： 640us低电平 + 1440us高电平组成 
//--------------------------
void IR_receive(void)
{
	switch(IR.step)
	{
		case 0:
			//----接收到低电平信号开始计时
			if(IRCheck == 0)
			{
				IR.start_f = 1;
				IR.time_h = 0;
				IR.time_l = 0;	
				IR.step++;
			}
			break;
		case 1:	
			if(IRCheck == 0)
			{
				IR.time_l++;	
				if(IR.time_l > 25)		//---25 * 200= 5000us = 5ms 如果低电平的时间大于5ms，证明不是引导码
				{
					IR.step = 0;		//--IR_cuowu();
				}				
			}
			else  //此时到了高电平，就要去判断前面低电平的时间长短是不是引导码的时间 
			{
				if(IR.time_l < 15)		//如果低电平时间不够4ms 证明不是引导码
				{
					IR.step = 0;		//--IR_cuowu();
				}		
				else	//如果达到了，证明是引导码的低电平
				{
					IR.step++;
				}
			}
			break;
		case 2:
			if(IRCheck == 0)  //如果经过高电平后到下一个低电平
			{
				if(IR.time_h < 35)		//判断刚才的高电平是否满足引导码的高电平时间  小于 8ms证明不是
				{
					IR.step = 0;		//--IR_cuowu();
				}
				else //如果引导码正确，开始进入字节接收
				{
					IR.step++;	
					IR.first_f = 0;
					IR.Bit_Count = 0;
					IR.Byte_Count = 0;
					IR.already_f = 0;
					IR.time_l = 1;
					IR.time_h = 0;		
				}
			}
			else	//如果还是继续持续刚才的高电平时间
			{
				IR.time_h++;		//继续计时
				if(IR.time_h > 45)			//--如果计时大于 9ms 证明不是引导码
				{
					IR.step = 0;			//---IR_cuowu();
				}
			}
			break;
		case 3:
			//----------------------bit0
			if(IRCheck == 0)  //此时还在低电平的时间内
			{
				IR.time_l++;   //继续计时	
			}
			else		//如果到了第一个字节的高电平，高电平时间从1开始，方便计算
			{
				IR.time_h = 1;
				IR.step++;
			}
			/*****以上就是bit0 ： 0x11的接收 因为引导码正确，直接进入字节接收******/
			break;
			//--------------------在此判断第一个BIT
		case 4:
			if(IRCheck == 0)  //这里到了BIT1的接收，并判断第一个字节
			{
				IR.time_l++;    //一个字节是由640us低电平+ （480us / 1440us）的高电平组成
				if(IR.time_l > 4)					//大于800us就丢弃
				{
					IR.step = 0;				//---IR_cuowu();
				}
				//---------------				
				if(IR.first_f == 0)
				{
					if(IR.time_h >= 7)			//---200 * 7 = 1400us 大于这个证明 这个字节是1 
					{
						//	IR.Recv_Data_Buf>>=1;
						//	IR.Recv_Data_Buf&=0x7f;
						IR.Recv_Data_Buf <<= 1;			
						IR.Recv_Data_Buf |= 0x01;	   //记录字节
						IR.first_f = 1;
						IR.Bit_Count++;
					}

					else if((IR.time_h >= 2)&&(IR.time_h <= 3))		//----在 400us 和 600us之间就是 0 的字节
					{
						//	IR.Recv_Data_Buf>>=1;			
						//	IR.Recv_Data_Buf|= 0x80;
						IR.Recv_Data_Buf <<= 1;
						IR.Recv_Data_Buf &= 0xfe;
						IR.first_f = 1;
						IR.Bit_Count++;
					}
					else
					//-------时间都不在这两个范围内证明数据错误  丢弃
					{
						IR.step = 0;			//---IR_cuowu();
					}
				}
				IR.time_h = 0;	//记录字节后 清0 等待下一次接收
				//------------ ------------------
				if(IR.Bit_Count >= 8)  //记录8个位后，即接收到一个字节
				{
					IR.Bit_Count = 0;	
					IR_databuffer[IR.Byte_Count] = IR.Recv_Data_Buf;
					IR.Byte_Count++;
					if(IR.Byte_Count >= 6)	//接收到6个字节后结束
					{
						IR.step++;	
						IR.already_f = 1;						
					}		
				}
					
			}
			else  //判断是否丢帧
			{
				IR.time_h++;
				if(IR.time_h > 8)
				{
					IR.step = 0;			//----IR_cuowu();
				}
				IR.first_f = 0;
				IR.time_l = 0;
			}
			break;
		case 5:
			//--------------判断结束码
			IR.step = 0;
			break;
		default:
			break;
	}
}

/***************************************/
//
//	解码并进行功能处理
//
//***************************************
void IR_Opration(void)
{
	uint_8	i,j;
	uint_8	temp1,temp2;
	uint_8	checksum;
	uint_8  Re_check;
	uint_8  Check_flag = 0;  //判断校验和
	uint_8	Comp_databuffer[User_DataSize];
	uint_8	TempBuf;	
	uint_8	DringFlag;
	if(IR.already_f)
	{	
	//--------判断接收到的数据是否正常
	//--------转换数据读取方式
	//--------先反序读取数据，
		for(i=0; i<IR_DataSize; i++ )
		{
			temp1 = IR_databuffer[i];  //循环赋值数据的每一个字节给 temp1
			for(j=0; j<8; j++)
			{
				if((temp1 & 0x80) == 0)
				{
					temp2 >>= 1;
					temp2 &= 0x7f;
				}
				else
				{
					temp2 >>= 1;
					temp2 |= 0x80;
				}
				temp1 <<= 1;
			}
			IR_databuffer[i] = temp2;
		}
		checksum = 0;
		for(i=1; i<(IR_DataSize-1); i++) //累加前5个字节
		{
			checksum += IR_databuffer[i];
		}

		
		//数据每次重发两次，这里需要处理，避免重复相应2次，方法是判断两次校验位是否相等			
		if(checksum == IR_databuffer[IR_DataSize-1])  //判断第一帧数据的校验和是否相等
		{
			if(Check_flag == 0)
			{ 
				Re_check = checksum;
				for(i=0; i<(IR_DataSize-1); i++)
				{
					Comp_databuffer[i] = IR_databuffer[i];	//把第一帧数据保存																										//	}
				}
				Check_flag = 1; 
			}
			//以下的初始化只会执行一次
			if(IR.TFDelay == 0)
			{				
				for(i=0; i<(IR_DataSize-1); i++)
				{
					User_databuffer[i] = 0;     //先清0
				}
			}
			else		//第二次间隔150ms判断
			{		
				for(i=0;i<(IR_DataSize-1);i++)
				{
					if(User_databuffer[i] != IR_databuffer[i])
					{
						IR.OK_f = 1;	
					}
				}
				
			}		
			IR.TFDelay = 15;
		}

		if(IR.OK_f == 1)
		{
			IR.OK_f = 0;
			Check_flag = 0;
			if(Re_check == checksum) //如果两次校验相等
			{
				for(i=0;i<(IR_DataSize-1);i++)
				{
					User_databuffer[i] = Comp_databuffer[i+1];
				}
			}
			else
			{
				for(i=0;i<(IR_DataSize-1);i++)
				{
					User_databuffer[i] = IR_databuffer[i+1];
				}
			}
			IR.already_f=0;
			buz_set(1,20,20);				//叮一下
			//------------------------------对RF_DataBuffer[]的内容进行处理
			//------------------------------判断接收数据是否正确
			if(Status.power_f == 1)
			{
				SoftPowerDeal.Delay = T10Min;
				SoftPowerDeal.Softpower_f = 1;
				temp1 = User_databuffer[3];
				if((temp1&0x50)==0x50)
				{	
					xiaobianled_set;	
				}
				else
				{
					xiaobianled_clr;
				}
				/*temp1 = User_databuffer[0] & 0x0f;
				if(temp1 == 0x01)
				{
					xiaobianled_set;
				}
				if(temp1 == 0x00)
				{
					xiaobianled_clr;
				}*/
				
			}
		}
		
	}

}




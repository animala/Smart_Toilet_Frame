#include "Instant_heat.h"

//---定义一个水温温度设定表格
const uint_8 Water_temp_table[5] = {
		32,	
		34,
		36,
		38,
		40
};
/*********************************
UART0信息定义
**************************************/ 	
uchar	rx0_buf[uart0_size];		//----------UART0接收缓存器
uchar	rx0_data[uart0_size];		//----------UART0接收数据
uchar	rx0_indx;					//--------- UART0接收计数
uchar	tx0_buf[uart0_size];		//--------	UART0发送缓存器
uchar	tx0_data[uart0_size];		//--------	UART0发送数据
uchar	tx0_indx;					//--------- UART0发送计数

uchar	uart_flag_f;				//---------bit0=1	uart0接收完成
									//-------bit1=1   uart0发送完成 
									//-------bit2=1   uart1接收完成
									//-------bit3=1	uart1发送完成
									//-------bit4=1	uart1接收到新数据									
uchar	uart_data_f;				//-------bit0=1	uart1接收数据正确
									//------ bit1=1 uart1接受数据正确

//***********************************
//            即热模块处理
//**********************************

void Urat0_Init(void)
{
	//计数器2开始计数，选择时钟源tm2psc
	TM2MD = 0x09;
	CK2MD = 0x00;			// Select the clock source to fpll/4
//	TM2OC=103;				////波特率((16*100000/4)/(103+1))/(2*8)=2400
	TM2OC = 206;				///波特率((16*100000/4)/(206+1))/(8)=2400	
	SC0SEL = 0x02;			//-------选择定时器2作为定时器输出	
	// bit 7 0 uart输出
	// bit 6-4 000 定时器输出
	// bit 3 0 A系统
	// bit 2-0 010 选择定时器2
	P0ODC = 0x0C;			//------设定P02.P03为开路
	P0PLUD = 0x00;			//------P02.P03无上拉
	P0DIR |= 0x08;			//------P03
	P0DIR &= ~0x04;			//-----P02

	//SC0MD0说明	
		//bit7=1 数据传输边沿，发送上升沿，接收下降沿
		//bit6=0,--
		//bit5=0 -- 		
		//bit4=0 MSB 首位
		//bit3=0 起始条件 无
		//bit2=1  2 - 0 同步方式串行传送位数 8位
		//bit1=1
		//bit0=1
	SC0MD0=0x10;	
	//SC0MD1说明	
		//bit7=0 RX输入引脚选择
		//bit6=0,SBTn引脚功能为端口
		//bit5=1设置为串行输入			
		//bit4=1设置TXD为串行数据输出
		//bit3=1分频
		//bit2=1主时钟
		//bit1=0选择8分频
		//bit0=1全双工通讯
	SC0MD1=0x3d;
	//SC0MD2说明	
		//bit7=1 -
		//bit6=0,7-6 指定帧格式 10 8位数据+1停止位
		//bit5=0 -		
		//bit4=0 指定附加位  0 0 发送时附加0	接收时检查0
		//bit3=1 校验 1 无奇偶校验
		//bit2=0 - 保留
		//bit1=0 0 数据接收
		//bit0=0 0 数据发送 
	SC0MD2=0x88;	//8位数据+1位停止位 无奇偶效验
	//SC0MD3说明	
		//bit7=0 -
		//bit6=0,- 7-6 00选择最后发送数据发送后SB0的输出 固定为 1
		//bit5=0 -
		//bit4=0 -
		//bit3=1 控制预分频器计数 1 允许计数
		//bit2=1 2-0 选择时钟
		//bit1=1  111 定时器输出，通过SC0SEL（2-0）选择定时器
		//bit0=1 
	SC0MD3=0x0f;	//----开始计数--可通过SC0SEL选择时钟 
	SC0TICR=SC0TICR|0X02;		//允许UART发A送中断
	//bit 7-6 设定中断等级
	//bit 5-2	--
	//bit 1  1： 允许中断
	//bit 0  0	 无中断请求	
	SC0RICR=SC0RICR|0X02;		//--允许串口0接收中断
	
	SC0STR=0x40;				//UART0准备接收


}



void Uart1_init(void)		//初始化UART1
{
	TMAMD1 = 0x08;		//计数器A开始计数，选择时钟源fpll=16m
	TMAMD2 = 0x40;		//预分频器开
//	TMAOC=103;			//频率=((16*100000)/(103+1))/(2*8)=9600
	TMAOC = 206;			//频率=((16*100000)/(206+1))/8=9600	
	SC1SEL = 0x0f;		//选择定时器A为时钟源  并选择B系统
			
	P7ODC = P7ODC|0x60;			//设定对应引脚p7.5.6。
	P7PLUD = P7PLUD|0x20;			//------bit5=1
	P7PLUD = P7PLUD&0xbf;			//-----bit6=0
	P7DIR = P7DIR|0x20;			//----bit5=1
	P7DIR = P7DIR&0xbf;			//----bit6=0
//	SC1MD0=0x08;
	SC1MD0 = 0x10;
	//SC1MD1说明	
		//bit7=0 RX输入引脚选择
		//bit6=0,SBTn引脚功能为端口
		//bit5=1设置为串行输入			
		//bit4=1设置TXD为串行数据输出
		//bit3=1分频
		//bit2=1主时钟
		//bit1=0选择8分频
		//bit0=1全双工通讯
	SC1MD1=0x3d;	
	SC1MD2=0x88;	//8位数据+1位停止位 无奇偶效验
	SC1MD3=0x0f;
	SC1TICR=SC1TICR|0X02;		//允许UART1发送中断	
	SC1RICR=SC1RICR|0X02;		//--允许串口1接收中断
	SC1STR=0x40;				//----UART1准备接受	
}

/*----------------------------------------------
函数名称：Uart0_TX_Byte
功能描述：串行口0发送字节
输入参数：buf:发送数据变量
返回参数：无
修改记录：暂未定义
------------------------------------------------*/
void	Uart0_TX_Byte(uchar	buf)
{
	while((SC0STR&0x20)!=0)		//发送缓冲器不为空时等待
	{
		asm("nop");
	}
	TXBUF0 = buf;
} 

/*----------------------------------------------
函数名称：Uart0_TX_Byte
功能描述：串行口1发送字节
输入参数：buf:发送数据变量
返回参数：无
修改记录：暂未定义
------------------------------------------------*/
void	Uart1_TX_Byte(uchar buf)
{
	while((SC1STR&0x20)!=0)		//发送缓冲器不为空时等待
	{
		asm("nop");
	}	
	TXBUF1 = buf;
}

/*----------------------------------------------
函数名称：Uart0_Send_Data
功能描述：串行口0发送数据
输入参数：uart_ch:为UART的通道号
		  *buf:发送数据缓存
		  len:发送数据长度
返回参数：无
修改记录：暂未定义
------------------------------------------------*/
void	Uart0_Send_Data(uchar uart_ch,uchar *buf,uchar len)
{
	uchar i;
	for(i=0;i<len;i++)
	{
		if(uart_ch == UART0_CH)
			Uart0_TX_Byte(*(buf+i));
		else
			Uart1_TX_Byte(*(buf+i));
	}
}



/*----------------------------------------------
函数名称：uart0_send
功能描述：串行口0发送数据
输入参数：无
返回参数：无
修改记录：
------------------------------------------------*/
void	uart0_send(void)
{
	uchar	i;
	for(i=0;i<uart0_size;i++)//加载发送数据
	{
		tx0_buf[i]=tx0_data[i];
	}
	for(i=0;i<uart0_size;i++)
	{
		while((SC0STR&0x20)!=0)		//发送缓冲器不为空时等待
		{
			asm("nop");
		}
		TXBUF0 = tx0_buf[i];
	}		
}

/*----------------------------------------------
函数名称：ReadRespRx0
功能描述：串行口0接收数据解析
输入参数：无
返回参数：无
修改记录：
------------------------------------------------*/
void ReadRespRx0(void)
{		
	uchar i;
    uchar checksum;
    if((uart_flag_f&0x01)==0x01)//UART0数据接收完成
	{
		uart_flag_f&=0xfe;
		for(i=0;i<uart0_size;i++)
			rx0_data[i]=rx0_buf[i];
		//------------------------------判断接收数据是否正确
		if(rx0_data[0]==0xcc)
		{
			checksum=0;
			for(i=1;i<(uart0_size-1);i++)
			{
				checksum+=rx0_data[i];
			}
			if(checksum==rx0_data[uart0_size-1])//校验和判断
				uart_data_f|=0x01;
			else
				uart_data_f&=0xfe;	
		}
		else
		{
			uart_data_f&=0xfe;	
		}
	}	
}

//*********************通讯数据格式***********************/
//  1）主板 到 即热
//	起始码    功能码	 	数据1		数据2		数据3		数据4		数据5		校验和
//	 0x33	 x	  设定水温    	  0		  0		  0		  0		功能~数据5
//  x ： 0x01 开启加热  0x00 关闭加热   设定水温 分辨率1° 在30~41°之间

//   2） 即热 到 主板
//	起始码    	功能码	 	数据1		数据2		数据3		数据4		数据5		校验和
//	 0xCC   0x01  	 x2 	0x0f	水温		水流量		  0		功能~数据5
//	x2：故障码      0 无故障     1 有故障  
//	bit2 ： 传感器开路
//	bit3 :  传感器断路
//  bit4: 	水路故障（流量低）

//********************************
//
//   发送数据包帧格式处理
//
//********************************
void Tx_frame_buff(void)
{
	tx0_data[0]=0x33;   
	tx0_data[1]=0x01;    //开启加热
	tx0_data[3]=0x00; 
	tx0_data[4]=0x00;
	tx0_data[5]=0x00;
	tx0_data[6]=0x00;
	tx0_data[7]=tx0_data[2]+0x01;	//校验码
}


void Water_temp_deal(void)
{
	
	if(Status.power_f == 1)  //
	{
		SpeedinessHeatPowerOn;   //开启即热模块电源
		if((Water.TempDeal_time == 0) && (Water.WaterIn_f == 1))  //如果接收下一帧的间隔时间到并且使能了进水
		{
			
			if(Water.Hot_f == 1)  //使能了加热
			{
				if(Status.Mode_select == 5)  //单独对某个模式设定固定温度，这里先设定为儿童模式
				{
					tx0_data[2] = 36;
				}
				else
				{
					tx0_data[2] = Water_temp_table[Status.Icon.water_temp_gear -1];  //否则水温设定直接按照档位给温度
				}
				if(Status.ZuoYu_f == 1)
				{
					tx0_data[2] = 40;    //坐浴固定为40度
				}
				if(Status.LengReAnMo_f == 1)	//冷热按摩
				{
					if(++Water.delay1 < 500)	   //5秒加热 
					{
						tx0_data[2] = 40;  
					}
					if(++Water.delay1 < 600)	   //1秒不加热 
					{
						tx0_data[2] = 0;  
					}
					else
					{
						Water.delay1 = 0;
					}
				}
			}
			else   //如果没有使能加热
			{
				tx0_data[2] = 0;  
			}
			
			Tx_frame_buff();    //准备发送数据包
			
			if(Status.PG_zero_f)  //如果喷杆收回，进冷水
			{
				tx0_data[2]=0;
				tx0_data[7]=tx0_data[2]+0x01;
			}
			Water.StopHotDelay = 0;     
			Water.JiRe_In_f = 1;
			Water.Hot_f = 1;
		}

		else
		{
			tx0_data[2] = 0;
			Tx_frame_buff();
			if(++Water.StopHotDelay > 2)
			{
				Water.StopHotDelay = 2;
				Water.JiRe_In_f = 0;
			}
			Water.Hot_f = 0;
		}
		uart0_send();   //发送数据包
		Water.TempDeal_time++;
	}

	else
	{
		Water.TempDeal_time++;
		if(Water.TempDeal_time > 50)
		{
			Water.TempDeal_time = 0;
			ReadRespRx0();		//串行接收数据解析
		}

		if(++Water.RX_delay > 300) //如果接收了数据之后超过3S接收到下一帧，则判定为超时通信
		{
			Water.RX_delay = 300;			//这里超过3S应该在接收中断里清0
			Water.Error_flag |= 0x80;    //超时错误标志
		}
		else
		{
			Water.Error_flag &= ~0x80;   //错误标志清0
		}

		if((uart_data_f & 0x01) == 0x01)  //如果接收到一帧数据了
		{
			uart_data_f &= ~0x01;	
			
			if(Water.JiRe_In_f == 1)
			{
				if(rx0_data[2] == 0)  //发过来故障码 没有故障
				{
					Water.Error_flag &= 0xE3;	
					Water.InputTemp = rx0_data[3]; //进水温度
					Water.OutputTemp = rx0_data[4]; //出水温度
				} 
				if((rx0_data[2] && 0x10) == 0x10)  //水路故障，流量低
				{
					Water.Error_flag |= 0x04;	
				}
				else
				{
					Water.Error_flag &= ~0x04;
				}
				
				if((rx0_data[2] && 0x04) == 0x04)  //短路故障
				{
					Water.Error_flag |= 0x02;	
				}
				else
				{
					Water.Error_flag &= ~0x02;
				}

				if((rx0_data[2] && 0x08) == 0x08)  //开路故障
				{
					Water.Error_flag |= 0x01;	
				}
				else
				{
					Water.Error_flag &= ~0x01;
				}				
			}
			else
			{
				if((rx0_data[2]&0x0f) == 0x00)//通讯正常
				{
					Error.value&=0xfffe;
					Water.InputTemp=rx0_data[3];
					Water.OutputTemp=rx0_data[4];		
				}
				else//通信命令错误
				{
					Water.Error_flag |= 0x40;	
				}
			}
		}
	}
}








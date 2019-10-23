#include "Cover_Circle.h"

/*******************************************************
/
/               翻圈翻盖控制  
/ 通过IO口模拟红外协议进行通信，避免串口不够用的情�?
/
*******************************************************/



unsigned char	Cover_databuffer[FG_DataSize];
unsigned char	Cover_user_buff [User_FG_DataSize];
unsigned char   Send_Data_buff[SendDataBuffSize];





//------------接收代码

void Error_data()
{

//	FGIR.time_h = 0;
	FGIR.time_l = 0;
	FGIR.step = 0;
}


void Cover_receive(void)
{

	switch (FGIR.step)
	{
		case 0:
		//---接收到信号开始计�?
		if(InceptDataPin == 0)
		{
			FGIR.step++;
		}
		
		break;
		case 1:
			if (InceptDataPin == 0)
			{
				FGIR.time_l ++;
				if (FGIR.time_l > 25)      // ----25*0.2ms = 5.0ms
				{
					Error_data();
				}
			}
			else
			{
				if (FGIR.time_l < 15) //  -----3ms
				{
					Error_data();
				}
				else
				{
					FGIR.step++;
					FGIR.first_f = 0;
					FGIR.Bit_Count = 0;
					FGIR.Byte_Count = 0;
					FGIR.already_f = 0;
					FGIR.time_h = 1;
					FGIR.time_l = 0;
				}
			}
		break;
		case 2:
			if (InceptDataPin == 0)
			{
				FGIR.time_l = 1;
				FGIR.step++;
			}
			else
			{
				FGIR.time_h ++;
				if (FGIR.time_h > 8)   //---1.6ms
				{
					Error_data();
				}
			}
		break;
		case 3:
			if (InceptDataPin == 0)
			{
				FGIR.time_l ++;
				FGIR.first_f = 1;
				if (FGIR.time_l > 15)
				{
					Error_data();
				}
				FGIR.time_h = 0;
			}
			else
			{
				FGIR.time_h++;
				if (FGIR.first_f == 1)
				{
					if((FGIR.time_l > 2) && (FGIR.time_l <= 7))     //  0.4 ~1.4
					{   //------0
						FGIR.Recv_Data_Buf <<= 1;
						FGIR.Recv_Data_Buf &= 0xfe;
						FGIR.first_f = 0;
						FGIR.Bit_Count++;
					}
					else if((FGIR.time_l > 8) && (FGIR.time_l <= 15))  //  1.6ms ~3.0ms
					{ //------1
						FGIR.Recv_Data_Buf <<= 1;
						FGIR.Recv_Data_Buf |= 0x01;
						FGIR.first_f = 0;
						FGIR.Bit_Count++;	
					}
					else
					{
						Error_data();
					}
					
					FGIR.time_l = 0;

					if(FGIR.Bit_Count >= 8)
					{
						FGIR.Bit_Count = 0;
						Cover_databuffer[FGIR.Byte_Count] = FGIR.Recv_Data_Buf;
						FGIR.Byte_Count++;
						if(FGIR.Byte_Count >= FG_DataSize)
						{
							FGIR.step++;
							FGIR.already_f = 1;
						}
					}
				}

				if (FGIR.time_h > 15)
				{
					Error_data();
				}				
			}
		break;
		case 4:
			//----end
			FGIR.step = 0;
		break;
		default: break;
			
		}
}

//--------------处理代码

void Cover_Opreation(void)
{
	uint_8 i;
	uint_8 check_cum;

	if (FGIR.already_f == 1)
	{
		// --------判断接受到的数据是否正确
		//---------根据协议转换数据
		//---------反序读取数据才是我们要用�?
		check_cum = 0;
		for (i = 0; i < (FG_DataSize -1); i ++)
		{
			check_cum += Cover_databuffer[i];
		}
		if (check_cum == Cover_databuffer[FG_DataSize -1])    //----判断校验�?
		{
			if ((Cover_databuffer[0] == 0xAA) && (Cover_databuffer[1] == 0x01))  //----判断头码和命令字
			{
				FGIR.OK_f = 1;
				//pcbtest.flag = 0;
			}
			if ((Cover_databuffer[0] == 0xAA) && (Cover_databuffer[1] == 0x02))  //----判断头码和命令字
			{
				SendData.SaveData_f = 0;
			}
			if(Status.PcbTest_f == 1)
			{
				if ((Cover_databuffer[0] == 0x55) && (Cover_databuffer[1] == 0x01))  //----判断头码和命令字
				{
					FGIR.JpioTest = 1;
				}
			}
		}

		if (FGIR.OK_f == 1)
		{
			FGIR.OK_f = 0;
			//收到应答消除
			if(CoverSeat.SpaceTime == 0)
			{
				CoverSeat.SeatDirStatus = 0;
				CoverSeat.CoverDirStatus = 0;
			}
			FGIR.already_f = 0;
			//-------自动上翻，包括圈和盖�?
			CoverSeat.SeatOpen_f =  Cover_databuffer[2];
			CoverSeat.CoverOpen_f = Cover_databuffer[3];
		}
		else
		{
			FGIR.already_f = 0;
		}
	}
}

//--------------------发送处�?
//--------200us scan

void Cover_SendData(void)
{
	if (SendData.Start_f == 1)
	{
		switch (SendData.Step)
		{
			case 0:
				SendData.Count++;
				SendData_Low;     //发送的引脚置低
				if (SendData.Count >= 20)
				{
					SendData.Count = 0;
					SendData_Hight;
					SendData.Count = 0;
					SendData.Bit_Count = 0;
					SendData.Byte_Count = 0;
					SendData.Step++;											
				}
			break;
			case 1:
				SendData.Data_Buf = Send_Data_buff[SendData.Byte_Count];
				SendData.Step++;
			break;
			case 2:
				SendData_Hight;
				SendData.Count++;
				if(SendData.Count >= 5)   // 5*200 = 1ms
				{
					SendData.Step = 3;
				}
			break;
			case 3:
				if((SendData.Data_Buf&0x80) == 0x80)
				{
					//------1
					SendData.Count = 0;
					SendData_Low;
					SendData.Data_Buf <<= 1;
					SendData.Step = 4;
				}
				else
				{
					//------0
					SendData.Count = 0;
					SendData_Low;
					SendData.Data_Buf <<= 1;
					SendData.Step = 5;
				}
			break;
			case 4:
				SendData.Count++;
				SendData_Low;
				if(SendData.Count >= 10)  // 2ms
				{
					SendData.Step = 6;
				}
			break;
			case 5:
				SendData.Count++;
				SendData_Low;
				if(SendData.Count >= 5)  // 1ms
				{
					SendData.Step = 6;
				}
			break;
			case 6:
				SendData.Bit_Count ++;
				SendData.Count = 0;
				if(SendData.Bit_Count >= 8)
				{
					SendData.Byte_Count++;
					if(SendData.Byte_Count >= FG_DataSize)
					{
						SendData.Step = 7;
					}
					else
					{
						SendData.Data_Buf = Send_Data_buff[SendData.Byte_Count];
						SendData.Bit_Count = 0;
						SendData.Step = 2;
					}
				}
				else
				{
					SendData.Step = 2;
				}

			break;
			case 7:
				SendData_Hight;  			//释放总线
				SendData.Enable = 0;
				SendData.Step = 0;
				SendData.Start_f = 0;
			break;
			default:
				break;
		}
	}
}


// ------翻盖信号处理

void Cover_send_datadeal(void)
{
	if(SendData.TF == 0)
	{
		Send_Data_buff[0] = 0x55;
		Send_Data_buff[1] = 0x01;
		Send_Data_buff[2] = CoverSeat.SeatDirStatus;
		Send_Data_buff[3] = CoverSeat.CoverDirStatus;
		Send_Data_buff[4] = Send_Data_buff[0] + Send_Data_buff[1] + Send_Data_buff[2] +Send_Data_buff[3];
		SendData.TF = Timer200MS;
		SendData.Start_f = 1;
	}
	if(CoverSeat.delay == 0)
	{
		if(CoverSeat.enable_f == 1)    //人离坐5分钟计时后 关盖
		{
			CoverSeat.CoverDirStatus = 0x02;
			CoverSeat.enable_f = 0;
		}

	} 
}












































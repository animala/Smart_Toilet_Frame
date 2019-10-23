

#include "R_main.h"

/**********************************
���θ�ʽ:
ͷ4MS�͵�ƿ��
����5λ���ݣ�
BIT0:	�ߵ�ƿ1MS �͵�ƿ1MS
BIT1:	�ߵ�ƿ1MS �͵�ƿ2MS
���ͼ��ʱ��>100MS
**********************************/

#define	IR_DataSize		5
#define	User_DataSize	5
#define	SendDataSize	5

uint_8	IR_databuffer[IR_DataSize];
uint_8	User_databuffer[User_DataSize];
uint_8	SendDataBuffer[SendDataSize];


//-----------------------������ܴ���
//-------------------�����Ǻ�����ܳ���
void	IR_cuowu(void)
{
	IR.time_h=0;
	IR.time_l=0;			
	IR.step=0;
}
//--------------------------
void IR_receive(void)
{
	//	unsigned char	i;
	//	unsigned char	checksum;
	switch(IR.step)
	{
		case 0:
			//------���յ��źſ�ʼ��ʱ
			if(InceptDataPin==0)
			{
				IR.step++;
			}
			else
			{
				IR.time_h=0;
				IR.time_l=0;
			}
			break;
		case 1:	
			if(InceptDataPin==0)
			{
				IR.time_l++;	
				if(IR.time_l>50)		//---40*100=4000
				{
					IR_cuowu();
				}
			}
			else
			{
				if(IR.time_l<30)
				{
					IR_cuowu();
				}
				else
				{
					IR.step++;
					IR.first_f=0;
					IR.Bit_Count=0;
					IR.Byte_Count=0;
					IR.already_f=0;
					IR.time_l=0;
					IR.time_h=1;
				}
			}
			break;			
		case 2:
			if(InceptDataPin==0)
			{
				IR.time_l=1;
				IR.step++;
			}
			else
			{
				IR.time_h++;
				if(IR.time_h>15)
				{
					IR_cuowu();
				}
			}
			break;	
			//--------------------�ڴ��жϵ�һ��BIT
		case 3:
			if(InceptDataPin==0)
			{			
				IR.time_l++;
				IR.first_f=1;
				if(IR.time_l>30)
				{
					IR_cuowu();
				}
				IR.time_h=0;
			}
			else
			{
				IR.time_h++;
				if(IR.first_f)
				{
					if((IR.time_l>6)&&(IR.time_l<=18))
					{
						//------0
						IR.Recv_Data_Buf<<=1;
						IR.Recv_Data_Buf&=0xfe;
						IR.first_f=0;
						IR.Bit_Count++;
					}
					else if((IR.time_l>18)&&(IR.time_l<=26))
					{
						//------1
						IR.Recv_Data_Buf<<=1;			
						IR.Recv_Data_Buf|= 0x01;	
						IR.first_f=0;
						IR.Bit_Count++;
					}
					else
					{
						IR_cuowu();
					}
					IR.time_l=0;
				
					if(IR.Bit_Count>=8)
					{
						IR.Bit_Count=0;	
						IR_databuffer[IR.Byte_Count]=IR.Recv_Data_Buf;
						IR.Byte_Count++;
						if(IR.Byte_Count>=IR_DataSize)					
						{
							IR.step++;	
							IR.already_f=1;

							if((IR_databuffer[2]!=0)||(IR_databuffer[3]!=0))
							{
								NOP();
								NOP();

							}



							
						}		
					}
				}
				if(IR.time_h>18)
				{
					IR_cuowu();

				}
			}
			break;
		case 4:
		//-------------------�жϽ�����
			IR.step=0;
			break;
		default:
		break;
	}
}

//----------------------������ճ�����
void	IR_Operation(void)
{
	uint_8	i;
	uint_8	checksum;
	if(IR.already_f)
	{	
	//--------�жϽ��յ��������Ƿ�����
	//--------ת�����ݶ�ȡ��ʽ
	//--------�ȷ����ȡ���ݣ�
	checksum=0;
	for(i=0;i<(IR_DataSize-1);i++)
	{
		checksum+=IR_databuffer[i];
	}
	if(checksum==IR_databuffer[IR_DataSize-1])					//------�ж�Ч����
	{
		if((IR_databuffer[0]==0x55)&&(IR_databuffer[1]==0x01))		//------�ж�ͷ���������
		{
					IR.OK_f=1;
					PcbTest.Flag=0;		
		}
		if((IR_databuffer[0]==0xAA)&&(IR_databuffer[1]==0x01))
		{
			PcbTest.Flag=1;
		}


		
	}
	//-----------------------
	if(IR.OK_f)				
	{	
		IR.OK_f=0;
		SendData.Enable=1;
		for(i=0;i<IR_DataSize;i++)
		{
			User_databuffer[i]=IR_databuffer[i];
		}
		
		IR.already_f=0;
		//------------------------------��RF_DataBuffer[]  �����ݽ��д���
		//------------------------------�жϽ��������Ƿ���ȷ
		if((SeatCircle.OpenDirStatus==0)&&(SeatCover.OpenDirStatus==0))
		{
			if(IR_databuffer[2]!=0)
			{
				Status.RunTime=Timer8S;
				SeatCircle.OpenDirStatus=IR_databuffer[2];
				Status.RamLog++;
				
			}
			if(IR_databuffer[3]!=0)
			{	
				Status.RunTime=Timer8S;
				SeatCover.OpenDirStatus=IR_databuffer[3];				
			}
		}
	}
	else
	{
		IR.already_f=0;
	}
}	
}



void SendSeatData(void)
{
	if(SendData.Enable)
	{
		switch(SendData.Step)
		{
			case 0:
				SendData.Count++;
				SendData_Low;
				if(SendData.Count>=40)
				{					
					SendData.Count=0;
					SendData_Hight;
					SendData.Count=0;
					SendData.Bit_Count=0;
					SendData.Byte_Count=0;
					SendData.Step++;
				}
				break;
			case 1:
				SendData.Data_Buf=SendDataBuffer[SendData.Byte_Count];
				SendData.Step++;
			case 2:
				SendData_Hight;
				SendData.Count++;
				if(SendData.Count>=10)
				{
					SendData.Step=3;
				}
				break;
			case 3:	
				if((SendData.Data_Buf&0x80)==0x80)
				{
					//------=1
					SendData.Count=0;
					SendData_Low;
					SendData.Data_Buf<<=1;			
					SendData.Step=4;	
				}
				else
				{
					//------=0
					SendData.Count=0;
					SendData_Low;
					SendData.Data_Buf<<=1;
					SendData.Step=5;
				}	
				break;
			case 4:
				SendData.Count++;
				SendData_Low;
				if(SendData.Count>=20)
				{
					SendData.Step=6;
				}
				break;
			case 5:
				SendData.Count++;
				SendData_Low;
				if(SendData.Count>=10)
				{
					SendData.Step=6;
				}
				break;
			case 6:
				SendData.Bit_Count++;
				SendData.Count=0;
				if(SendData.Bit_Count>=8)
				{
					SendData.Byte_Count++;
					if(SendData.Byte_Count>=SendDataSize)
					{
						SendData.Step=7;
					}
					else
					{
						SendData.Data_Buf=SendDataBuffer[SendData.Byte_Count];
						SendData.Bit_Count=0;
						SendData.Step=2;
					}
				}
				else
				{
					SendData.Step=2;
				}
				break;
			case 7:
				SendData_Hight;
				SendData.Bit_Count=0;
				SendData.Byte_Count=0;
				SendData.Enable=0;
				SendData.Step=0;
				SendData.Count=0;
				SendData.TF=Timer100MS;
				break;
			default:
				
				break;
		}
	}
}

void SendDataDeal(void)
{
	SendDataBuffer[0]=0xaa;
	SendDataBuffer[1]=0x01;
	SendDataBuffer[2]=Status.SeatOpen_f;
	SendDataBuffer[3]=Status.CoverOpen_f;	
	//--------------------------
	SendDataBuffer[4]=SendDataBuffer[0]+SendDataBuffer[1]+SendDataBuffer[2]+SendDataBuffer[3];
}




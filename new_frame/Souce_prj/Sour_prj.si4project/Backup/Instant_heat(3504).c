#include "Instant_heat.h"


uart_str UART_0;
uart_str UART_1;


//---����һ��ˮ���¶��趨���
const uint_8 Water_temp_table[5] = {
		32,	
		34,
		36,
		38,
		40
};

//************************
//
//	����0�ĳ�ʼ��
//
//************************
void Urat0_Init(void)
{
	//������2��ʼ������ѡ��ʱ��Դtm2psc
	TM2MD = 0x09;
	CK2MD = 0x00;			// Select the clock source to fpll/4
//	TM2OC=103;				////������((16*100000/4)/(103+1))/(2*8)=2400
	TM2OC = 103;				///������((16*100000/4)/(206+1))/(8)=2400	
	SC0SEL = 0x02;			//-------ѡ��ʱ��2��Ϊ��ʱ�����	
	// bit 7 0 uart���
	// bit 6-4 000 ��ʱ�����
	// bit 3 0 Aϵͳ
	// bit 2-0 010 ѡ��ʱ��2
	P0ODC = 0x0C;			//------�趨P02.P03Ϊ��·
	P0PLUD = 0x00;			//------P02.P03������
	P0DIR |= 0x08;			//------P03
	P0DIR &= ~0x04;			//-----P02

	//SC0MD0˵��	
		//bit7=1 ���ݴ�����أ����������أ������½���
		//bit6=0,--
		//bit5=0 -- 		
		//bit4=0 MSB ��λ
		//bit3=0 ��ʼ���� ��
		//bit2=1  2 - 0 ͬ����ʽ���д���λ�� 8λ
		//bit1=1
		//bit0=1
	SC0MD0=0x10;	
	//SC0MD1˵��	
		//bit7=0 RX��������ѡ��
		//bit6=0,SBTn���Ź���Ϊ�˿�
		//bit5=1����Ϊ��������			
		//bit4=1����TXDΪ�����������
		//bit3=1��Ƶ
		//bit2=1��ʱ��
		//bit1=0ѡ��8��Ƶ
		//bit0=1ȫ˫��ͨѶ
	SC0MD1=0x3d;
	//SC0MD2˵��	
		//bit7=1 -
		//bit6=0,7-6 ָ��֡��ʽ 10 8λ����+1ֹͣλ
		//bit5=0 -		
		//bit4=0 ָ������λ  0 0 ����ʱ����0	����ʱ���0
		//bit3=1 У�� 1 ����żУ��
		//bit2=0 - ����
		//bit1=0 0 ���ݽ���
		//bit0=0 0 ���ݷ��� 
	SC0MD2=0x88;	//8λ����+1λֹͣλ ����żЧ��
	//SC0MD3˵��	
		//bit7=0 -
		//bit6=0,- 7-6 00ѡ����������ݷ��ͺ�SB0����� �̶�Ϊ 1
		//bit5=0 -
		//bit4=0 -
		//bit3=1 ����Ԥ��Ƶ������ 1 �������
		//bit2=1 2-0 ѡ��ʱ��
		//bit1=1  111 ��ʱ�������ͨ��SC0SEL��2-0��ѡ��ʱ��
		//bit0=1 
	SC0MD3=0x0f;	//----��ʼ����--��ͨ��SC0SELѡ��ʱ�� 
	SC0TICR=SC0TICR|0X02;		//����UART��A���ж�
	//bit 7-6 �趨�жϵȼ�
	//bit 5-2	--
	//bit 1  1�� �����ж�
	//bit 0  0	 ���ж�����	
	SC0RICR=SC0RICR|0X02;		//--������0�����ж�
	
	SC0STR=0x40;				//UART0׼������

	//�ṹ���ʼ��
	UART_0.ch = UART0_CH;
	UART_0.len = Data_size;

}


void Uart1_init(void)		//��ʼ��UART1
{
	TMAMD1 = 0x08;		//������A��ʼ������ѡ��ʱ��Դfpll=16m
	TMAMD2 = 0x40;		//Ԥ��Ƶ����
//	TMAOC=103;			//Ƶ��=((16*100000)/(103+1))/(2*8)=9600
	TMAOC = 206;			//Ƶ��=((16*100000)/(206+1))/8=9600	
	SC1SEL = 0x0f;		//ѡ��ʱ��AΪʱ��Դ  ��ѡ��Bϵͳ
			
	P7ODC = P7ODC|0x60;			//�趨��Ӧ����p7.5.6��
	P7PLUD = P7PLUD|0x20;			//------bit5=1
	P7PLUD = P7PLUD&0xbf;			//-----bit6=0
	P7DIR = P7DIR|0x20;			//----bit5=1
	P7DIR = P7DIR&0xbf;			//----bit6=0
//	SC1MD0=0x08;
	SC1MD0 = 0x10;
	//SC1MD1˵��	
		//bit7=0 RX��������ѡ��
		//bit6=0,SBTn���Ź���Ϊ�˿�
		//bit5=1����Ϊ��������			
		//bit4=1����TXDΪ�����������
		//bit3=1��Ƶ
		//bit2=1��ʱ��
		//bit1=0ѡ��8��Ƶ
		//bit0=1ȫ˫��ͨѶ
	SC1MD1=0x3d;	
	SC1MD2=0x88;	//8λ����+1λֹͣλ ����żЧ��
	SC1MD3=0x0f;
	SC1TICR=SC1TICR|0X02;		//����UART1�����ж�	
	SC1RICR=SC1RICR|0X02;		//--������1�����ж�
	SC1STR=0x40;				//----UART1׼������	
}

/*----------------------------------------------
�������ƣ�Uart_TX_Byte
�������������пڷ����ֽ�
���������   buf:�������ݱ���    ch  : ���ں�
���ز�������
�޸ļ�¼����δ����
------------------------------------------------*/
void	Uart_TX_Byte(uart_str *p)
{
	if(p->ch == 0)  //����0�����ֽڴ���
	{
		while((SC0STR&0x20)!=0) 	//���ͻ�������Ϊ��ʱ�ȴ�
		{
			asm("nop");
		}	
		Tx0_buf_reg = p->Tx_buff[0];
	}
	else   //����1�����ֽڴ���
	{
		while((SC1STR&0x20)!=0)		//���ͻ�������Ϊ��ʱ�ȴ�
		{
			asm("nop");
		}	
		Tx1_buf_reg = p->Tx_buff[0];
	}
}


//***********************************************/
//
//	���ڴ����ж��У���������
//
//***********************************************/
void Uart0_send_data(uart_str *p)
{
	uint_8 i;
	Tx0_buf_reg = p->Tx_buff[i];
	i = (i+1) % Data_size;
}

//***********************************************/
//
//	�����¶ȴ����У�׼����������
//
//***********************************************/
void Uart0_data_pre(uart_str *p)
{
	uint_8 i;
	for(i=0; i<p->len; i++)
	{
		p->Tx_buff[i] = p->Tx_data[i];    //�ѷ������������
	}	
}

//***********************************************/
//
//	���ڽ����ж��У���������
//
//***********************************************/
void Uart0_Reverive(uart_str *p)
{
	if((SC0STR&0x10) == 0x10)
	{
		Water.RX_delay=0;
		if((p->Rx_flag & 0x01) == 0)
		{
			p->Rx_buff[p->Data_count] = Rx0_buf_reg;    //�ѽ��յ������ݷŵ�����
			p->Data_count = (p->Data_count+1) % Data_size;	 //�Լ�		
			if(p->Data_count == 0)
			{
				p->Rx_flag |= 0x01;
			}
		}
	}
}


/*----------------------------------------------
�������ƣ�ReadRespRx0
�������������п�0�������ݽ���
�����������
���ز�������
�޸ļ�¼��
------------------------------------------------*/
void ReadRespRx0(uart_str *p)
{		
	uchar i;
    uchar checksum;
    if((p->Rx_flag & 0x01)==0x01)   //UART0���ݽ������
	{
		p->Rx_flag &= 0xfe;
		for(i=0;i<p->len;i++)
			p->Rx_data[i]=p->Rx_buff[i];
		//------------------------------�жϽ��������Ƿ���ȷ
		if((p->Rx_data[0]==0x32) && (p->Rx_data[0]==0x34))  
		{
			checksum=0;
			for(i=1;i<11;i++)
			{
				checksum ^= p->Rx_data[i];   //���
			}
			if(checksum == p->Rx_data[Data_size-1]) //У����ж�
				p->Rx_flag |= 0x01;
			else
				p->Rx_flag &= 0xfe;	
		}
		else
		{
			p->Rx_flag &= 0xfe;	
		}
	}	
}


//*********************ͨѶ���ݸ�ʽ***********************/
//  1������ �� ����
//	��ʼ��    ������	 	����1		����2		����3		����4		����5		У���
//	 0x33	 x	  �趨ˮ��    	  0		  0		  0		  0		����~����5
//  x �� 0x01 ��������  0x00 �رռ���   �趨ˮ�� �ֱ���1�� ��30~41��֮��

//   2�� ���� �� ����
//	��ʼ��    	������	 	����1		����2		����3		����4		����5		У���
//	 0xCC   0x01  	 x2 	0x0f	ˮ��		ˮ����		  0		����~����5
//	x2��������      0 �޹���     1 �й���  
//	bit2 �� ��������·
//	bit3 :  ��������·
//  bit4: 	ˮ·���ϣ������ͣ�

//********************************
//
//   �������ݰ�֡��ʽ����
//
//********************************
void Tx_frame_buff(uart_str *p, uint_8 temp)
{
	uint_8 i;

	p->Tx_data[0]=0x32;   	//��ͷ 
	p->Tx_data[1]=0xF0;    //add
	p->Tx_data[2]=0x81; 	//MODE
	p->Tx_data[4]=temp/256;		//Tset_H
	p->Tx_data[5]=temp%256;		//Tset_L
	p->Tx_data[6]=0x00;	
	p->Tx_data[7]=0x00;	
	p->Tx_data[8]=0x00;	
	p->Tx_data[9]=0x00;	
	p->Tx_data[10]=0x00;
	for(i=1;i<11;i++)
	{
		p->Tx_data[11] ^= p->Tx_data[i];	//Xor(Add~data8)	
	}	
	p->Tx_data[12]=0x34;	//��β	
}


//*******************************
//
//   �¶ȴ���
//
//*******************************
void Water_Temp_Deal(uart_str *p)
{
	uint_8 water_temp = 0;
	if(Status.power_f == 1)  //
	{
		SpeedinessHeatPowerOn;   //��������ģ���Դ
		if((Water.TempDeal_time == 0) && (Water.WaterIn_f == 1))  //���������һ֡�ļ��ʱ�䵽����ʹ���˽�ˮ
		{
			
			if(Water.Hot_f == 1)  //ʹ���˼���
			{
				if(Status.Mode_select == 5)  //������ĳ��ģʽ�趨�̶��¶ȣ��������趨Ϊ��ͯģʽ
				{
					water_temp = 36;
				}
				else
				{
					water_temp = Water_temp_table[Status.Icon.water_temp_gear - 1];  //����ˮ���趨ֱ�Ӱ��յ�λ���¶�
				}
				if(Status.ZuoYu_f == 1)
				{
					water_temp = 40;    //��ԡ�̶�Ϊ40��
				}
				if(Status.LengReAnMo_f == 1)	//���Ȱ�Ħ
				{
					if(++Water.delay1 < 500)	   //5����� 
					{
						water_temp = 40;  
					}
					if(++Water.delay1 < 600)	   //1�벻���� 
					{
						water_temp = 0;  
					}
					else
					{
						Water.delay1 = 0;
					}
				}
			}
			else   //���û��ʹ�ܼ���
			{
				p->Tx_data[3] = 0x00;  //�رռ���
			}
			
			if(Status.PG_zero_f == 1)  //�������ջأ�����ˮ
			{
				p->Tx_data[3] = 0x00;
			}
			else
			{
				p->Tx_data[3] = 0x01;    //��������			
			}
			Tx_frame_buff(p, water_temp);    //׼���������ݰ�
			
			Water.StopHotDelay = 0;     
			Water.JiRe_In_f = 1;
			Water.Hot_f = 1;
		}

		else
		{
			p->Tx_data[3] = 0x00;
			Tx_frame_buff(p, water_temp);  //���¶�ֵ�Ž�ȥ����
			if(++Water.StopHotDelay > 2)
			{
				Water.StopHotDelay = 2;
				Water.JiRe_In_f = 0;
			}
			Water.Hot_f = 0;
		}
		Uart0_data_pre(p);   //�������ݰ�
		Water.TempDeal_time++;
	}

	else
	{
		Water.TempDeal_time++;
		if(Water.TempDeal_time > 50)
		{
			Water.TempDeal_time = 0;
			ReadRespRx0(p);		//���н������ݽ���
		}

		if(++Water.RX_delay > 300) //�������������֮�󳬹�3S���յ���һ֡�����ж�Ϊ��ʱͨ��
		{
			Water.RX_delay = 300;			//���ﳬ��3SӦ���ڽ����ж�����0
			Water.Error_flag |= 0x80;    //��ʱ�����־
		}
		else
		{
			Water.Error_flag &= ~0x80;   //�����־��0
		}

		/*if((uart_data_f & 0x01) == 0x01)  //������յ�һ֡������
		{
			uart_data_f &= ~0x01;	
			
			if(Water.JiRe_In_f == 1)
			{
				if(rx0_data[2] == 0)  //������������ û�й���
				{
					Water.Error_flag &= 0xE3;	
					Water.InputTemp = rx0_data[3]; //��ˮ�¶�
					Water.OutputTemp = rx0_data[4]; //��ˮ�¶�
				} 
				if((rx0_data[2] && 0x10) == 0x10)  //ˮ·���ϣ�������
				{
					Water.Error_flag |= 0x04;	
				}
				else
				{
					Water.Error_flag &= ~0x04;
				}
				
				if((rx0_data[2] && 0x04) == 0x04)  //��·����
				{
					Water.Error_flag |= 0x02;	
				}
				else
				{
					Water.Error_flag &= ~0x02;
				}

				if((rx0_data[2] && 0x08) == 0x08)  //��·����
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
				if((rx0_data[2]&0x0f) == 0x00)//ͨѶ����
				{
					Error.value&=0xfffe;
					Water.InputTemp=rx0_data[3];
					Water.OutputTemp=rx0_data[4];		
				}
				else//ͨ���������
				{
					Water.Error_flag |= 0x40;	
				}
			}
		}*/
	}
}








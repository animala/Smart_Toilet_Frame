#include "Function_deal.h"
#include "TM1629.h"
#include "Pump_pwm.h"


const uint_8 DryingDutyTable[8][6]=
{
   //--30-40-50-60
   //--36-43-nu-50
   {0,40,42,45,47,47},		//<3
   {0,35,37,39,42,42},		//<3~8
   {0,30,32,33,37,37},		//<8~13   ---������
   {0,26,30,30,34,34},		//<13~18
   {0,21,22,26,30,32},		//<18~23
   {0,32,41,55,54,27},		//<23~28
   {0,33,40,48,52,22},		//<28~33
   {0,6,6,10,10,16},		//>33		
};

//**************************
//
//    ��Դ���ع��ܺ���
//    �ػ����ڸ�λ���֮��
//
//**********************/
void Power_Switch_deal(void)
{
	if(timer.t_power_1s == 1)
	{
		timer.t_power_1s = 0;
		if(Status.Power_e == 1)
		{
			if(Status.power_f == 1)   //�ػ�
			{
				Status.Icon.power_disp = 1;
				Status.Power_e = 0;
				Status.power_f = 0;
			}
			else			//����
			{
				Status.Icon.power_disp = 0;
				Status.Power_e = 0;
				Status.power_f = 1;
			}
		}
	}	
}

//**************************
//
//    ֹͣ���ܺ���
//
//**********************/

void Close_all_function(void)
{
	Status.Icon.power_disp = 0;  //�رյ�Դͼ��
	Status.Icon.energy_disp = 0;	//�رս���
	Status.Icon.wind_gear = 0;    //���µ�λ��0
	Status.Icon.water_yeild = 0;  //ˮ����λ��0
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	IR.Last_value = 0;    //��ֵ������0
	work.step = 0;
	work.time = 0;     //ʱ����0
	Status.reciprocate_f = 0;
	Status.LengReAnMo_f = 0;
	if(Status.dring_f == 1)
	{
		Drying.enable_f = 0;
		Drying.HotEndTime = T10S;   //10����ȴ
		Drying.step = 0;
	}	
}

//**************************
//
//    ��ϴ���ܺ���
//
//**********************/

void Hip_Wash_Enable(void)
{

	if((Status.seat_f == 1) && (Status.PowerEnd_f == 1))
	{
		if((Status.Mode_select == 0) ||			//����ǵ�һ��ѡ����ϴ����
			((Status.Mode_select != 0) && (Status.Mode_select != 1))) //���߲��ǵ�һ�ν���������������ڽ�������Ĺ���		 
		{
			if(Drying.HotEndTime == 0)   //���ﴦ��Ӻ��״̬�½�����ϴ״̬���ȵȷ���ر��ٽ�����ϴ 2019-8-9��
			{
				Status.Mode_select = 1;   //1Ϊ��ϴ
				Status.Pres_select = 2;   //Ĭ��ˮѹ��2��
				Status.PG_gear = Status.Pres_select;  //�Ȱѹ���ѡ��λ��ֵ����λ���ٶԵ�λ���в���	
				Status.Icon.water_yeild = Status.Pres_select;  //�ѳ�ʼ��λ��ֵ��ˮ����λ��ʾ
			}
			if(Status.Mode_select == 0)
			{
				Status.QingXiQieHuan_f = 0;  //��ϴ�л�	
			}
			else
			{
				Status.QingXiQieHuan_f = 1;  //��ϴ�л�
			}
			Status.Working_f = 0;
			work.enable_f = 1;    		//ʹ�ܹ���
			work.step = 0;   			//������0
			Water.WashTimer = T1Min;     //��ϴʱ��Ĭ��1����
		}	
	
		if(Drying.enable_f == 1)   //���ʹ���˺��
		{
			Status.dring_f = 0;   //�رպ��
			Drying.enable_f = 0;
			Drying.step = 0;
			Drying.HotEndTime = 5;     //����Ӻ��״̬ת����ϴ״̬���ȸ�����˿����5��  8-9 ��
		}	
		Status.LengReAnMo_f = 0;
		Status.ShuiYaAnMo_f = 0;
		Status.reciprocate_f = 0;
		Status.fangwu_f = 0;
		Drying.swash_f = 0;
		
	}
}


//**************************
//
//    ��ϴ���ܺ���
//
//**********************/

void Wemen_Wash_Enable(void)
{
	if((Status.seat_f == 1) && (Status.PowerEnd_f == 1))
	{
		if((Status.Mode_select == 0) ||  //����ǵ�һ��ѡ��ϴ����
			((Status.Mode_select != 0) && (Status.Mode_select != 2))) //������ǵ�һ�ν���������������ڽ�������Ĺ���
		{
			if(Drying.HotEndTime == 0)   //���ﴦ��Ӻ��״̬�½�����ϴ״̬���ȵȷ���ر��ٽ�����ϴ 2019-8-9��
			{
				Status.Mode_select = 2;   //2Ϊ��ϴ
				Status.Pres_select = 2;   //Ĭ��ˮѹ��2��
				Status.PG_gear = Status.Pres_select;  //�Ȱѹ���ѡ��λ��ֵ����λ���ٶԵ�λ���в���	
				Status.Icon.water_yeild = Status.Pres_select;  //�ѳ�ʼ��λ��ֵ��ˮ����λ��ʾ
			}
			
			if(Status.Mode_select == 0)
			{
				Status.QingXiQieHuan_f = 0;  //��ϴ�л�	
			}
			else
			{
				Status.QingXiQieHuan_f = 1;  //��ϴ�л�
			}
			Status.Working_f = 0;
			work.enable_f = 1;			//ʹ�ܹ���
			work.step = 0;				//������0
			Water.WashTimer = T1Min;	 //��ϴʱ��Ĭ��1����
			
		}
		if(Drying.enable_f == 1)   //���ʹ���˺��
		{ 
			Status.dring_f = 0;   //�رպ��
			Drying.enable_f = 0;
			Drying.step = 0;
			Drying.HotEndTime = 5;     //����Ӻ��״̬ת����ϴ״̬���ȸ�����˿����5��  8-9 ��
		}	
		Status.LengReAnMo_f = 0;
		Status.ShuiYaAnMo_f = 0;
		Status.reciprocate_f = 0;
		Status.fangwu_f = 0;
		Drying.swash_f = 0;
	}
}

//*******************************
//
//---��ɹ�����������IRң���е���
//
//*******************************
void Dring_Work_Enable(void)
{
	if((Status.seat_f == 1) && (Status.power_f == 1))
	{
		if(Status.dring_f == 0)    //������ڹ�����ϴ״̬��
		{
			Status.stop_f = 0;
			Status.Mode_select = 0;  //�رչ�����ϴ
			Status.QingXiQieHuan_f = 0;  //��ϴ�л���0
		
			work.step = 0;
			Status.dring_f = 1;
			Drying.enable_f = 1;  //���ʹ�ܱ�־λ��1
			Drying.step = 0;
			Status.ZuoYu_f = 0;
			Status.LengReAnMo_f = 0;
			Status.ShuiYaAnMo_f = 0;
			Status.reciprocate_f = 0;
			Drying.WorkingTimer = T4Min;  //���ʱ��4����
		}
		work.LianXu_f = 0;
		work.LianXuBuf = 0;
	}
}

//**************************
//
//    �������ܺ���
//
//**********************/

void Deodorization_Deal(void)
{	
	if(Status.test_f == 0)
	{
		if((Status.power_f == 1) && (Status.seat_f == 1))   //�ϵ����,����
		{
			if(Status.chuchou_e&&Status.chuchou_f&&(Status.dring_f==0)&&(Status.PowerEnd_f==1)) //����ʹ�ܣ����ں�ɣ���λ���
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


//---------------------------
//----��ˮ���ˮ����
//--------------------------
void FlushWater_Board_Deal	(void)
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
//	��˵��ڲ���
//
//***************************************/
void Spraylance_move_deal(uint_8 select)
{

	if((PenGan.PGmove_f == 0) && (Status.Working_f == 1) && (Status.reciprocate_f == 0) && (Status.LengReAnMo_f == 0))
	{			
		if(timer.t_receive_1s == 1)  //λ�õ��� +
		{
			timer.t_receive_1s = 0;
			
			if((select & 0x20) == 0x20)
			{		
				PenGan.PGmove_f = 1;	//��˵���ʹ��			
				Status.PG_gear++;		//���λ��+	
				if(Status.PG_gear > 4)  //�޶�λ��
				{
					Status.PG_gear = 4;
				}
			}
			
			if((select & 0x10) == 0x10)  //λ�õ���-
			{		
				PenGan.PGmove_f = 1;	//��˵���ʹ��		
				if(Status.PG_gear > 0) //�޶�λ��
				{
					Status.PG_gear --;
				}
			}
		}
	}
}

//***************************************/
//void Water_change(uint_8 select)
//	
//	ˮ�����ڲ���
//
//***************************************/
void Water_change(uint_8 select)  
{
	if(Water.pressure_f == 0 && Status.Working_f == 1)	  //���������ִ����ϴ����
	{
		Water.pressure_f = 1;
	}
}


//***************************************/
//void Cover_status_change(uint_8 select)
//	
//	���ǵ��ڲ���  2019-9-2
//
//***************************************/
void Cover_status_change(void)  
{

	if(Status.seat_f == 0)   //���û������
	{
		if(CoverSeat.CoverOpen_f == 0)  //���û�з���
		{
			buz_set(1, 30, 30);
			CoverSeat.CoverDirStatus = 1;
			CoverSeat.delay = T5Min;
			CoverSeat.enable_f = 1;			
		} 
		else 			//	�ظ�
		{
			CoverSeat.CoverDirStatus = 2;	
		}
		CoverSeat.SpaceTime = Timer300MS;
	}
}


//***************************************/
//void Circle_status_change(void)
//	
//	���ǵ��ڲ���  2019-9-2
//
//***************************************/
void Circle_status_change(void)  
{

	if(Status.seat_f == 0)   //���û������
	{
		if(CoverSeat.SeatOpen_f == 0)  //���û�з�Ȧ
		{
			buz_set(1, 30, 30);
			CoverSeat.SeatDirStatus = 1;
			CoverSeat.delay = T5Min;
			CoverSeat.enable_f = 1;			
		}
		else 			//	��Ȧ
		{
			CoverSeat.SeatDirStatus = 2;	
		}
		CoverSeat.SpaceTime = Timer300MS;
	}
}



//***************************************/
//void Gear_deal(uint_8 select)
//	��λ����ѡ����
//	--����ң�ط������ĵ�λ����
//***************************************/
uint_8 Gear_deal(uint_8 select)
{
	uint_8 temp = 0;
	temp = select & 0x0f;
	return temp;
}


//********************************************/
//
//�������~
//
//******************************************/
void Sitdown_Check(void)
{
	if(ZhaoZuo_pin == 0)  //��⵽����
	{
		Seat.count1++;
		Seat.count2 = 0;
		if(Seat.count1 > 10)
		{
			//------------100MS������Ч
			Entironment.time = T30Min;     //��ȡ�����¶ȵ�ʱ��
			CoverSeat.delay = T5Min;
			CoverSeat.enable_f = 1;
			Status.chuchou_f = 1;		//-----��������ʹ��
			Status.jieneng_e = 0;		//�رս���
			Seat.Flag |= 0x01;
			if(Status.seat_f == 0)
			{
				Status.seat_f = 1;
				Status.power_f = 1;		//������־λ��1
				//SpeedinessHeatPowerOn;
				//WifiPowerOn;
				//CO2_clr_seat;
				Status.fangwu_f = 1;	//���۱�־λ��1
				fangwu.step = 0;		
				penkou.step = 0;		//���������ϴ��ͷ������ֹͣ�ջ�
				Status.penkou_f = 0;		
				buz_set(1,30,30);	
			}
			if(Seat.count1 > 1000)		//---------����10S�Զ���ˮ����
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
		//------------����2S��Ч
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
				//CO2_set_seat;
				Seat.first_f = 0;
				Status.stop_f = 1;
				Status.Mode_select = 0;
				work.LianXu_f = 0;
				work.LianXuBuf = 0;
				work.step = 0;	
				if(Status.dring_f == 1)   //���ں�ɵ����������
				{
					Status.dring_f = 0;
					Drying.enable_f = 0;
					Drying.step = 0;
					Drying.HotEndTime = T10S;
				}
				work.time = 0;
				Status.ShuiYaAnMo_f = 0;
				Status.reciprocate_f = 0;
				Status.dring_wf_f = 0;
				Status.ZuoYu_f = 0;
				Status.LengReAnMo_f = 0;
				if(penkou.enable_f == 1)  //������ϴ��ڵ����������
				{
					penkou.step = 0;
					Status.penkou_f = 0;
				}					
			}
		}
		//----------����6S�Զ���ˮ
		if(Seat.count2 > 600)		
		{
			if(MachineTest.Flag == 0)
			{
				if(Status.auto_f)
				{
					if(Status.chongshui_e)
					{
						Status.chongshui_e = 0;
						//Status.chongshui_f = 1;
						Status.chongshuiban_f = 1;
					}
				}
			}
		}
		//---����1�ӹس���
		if(Seat.count2 > 6000)		
		{
			Status.chuchou_f = 0;	
		}

		//----------����10���ӽ������ģʽ
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
void FanSetDeal(void)			///---------�����趨�¶ȴ���
{
	if(Drying.enable_f == 1)    //���ʹ��
	{
		if((Status.dring_f == 1)&&(Status.power_f == 1))  //�ϵ���ϣ����״̬��1
		{
			if(Status.PG_zero_f == 1)   //���������λ
			{
				Status.Dry_zero_f = 0;
				
				switch(Drying.step)
				{
					case 0:
						HotFan_set;	     //�ȿ����ȣ��ټ���			
						Drying.DutyPwm = 0;
						Drying.time = 0;
						if(Status.auto_f  & (Drying.swash_f==0))  //���ʹ�����Զ���ˮ����
						{
							if(Status.chongshui_e == 1)
							{
								Drying.swash_f = 1;
								Status.chongshui_f = 1;
								Status.chongshuiban_f = 1;
								Status.chongshui_e = 0;
							}
						}
						
						Drying.step++;
						break;
					case 1:
						Drying.time++;
						if(Drying.time > 10)
						{
							Drying.time = 0;
							Drying.step++;
						}
						break;
					case 	2:
						work.time = Drying.WorkingTimer;
						work.Start_f = 1;
						//--------------Ĭ�Ͽ�ʼ�����¶��ڻ����¶�25���¿�ʼ����
						Drying.DutyPwm = DryingDutyTable[Entironment.Index][Drying.DangWei];
						Status.Icon.wind_gear = Drying.DangWei;    //��ʾ��ǰĬ�ϵĵ�λ													
						Drying.step++;
						break;
					case 	3:
						if(work.time == 0)   	//����ʱ�����
						{ 
							work.Start_f = 0;
							Status.dring_f = 0;
							Drying.DutyPwm = 0;
							FanHeat_clr;      	//�رռ���˿
							Drying.step = 0;
							Drying.enable_f = 0;   //�رպ��ʹ��
							Drying.HotEndTime = T10S;  //�趨�ر���ȴʱ��10S
						}					
						break;
					default:
						Status.dring_f = 0;
						HotFan_clr;
						FanHeat_clr;
						Drying.step = 0;
						break;
				}
				if(Status.Mode_select == 3)   //���ﵥ����ĳ��ģʽ���н���PWM���Ʋ������������趨Ϊ��ͯģʽ
				{
					Drying.DutyPwm = 35;			//----�����趨��ģʽ��PWMֵ
				}
				else if(Status.Mode_select < 3)// && (Status.Mode_select > 0))
				{
					Drying.DutyPwm = DryingDutyTable[Entironment.Index][Status.Icon.wind_gear];   //��λ����
				}
			}	
		}
	}
	else   //������ɲ���
	{
		Drying.DutyPwm = 0;
		FanHeat_clr;         //�ȹرռ��ȣ��ٹط���		 
		if(Drying.HotEndTime == 0)
		{
			HotFan_clr;
			Status.dring_f = 0;    //��ɱ�־λ��0
		//	work.time = 0;         //����ʱ����0
		}
		else
		{
			HotFan_set;	
		}
	}
}
//*******************************************
//
//		���PWMִ�к���--����1ms�ж���ִ��
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
		if(Drying.DutyCount < Drying.DutyPwm)   //ռ�ձ�++
		{
			FanHeat_set;
		}
		else
		{
			FanHeat_clr;
		}
	}
}
//********************************
//
//------���۴�����������ʹ�ܱ�־λ
//
//********************************
void Antifouling_Deal(void)
{
	if((Status.fangwu_f == 1)&&(Status.PowerEnd_f == 1))   //�ڸ�λ������ʹ�ܷ��۱�־λ
	{
		switch(fangwu.step)
		{
			case 0:
				fangwu.delay = 0;
				Water.WaterIn_f = 1;   //��ˮ
				fangwu.step++;
				break;
			case 1:
				if(++fangwu.delay > 300)		//-----ִ��3��
				{
					Water.WaterIn_f = 0;
					Status.fangwu_f = 0;
				}
				break;
			default:			//����
				Status.fangwu_f = 0;
			break; 
		}
	}
}
//*********************************************
//
//   	ˮѹ������ 
//	����ִ�����ٴΰ��¸���ϴ������λ����ˮѹ
//*******************************************
void Water_press_deal(void)
{
	uint_8 temp = 0;
	
	if((Water.WaterIn_f == 1) && (Status.QiBeng_f == 1))
	{
		
		if(Status.Mode_select > 0)
		{
			temp = Status.Icon.water_yeild;  //ˮѹ��λ����ˮ����λ���Ӷ�����
			
			if(Status.Icon.water_yeild > 2)   //С��2��Ϊ��ѹ�������ѹ
			{
				PWM_Control(ON, temp-1);   //�ѵ�λ����PWM�������õ�pwm����
			}
			else
			{
				PWM_Control(OFF, temp-1);   //�ر�PWM���
			}
			
		}
	}
	else
	{
		PWM_Control(OFF,0);	//�ر�PWM����ѹ  
	}
}

//*********************************************
//
//   	����ˮ������ 
//	����ִ�е�ʱ����ƽ�ˮ��ˮ��־λ
//*******************************************

void WaterInOutDeal(void)
{
	if(Water.WaterIn_f == 0)   // ���û��ʹ�ܽ�ˮ
	{
		if(Water.JiRe_In_f == 0)   //���Ȳ�ʹ��
		{
			PUMPB_clr;
		}
		else
		{
			PUMPB_set;
		}
	}	
	else			//���ʹ���˽�ˮ
	{
		PUMPB_set;
	}
}




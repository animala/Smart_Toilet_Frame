#include "Function_deal.h"

//    ���ܺ���
/**********************/

void Close_all_function(void)
{
	Status.Icon.power_disp = 0;  //�رյ�Դͼ��
	Status.Icon.energy_disp = 0;	//�رս���
	Status.Mode_select = 0;
	Status.Pres_select = 0;
	work.step = 0;
	Status.reciprocate_f = 0;
}

void TunBuWashEnable(void)
{
	if(Status.Mode_select == 0)  //����ǵ�һ��ѡ����ϴ����
	{
		Status.Mode_select = 1;   //1Ϊ��ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 1)) //������ǵ�һ�ν���������������ڽ�������Ĺ���
	{
		Status.Mode_select = 1;    //������ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
		Status.QingXiQieHuan_f = 1;  //��ϴ�л�
	}
	work.enable_f = 1;    		//ʹ�ܹ���
	work.step = 0;   			//������0
	if(Status.dring_f == 1)   //���ʹ���˺��
	{
		Status.dring_f = 0;   //�رպ��
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
	if(Status.Mode_select == 0)  //����ǵ�һ��ѡ��ϴ����
	{
		Status.Mode_select = 2;   //2Ϊ��ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
	}
	if((Status.Mode_select != 0) && (Status.Mode_select != 2)) //������ǵ�һ�ν���������������ڽ�������Ĺ���
	{
		Status.Mode_select = 2;    //���븾ϴ
		Status.Pres_select = 3;   //Ĭ��ˮѹ��3��
		Status.QingXiQieHuan_f = 1;  //��ϴ�л�
	}
	work.enable_f = 1;    		//ʹ�ܹ���
	work.step = 0;   			//������0
	if(Status.dring_f == 1)   //���ʹ���˺��
	{
		Status.dring_f = 0;   //�رպ��
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


//---------------------------��ˮ���ˮ����
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
















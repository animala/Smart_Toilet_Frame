#include "Rolling.h"


//*************2019-7-29 暂停旋钮板的程序编写，没有硬件可用
uchar Readbyte_RollingPcb(void)		//////读8BITS数据
{
	uchar i;
	uchar outputdata=0;
	delay_us(20);
	KeySdaIn;
	delay_us(20);
	for(i=0;i<8;i++)
	{
		outputdata=outputdata >> 1;
		KeySckSet;
		delay_us(20); 
		KeySckClr;
		delay_us(20);
		if(KeySdaPin == ReadKeySdaVale)
		{
			outputdata |= 0x80;
		}	
		else
		{
			outputdata &= 0x7f;
		}	
		delay_us(20);	
	}
	KeySckSet;
	KeySdaOut;
	delay_us(20); 
	return outputdata;	
}

void writebyte_RollingPcb(uchar inputdata)		
{


	uchar i;
	for(i=8;i>0;i--)
	{
		if(inputdata & 0x01)
		{
			KeySdaSet;
		}
		else
		{
			KeySdaClr;
		}	
		inputdata = (inputdata>>1);   			//right shift
		delay_us(30);
		KeySckSet;
		delay_us(30);
		KeySckClr;
		delay_us(30);
	}
	KeySckSet;	
	delay_us(30);
}


void ReadKeyRollingPcb(void)				//读按键
{
	writebyte_RollingPcb(0x41);	//ReadKey
	Rolling.KeyData = Readbyte_RollingPcb(); 
}

/*void ReadKeyRollingPcb(void)				//读按键
{
	uint_8	temp;
	writebyte_RollingPcb(ReadKey);	
	writebyte_RollingPcb(~ReadKey);
	delay_us(20);
	delay_us(20);
	Rolling.KeyData = Readbyte_RollingPcb(); 
	temp=Rolling.KeyData;
	temp=temp>>4;
	if(temp==(Rolling.KeyData&0x0f))
	{
		Rolling.KeyData=(Rolling.KeyData&0x0f);
	}
	else
	{
		Rolling.KeyData=0xff;
	}

}
*/
//-------------显示处理--------------//
void DisplayRollingPcb(void)
{  
  if(Status.PowerEnd_f != 1)
  {
  	Rolling.DispalyMode = 0;//静止
  	Rolling.LedBuf[0] = 0x01ff;//白灯
	Rolling.LedBuf[1] = 0x0000;
	Rolling.LedBuf[2] = 0x0000;
  }
  else 
  {

	  if(Status.Mode_select > 0 && Status.auto_f == 1)
	  {

		Rolling.DispalyMode = Status.reciprocate_f+1;   //标志位+1 就可以得出 1 或者 2 
		Rolling.ChoiceRGB = Status.Mode_select-1;
      }
      else
      {
    	Rolling.DispalyMode = 0;//静止
    	if(Status.chongshuiban_f == 1)
    	{
    		Rolling.LedBuf[0]=0x01ff;//黄灯
	  		Rolling.LedBuf[1]=0x01ff;
	  		Rolling.LedBuf[2]=0x0000;
    	}
    	else
    	{
    		if(Drying.enable_f)
    		{
			  	Rolling.LedBuf[0]=0x01ff;//zi灯
				Rolling.LedBuf[1]=0x0000;
				Rolling.LedBuf[2]=0x01ff;
    		}
    		else
    		{
    			if(Status.enfant_f)
    			{
    				Rolling.LedBuf[0]=0x0000;//绿灯
	  		    	Rolling.LedBuf[1]=0x01ff;
	  		    	Rolling.LedBuf[2]=0x0000;
    			}
    			else
    			{

				 	Rolling.LedBuf[0]=0x0000;//绿灯
  		     	 	Rolling.LedBuf[1]=0x01ff;
  		     	 	Rolling.LedBuf[2]=0x01ff;
    			}
    		}  			
    	}
     }
  }
  /*if(Status.seat_f == 1)//||(Status.CloseRollLed_f==1))
  {
  		Rolling.DispalyMode = 0;//静止
  		Rolling.LedBuf[0] = 0x01ff;//白灯
		Rolling.LedBuf[1] = 0x01ff;
		Rolling.LedBuf[2] = 0x01ff;
  }*/
	switch(Rolling.DispalyMode)
	{
		case 0:
			//-----------单独控制每一个LED 
		//	Rolling.LedBuf[3]=(0x42^Rolling.LedBuf[0]^Rolling.LedBuf[1]^Rolling.LedBuf[2]);//校验
			writebyte_RollingPcb(0x42);//WriteLed
			writebyte_RollingPcb(Rolling.LedBuf[0]>>8);
			writebyte_RollingPcb(Rolling.LedBuf[0]);
			writebyte_RollingPcb(Rolling.LedBuf[1]>>8);
			writebyte_RollingPcb(Rolling.LedBuf[1]);
			writebyte_RollingPcb(Rolling.LedBuf[2]>>8);
			writebyte_RollingPcb(Rolling.LedBuf[2]);
		//	writebyte_RollingPcb(0x24);//WriteLed
			//writebyte_RollingPcb(Rolling.LedBuf[3]>>8);
		//	writebyte_RollingPcb(Rolling.LedBuf[3]);
			break;
		case 1:
			//----------实现指定一组LED渐亮渐灭	
			//Rolling.ChoiceRGB=1;	
			//Rolling.CheckNum=(0x43^Rolling.ChoiceRGB^Rolling.Brightness);//校验
			Rolling.Brightness=10;			
			writebyte_RollingPcb(0x43);//StingBrightness
			writebyte_RollingPcb(Rolling.ChoiceRGB);
			writebyte_RollingPcb(Rolling.Brightness);
		//	writebyte_RollingPcb(0x34);
			break;			  
		case 2:
			//----------实现指定一组LED做跑马灯显示
			//Rolling.ChoiceRGB=2;	
			//Rolling.CheckNum=(0x44^Rolling.ChoiceRGB^Rolling.SpeedCount);//校验
			Rolling.SpeedCount=20;			
			writebyte_RollingPcb(0x44);//StingSpeed
			writebyte_RollingPcb(Rolling.ChoiceRGB);
			writebyte_RollingPcb(Rolling.SpeedCount);
		//	writebyte_RollingPcb(0x55);     
			break;
		default:
			break;
	}
}

void RollingPcbDeal(void)
{
	if(timer.t_100ms_f)
	{
		//-------显示处理
		timer.t_100ms_f = 0;
		DisplayRollingPcb();    //100ms刷新显示		
	}
	else	
	{	//------按键处理
		ReadKeyRollingPcb();
		
		if(Rolling.KeyData == nokey)
		{
			KEY.count1 = 0;
			KEY.count2++;
			if(KEY.count2 > 2)
			{ 
				KEY.count2 = 2;
				if(((KEY.back == 3)||(KEY.back == 2))&&(KEY.flag2 == 0))
				{
					//------------------------短按POWER
					KEY.flag1 = 1;
					KEY.updata_f = 1;
					KEY.vale = KEY.back;
					KEY.back = nokey;
				}
				else
				{
					KEY.back = nokey;
					KEY.vale = nokey;
					KEY.indx = nokey;
					KEY.flag1 = 0;
					KEY.flag2 = 0;
				}
			}
		}
		else
		{
			KEY.count2 = 0;
			KEY.count1++;
			//--------------------有按键
			if(Rolling.KeyData != KEY.back)
			{
				KEY.back = Rolling.KeyData;
				//KEY.count1=0;
			}
			else
			{
				if(KEY.count1 > 2)
				{
					//------------------按键有效
					if(KEY.flag1 == 0)
					{
						if(KEY.back == 3)	 //power
						{
							if(KEY.count1 > 200)		//-------->2s
							{
								KEY.count1 = 200;
								KEY.flag1 = 1;
								KEY.flag2 = 1;
								KEY.updata_f = 1;
								KEY.vale = KEY.back;
							}
						}
						else if(KEY.back == 2)	 //power
						{
							if(KEY.count1 > 220)		//-------->2s
							{
								KEY.count1 = 220;
								KEY.flag1 = 1;
								KEY.flag2 = 1;
								KEY.updata_f = 1;
								KEY.vale = KEY.back;
							}
						}
						else
						{
							KEY.count1 = 2;
							KEY.flag1 = 1;
							KEY.updata_f = 1;
							KEY.vale = KEY.back;
						}
					}
				}
			}
		}
	}
}	
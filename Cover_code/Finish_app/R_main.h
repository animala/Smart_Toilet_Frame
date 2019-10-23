#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"





//-------------------common
#define	uint_8  unsigned char
#define	int_8   char
#define	uint_16 unsigned int
#define	int_16  int
#define	uint_32 unsigned long  
#define	int_32  long
#define Bit(i)	(0x01 << (i))
#define Set_Bit(Byte,i)	Byte  |= Bit(i)
#define Clr_Bit(Byte,i)	Byte  &= (0xff - Bit(i))
#define Turn_Bit(Byte,i) Byte  ^= Bit(i)
#define Read_Bit(Byte,i) (Byte &  Bit(i))
#define Clr_Byte(Byte)	Byte  =  0x00
#define	ON	1
#define	OFF	0


#define	LightLoop	5
#define	Repeat500MS	5

//--------------10MS为基准
#define	Timer100MS				10
//----------------10MS基准时间
#define	T10S			800			//----3*1000/ 10MS = 3s
#define	T30S			3000		//----30*1000/ 10MS = 30s  15s  10s


//-------------100MS为基准
#define	Timer8S					80
#define	Timer10S				100
#define	Timer1Min				6000
#define	Timer2Min				12000

#define	PWMCYC		20		//-----定义PWM周期大小

#define	CurrentOverVale		320

/************旧版本
#define	SeatPositionMax		892
#define	SeatPosition5		856
#define	SeatPosition4		816
#define	SeatPosition3		650
#define	SeatPosition2		450
#define	SeatPosition1		250
#define	SeatPositionMin		85
*****************/
//--------------20160523    V0006
#define	SeatPositionAddMax		820
#define	SeatPositionAdd5		780
#define	SeatPositionAdd4		650
#define	SeatPositionAdd3		500
#define	SeatPositionAdd2		375
#define	SeatPositionAdd1		125
#define	SeatPositionMin			120

/*****************旧版本
#define	CoverPostionMax	925		//-----最大停止位
#define	CoverPostion5		821		//-----静止位
#define	CoverPostion4		764		//-----静止位
#define	CoverPostion3		600		//----pwm	8
#define	CoverPostion2		400		//----pwm	10
#define	CoverPostion1		200		//----pwm	12
#define	CoverPostionMin		90		//----pwm	14
********************/
#define	CoverPositionAddMax		780		//-----最大停止位
#define	CoverPositionAdd5		710		//-----静止位
#define	CoverPositionAdd4		514		//-----静止位
#define	CoverPositionAdd3		364		//----pwm	8
#define	CoverPositionAdd2		264		//550		//----pwm	10
#define	CoverPositionAdd1		114		//----pwm	12
//#define	CoverPositionMin		150		//----pwm	14		//---120  小
#define	CoverPositionMin		180		//----pwm	14		



#define	QuanControl		Set_Bit(P0,0)
#define	GaiControl			Set_Bit(P2,0)

#define	MA_EN_ON			Set_Bit(P2,1)	
#define	MA_EN_OFF			Clr_Bit(P2,1)
#define	MB_EN_ON			Set_Bit(P2,2)
#define	MB_EN_OFF			Clr_Bit(P2,2)

#define	MotIns1On			Set_Bit(P1,4)
#define	MotIns1Off			Clr_Bit(P1,4)
#define	MotIns2On			Set_Bit(P3,0)	
#define	MotIns2Off			Clr_Bit(P3,0)
#define	MotIns3On			Set_Bit(P14,7)
#define	MotIns3Off			Clr_Bit(P14,7)
#define	MotIns4On			Set_Bit(P2,3)
#define	MotIns4Off			Clr_Bit(P2,3)


//---------------------------------------
#define	InceptDataPin		Read_Bit(P1,1)
#define	SendData_Hight		Set_Bit(P1,2)
#define	SendData_Low		Clr_Bit(P1,2)	
//-----------------------------------
typedef struct {
		uint_8	end_f:1;
		uint_8	sing1s_f:1;
		uint_8	TimerCount;		
                } init_CB;                               
extern init_CB init;
typedef struct {
		uint_8	sing100us;			//-----100us加一
		uint_8	sing10ms;			//-----10ms加一
		uint_8	sing10ms_f:1;			
		uint_8	sing100ms_f:1;
                } timer_CB;                               
extern timer_CB timer;

//--------------------座圈
typedef struct{
		uint_8	OpenDirStatus;		
		uint_16	Duty;			
		uint_16	PositionIndex;		//------转动角度位置
		uint_16	AdcBuf[5];
		uint_8	AdcCount;
		uint_8	LockDieCount;
		uint_16	DelayTime;			//-----间隙时间
		uint_8	BuShangTime;
		uint_8	BuShang_f:1;
		uint_8	Enable_f:1;			//------翻盖使能
		uint_8	OpenOrClose_f:1;	//------表示座圈开关状态
		uint_8	OpenDir_f:1;		//------表示翻座圈方向
		uint_8	DirDown_f;			//------电极转动方向
		uint_8	DirUp_f1:1;			//------电极转动方向
}SeatCircle_CB;
extern  SeatCircle_CB SeatCircle;
//------------------座盖
typedef struct{
		uint_8	OpenDirStatus;		//---=1 需要向上翻，=2 需要向下翻
		uint_8	Enable_f:1;
		uint_8	OpenOrClose_f:1;		//------表示座圈开关状态
		uint_8	OpenDir_f:1;				//------表示翻座圈方向
		uint_8	DirUp_f:1;				//------电极转动方向
		uint_8	DirDown_f:1;			//------电极转动方向
		uint_16	Duty;					//------频率占空比
		uint_16	PositionIndex;			//------转动角度位置
		uint_16	AdcBuf[5];
		uint_8	AdcCount;
		uint_8	LockDieCount;
		uint_16	DelayTime;				//-----间隙时间

		uint_8	BuShang_f:1;
		uint_8	BuShangTime;
		}SeatCover_CB;
extern  SeatCover_CB SeatCover;

typedef struct{
		uint_8	AdcChoice;					//------ADC选择
		uint_16	LevelOffTime;				
		//------翻盖停止运动后延时时间
		uint_8	SeatOpen_f:1;				//------座圈状态标志
		uint_8	CoverOpen_f:1;				//------座盖状态标志		
		uint_8	AutoCoverCircleStep;
		uint_16	DelayTime;					//-------翻盖间隔时间
		uint_16	RunTime;					//------翻盖运行时间
		uint_16	RamLog;
		}Status_CB;
extern  Status_CB Status;


typedef struct {                                               
		uint_16	adc1_zuowen_vale;                 
		uint_16	adc2_shuiwen_vale;
		uint_16	adc_vale_buf;			 
		uint_8	adc_count;         
		uint_8	adc_flag:1;  
		uint_8	adc_start_flag:1;			 
		uint_8	adc_chunnel:1;
                } adc_CB;                               
extern adc_CB ADC; 


typedef struct{
		uint_8	step;
		uint_16	time_h;
		uint_16	time_l;
		uint_8	start_f:1;
		uint_8	first_f:1;
		uint_8	already_f:1;
		uint_8	OK_f:1;
		uint_8	Bit_Count;
		uint_8	Byte_Count;
		uint_8	Recv_Data_Buf;
		}IR_CB;
extern  IR_CB IR;

typedef struct{
		uint_8	Step;
		uint_8	Enable;
		uint_8	Start_f:1;
		uint_8	Count;
		uint_8	Bit_Count;
		uint_8	Byte_Count;
		uint_8	Data_Buf;
		uint_8	TF;	

		
		}SendData_CB;
extern  SendData_CB SendData;



typedef struct{
		uint_16	PositionMax;
		uint_16	Position5;
		uint_16	Position4;
		uint_16	Position3;
		uint_16	Position2;
		uint_16	Position1;
		uint_16	PositionMin;
		uint_8	PositionCount;
		uint_16	PositionMinBUfferr[5];
			}Seat_CB;
extern  Seat_CB	Seat;
typedef struct{
		uint_16	PositionMax;
		uint_16	Position5;
		uint_16	Position4;
		uint_16	Position3;
		uint_16	Position2;
		uint_16	Position1;
		uint_16	PositionMin;
		uint_8	PositionCount;
		uint_16	PositionMinBUfferr[5];
		
			}Cover_CB;
extern  Cover_CB	Cover;

typedef struct{
		uint_8	Step;
		uint_8	Flag:1;
		uint_8	Delay;
		uint_8	CoverLedDir;
		uint_8	SeatLedDir;

		}PcbTest_CB;
extern  PcbTest_CB PcbTest;

extern	uint_16	temperature_adcbuf[5];
extern	uint_8 read_data;
extern	const unsigned int CSK_table[];
extern	const unsigned int Temp_table[];
extern	const unsigned int Temp_table1[];


void DelayUs(uint_8  Loop);
void Raminitial(void);
void timer_manage(void);

void Temperature_ADCDeal(void);

void Seat_Stop(void);
void Cover_Stop(void);
void ReadADCDeal(void);
void CoverCircleDeal(void);

	

void	IR_receive(void);
void	IR_Operation(void);
void	SendSeatData(void);
void SendDataDeal(void);
void PcbTestProgrom(void);
uint_16	ReadADC(uint_8	ADCchannel);
void CircleCoverControl(void);
void SeatCircleMotorDown(uint_16 Duty);

void SeatCircleMotorUp(uint_16 Duty);


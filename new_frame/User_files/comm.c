/******************************************************************/
/* company: topband	                                           */
/* designer: dengyingbin                                          */
/* date:  2016/1/20                                               */
/******************************************************************/
#include "comm.h"
#include "MN101af50d.h"
#include "main.h"

#ifdef _COMM_FUN_

typedef enum {
	CT_HEART,
	CT_HEATTOBOARD,
	CT_HANDTOBOARD,					//握手
	CT_HANDTOPC,						//心跳
	CT_INITBOARD,
	CT_INITBOARDOK,					//初始化成功回复
	CT_SCANINFO,						//引脚扫描信息
	CT_TESTNEXT,						//后台回复，继续测试
	CT_TESTEND,						//测试结束
	CT_RSV
};

typedef enum {
	TFI_HEAD,
	TFI_HEAD2,
	TFI_CMD,
	TFI_LEN,				
	TFI_LEN2,
	TFI_DATA,
	TFI_RSV
}TestFrameInfo;

typedef enum {
	TM_NONE,
	TM_INPUT,
	TM_OUTPUT,
	TM_MADC,
	TM_TADC5V,
	TM_TADC25V,
	TM_CHIP,
	TM_EEPROM,
	TM_220V,
	TM_PULSE,
	TM_RSV
}TestMode;

typedef enum {
	CM_XOR, 				//异或
	CM_SUM, 				//累加和
	CM_RSV
}CheckMode;

typedef enum {
	IFI_HEAD,				//报头0x32
	IFI_ADDR,				//设备地址
	IFI_CMD,				//命令
	IFI_DATA1,		
	IFI_ERROR,
	IFI_INPUTTEMPH,
	IFI_INPUTTEMPL,
	IFI_OUTTEMPH,
	IFI_OUTTEMPL,
	IFI_FLOWH,
	IFI_FLOWL,
	IFI_XOR,
	IFI_STOP,
	IFI_RSV
}InsFrameInfo;

#define COMM_RX_FRAME_MAX_SIZE	50
#define COMM_RX_DATA_BUF_SIZE		(2 * COMM_RX_FRAME_MAX_SIZE)
#define COMM_RX_FRAME_NUM		5

#define GPIO_OUT_ADDRBASE 		0x3E70
#define GPIO_IN_ADDRBASE		0x3E80
#define GPIO_DIR_ADDRBASE		0x3E90
#define GPIO_PLUD_ADDRBASE		0x3EA0
#define GPIO_PIN_NUM			88
#define GPIO_GROUP_NUM			11

typedef struct {
	bool isOk;
	u8 val;
	u8 tbCnt;
}GpioInfo;

typedef struct {
	bool 	isOk;				//读取稳定值，结束扫描
	u8	val;				//值
	u32	debCnt ; 			//消抖时间计数
	u32	tbCnt ;			//扫描时间计数
}GpioGroupInfo;

typedef struct {
	//u8 boardID[8];			//控制板ID，用于引脚信息自动装载
	u8 testNum;			//需测试的引脚数
	u8 groupCnt;			//已扫描引脚组计数
	u8 gpioCnt;
	bool delay_f;
	u16 delayCnt;
	bool ac1Scan_f;
	bool scan_f;			//扫描中标志
	bool switchBaud_f;	//切换波特率
	bool tBoardScanEnd;	//测试板扫描结束
	bool mBoardScanEnd;	//主控板扫描结束
	bool isChipOk;
	bool isEnd;
	u8 scanNo;			//扫描序号
	GpioGroupInfo group[GPIO_GROUP_NUM];	
	u8 tMode[GPIO_PIN_NUM];			//测试类型，0-不测；1-输入；2-输出
	GpioInfo gpio[GPIO_PIN_NUM];
}TestInfo;
TestInfo gTestInfo;

bool gTestLock_f = FALSE;			//测试锁功能标志


/*-----------------------接收帧结构-------------------------------------------*/
typedef struct {
	u16 protocol;									//协议编号
	u8  buf[COMM_RX_FRAME_MAX_SIZE];				//帧缓存；
}CommRxFrame;

/*-----------------------用于通讯数据接收的数据结构---------------------------*/
typedef struct {
	u16 wrtPtr;									//帧队列存储指针
	u16 readPtr;									//帧队列读取指针
	u16 dataWrtPtr;								//数据队列存储指针
	u8  dataBuf[COMM_RX_DATA_BUF_SIZE];				//数据缓存 
	CommRxFrame frameArry[COMM_RX_FRAME_NUM];	//帧缓存
}CommRxBuf;
CommRxBuf  gCommRxBuf;

void insHotRxDealwith(u8* pData);
void testRxDealwith(u8* pData);

/*----------------------协议注册信息结构--------------------------------------*/
typedef enum {
	//PT_INSHOT,					//即热模块报文
	PT_TEST,						//测试报文
	PT_RSV
}ProtocolType;

typedef enum {
	LM_FIXED,		//固定长度
	LM_UNFIXED,		//变长
	LM_RSV
}FrameMode;

typedef  void(*CommRxDeal)(u8* pBuf);
typedef struct {
	u8 lenPos;					//固定帧长度,或者变长帧长度反码位置(1开始)
	u8 headNum;					//报头个数
	u8 head1;						//报头
	u8 head2;						//报头
	u8 fMode;						//变长帧或固定帧
	u8 checkMode;					//校验模式crc of sum
	u16 crcStart;					//校验开始位置	
	u16 crcEnd;					//倒数位置
	CommRxDeal  dealFun;			//接收处理函数
}CommProtocolInfo;
CommProtocolInfo gCommProtocolInfoArry[PT_RSV] = {
		//{8, 1, PRO_HEAD_INSHOT, 0, LM_FIXED, CM_SUM, IFI_ADDR, 1, insHotRxDealwith},
		{5, 2, PRO_HEAD1_TEST, PRO_HEAD2_TEST, LM_UNFIXED, CM_XOR, TFI_CMD, 1, testRxDealwith}
};
/*----------------------相应协议接收处理结构---------------------------------*/
typedef struct {
	u16 dataRdPtr;									//数据队列读取指针
	u16 dataLen;									//数据队列有效数据长度
}CommRxInfo;
CommRxInfo gCommRxInfoArry[PT_RSV];


#define COMM_TX_FRAME_MAX_SIZE	30
#define COMM_TX_FRAME_NUM		5
/*---------------------用于发送数据帧的数据结构------------------------------*/
typedef struct {
	u16 cnt;			//发送数据计数器
	u16 len;			//应发数据长度
	u8   buf[COMM_TX_FRAME_MAX_SIZE];
}CommTxFrame;

typedef struct {
	bool isBusy;
	bool delay_f;
	u16 delayCnt;
	u8 wrtPtr;
	u8 readPtr;
	CommTxFrame frm[COMM_TX_FRAME_NUM];
}CommTxInfo;
CommTxInfo gCommTxInfo;

u8 group[GPIO_GROUP_NUM + 4];
//u8 adcChnl  = 0;
//u16 adcBufArry[4];
void sendPulseToTBoard(u8 result);


void memSetEx(void* p, u8 val, u16 size)
{
	u16 i;
	u16 l = size;
	for(i = 0; i < l; i++)
	{
		((u8*)p)[i] = val;
	}
}
//--------------------------------------------------------------
//				计算校验
//			pData:  数据数组
//			len :  计算长度
//			checkMode: 校验模式
//--------------------------------------------------------------
u8 calcCRC(u8 *pData, u16 len, u8 checkMode)
{
	u8 sum = 0;
	u16 i;
	
	for(i = 0; i < len; i++)
	{
		switch(checkMode)
		{
		case CM_XOR:
			sum ^= pData[i];
			break;
			
		case CM_SUM:
		default:
			sum += pData[i];
			break;
		}
	}

	return sum;
}


//----------------------------------------------------------------
//			串口接收处理
//			放置于串口接收中断里
//----------------------------------------------------------------
void commRx(u8 data)
{
	u16 i;
	gCommRxBuf.dataBuf[gCommRxBuf.dataWrtPtr] = data;
	for(i = 0; i < PT_RSV; i++)
		gCommRxInfoArry[i].dataLen++;
	gCommRxBuf.dataWrtPtr = (gCommRxBuf.dataWrtPtr + 1)  %  COMM_RX_DATA_BUF_SIZE;
}

void moveReadPtr(CommRxInfo  *p, u16 num)
{
	p->dataRdPtr = (p->dataRdPtr + num) % COMM_RX_DATA_BUF_SIZE;
	p->dataLen -= num;
}

#define LEN_ERROR 	0xff
u8 getFrameLen(u16 rdPtr, u8 lenPos, u8 fmode)
{
	u16 len;
	u8 l;
	u8 l1;
	
	switch(fmode)
	{
	case LM_UNFIXED:
		lenPos -= 2;	//获取从0开始的长度字节位置。
		l = gCommRxBuf.dataBuf[(rdPtr + lenPos) % COMM_RX_DATA_BUF_SIZE];
		l1 = gCommRxBuf.dataBuf[(rdPtr +lenPos + 1) % COMM_RX_DATA_BUF_SIZE];    //获取长度的2个字节
		if(l ^ l1 == 0xff)
			len = l + lenPos + 3;
		else
			len = LEN_ERROR;	//长度出错，返回0xff
		break;

	case LM_FIXED:
	default:
		len = lenPos;
		break;
	}
	return len;
}

//-----------------------------------------------------------------
//			从数据缓存里提取帧
//----------------------------------------------------------------
void commGetFrames(void)
{
	u16 i, j;
	u16 len;
	u16 cLen; 		//参与校验和计算的字节长度
	u16 dLen;
	u16 fLen;
	u8 crcPos;
	CommRxInfo *pCri;
	CommProtocolInfo *pCpi;

	for(i = 0; i < PT_RSV; i++)
	{
		pCri = &gCommRxInfoArry[i];
		pCpi = &gCommProtocolInfoArry[i];

		//接收数据长度大于帧数据长度字节的位置加一则处理,长度为2字节
		dLen = pCri->dataLen; 
		len = pCpi->lenPos;
		while(dLen >=  len)
		{
			//确定是否为报头以及加入数据长度的字节数小于帧最大字节数
			if((gCommRxBuf.dataBuf[pCri->dataRdPtr] == pCpi->head1)
				&& ((pCpi->headNum == 2)  
				&& (gCommRxBuf.dataBuf[(pCri->dataRdPtr + 1) % COMM_RX_DATA_BUF_SIZE] == pCpi->head2)
				|| (pCpi->headNum == 1)))
			{					
				fLen = getFrameLen(pCri->dataRdPtr,  pCpi->lenPos, pCpi->fMode);
				//数据从数据缓存提取到帧缓存
				if(fLen != LEN_ERROR)
				{
					if(dLen >=fLen)
					{
						for(j = 0; j < fLen;  j++)
						{
							gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[j] = 
								gCommRxBuf.dataBuf[(pCri->dataRdPtr + j)  %  COMM_RX_DATA_BUF_SIZE];
						}
						
						//检验校验和
						crcPos = fLen - pCpi->crcEnd;
						cLen = crcPos - pCpi->crcStart;  			
						if(calcCRC(&gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[pCpi->crcStart], 
							cLen, pCpi->checkMode) == gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[crcPos])
						{
							//帧缓写计数器加一，提取一帧
							gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].protocol = i;
							gCommRxBuf.wrtPtr = (gCommRxBuf.wrtPtr + 1)  %  COMM_RX_FRAME_NUM;   
							//提取指定长度数据，数据缓存计数器增加指定长度
							moveReadPtr(pCri, fLen);
							dLen -= fLen;
						}
						else
						{
							moveReadPtr(pCri, 1);	//校验和错，丢弃数据
							dLen--;
						}		
					}
					else
						return;
				}
				else
				{
					moveReadPtr(pCri, 1);//长度有误，丢弃数据 ;
					dLen--;
				}
			}
			else
			{
				moveReadPtr(pCri, 1);		//不是报头则丢弃
				dLen--;
			}
		}
	}
}

//-----------------------------------------------------------------
//				串口接收处理
//-----------------------------------------------------------------
void commRxDeal(void)
{
	CommRxDeal fun;
	//提取帧处理
	commGetFrames();
	
	//帧处理过程
	while(gCommRxBuf.readPtr != gCommRxBuf.wrtPtr)
	{
		fun = gCommProtocolInfoArry[gCommRxBuf.frameArry[gCommRxBuf.readPtr].protocol].dealFun;
		if(fun != nullptr)
		{
			//调用接收处理函数
			(*fun)(gCommRxBuf.frameArry[gCommRxBuf.readPtr].buf);
		}		
		gCommRxBuf.readPtr = (gCommRxBuf.readPtr + 1)  %  COMM_RX_FRAME_NUM;
	}
}

//-----------------------------------------------------------------
//		发送数据
//		uartx:串口号
//		pData:数据数组指针
//		len:  发送数据字节数
//-----------------------------------------------------------------
void commTxDeal(void)
{
	if(gCommTxInfo.wrtPtr != gCommTxInfo.readPtr
		&& !gCommTxInfo.isBusy)
	{
		gCommTxInfo.isBusy = TRUE;
		gCommTxInfo.delay_f = TRUE;
		gCommTxInfo.delayCnt = 0;
		//SetTimer(TIMER_TX_WAIT, 1000, 1);
		commTx();		
	}
}

void commTxBusyDelay(void)
{
	if(gCommTxInfo.delay_f)
	{
		gCommTxInfo.delayCnt++;
		if(gCommTxInfo.delayCnt >= 50)
		{
			gCommTxInfo.delay_f = FALSE;
			gCommTxInfo.isBusy = FALSE;
		}
	}
}

void commTestPulseDelay(void)
{
	//脉冲检测超时处理
	if(gTestInfo.ac1Scan_f )
	{
		gTestInfo.delayCnt++;
		if(gTestInfo.delayCnt >= 200) //200ms
		{
			gTestInfo.ac1Scan_f = FALSE;
			sendPulseToTBoard(0x01);	//检测到错误			
		}
	}
}

void commTestDelay(void)
{
	commTestPulseDelay();
	commTxBusyDelay();
}

//----------------------------------------------------------------
//			串口发送处理
//			放置于串口发送中断里
//----------------------------------------------------------------
void commTx(void)
{
	if(gTestLock_f)
	{
		u8 rdPtr = gCommTxInfo.readPtr;
		if(gCommTxInfo.frm[rdPtr].cnt >= gCommTxInfo.frm[rdPtr].len)
		{
				//一帧发送完成
				rdPtr = (rdPtr + 1) % COMM_TX_FRAME_NUM;
				//KillTimer(TIMER_TX_WAIT);
				gCommTxInfo.readPtr = rdPtr;
				//gCommTxInfo.delay_f = TRUE;
				//gCommTxInfo.delayCnt = 0;
				gCommTxInfo.isBusy = FALSE;
				if(gTestInfo.switchBaud_f)
				{
					gTestInfo.switchBaud_f = FALSE;
					TM2OC = 12;
				}
		}
		else //if(gCommTxInfo.frm[rdPtr].cnt < gCommTxInfo.frm[rdPtr].len)
		{
			TXBUF0 = gCommTxInfo.frm[rdPtr].buf[gCommTxInfo.frm[rdPtr].cnt];
			gCommTxInfo.frm[rdPtr].cnt++;			
		}			
	}
}

//----------------------------------------------------------
//				即热模块加热开启和温度设置函数
//				on:开关标志
//				temp:温度
//----------------------------------------------------------
void sendInstantHotTemp(u8 on, u16 temp)
{
	u8  wPtr;
	u16 flen = 13;
	u8* p; 

	/*获取通讯缓冲区*/
	DISABLEINT;
	wPtr = gCommTxInfo.wrtPtr;
	gCommTxInfo.wrtPtr  = (gCommTxInfo.wrtPtr + 1) % COMM_TX_FRAME_NUM;
	ENABLEINT;
	p = gCommTxInfo.frm[wPtr].buf;
	
	if(flen > COMM_TX_FRAME_MAX_SIZE)
		return;

	/*数据打包*/
	p[IFI_HEAD] = PRO_HEAD_INSHOT;
	p[IFI_ADDR] = 0xF0;		
	p[IFI_CMD] = 0x81; 
	p[IFI_DATA1] = on;
	p[IFI_ERROR] = (temp >> 8) & 0xff;
	p[IFI_INPUTTEMPH] = temp & 0xff;
	p[IFI_INPUTTEMPL] = 0x00;
	p[IFI_OUTTEMPH] = 0x00;
	p[IFI_OUTTEMPL] = 0x00;
	p[IFI_FLOWH] = 0x00;
	p[IFI_FLOWL] = 0x00;
	p[IFI_XOR] = calcCRC(&p[1], flen - 3, CM_XOR);
	p[IFI_STOP] = 0x34;
	gCommTxInfo.frm[wPtr].len =flen;
	gCommTxInfo.frm[wPtr].cnt = 0;
}

//----------------------------------------------------------------------
//				即热通讯处理
//----------------------------------------------------------------------
void insHotRxDealwith(u8* pData)
{	
	int i;
	Water.RX_delay=0;
	if((uart_flag_f&0x01)==0)
	{
		uart_flag_f|=0x01;
		for(i = 0; i < uart0_size; i++)
			rx0_buf[i] = pData[i];
	}
}

//----------------------------------------------------------------------
//				后台调试处理
//----------------------------------------------------------------------
void pcRxDealwith(u8* pData)
{
	pData = pData;
#if 0
	u16 t;
	u8 ck;
	u8 val;
	/*后台调试功能*/
	if(pData[FFI_CMD] == 0x0a)
	{
		ck = pData[FFI_DATA1];
		val = pData[FFI_DATA1 + 1];
		if(ck != 0)
			cleanAirPumpOn(ck, val);
		else
			cleanAirPumpOff();
		//t = ((u16)pData[FFI_DATA1] << 8) | pData[FFI_DATA1 + 1];
		//gMotors[MOTOR_DIVIDER].posDest = t;
		//gSeat.tempCnt = pData[FFI_DATA1];
		//gDrying.tempCnt = pData[FFI_DATA1 + 1];
	}
#endif
}

void encodeFrame(u8 cmd, u8* pData, u8 len)
{
	u8  wPtr;
	u16 flen = len + 6;
	u8* p;
	u8 i;

	DISABLEINT;
	wPtr = gCommTxInfo.wrtPtr;
	gCommTxInfo.wrtPtr  = (gCommTxInfo.wrtPtr + 1) % COMM_TX_FRAME_NUM;
	ENABLEINT;
	p = gCommTxInfo.frm[wPtr].buf;
	
	if(flen > COMM_TX_FRAME_MAX_SIZE)
		return;
	
	p[TFI_HEAD] = PRO_HEAD1_TEST;
	p[TFI_HEAD2] = PRO_HEAD2_TEST;
	p[TFI_CMD] = cmd; 
	p[TFI_LEN] = len;
	p[TFI_LEN2] = ~len;
	if (pData != nullptr)
	{
		if(cmd == CT_SCANINFO)
		{
			if(gTestInfo.isChipOk)
			{
				pData[3] |= 0x80;
				gTestInfo.isChipOk = FALSE;
			}
			else
				pData[3] &= 0x7f;
		}
		
		for(i = 0; i < len; i++)
			p[TFI_DATA + i] = pData[i];
	}
	p[flen - 1] = calcCRC(&p[TFI_CMD], flen - 3, CM_XOR);
	gCommTxInfo.frm[wPtr].len =flen;
	gCommTxInfo.frm[wPtr].cnt = 0;
}

//--------------------------------------------------------
//			引脚输出处理
// 		scanNo:引脚序号
//			val: TRUE输出1，FALSE输出0
//-------------------------------------------------------
void POUT(u8 gpio, bool val)
{
	u8 g = gpio / 8;
	u8 pin = gpio % 8;

	if(val)
		__UMEM8(GPIO_OUT_ADDRBASE + g)  |= (0x01 << pin);
	else
		__UMEM8(GPIO_OUT_ADDRBASE + g) &= ~(0x01 << pin);
}

void  sendADCToTBoard(u8 mGpio)
{
#define DRINGFANGPIO				0x54		//烘干风机状态检测AD采样引脚
#define SEATTEMPGPIO				0x57		//座温采样引脚
#define ROOMTEMPGPIO				0x55		//室温采样引脚
#define WATERTEMPGPIO			0x56		//水温采样引脚
#define DRINGFAN_CONTROL_GPIO   	0x2F      		//烘干风扇控制引脚
#define TEMPADCTESTUPVAL			535			//AD采样检测上限值
#define TEMPADCTESTDOWNVAL 		425			//AD采样检测下限值

/*并行发送，第4字节表示可控硅的完成状态*/
	u8 data[4];
	u16 temp;
	data[0] = mGpio;
	switch(mGpio)
	{
	case SEATTEMPGPIO:
		temp = adcSample(SEATTEMPGPIO -DRINGFANGPIO);
		data[2] = !(temp < TEMPADCTESTUPVAL && temp > TEMPADCTESTDOWNVAL);
		break;
//#if 0
	case WATERTEMPGPIO:
		temp = adcSample(WATERTEMPGPIO -DRINGFANGPIO);
		data[2] = !(temp < TEMPADCTESTUPVAL && temp > TEMPADCTESTDOWNVAL);
		break;
//#endif
	case DRINGFANGPIO:
		POUT(DRINGFAN_CONTROL_GPIO, 1);
		temp = adcSample(DRINGFANGPIO  -DRINGFANGPIO);
		data[2] = !(temp >  5); 	//大于5表示风机工作正常
		POUT(DRINGFAN_CONTROL_GPIO, 0);
		break;
	
	case ROOMTEMPGPIO:
	default:
		temp = adcSample(ROOMTEMPGPIO  -DRINGFANGPIO);
		data[2] = !(temp < TEMPADCTESTUPVAL && temp > TEMPADCTESTDOWNVAL);
		break;
	}
	data[1] = 0;
	encodeFrame(CT_SCANINFO, data, 4);
}

//-----------------------------------------------------------------
//			发送握手帧
//-----------------------------------------------------------------
volatile u8 boardID[15] = {0x17, 0x10, 0x09, 0x09, 0x10, 0x01, 0x97, 0x02, 0, 0, 0, 0, 0, 0, 0};
void sendHandCmd(void)
{
	encodeFrame(CT_HANDTOBOARD, boardID, 8);
}

//----------------------------------------------------
//
//------------------------------------------------------------
void delay_Us(u16 t)
{
	while(t > 0)
	{
		asm("nop");
		asm("nop");	//  150ns
		asm("nop");
		asm("nop");
		asm("nop");	
		asm("nop");
		asm("nop");
		t--;
	}
}

void  delayMs(uchar loop)
{
	uchar	i,j;
	for(i=0;i<loop;i++)
	{
		for(j=0;j<200;j++)	
		{
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");		
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");		
			asm("nop");
			asm("nop");		
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
		}
	}
}


void gpioScan(u8 *p, u8* group,  u8 num)
{
	u16 j;
	u16 i;
	u8 pre = 0;
	u8 pin;
	u8 cnt = 0;
	delay_Us(10);
//	memSetEx(gTestInfo.gpio, 0, sizeof(gTestInfo.gpio));
	gTestInfo.gpioCnt = 0;
	/*引脚读取，并发送到测试板*/
	while(cnt < 20)
	{
		cnt++;
		delay_Us(1000);
		for(i = 0; i < GPIO_GROUP_NUM; i++)
		{
			for(j = 0; j < 8; j++)
			{
				pin = i * 8 + j;
				if(!gTestInfo.gpio[pin].isOk
					&& gTestInfo.tMode[pin] == TM_INPUT)
				{
					pre = __UMEM8(GPIO_IN_ADDRBASE + i);
					pre = (pre >> j) & 0x01;
					if(pre == gTestInfo.gpio[pin].val)
					{
						gTestInfo.gpio[pin].tbCnt++;
						if(gTestInfo.gpio[pin].tbCnt >= 10)
						{
							gTestInfo.gpio[pin].isOk = TRUE;
							if(gTestInfo.gpio[pin].val == 0x01)
								group[ i] |= (0x01 << j);
							else
								group[ i] &= ~(0x01 << j);
							gTestInfo.gpioCnt++;
						}
					}
					else
					{
						gTestInfo.gpio[pin].tbCnt = 0;
						gTestInfo.gpio[pin].val = pre;
					}							
				}
			}
		}
	
		if(gTestInfo.gpioCnt >= num)
			break;				
	}
}

void testPinOut(u8* p, u8 val, u8 mGpio)
{
	u8 i;
	for(i = 0; i < GPIO_PIN_NUM; i++)
	{
		if(gTestInfo.tMode[i] == TM_OUTPUT)
		{
			if(mGpio == i)
				POUT(i, val);
			else
				POUT(i, (p[i / 8] >> ( i % 8)) & 0x01);
		}
	}
}

void testScanInfo(u8 *p)
{
	u8 mGpio = *p;
	u8 tMode = p[1];
	u8 val = p[2];
	u8 num = p[3] & 0x7f;
	bool isEnd = (p[3] >> 7) & 0x01;
	u8 eeVal = 0;
	u8 eVal = 0;
	u8 i;
	
	switch(tMode)
	{
	case TM_CHIP:
		/*p[4]可控硅测试项目数；p[5]开始是可控硅的管脚信息*/
		for(i = 0; i < p[4]; i++)
			POUT(p[5 + i], val);

		/*除可控硅的测试完成，单独发送可控硅测试回复*/
		if(isEnd)
		{
			memSetEx(group, 0, GPIO_GROUP_NUM + 4);
			group[0] = *p;
			group[1] = tMode;
			group[2] = val;
			group[3] = num;
			encodeFrame(CT_SCANINFO, group, GPIO_GROUP_NUM + 4);		
		}
		else
			gTestInfo.isChipOk = TRUE;
		break;
		
	case TM_OUTPUT:
	case TM_INPUT:
		testPinOut(&p[4], val, mGpio);
		delay_Us(100);
		//if(*p == 0x3f || *p == 0x47)// || *p == 0x55)
		//	*p = *p;
		memSetEx(group, 0, GPIO_GROUP_NUM + 4);
		gpioScan(&p[4], &group[4], num);
		group[0] = *p;
		group[1] = tMode;
		group[2] = val;
		group[3] = num;
		encodeFrame(CT_SCANINFO, group, GPIO_GROUP_NUM + 4);			
		break;
	
	case TM_MADC:
		sendADCToTBoard(mGpio);
		break;		

	case 	TM_EEPROM:
		eeVal = i2c_read(2);//i2cReadByte(WATERTEMPERATUREADDRESS);
		delayMs(200);
		i2c_write_8bit(2, 0x5a);		//WATERTEMPERATUREADDRESS
		//gpioScan(&p[4], &group[4], num);
		group[0] = *p;
		group[1] = tMode;
		delayMs(200);
		eVal = i2c_read(2) ;
		group[2] = (eVal != 0x5a);//WATERTEMPERATUREADDRESS
		group[3] = num;
		encodeFrame(CT_SCANINFO, group, GPIO_GROUP_NUM + 4);		
		i2c_write_8bit(2, eeVal);//WATERTEMPERATUREADDRESS
		delayMs(200);
		break;

	case TM_PULSE:
		 gTestInfo.ac1Scan_f  = TRUE;		 
		 gTestInfo.delayCnt = 0;
		break;
		
	default:
		break;
	}
}

void sendPulseToTBoard(u8 result)
{
	u8 data[4];
	data[0] = 0;
	data[1] = TM_PULSE;
	data[2] = result;
	encodeFrame(CT_SCANINFO, data, 4);
}

void initTestMode(u8* p)
{
	u8 i;
	for( i = 0; i < GPIO_PIN_NUM; i++)
	{
		//gTestInfo.tMode[i] = (p[i / 4] >> (2 * (3 - (i % 4)))) & 0x3; 
		gTestInfo.tMode[i] = (p[i / 2] >> (4 * (i % 2))) & 0xf; 
		if(gTestInfo.tMode[i] == TM_INPUT)
			__UMEM8(GPIO_DIR_ADDRBASE  +  i / 8) &= ~(0x01 << (i % 8));
		else if(gTestInfo.tMode[i] == TM_OUTPUT)
			__UMEM8(GPIO_DIR_ADDRBASE + i / 8)  |= (0x01 << (i % 8));
		else if(gTestInfo.tMode[i] == TM_CHIP)
			__UMEM8(GPIO_OUT_ADDRBASE + i / 8)  |= (0x01 << (i % 8));
	}
}

void testRxDealwith(u8* pData)
{
	u8 cmd = pData[TFI_CMD];
	u8* p = &pData[TFI_DATA];
	gTestLock_f = TRUE;

	switch(cmd)
	{
	case CT_HANDTOBOARD:
		if(gTestInfo.isEnd)
			encodeFrame(CT_HEATTOBOARD, nullptr, 0);
		else
		{
			gTestInfo.switchBaud_f = TRUE;
			SC1MD1 &= 0xEF;	//设置wifi的串口功能为普通IO口
			sendHandCmd();
		}
		break;

	case CT_INITBOARD:
		initTestMode(p);
		encodeFrame(CT_INITBOARDOK, nullptr, 0);
		break;

	case CT_SCANINFO:
		testScanInfo(p);
		break;

	case CT_HEATTOBOARD:
		encodeFrame(CT_HEATTOBOARD, nullptr, 0);
		break;

	case CT_TESTEND:
		gTestInfo.isEnd = TRUE;
		buz_set(2, 5, 1);
		break;
		
	default:

		break;
	}
}


void commTxAvail(void)
{
	gCommTxInfo.isBusy = FALSE;
}


#define ACC220_PLUSE_TIME_MIN_16M	18000
#define ACC220_PLUSE_TIME_MAX_16M   22000
#define ACC220_PLUSE_TIME_MIN_8M	9000
#define ACC220_PLUSE_TIME_MAX_8M   11000
void scanAc220Gpio(void)
{
	static u8 t = 0;   		//正确脉冲计数
	static u8 tt = 0;			//脉冲总计数
	static u16 startcnt = 0;
	u16 val;
	u16 cnt = 0;	

	TM7MD1 &= ~-0x10;  		//关闭
	cnt = TM7BC;				//关闭状态下读取定时器计数值
	TM7MD1 |= 0x10; 			//启动
	//定时器计数溢出处理
	val  = ((cnt > startcnt) ?  (cnt - startcnt) : (0xffff - startcnt  + cnt));  
	startcnt = cnt;
	if(val >= ACC220_PLUSE_TIME_MIN_16M 
		&& val <= ACC220_PLUSE_TIME_MAX_16M)
	{
		/*检测6个脉冲*/
		t++;
		if(t > 12)
		{
			gTestInfo.ac1Scan_f = FALSE;
			t = 0;
			sendPulseToTBoard(0x00);
		}
	}
	else
	{
		t = 0;		
	}
}

void testPulseIRQ(void)
{
	static bool upEdge_f = TRUE;
	
	if( gTestInfo.ac1Scan_f )
	{
		scanAc220Gpio();
		/*上下沿触发中断轮流切换*/
		upEdge_f = !upEdge_f;
		if(upEdge_f)
			IRQ0ICR |= 0x20;   //上升沿触发
		else
			IRQ0ICR &= ~0x20;	//下降沿触发
	}
}

//-----------------------------------------------------------------
//					ADC启动函数
//-----------------------------------------------------------------
#define 	ADCK				942				//0.98的定标	0.96*1024
#define  	ADCB				82				//0.02的定标	0.04*1024
#define	ADCFACTOR			10				//adc定标系数
u16 adcSample(u8 chnl)
{	
	u32 v ;
	u32 tmp;
	u16 retVal = 0;
	u8 i = 100;
	
	while(i)
	{
		i--;
		ANCTR1 = chnl + 4; 
		delay(5);				//通道选择后延时5us
		ANCTR2 = 0x80;			//启动采样

		delayMs(1);	
		while((ANCTR2&0x80)==0x80) ;
	
		v = ((u16)ANBUF1 << 2) | (((u16)ANBUF0 >> 6) & 0x3);
		tmp = retVal;

		//滤波算法
		retVal =   (tmp * ADCK + v * ADCB)  >> ADCFACTOR; 
		delayMs(3);
	}
	return retVal;
}


/*-----------------------------------------------
IRQ0 interrupt
-----------------------------------------------*/
#pragma _interrupt INT_IRQ0
void INT_IRQ0(void)					
{
	/*过零检测*/
	TESTPULSEIRQ();    	//dengyingb 2017.6.26
}


#endif   //#ifdef COMM_FUN



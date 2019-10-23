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
	CT_HANDTOBOARD,					//����
	CT_HANDTOPC,						//����
	CT_INITBOARD,
	CT_INITBOARDOK,					//��ʼ���ɹ��ظ�
	CT_SCANINFO,						//����ɨ����Ϣ
	CT_TESTNEXT,						//��̨�ظ�����������
	CT_TESTEND,						//���Խ���
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
	CM_XOR, 				//���
	CM_SUM, 				//�ۼӺ�
	CM_RSV
}CheckMode;

typedef enum {
	IFI_HEAD,				//��ͷ0x32
	IFI_ADDR,				//�豸��ַ
	IFI_CMD,				//����
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
	bool 	isOk;				//��ȡ�ȶ�ֵ������ɨ��
	u8	val;				//ֵ
	u32	debCnt ; 			//����ʱ�����
	u32	tbCnt ;			//ɨ��ʱ�����
}GpioGroupInfo;

typedef struct {
	//u8 boardID[8];			//���ư�ID������������Ϣ�Զ�װ��
	u8 testNum;			//����Ե�������
	u8 groupCnt;			//��ɨ�����������
	u8 gpioCnt;
	bool delay_f;
	u16 delayCnt;
	bool ac1Scan_f;
	bool scan_f;			//ɨ���б�־
	bool switchBaud_f;	//�л�������
	bool tBoardScanEnd;	//���԰�ɨ�����
	bool mBoardScanEnd;	//���ذ�ɨ�����
	bool isChipOk;
	bool isEnd;
	u8 scanNo;			//ɨ�����
	GpioGroupInfo group[GPIO_GROUP_NUM];	
	u8 tMode[GPIO_PIN_NUM];			//�������ͣ�0-���⣻1-���룻2-���
	GpioInfo gpio[GPIO_PIN_NUM];
}TestInfo;
TestInfo gTestInfo;

bool gTestLock_f = FALSE;			//���������ܱ�־


/*-----------------------����֡�ṹ-------------------------------------------*/
typedef struct {
	u16 protocol;									//Э����
	u8  buf[COMM_RX_FRAME_MAX_SIZE];				//֡���棻
}CommRxFrame;

/*-----------------------����ͨѶ���ݽ��յ����ݽṹ---------------------------*/
typedef struct {
	u16 wrtPtr;									//֡���д洢ָ��
	u16 readPtr;									//֡���ж�ȡָ��
	u16 dataWrtPtr;								//���ݶ��д洢ָ��
	u8  dataBuf[COMM_RX_DATA_BUF_SIZE];				//���ݻ��� 
	CommRxFrame frameArry[COMM_RX_FRAME_NUM];	//֡����
}CommRxBuf;
CommRxBuf  gCommRxBuf;

void insHotRxDealwith(u8* pData);
void testRxDealwith(u8* pData);

/*----------------------Э��ע����Ϣ�ṹ--------------------------------------*/
typedef enum {
	//PT_INSHOT,					//����ģ�鱨��
	PT_TEST,						//���Ա���
	PT_RSV
}ProtocolType;

typedef enum {
	LM_FIXED,		//�̶�����
	LM_UNFIXED,		//�䳤
	LM_RSV
}FrameMode;

typedef  void(*CommRxDeal)(u8* pBuf);
typedef struct {
	u8 lenPos;					//�̶�֡����,���߱䳤֡���ȷ���λ��(1��ʼ)
	u8 headNum;					//��ͷ����
	u8 head1;						//��ͷ
	u8 head2;						//��ͷ
	u8 fMode;						//�䳤֡��̶�֡
	u8 checkMode;					//У��ģʽcrc of sum
	u16 crcStart;					//У�鿪ʼλ��	
	u16 crcEnd;					//����λ��
	CommRxDeal  dealFun;			//���մ�����
}CommProtocolInfo;
CommProtocolInfo gCommProtocolInfoArry[PT_RSV] = {
		//{8, 1, PRO_HEAD_INSHOT, 0, LM_FIXED, CM_SUM, IFI_ADDR, 1, insHotRxDealwith},
		{5, 2, PRO_HEAD1_TEST, PRO_HEAD2_TEST, LM_UNFIXED, CM_XOR, TFI_CMD, 1, testRxDealwith}
};
/*----------------------��ӦЭ����մ���ṹ---------------------------------*/
typedef struct {
	u16 dataRdPtr;									//���ݶ��ж�ȡָ��
	u16 dataLen;									//���ݶ�����Ч���ݳ���
}CommRxInfo;
CommRxInfo gCommRxInfoArry[PT_RSV];


#define COMM_TX_FRAME_MAX_SIZE	30
#define COMM_TX_FRAME_NUM		5
/*---------------------���ڷ�������֡�����ݽṹ------------------------------*/
typedef struct {
	u16 cnt;			//�������ݼ�����
	u16 len;			//Ӧ�����ݳ���
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
//				����У��
//			pData:  ��������
//			len :  ���㳤��
//			checkMode: У��ģʽ
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
//			���ڽ��մ���
//			�����ڴ��ڽ����ж���
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
		lenPos -= 2;	//��ȡ��0��ʼ�ĳ����ֽ�λ�á�
		l = gCommRxBuf.dataBuf[(rdPtr + lenPos) % COMM_RX_DATA_BUF_SIZE];
		l1 = gCommRxBuf.dataBuf[(rdPtr +lenPos + 1) % COMM_RX_DATA_BUF_SIZE];    //��ȡ���ȵ�2���ֽ�
		if(l ^ l1 == 0xff)
			len = l + lenPos + 3;
		else
			len = LEN_ERROR;	//���ȳ�������0xff
		break;

	case LM_FIXED:
	default:
		len = lenPos;
		break;
	}
	return len;
}

//-----------------------------------------------------------------
//			�����ݻ�������ȡ֡
//----------------------------------------------------------------
void commGetFrames(void)
{
	u16 i, j;
	u16 len;
	u16 cLen; 		//����У��ͼ�����ֽڳ���
	u16 dLen;
	u16 fLen;
	u8 crcPos;
	CommRxInfo *pCri;
	CommProtocolInfo *pCpi;

	for(i = 0; i < PT_RSV; i++)
	{
		pCri = &gCommRxInfoArry[i];
		pCpi = &gCommProtocolInfoArry[i];

		//�������ݳ��ȴ���֡���ݳ����ֽڵ�λ�ü�һ����,����Ϊ2�ֽ�
		dLen = pCri->dataLen; 
		len = pCpi->lenPos;
		while(dLen >=  len)
		{
			//ȷ���Ƿ�Ϊ��ͷ�Լ��������ݳ��ȵ��ֽ���С��֡����ֽ���
			if((gCommRxBuf.dataBuf[pCri->dataRdPtr] == pCpi->head1)
				&& ((pCpi->headNum == 2)  
				&& (gCommRxBuf.dataBuf[(pCri->dataRdPtr + 1) % COMM_RX_DATA_BUF_SIZE] == pCpi->head2)
				|| (pCpi->headNum == 1)))
			{					
				fLen = getFrameLen(pCri->dataRdPtr,  pCpi->lenPos, pCpi->fMode);
				//���ݴ����ݻ�����ȡ��֡����
				if(fLen != LEN_ERROR)
				{
					if(dLen >=fLen)
					{
						for(j = 0; j < fLen;  j++)
						{
							gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[j] = 
								gCommRxBuf.dataBuf[(pCri->dataRdPtr + j)  %  COMM_RX_DATA_BUF_SIZE];
						}
						
						//����У���
						crcPos = fLen - pCpi->crcEnd;
						cLen = crcPos - pCpi->crcStart;  			
						if(calcCRC(&gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[pCpi->crcStart], 
							cLen, pCpi->checkMode) == gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].buf[crcPos])
						{
							//֡��д��������һ����ȡһ֡
							gCommRxBuf.frameArry[gCommRxBuf.wrtPtr].protocol = i;
							gCommRxBuf.wrtPtr = (gCommRxBuf.wrtPtr + 1)  %  COMM_RX_FRAME_NUM;   
							//��ȡָ���������ݣ����ݻ������������ָ������
							moveReadPtr(pCri, fLen);
							dLen -= fLen;
						}
						else
						{
							moveReadPtr(pCri, 1);	//У��ʹ���������
							dLen--;
						}		
					}
					else
						return;
				}
				else
				{
					moveReadPtr(pCri, 1);//�������󣬶������� ;
					dLen--;
				}
			}
			else
			{
				moveReadPtr(pCri, 1);		//���Ǳ�ͷ����
				dLen--;
			}
		}
	}
}

//-----------------------------------------------------------------
//				���ڽ��մ���
//-----------------------------------------------------------------
void commRxDeal(void)
{
	CommRxDeal fun;
	//��ȡ֡����
	commGetFrames();
	
	//֡�������
	while(gCommRxBuf.readPtr != gCommRxBuf.wrtPtr)
	{
		fun = gCommProtocolInfoArry[gCommRxBuf.frameArry[gCommRxBuf.readPtr].protocol].dealFun;
		if(fun != nullptr)
		{
			//���ý��մ�����
			(*fun)(gCommRxBuf.frameArry[gCommRxBuf.readPtr].buf);
		}		
		gCommRxBuf.readPtr = (gCommRxBuf.readPtr + 1)  %  COMM_RX_FRAME_NUM;
	}
}

//-----------------------------------------------------------------
//		��������
//		uartx:���ں�
//		pData:��������ָ��
//		len:  ���������ֽ���
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
	//�����ⳬʱ����
	if(gTestInfo.ac1Scan_f )
	{
		gTestInfo.delayCnt++;
		if(gTestInfo.delayCnt >= 200) //200ms
		{
			gTestInfo.ac1Scan_f = FALSE;
			sendPulseToTBoard(0x01);	//��⵽����			
		}
	}
}

void commTestDelay(void)
{
	commTestPulseDelay();
	commTxBusyDelay();
}

//----------------------------------------------------------------
//			���ڷ��ʹ���
//			�����ڴ��ڷ����ж���
//----------------------------------------------------------------
void commTx(void)
{
	if(gTestLock_f)
	{
		u8 rdPtr = gCommTxInfo.readPtr;
		if(gCommTxInfo.frm[rdPtr].cnt >= gCommTxInfo.frm[rdPtr].len)
		{
				//һ֡�������
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
//				����ģ����ȿ������¶����ú���
//				on:���ر�־
//				temp:�¶�
//----------------------------------------------------------
void sendInstantHotTemp(u8 on, u16 temp)
{
	u8  wPtr;
	u16 flen = 13;
	u8* p; 

	/*��ȡͨѶ������*/
	DISABLEINT;
	wPtr = gCommTxInfo.wrtPtr;
	gCommTxInfo.wrtPtr  = (gCommTxInfo.wrtPtr + 1) % COMM_TX_FRAME_NUM;
	ENABLEINT;
	p = gCommTxInfo.frm[wPtr].buf;
	
	if(flen > COMM_TX_FRAME_MAX_SIZE)
		return;

	/*���ݴ��*/
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
//				����ͨѶ����
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
//				��̨���Դ���
//----------------------------------------------------------------------
void pcRxDealwith(u8* pData)
{
	pData = pData;
#if 0
	u16 t;
	u8 ck;
	u8 val;
	/*��̨���Թ���*/
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
//			�����������
// 		scanNo:�������
//			val: TRUE���1��FALSE���0
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
#define DRINGFANGPIO				0x54		//��ɷ��״̬���AD��������
#define SEATTEMPGPIO				0x57		//���²�������
#define ROOMTEMPGPIO				0x55		//���²�������
#define WATERTEMPGPIO			0x56		//ˮ�²�������
#define DRINGFAN_CONTROL_GPIO   	0x2F      		//��ɷ��ȿ�������
#define TEMPADCTESTUPVAL			535			//AD�����������ֵ
#define TEMPADCTESTDOWNVAL 		425			//AD�����������ֵ

/*���з��ͣ���4�ֽڱ�ʾ�ɿع�����״̬*/
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
		data[2] = !(temp >  5); 	//����5��ʾ�����������
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
//			��������֡
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
	/*���Ŷ�ȡ�������͵����԰�*/
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
		/*p[4]�ɿع������Ŀ����p[5]��ʼ�ǿɿع�Ĺܽ���Ϣ*/
		for(i = 0; i < p[4]; i++)
			POUT(p[5 + i], val);

		/*���ɿع�Ĳ�����ɣ��������Ϳɿع���Իظ�*/
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
			SC1MD1 &= 0xEF;	//����wifi�Ĵ��ڹ���Ϊ��ͨIO��
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
	static u8 t = 0;   		//��ȷ�������
	static u8 tt = 0;			//�����ܼ���
	static u16 startcnt = 0;
	u16 val;
	u16 cnt = 0;	

	TM7MD1 &= ~-0x10;  		//�ر�
	cnt = TM7BC;				//�ر�״̬�¶�ȡ��ʱ������ֵ
	TM7MD1 |= 0x10; 			//����
	//��ʱ�������������
	val  = ((cnt > startcnt) ?  (cnt - startcnt) : (0xffff - startcnt  + cnt));  
	startcnt = cnt;
	if(val >= ACC220_PLUSE_TIME_MIN_16M 
		&& val <= ACC220_PLUSE_TIME_MAX_16M)
	{
		/*���6������*/
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
		/*�����ش����ж������л�*/
		upEdge_f = !upEdge_f;
		if(upEdge_f)
			IRQ0ICR |= 0x20;   //�����ش���
		else
			IRQ0ICR &= ~0x20;	//�½��ش���
	}
}

//-----------------------------------------------------------------
//					ADC��������
//-----------------------------------------------------------------
#define 	ADCK				942				//0.98�Ķ���	0.96*1024
#define  	ADCB				82				//0.02�Ķ���	0.04*1024
#define	ADCFACTOR			10				//adc����ϵ��
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
		delay(5);				//ͨ��ѡ�����ʱ5us
		ANCTR2 = 0x80;			//��������

		delayMs(1);	
		while((ANCTR2&0x80)==0x80) ;
	
		v = ((u16)ANBUF1 << 2) | (((u16)ANBUF0 >> 6) & 0x3);
		tmp = retVal;

		//�˲��㷨
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
	/*������*/
	TESTPULSEIRQ();    	//dengyingb 2017.6.26
}


#endif   //#ifdef COMM_FUN



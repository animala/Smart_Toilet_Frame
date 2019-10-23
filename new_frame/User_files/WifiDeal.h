


#define	ON	1
#define	OFF	0	

#define CommRepeat  5

#define	Uart1_Rx_Head1	0xff				//----bit0		����ͷ	
#define	Uart1_Rx_Head2	0xff				//----bit1
											//---bit2	�������ݳ���

#define WifiTXBufMax 128
#define WifiRXBufMax 128


//----------------10msλ��׼��λ��200MSû��Ӧ���ź����·���
#define	Timer200ms		20
#define	Timer1000ms	100
//---------------100msΪ��׼��λ
#define	Timer500ms	5						//-----------ÿ��1s����һ��״̬��Ϣ
//----------------500msλ��׼��λ��  //----------ÿ��1���ӷ���һ������
#define	Timer1min	120
//---------------------------------





//--------------������������ַ
#define	AddressFrameLong		2				//--- ���֡���ȵ�ַ
#define	AddressConrrol			3				//----��ſ�������

#define	AddressMode			5+1				//----���ģʽ��ַ
#define	AddressWaterTemp		5+2				//----��ϴˮ��
#define	AddressWaterPressure	5+3				//----��ϴˮѹ
#define	AddressPGLevel			5+4				//----���

#define	AddressWashTimerSet	5+5				//----������ϴʱ��
#define	AddressWashTimer		5+6				//----��ϴʱ��
#define	AddressShuiYaAnMo		5+7				//----����ƶ���Ħ
#define	AddressYiDongAnMo		5+8				//----ˮѹ��Ħ
#define	AddressLengReSpa		5+9				//----���Ȱ�Ħ
#define	AddressDringLevel		5+10			//----���µ�λ
#define	AddressDringTimerSet	5+11			//----���ú��ʱ��
#define	AddressDringTimer		5+12			//----���ʱ��
#define	AddressJieNeng			5+13			//----����
#define	Addressdengkong		5+14			//----��
#define	AddressSeatTemp		5+15			//----����
#define	AddressPenKou			5+16			//----�����ϴ
#define	AddressAutoEnable		5+17			//----��ˮʹ��

#define	AddressFaPao			5+18			//----����

#define	AddressSleep			5+19			//----����

#define	AddressYuLiu3			5+20			//----Ԥ��


//--------------����֡��������
#define 	ComdDataAndControl			1		//----���ݿ�������
#define 	ComdStatusAndAlarm		2		//----״̬������Ϣ
#define 	ComdInefficacy				3		//----��Ч����

#define 	ComdAffirm					5		//----ȷ��֡
#define 	ComdReport					6		//----�㱨֡
//#define 	ComdCloudMenu				7		//----�Ʋ���
#define 	ComdStopAlarm				7		//----ֹͣ������Ϣ
#define 	ComdSeeAboutEdition		8	//----��ѯ�豸�汾
#define 	ComdEditionResponsion		9	//----�豸�汾Ӧ��
#define 	ComdModuleTest				0x90	//----ģ����������
#define 	ComdModuleTestReport		0x91	//----ģ����������
//#define 	ComdConfigureReport		0x7c	//----�豸�㱨����֡
//#define 	ComdConfigureResponsion	0x7d	//----�豸�㱨����Ӧ��֡
#define 	ComdSeeAboutNetwork		0xf0	//----��ѯ����״̬
#define 	ComdSeeAboutNetworkRep	0xf1	//----����״̬Ӧ��֡
#define 	ComdConfigureNetwork		0xf2	//----��������
//#define 	ComdConfigureNetworkRep	0xf3	//----��������Ӧ��
//#define 	ComdWorkingNetwork		0xf4	//----�������繤��ģʽ
//#define 	ComdWorkingNetworkRep	0xf5	//----�������繤��ģʽӦ��
//#define 	ComdUnchainNetwork		0xf6	//----��������
//#define 	ComdUnchainNetworkRep		0xf7	//----��������Ӧ��






extern	uint_8	WifiTxBuf[WifiTXBufMax];
extern	uint_8	WifiRxBuf[WifiRXBufMax];

#define 	ReturnStatusSize 30
extern	uint_8	ReturnStatusBuffer[ReturnStatusSize];
extern	uint_8	ReturnStatusBufferBack[ReturnStatusSize];



typedef struct{
		uint_8	Tx_size;				//------UART1�����ܳ���
		uint_8	Tx_count;			//------UART1���͵�ǰ����
		uint_8	Tx_num;			//------UART1λ
		uint_8	Tx_f:1;				//------UART1���ͷ��ͱ�־
		uint_8	Tx_yingda;			//------������Ӧ��������ϴ�
		uint_8 	Tx_55_f:1;
		uint_8	Tx_55_sum;
		uint_8	Rx_size;				//------UART1�����ܳ���
		uint_8	Rx_count;			//------UART1���ܵ�ǰ����
		uint_8	Rx_num;			//------UART1λ
		uint_8	Rx_f:1;				//------UART1���ܷ��ͱ�־ 
		uint_8	Rx_ff_f:1;			//------���ܵ� 0xff��־
		uint_8	Rx_head_f:1;		//------�������ܵ� 2��0xff��Ϊ���ܵ�ͷ
		uint_8	Rx_error_f:1;		//-------ERROR_F
		uint_8	Rx_error_count;		//------���ܴ������		
		uint_8	Rx_wuxiao_f:1;		//-------ERROR_F
		uint_8	Rx_ok_f:1;			//-------ok_f
		uint_8	Rx_55_sum;			//-------ok_f
		uint_8	Rxtime;

			}WifiSendRepDeal_CB;
extern WifiSendRepDeal_CB WifiSendRepDeal;

typedef struct{
		uint_8	TimerCount;			//-------WIFIʱ���ʱ
		uint_8	send_count;			//-------�������ʹ���
		uint_8 	repeater_timer;		//------�ظ�����������
		uint_8 	repeater1_timer;	//------1s�ظ�
		uint_8	repeater1_f;			//------״̬�ı��־
		uint_8	repeater1_count;	//-------  ��3��
		uint_8 	repeater2_timer;	//------1�ظ�
		uint_8	repeater2_f;			//------״̬�ı��־
		uint_8	repeater2_count;	//-------  ��3��
		uint_8 	alram_f:1;
		uint_8 	alramstop_f:1;
		uint_8 	alram_timer1;		//------����ʱ��1����
		uint_8 	alram_timer2;		//------����ʱ��2����
		uint_8	repeater_f:1;		//------״̬����Ӧ��
		uint_8	invalid_f:1;			//------��Ч����
		uint_8	alarm_f:1;			//------����
		uint_8	ACK_f:1;				//------ȷ��
		uint_8 	huibao_f:1;			//------�㱨
		uint_8 	shebeibanben_f:1;	//------�豸�汾
		uint_8 	save_f:1;			//------��������
		uint_8 	read_f:1;			//------������ȡ������Ϣ

		
		uint_8 	shibiemachaxun_f:1;		//------ʶ�����ѯ	
		uint_8 	chaxunbaojing_f:1;	//------��ѯ����Ӧ��
		uint_8	chaxunzu_f:1;
		uint_8 	shezhishebeihuibao_f:1;	//------�����豸�㱨
		uint_16	shebeihuibao_time;
		uint_8	work_R_f:1;			//------��������
		uint_8	WifiSet_T_f:1;		//------wifi��������

		uint_8 	WifiInit_T_f:1;		//-----�ָ�������������

		uint_8 	wangluozhuangtai_f:1;	//------����״̬��ѯ
		uint_8	wuxiao_f;				//------��Ч��������
		uint_8	wuxiaocanshu;		

		uint_8 	wifi_zijian_f:1;

		uint_8	wifi_zhuangtai_f:1;
		uint_8	wifiStatuse;
		uint_8	wifiSetTime;			//-----����WIFI��ʾʱ�� 30S
		

			}WifiRegisterSign_CB;
extern WifiRegisterSign_CB WifiRegisterSign;





typedef struct{
		uint_8	wifi_f:1;
		uint_8	SMARTLINK_Ok_f:1;				//--------�󶨳ɹ�
		uint_8	CloudOk_f:1;						//--------�����ӳɹ�
		uint_8	RouterOk_f:1;					//--------·�����ӳɹ�
		uint_8	DataBufLong;					//--------״̬���ݳ���
		}WifiStatus_CB;	
extern  WifiStatus_CB WifiStatus;


void CloseAllFunction(void);
void CloseLiquid(void);
void PenKouEnable(void);
void TunBuWashEnable(void);
void NvXingWashEnable(void);
void DringWorkEnable(void);


void Uart1_init(void);	
void get_Return_status_buffer_back(void);
void compare_status_buffer(void);
void Get_Return_status_buffer(void);

void WifiRx(void);
void	WifiRxprogram(void);
void	WifiSend(void);
void WifiTiming(void);





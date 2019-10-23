


#define	ON	1
#define	OFF	0	

#define CommRepeat  5

#define	Uart1_Rx_Head1	0xff				//----bit0		接受头	
#define	Uart1_Rx_Head2	0xff				//----bit1
											//---bit2	接受数据长度

#define WifiTXBufMax 128
#define WifiRXBufMax 128


//----------------10ms位基准单位，200MS没有应答信号重新发送
#define	Timer200ms		20
#define	Timer1000ms	100
//---------------100ms为基准单位
#define	Timer500ms	5						//-----------每隔1s发送一个状态信息
//----------------500ms位基准单位，  //----------每隔1分钟发送一次命令
#define	Timer1min	120
//---------------------------------





//--------------定义控制命令地址
#define	AddressFrameLong		2				//--- 存放帧长度地址
#define	AddressConrrol			3				//----存放控制命令

#define	AddressMode			5+1				//----存放模式地址
#define	AddressWaterTemp		5+2				//----清洗水温
#define	AddressWaterPressure	5+3				//----清洗水压
#define	AddressPGLevel			5+4				//----喷杆

#define	AddressWashTimerSet	5+5				//----设置清洗时间
#define	AddressWashTimer		5+6				//----清洗时间
#define	AddressShuiYaAnMo		5+7				//----喷杆移动按摩
#define	AddressYiDongAnMo		5+8				//----水压按摩
#define	AddressLengReSpa		5+9				//----冷热按摩
#define	AddressDringLevel		5+10			//----风温档位
#define	AddressDringTimerSet	5+11			//----设置烘干时间
#define	AddressDringTimer		5+12			//----烘干时间
#define	AddressJieNeng			5+13			//----节能
#define	Addressdengkong		5+14			//----灯
#define	AddressSeatTemp		5+15			//----座温
#define	AddressPenKou			5+16			//----喷口清洗
#define	AddressAutoEnable		5+17			//----冲水使能

#define	AddressFaPao			5+18			//----发炮

#define	AddressSleep			5+19			//----休眠

#define	AddressYuLiu3			5+20			//----预留


//--------------定义帧命令类型
#define 	ComdDataAndControl			1		//----数据控制命令
#define 	ComdStatusAndAlarm		2		//----状态报警信息
#define 	ComdInefficacy				3		//----无效命令

#define 	ComdAffirm					5		//----确认帧
#define 	ComdReport					6		//----汇报帧
//#define 	ComdCloudMenu				7		//----云菜谱
#define 	ComdStopAlarm				7		//----停止报警信息
#define 	ComdSeeAboutEdition		8	//----查询设备版本
#define 	ComdEditionResponsion		9	//----设备版本应答
#define 	ComdModuleTest				0x90	//----模块生产测试
#define 	ComdModuleTestReport		0x91	//----模块生产测试
//#define 	ComdConfigureReport		0x7c	//----设备汇报配置帧
//#define 	ComdConfigureResponsion	0x7d	//----设备汇报配置应答帧
#define 	ComdSeeAboutNetwork		0xf0	//----查询网络状态
#define 	ComdSeeAboutNetworkRep	0xf1	//----网络状态应答帧
#define 	ComdConfigureNetwork		0xf2	//----配置网络
//#define 	ComdConfigureNetworkRep	0xf3	//----配置网络应答
//#define 	ComdWorkingNetwork		0xf4	//----进入网络工作模式
//#define 	ComdWorkingNetworkRep	0xf5	//----进入网络工作模式应答
//#define 	ComdUnchainNetwork		0xf6	//----解除网络绑定
//#define 	ComdUnchainNetworkRep		0xf7	//----解除网络绑定应答






extern	uint_8	WifiTxBuf[WifiTXBufMax];
extern	uint_8	WifiRxBuf[WifiRXBufMax];

#define 	ReturnStatusSize 30
extern	uint_8	ReturnStatusBuffer[ReturnStatusSize];
extern	uint_8	ReturnStatusBufferBack[ReturnStatusSize];



typedef struct{
		uint_8	Tx_size;				//------UART1发送总长度
		uint_8	Tx_count;			//------UART1发送当前个数
		uint_8	Tx_num;			//------UART1位
		uint_8	Tx_f:1;				//------UART1发送发送标志
		uint_8	Tx_yingda;			//------区别是应答或主动上传
		uint_8 	Tx_55_f:1;
		uint_8	Tx_55_sum;
		uint_8	Rx_size;				//------UART1接受总长度
		uint_8	Rx_count;			//------UART1接受当前个数
		uint_8	Rx_num;			//------UART1位
		uint_8	Rx_f:1;				//------UART1接受发送标志 
		uint_8	Rx_ff_f:1;			//------接受到 0xff标志
		uint_8	Rx_head_f:1;		//------连续接受到 2个0xff认为接受到头
		uint_8	Rx_error_f:1;		//-------ERROR_F
		uint_8	Rx_error_count;		//------接受错误次数		
		uint_8	Rx_wuxiao_f:1;		//-------ERROR_F
		uint_8	Rx_ok_f:1;			//-------ok_f
		uint_8	Rx_55_sum;			//-------ok_f
		uint_8	Rxtime;

			}WifiSendRepDeal_CB;
extern WifiSendRepDeal_CB WifiSendRepDeal;

typedef struct{
		uint_8	TimerCount;			//-------WIFI时间计时
		uint_8	send_count;			//-------连续发送次数
		uint_8 	repeater_timer;		//------重复发送命令间隔
		uint_8 	repeater1_timer;	//------1s重复
		uint_8	repeater1_f;			//------状态改变标志
		uint_8	repeater1_count;	//-------  发3次
		uint_8 	repeater2_timer;	//------1重复
		uint_8	repeater2_f;			//------状态改变标志
		uint_8	repeater2_count;	//-------  发3次
		uint_8 	alram_f:1;
		uint_8 	alramstop_f:1;
		uint_8 	alram_timer1;		//------报警时间1设置
		uint_8 	alram_timer2;		//------报警时间2设置
		uint_8	repeater_f:1;		//------状态返回应答
		uint_8	invalid_f:1;			//------无效命令
		uint_8	alarm_f:1;			//------报警
		uint_8	ACK_f:1;				//------确认
		uint_8 	huibao_f:1;			//------汇报
		uint_8 	shebeibanben_f:1;	//------设备版本
		uint_8 	save_f:1;			//------本机保存
		uint_8 	read_f:1;			//------本机读取本机信息

		
		uint_8 	shibiemachaxun_f:1;		//------识别码查询	
		uint_8 	chaxunbaojing_f:1;	//------查询报警应答。
		uint_8	chaxunzu_f:1;
		uint_8 	shezhishebeihuibao_f:1;	//------设置设备汇报
		uint_16	shebeihuibao_time;
		uint_8	work_R_f:1;			//------启动命令
		uint_8	WifiSet_T_f:1;		//------wifi设置命令

		uint_8 	WifiInit_T_f:1;		//-----恢复出厂设置命令

		uint_8 	wangluozhuangtai_f:1;	//------网络状态查询
		uint_8	wuxiao_f;				//------无效返回命令
		uint_8	wuxiaocanshu;		

		uint_8 	wifi_zijian_f:1;

		uint_8	wifi_zhuangtai_f:1;
		uint_8	wifiStatuse;
		uint_8	wifiSetTime;			//-----配置WIFI显示时间 30S
		

			}WifiRegisterSign_CB;
extern WifiRegisterSign_CB WifiRegisterSign;





typedef struct{
		uint_8	wifi_f:1;
		uint_8	SMARTLINK_Ok_f:1;				//--------绑定成功
		uint_8	CloudOk_f:1;						//--------云连接成功
		uint_8	RouterOk_f:1;					//--------路由连接成功
		uint_8	DataBufLong;					//--------状态数据长度
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





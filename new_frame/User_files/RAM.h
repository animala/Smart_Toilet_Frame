
/************************************************/
/*	RAM及FLAG定义				*/
/************************************************/
#ifndef RAM
#define RAM

#ifdef root								//仅在main.c中定义，其他.c中不要#define之
#define ramExtern 	 					//在main.c中加上"#define root", 则 ramExtern 被定义为空，
#else				
#define ramExtern extern				//在其他的.c文件中没有"#define root",也包含本文件时， ramExtern 被定义为"extern”，避免多重定义的问题。
#endif									//(因此在每个变量的定义前都必须加上 ramExtern



/*********************************************
常量定义
*********************************************/
#define 	u8_SOFTWARE_VERSION	1		//显示板软件版本号 
#define		u8_PROTOC0L_VERSION	2		//物联网协议版本号
#define		u8_FRAME_VERSION	0		//物联网框架协议版本号

#define		u8_Item_Code_H			0x01 			//物料编码 P73001577018 PDM:	
#define		u8_Item_Code_M			0x2C
#define		u8_Item_Code_L			0xDA

#define		U16_RAM_LOWLIMIT		0X00000
#define		U16_RAM_UPLIMIT		0X02FFF

/*********************************************
Eeprom constant define table
*********************************************/
#define     elengthequ          8
#define     videntifier1        0x6a
#define     eedelaytime         25     
#define     savepage            0x10    
#define     store_bytes_num     2
#define     BarLength           20
#define     BarLengthL          16
#define     BarLengthH          4
#define     BarSavePageL        0x40 
#define     BarSavePageH        0x50
#define     EeErrCheckAdr       0x5f
#define     DeviceWrite			0xA0				// 写
#define     DeviceRead			0xA1				// 读
#define     EeErrCheckByte		0xA5

#define			BAR_CODE_NUMBER		20
#define			BAR_CODE_SENDTIME	8
#define		TypeModeEquA0		 0xA0
#define     TypeModeEquA2       0xA2
#define     TypeModeEquA3       0xA3
#define		TypeModeEquA4		0xA4
#define	    TypeModeEquA5		0xA5
#define		TypeModeEquA6		0xA6
#define		TypeModeEquA7		0xA7
#define		TypeModeEquA8		0xA8
#define		TypeModeEquA9		0xA9
#define		TypeModeEquAB		0xAB
#define		TypeModeEquAC		0xAC
#define		TypeModeEquAD		0xAD
#define		TypeModeEquAE		0xAE
#define		TypeModeEquAF		0xAF
#define		TypeModeEquB4		0xB4
#define		TypeModeEquB0		0xB0

#define     EeData      		0x80			//电表数据存储的位置


enum{MemoryState,MemoryFanSpeedGrade,Symbol,MemoryMode,MemorySetTemp,MemorySetFanSpeed,MemoryAssis,NUM17,NUM18,NUM19,NUM1A,NUM1B,NUM1C,NUM1D,NUM1E,MemorySum};

#define			MemorySetTim_equ	200			//200*100MS=20000MS=20S   上电20S内可以通过遥控器开启关闭掉电记忆
#define			MemoryDisTim_equ  	50			//50*100ms=5000ms=5s			设置完掉电记忆要闪烁5秒
#define			MemorySaveAddress	0x10
#define			Symbol_equ			0x6A
#define			MemoryNUM			16			//  2014042103

#define		MACHINE_TYPE		1				//查询数据的类型
#define		FREMAXHAET			2
#define		FREMAXCOOL			3
#define		RFID				4				//查询ID号


#define		RF_Eeprom_Addr		0x70	//RF参数 E方入口地址
#define		EEPROM_DataLenth	0x0c	//RF参数 数据长度 

#define		SpeedSet_2S_equ		20     

              


#define CC1100_IOCFG2       0x00		// GDO2 output pin configuration
#define CC1100_IOCFG1       0x01        // GDO1 output pin configuration
#define CC1100_IOCFG0       0x02        // GDO0 output pin configuration
#define CC1100_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CC1100_SYNC1        0x04        // Sync word, high byte
#define CC1100_SYNC0        0x05        // Sync word, low byte
#define CC1100_PKTLEN       0x06        // Packet length
#define CC1100_PKTCTRL1     0x07        // Packet automation control
#define CC1100_PKTCTRL0     0x08        // Packet automation control
#define CC1100_ADDR         0x09        // Device address
#define CC1100_CHANNR       0x0A        // Channel number
#define CC1100_FSCTRL1      0x0B        // Frequency synthesizer control
#define CC1100_FSCTRL0      0x0C        // Frequency synthesizer control
#define CC1100_FREQ2        0x0D        // Frequency control word, high byte
#define CC1100_FREQ1        0x0E        // Frequency control word, middle byte
#define CC1100_FREQ0        0x0F        // Frequency control word, low byte
#define CC1100_MDMCFG4      0x10        // Modem configuration
#define CC1100_MDMCFG3      0x11        // Modem configuration
#define CC1100_MDMCFG2      0x12        // Modem configuration
#define CC1100_MDMCFG1      0x13        // Modem configuration
#define CC1100_MDMCFG0      0x14        // Modem configuration
#define CC1100_DEVIATN      0x15        // Modem deviation setting
#define CC1100_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define CC1100_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define CC1100_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define CC1100_FOCCFG       0x19        // Frequency Offset Compensation config
#define CC1100_BSCFG        0x1A        // Bit Synchronization configuration
#define CC1100_AGCCTRL2     0x1B        // AGC control
#define CC1100_AGCCTRL1     0x1C        // AGC control
#define CC1100_AGCCTRL0     0x1D        // AGC control
#define CC1100_WOREVT1      0x1E        // High byte Event 0 timeout
#define CC1100_WOREVT0      0x1F        // Low byte Event 0 timeout
#define CC1100_WORCTRL      0x20        // Wake On Radio control
#define CC1100_FREND1       0x21        // Front end RX configuration
#define CC1100_FREND0       0x22        // Front end TX configuration
#define CC1100_FSCAL3       0x23        // Frequency synthesizer calibration
#define CC1100_FSCAL2       0x24        // Frequency synthesizer calibration
#define CC1100_FSCAL1       0x25        // Frequency synthesizer calibration
#define CC1100_FSCAL0       0x26        // Frequency synthesizer calibration
#define CC1100_RCCTRL1      0x27        // RC oscillator configuration
#define CC1100_RCCTRL0      0x28        // RC oscillator configuration
#define CC1100_FSTEST       0x29        // Frequency synthesizer cal control
#define CC1100_PTEST        0x2A        // Production test
#define CC1100_AGCTEST      0x2B        // AGC test
#define CC1100_TEST2        0x2C        // Various test settings
#define CC1100_TEST1        0x2D        // Various test settings
#define CC1100_TEST0        0x2E        // Various test settings

// Strobe commands
#define CC1100_SRES         0x30        // Reset chip.
#define CC1100_SFSTXON      0x31        // Enable/calibrate freq synthesizer
#define CC1100_SXOFF        0x32        // Turn off crystal oscillator.
#define CC1100_SCAL         0x33        // Calibrate freq synthesizer & disable
#define CC1100_SRX          0x34        // Enable RX.
#define CC1100_STX          0x35        // Enable TX.
#define CC1100_SIDLE        0x36        // Exit RX / TX
#define CC1100_SAFC         0x37        // AFC adjustment of freq synthesizer
#define CC1100_SWOR         0x38        // Start automatic RX polling sequence
#define CC1100_SPWD         0x39        // Enter pwr down mode when CSn goes hi
#define CC1100_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CC1100_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CC1100_SWORRST      0x3C        // Reset real time clock.
#define CC1100_SNOP         0x3D        // No operation.

// Status registers
#define CC1100_PARTNUM      0x30        // Part number
#define CC1100_VERSION      0x31        // Current version number
#define CC1100_FREQEST      0x32        // Frequency offset estimate
#define CC1100_LQI          0x33        // Demodulator estimate for link quality
#define CC1100_RSSI         0x34        // Received signal strength indication
#define CC1100_MARCSTATE    0x35        // Control state machine state
#define CC1100_WORTIME1     0x36        // High byte of WOR timer
#define CC1100_WORTIME0     0x37        // Low byte of WOR timer
#define CC1100_PKTSTATUS    0x38        // Current GDOx status and packet status
#define CC1100_VCO_VC_DAC   0x39        // Current setting from PLL cal module
#define CC1100_TXBYTES      0x3A        // Underflow and # of bytes in TXFIFO
#define CC1100_RXBYTES      0x3B        // Overflow and # of bytes in RXFIFO
#define CC1100_NUM_RXBYTES  0x7F        // Mask "# of bytes" field in _RXBYTES

#define	RF_SYNC_CREATLINK1		0xA5	//对码接收同步字
#define	RF_SYNC_CREATLINK0		0xB3

#define	RF_SYNC_HOST_NORMAL1	0xB5	//主控常规接收同步字
#define	RF_SYNC_HOST_NORMAL0	0x5A
#define RF_GDO4RX				0x06	//GDO配置为RX 接收到同步字时变换，数据接收完毕反变换

// Other memory locations
#define CC1100_PATABLE      0x3E
#define CC1100_TXFIFO       0x3F
#define CC1100_RXFIFO       0x3F

// Masks for appended status bytes
#define CC1100_LQI_RX       0x01        // Position of LQI byte
#define CC1100_CRC_OK       0x80        // Mask "CRC_OK" bit within LQI byte

// Definitions to support burst/single access:
#define CC1100_WRITE_BURST  0x40
#define CC1100_READ_SINGLE  0x80
#define CC1100_READ_BURST   0xC0

#define RF_CHANNEL				21		//通信频道    
#define	RF_HOST_NORMALADDR		0xAC	//主控常规接收地址

#define	RF_SYNC_GUESTCTRL1		0xE6	//遥控控制返回同步字
#define	RF_SYNC_GUESTCTRL0		0xE7	

#define 	RF_DATALENTH		20		//数据包长度
#define 	RF_PKTLENTH			29		//数据包长度
#define 	RF_GDO4TX			0x06	//GDO配置为TX
#define 	RF_PKTLEN_SHORT		30		//短指令包长度 30字节


#define	AIRCONDITIONER_TYPE		0x03	//空调器器类型，


#define	POWER_FOR_CREATLINK_STEP0	0x15	//対码第一阶段功率	-15dBmW
#define	POWER_FOR_CREATLINK_STEP1	0x12	//対码第一阶段功率	5dBmW	
#define	POWER_FOR_WORK				0x10	//正常工作功率		10dBmW

#define	CreateLinkTotalTime		20
#define	CreateLinkFinshTime		3


#define	RF_code_db	0x15				//对码功率



#define     hleadcodel        3080             //tolerance 30%
#define     hleadcodeh        5720             //
#define     OneCode           2160             //tolerance 25%
#define     onecodel          1624             //
#define     onecodeh          2704             //
#define     ZeroCode          1080             //tolerance 30%
#define     zerocodel         760              //
#define     zerocodeh         1400             //
#define     SepCode           5760             //tolerance 20%
#define     sepcodel          4608             //
#define     sepcodeh          6912             //


#define		RFTimeEqu		50
#define     SpeedSetTimeequ   80    //80*0.1ms=8s
#define     SpeedSet_1S_equ	  20	 


#define     errkindmax    32
#define     runkindmax    16
#define	    Error_PA_EQU  22


#define		down_key_equ	0x01
#define		up_key_equ		0x02
#define		speed_key_equ	0x04
#define		mode_key_equ	0x08	
#define		FanLead_equ		0x10	
#define		cleankey_equ	0x03
#define		testrun_key_equ	0x18
#define		keywifi_equ		0x0A
#define		lock_key_equ	0x06
#define		wifi_resume_equ 	0x11		//xxh

#define     TypeModeEqu       0xA2

#define     SmileFaceTotalFrame		29

#define	b0000_0000	0x00	//	0
#define	b0000_0001	0x01	//	1
#define	b0000_0010	0x02	//	2
#define	b0000_0011	0x03	//	3
#define	b0000_0100	0x04	//	4
#define	b0000_0101	0x05	//	5
#define	b0000_0110	0x06	//	6
#define	b0000_0111	0x07	//	7
#define	b0000_1000	0x08	//	8
#define	b0000_1001	0x09	//	9
#define	b0000_1010	0x0A	//	10
#define	b0000_1011	0x0B	//	11
#define	b0000_1100	0x0C	//	12
#define	b0000_1101	0x0D	//	13
#define	b0000_1110	0x0E	//	14
#define	b0000_1111	0x0F	//	15
#define	b0001_0000	0x10	//	16
#define	b0001_0001	0x11	//	17
#define	b0001_0010	0x12	//	18
#define	b0001_0011	0x13	//	19
#define	b0001_0100	0x14	//	20
#define	b0001_0101	0x15	//	21
#define	b0001_0110	0x16	//	22
#define	b0001_0111	0x17	//	23
#define	b0001_1000	0x18	//	24
#define	b0001_1001	0x19	//	25
#define	b0001_1010	0x1A	//	26
#define	b0001_1011	0x1B	//	27
#define	b0001_1100	0x1C	//	28
#define	b0001_1101	0x1D	//	29
#define	b0001_1110	0x1E	//	30
#define	b0001_1111	0x1F	//	31
#define	b0010_0000	0x20	//	32
#define	b0010_0001	0x21	//	33
#define	b0010_0010	0x22	//	34
#define	b0010_0011	0x23	//	35
#define	b0010_0100	0x24	//	36
#define	b0010_0101	0x25	//	37
#define	b0010_0110	0x26	//	38
#define	b0010_0111	0x27	//	39
#define	b0010_1000	0x28	//	40
#define	b0010_1001	0x29	//	41
#define	b0010_1010	0x2A	//	42
#define	b0010_1011	0x2B	//	43
#define	b0010_1100	0x2C	//	44
#define	b0010_1101	0x2D	//	45
#define	b0010_1110	0x2E	//	46
#define	b0010_1111	0x2F	//	47
#define	b0011_0000	0x30	//	48
#define	b0011_0001	0x31	//	49
#define	b0011_0010	0x32	//	50
#define	b0011_0011	0x33	//	51
#define	b0011_0100	0x34	//	52
#define	b0011_0101	0x35	//	53
#define	b0011_0110	0x36	//	54
#define	b0011_0111	0x37	//	55
#define	b0011_1000	0x38	//	56
#define	b0011_1001	0x39	//	57
#define	b0011_1010	0x3A	//	58
#define	b0011_1011	0x3B	//	59
#define	b0011_1100	0x3C	//	60
#define	b0011_1101	0x3D	//	61
#define	b0011_1110	0x3E	//	62
#define	b0011_1111	0x3F	//	63
#define	b0100_0000	0x40	//	64
#define	b0100_0001	0x41	//	65
#define	b0100_0010	0x42	//	66
#define	b0100_0011	0x43	//	67
#define	b0100_0100	0x44	//	68
#define	b0100_0101	0x45	//	69
#define	b0100_0110	0x46	//	70
#define	b0100_0111	0x47	//	71
#define	b0100_1000	0x48	//	72
#define	b0100_1001	0x49	//	73
#define	b0100_1010	0x4A	//	74
#define	b0100_1011	0x4B	//	75
#define	b0100_1100	0x4C	//	76
#define	b0100_1101	0x4D	//	77
#define	b0100_1110	0x4E	//	78
#define	b0100_1111	0x4F	//	79
#define	b0101_0000	0x50	//	80
#define	b0101_0001	0x51	//	81
#define	b0101_0010	0x52	//	82
#define	b0101_0011	0x53	//	83
#define	b0101_0100	0x54	//	84
#define	b0101_0101	0x55	//	85
#define	b0101_0110	0x56	//	86
#define	b0101_0111	0x57	//	87
#define	b0101_1000	0x58	//	88
#define	b0101_1001	0x59	//	89
#define	b0101_1010	0x5A	//	90
#define	b0101_1011	0x5B	//	91
#define	b0101_1100	0x5C	//	92
#define	b0101_1101	0x5D	//	93
#define	b0101_1110	0x5E	//	94
#define	b0101_1111	0x5F	//	95
#define	b0110_0000	0x60	//	96
#define	b0110_0001	0x61	//	97
#define	b0110_0010	0x62	//	98
#define	b0110_0011	0x63	//	99
#define	b0110_0100	0x64	//	100
#define	b0110_0101	0x65	//	101
#define	b0110_0110	0x66	//	102
#define	b0110_0111	0x67	//	103
#define	b0110_1000	0x68	//	104
#define	b0110_1001	0x69	//	105
#define	b0110_1010	0x6A	//	106
#define	b0110_1011	0x6B	//	107
#define	b0110_1100	0x6C	//	108
#define	b0110_1101	0x6D	//	109
#define	b0110_1110	0x6E	//	110
#define	b0110_1111	0x6F	//	111
#define	b0111_0000	0x70	//	112
#define	b0111_0001	0x71	//	113
#define	b0111_0010	0x72	//	114
#define	b0111_0011	0x73	//	115
#define	b0111_0100	0x74	//	116
#define	b0111_0101	0x75	//	117
#define	b0111_0110	0x76	//	118
#define	b0111_0111	0x77	//	119
#define	b0111_1000	0x78	//	120
#define	b0111_1001	0x79	//	121
#define	b0111_1010	0x7A	//	122
#define	b0111_1011	0x7B	//	123
#define	b0111_1100	0x7C	//	124
#define	b0111_1101	0x7D	//	125
#define	b0111_1110	0x7E	//	126
#define	b0111_1111	0x7F	//	127
#define	b1000_0000	0x80	//	128
#define	b1000_0001	0x81	//	129
#define	b1000_0010	0x82	//	130
#define	b1000_0011	0x83	//	131
#define	b1000_0100	0x84	//	132
#define	b1000_0101	0x85	//	133
#define	b1000_0110	0x86	//	134
#define	b1000_0111	0x87	//	135
#define	b1000_1000	0x88	//	136
#define	b1000_1001	0x89	//	137
#define	b1000_1010	0x8A	//	138
#define	b1000_1011	0x8B	//	139
#define	b1000_1100	0x8C	//	140
#define	b1000_1101	0x8D	//	141
#define	b1000_1110	0x8E	//	142
#define	b1000_1111	0x8F	//	143
#define	b1001_0000	0x90	//	144
#define	b1001_0001	0x91	//	145
#define	b1001_0010	0x92	//	146
#define	b1001_0011	0x93	//	147
#define	b1001_0100	0x94	//	148
#define	b1001_0101	0x95	//	149
#define	b1001_0110	0x96	//	150
#define	b1001_0111	0x97	//	151
#define	b1001_1000	0x98	//	152
#define	b1001_1001	0x99	//	153
#define	b1001_1010	0x9A	//	154
#define	b1001_1011	0x9B	//	155
#define	b1001_1100	0x9C	//	156
#define	b1001_1101	0x9D	//	157
#define	b1001_1110	0x9E	//	158
#define	b1001_1111	0x9F	//	159
#define	b1010_0000	0xA0	//	160
#define	b1010_0001	0xA1	//	161
#define	b1010_0010	0xA2	//	162
#define	b1010_0011	0xA3	//	163
#define	b1010_0100	0xA4	//	164
#define	b1010_0101	0xA5	//	165
#define	b1010_0110	0xA6	//	166
#define	b1010_0111	0xA7	//	167
#define	b1010_1000	0xA8	//	168
#define	b1010_1001	0xA9	//	169
#define	b1010_1010	0xAA	//	170
#define	b1010_1011	0xAB	//	171
#define	b1010_1100	0xAC	//	172
#define	b1010_1101	0xAD	//	173
#define	b1010_1110	0xAE	//	174
#define	b1010_1111	0xAF	//	175
#define	b1011_0000	0xB0	//	176
#define	b1011_0001	0xB1	//	177
#define	b1011_0010	0xB2	//	178
#define	b1011_0011	0xB3	//	179
#define	b1011_0100	0xB4	//	180
#define	b1011_0101	0xB5	//	181
#define	b1011_0110	0xB6	//	182
#define	b1011_0111	0xB7	//	183
#define	b1011_1000	0xB8	//	184
#define	b1011_1001	0xB9	//	185
#define	b1011_1010	0xBA	//	186
#define	b1011_1011	0xBB	//	187
#define	b1011_1100	0xBC	//	188
#define	b1011_1101	0xBD	//	189
#define	b1011_1110	0xBE	//	190
#define	b1011_1111	0xBF	//	191
#define	b1100_0000	0xC0	//	192
#define	b1100_0001	0xC1	//	193
#define	b1100_0010	0xC2	//	194
#define	b1100_0011	0xC3	//	195
#define	b1100_0100	0xC4	//	196
#define	b1100_0101	0xC5	//	197
#define	b1100_0110	0xC6	//	198
#define	b1100_0111	0xC7	//	199
#define	b1100_1000	0xC8	//	200
#define	b1100_1001	0xC9	//	201
#define	b1100_1010	0xCA	//	202
#define	b1100_1011	0xCB	//	203
#define	b1100_1100	0xCC	//	204
#define	b1100_1101	0xCD	//	205
#define	b1100_1110	0xCE	//	206
#define	b1100_1111	0xCF	//	207
#define	b1101_0000	0xD0	//	208
#define	b1101_0001	0xD1	//	209
#define	b1101_0010	0xD2	//	210
#define	b1101_0011	0xD3	//	211
#define	b1101_0100	0xD4	//	212
#define	b1101_0101	0xD5	//	213
#define	b1101_0110	0xD6	//	214
#define	b1101_0111	0xD7	//	215
#define	b1101_1000	0xD8	//	216
#define	b1101_1001	0xD9	//	217
#define	b1101_1010	0xDA	//	218
#define	b1101_1011	0xDB	//	219
#define	b1101_1100	0xDC	//	220
#define	b1101_1101	0xDD	//	221
#define	b1101_1110	0xDE	//	222
#define	b1101_1111	0xDF	//	223
#define	b1110_0000	0xE0	//	224
#define	b1110_0001	0xE1	//	225
#define	b1110_0010	0xE2	//	226
#define	b1110_0011	0xE3	//	227
#define	b1110_0100	0xE4	//	228
#define	b1110_0101	0xE5	//	229
#define	b1110_0110	0xE6	//	230
#define	b1110_0111	0xE7	//	231
#define	b1110_1000	0xE8	//	232
#define	b1110_1001	0xE9	//	233
#define	b1110_1010	0xEA	//	234
#define	b1110_1011	0xEB	//	235
#define	b1110_1100	0xEC	//	236
#define	b1110_1101	0xED	//	237
#define	b1110_1110	0xEE	//	238
#define	b1110_1111	0xEF	//	239
#define	b1111_0000	0xF0	//	240
#define	b1111_0001	0xF1	//	241
#define	b1111_0010	0xF2	//	242
#define	b1111_0011	0xF3	//	243
#define	b1111_0100	0xF4	//	244
#define	b1111_0101	0xF5	//	245
#define	b1111_0110	0xF6	//	246
#define	b1111_0111	0xF7	//	247
#define	b1111_1000	0xF8	//	248
#define	b1111_1001	0xF9	//	249
#define	b1111_1010	0xFA	//	250
#define	b1111_1011	0xFB	//	251
#define	b1111_1100	0xFC	//	252
#define	b1111_1101	0xFD	//	253
#define	b1111_1110	0xFE	//	254
#define	b1111_1111	0xFF	//	255



#define		DryMode_Equ		1
#define		HeatMode_Equ	2
#define		CoolMode_Equ	3
#define		FanMode_Equ		4
#define		AutoMode_Equ	5



//#define		NumN			26
//#define		NumA			15
//#define		NumE			12
//#define		NumP			13
//#define		NumF			18
//#define		NumL			19
//#define		NumT			25
//#define		Numr			27
//#define		Numb			16


#define		Num0			0xFC	//0b11111100			//0   ABCDEFGH
#define		Num1			0x60	//0b01100000			//1   
#define		Num2            0xDA	//0b11011010			//2   
#define		Num3            0xF2	//0b11110010        //3   
#define		Num4            0x66	//0b01100110        //4   
#define		Num5            0xB6	//0b10110110        //5
#define		Num6            0xBE	//0b10111110        //6
#define		Num7            0xE0	//0b11100000        //7
#define		Num8            0xFE	//0b11111110        //8
#define		Num9            0xF6	//0b11110110        //9
#define		NumBLANK        0x00    //0b00000000    //nothing  10              
#define		NumMinus        0x02    //0b00000010    //-        11           
#define		NumE            0x9E	//0b10011110        //E        12                  
#define		NumP            0xCE	//0b11001110        //p        13
#define		NumD            0x7A	//0b01111010        //d        14
#define		NumA            0xEE	//0b11101110        //A        15
#define		NumB            0x3E	//0b00111110        //b        16
#define		NumC            0x9C	//0b10011100        //c        17
#define		NumF            0x8E	//0b10001110        //F        18 
#define		NumL            0x1C	//0b00011100        //L        19
#define		NumMinusOne     0x62	//0b01100010        //-|       20
#define		Numu            0x38	//0b00111000				 //u        21
#define		NumT            0x8C	//0b10001100				 //T				22 
#define		NumR            0x0A	//0b00001010				 //r				23
#define		NumO            0x3A	//0b00111010				 //o				24
#define		NumN            0x2A	//0b00101010				 //n				25 
#define		NumU            0x7C	//0b01111100				 //U				26
#define		NumH            0x6E	//0b01101110				 //H				27
#define		NumS            0xB6	//0b10110110
#define		Numi            0x20	//0b00100000

#define		NumBLANKTab		10
#define		DispMinus        11 
#define		DispE            12
#define		DispP            13
#define		DispL            19
#define		DispD            14
#define		DispA            15
#define		DispB            16
#define		DispC            17
#define		DispF           18 
#define		DispL19
#define		DispMinusOne    20
#define		Dispu            21
#define		DispT           22 
#define		DispR           23
#define		DispO           24
#define		DispN           25 
#define		DispU           26
#define		DispH           27
#define		Dispi           28

#define		speed_equ		1
#define		duty_equ		0

#define     ForceKeyEqu         1                  //强制按键
#define     CleanKeyEqu         2                  //清洁按键
#define     NoKeyEqu            0                  //没有按键按下


#define		Led_off_equ		0
#define		Led_orange_equ	1
#define		Led_blue_equ	2

#define		lightdelay_equ	6
#define		brightness_que	2400

#define		dry_10min_equ	1
#define		dry_3min_equ	2
#define		dry_30s_equ		3
#define		dry_10s_equ		4


/*********************************************/

#define 	clrb(x,y) 	(x&=~(1<<y))  	//位清0
#define 	setb(x,y) 	(x|= (1<<y))  	//位置1
#define 	getb(x,y) 	(x&(1<<y))    	//位判断
#define 	xorb(x,y) 	(x^=(1<<y))   	//位取反


#define     Delay1Us()      asm("nop"); asm("nop"); asm("nop"); asm("nop")
#define     NOP()           asm("nop")

#ifdef 		root

const	uchar BuzTimeTAB[]={0,0,0,0,0,0,0,0,1,0,        //无用数据
	                        4,6,4,6,4,6,4,50,1,0,    	//上电蜂鸣器时间表  1,1表示跳过这一步; 1,0代表发声结束                           
                            1,1,3,4,3,4,3,50,1,0,       //开机蜂鸣器时间表
                            1,1,3,4,3,4,3,50,1,0,       //关机蜂鸣器时间表
                            1,1,1,1,1,1,4,50,1,0,       //一般蜂鸣器时间表
                            1,1,2,4,2,3,2,50,1,0,       //上升蜂鸣器时间表
                            1,1,2,4,2,3,2,50,1,0,     	//下降蜂鸣器时间表
                            3,4,3,4,3,4,3,50,1,0,};     //对码蜂鸣器时间表  3/4拍  	
 
const	uchar BuzFreqTAB[]={0,0,0,0,                   	//无用数据
	                        69,61,53,45,               	//上电蜂鸣器频率表
	                        0,61,57,53,                	//开机蜂鸣器频率表
	                        0,45,53,61,                	//关机蜂鸣器频率表
                            0,0,0,53,                  	//一般蜂鸣器频率表       
                            0,77,69,61,                	//上升蜂鸣器频率表     
                            0,61,69,77,             	//下降蜂鸣器频率表 
                            85,75,65,55,}; 		  		//对码蜂鸣器频率表    7

const	uchar SetTempTAB[]={                     
                           	0x00,    		//17
                           	0x01,    		//18
                           	0x03,    		//19
                           	0x02,    		//20
                           	0x06,    		//21
                           	0x07,    		//22
                           	0x05,    		//23
                           	0x04,    		//24
							0x0C,    		//25
                           	0x0D,    		//26
                           	0x09,    		//27
                           	0x08,    		//28
                           	0x0A,    		//29
                           	0x0B,    		//30
                           	0x0E,};  		//送风  
                           	
//const uchar laugh_enable[11] ={  0xff,0xff,0xfb,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0x01,};
const uchar laugh_enable[11] ={  0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x01,};

const uchar KindTAB[]={	
	                 0x01,
	                 0x02,                                           
                     0x04,
                     0x08,
                     0x10,                      
                     0x20,
                     0x40,                      
                     0x80,
                     };
const uchar ucRecAfspeedTAB[]={
	                          0,        //Running fanspeed: stop 
	                          2,        //Running fanspeed: high
	                          4,        //Running fanspeed: mid
	                          1,        //Running fanspeed: low
	                          3,        //Running fanspeed: strong
	                          5,        //Running fanspeed: sleep
	                          };

const  uchar  ucdefaultPAtable[8] = {	0xc0,	0xc8,	0x84,	0x60,	0x34,	0x1d,	0x0e,	0x12};		//默认PA表格
//										10		7		5		0		-10		-15		-20		-30			dbmW
	

const uchar crc8_854_table[] =								//  2014042601
{
	0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
	157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
	35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
	190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
	70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
	219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
	101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
	248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
	140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
	17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
	175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
	50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
	202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
	87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
	233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
	116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};


const	unsigned char  ucPQTempTab[256] = { //温度值	    AD值	温度值	电阻值
											48,				//0		-48
											48,				//1		-48
											33,				//2		-33
											25,				//3		-25
											20,				//4		-20		542.7
											16,				//5		-16		430.5
											13,				//6		-13		363.3
											10,				//7		-10		307.7
											7,				//8		-7 		261.4
											4,				//9		-4 		222.8
											2,				//10	-2 		200.7
											0,				//11	0  		180.9
											2,				//12	2  		163.3
											3,				//13	3  		155.2
											5,				//14	5  		140.4
											6,				//15	6  		133.5
											8,				//16	8  		121
											9,				//17	9  		115.2
											11,				//18	11 		104.6
											12,				//19	12 		99.69
											13,				//20	13 		95.05
											14,				//21	14 		90.66
											15,				//22	15 		86.49
											16,				//23	16 		82.54
											17,				//24	17 		78.79
											18,				//25	18 		75.24
											19,				//26	19 		71.86
											20,				//27	20 		68.66
											21,				//28	21 		65.62
											22,				//29	22 		62.73
											23,				//30	23 		59.98
											24,				//31	24 		57.37
											24,				//32	24
											25,				//33	25 		54.89
											26,				//34	26 		52.53
											27,				//35	27 		50.28
											27,				//36	27
											28,				//37	28 		48.14
											29,				//38	29 		46.11
											30,				//39	30 		44.17
											30,				//40	30
											31,				//41	31 		42.33
											32,				//42	32 		40.57
											32,				//43	32
											33,				//44	33 		38.89
											34,				//45	34 		37.3
											34,				//46	34
											35,				//47	35 		35.78
											36,				//48	36 		34.32
											36,				//49	36
											37,				//50	37 		32.94
											37,				//51	37
											38,				//52	38 		31.62
											39,				//53	39 		30.36
											39,				//54	39
											40,				//55	40 		29.15
											40,				//56	40
											41,				//57	41 		28
											41,				//58	41
											42,				//59	42 		26.9
											42,				//60	42
											43,				//61	43 		25.86
											44,				//62	44 		24.85
											44,				//63	44
											45,				//64	45		23.89
											45,				//65	45
											46,				//66	46		22.89
											46,				//67	46
											47,				//68	47		22.1
											47,				//69	47
											48,				//70	48		21.26
											48,				//71	48
											49,				//72	49		20.46
											49,				//73	49
											50,				//74	50		19.69
											50,				//75	50
											51,				//76	51		18.96
											51,				//77	51
											52,				//78	52		18.26
											52,				//79	52
											53,				//80	53		17.58
											53,				//81	53
											54,				//82	54		16.94
											54,				//83	54
											55,				//84	55		16.32
											55,				//85	55
											56,				//86	56		15.73
											56,				//87	56
											56,				//88	56
											57,				//89	57		15.16
											57,				//90	57
											58,				//91	58		14.62
											58,				//92	58
											59,				//93	59		14.09
											59,				//94	59
											60,				//95	60		13.59
											60,				//96	60
											61,				//97	61		13.11
											61,				//98	61
											62,				//99	62		12.65
											62,				//100	62
											63,				//101	63		12.21
											63,				//102	63
											63,				//103	63
											64,				//104	64		11.79
											64,				//105	64
											65,				//106	65		11.38
											65,				//107	65
											66,				//108	66		10.99
											66,				//109	66
											67,				//110	67		10.61
											67,				//111	67
											68,				//112	68		10.25
											68,				//113	68
											69,				//114	69		9.902
											69,				//115	69
											69,				//116	69
											70,				//117	70		9.569
											70,				//118	70
											71,				//119	71		9.248
											71,				//120	71
											72,				//121	72		8.94
											72,				//122	72
											73,				//123	73		8.643
											73,				//124	73
											74,				//125	74		8.358
											74,				//126	74
											75,				//127	75		8.084
											75,				//128	75
											76,				//129	76 		7.82
											76,				//130	76
											76,				//131	76
											77,				//132	77 		7.566
											77,				//133	77
											78,				//134	78 		7.321
											78,				//135	78
											79,				//136	79 		7.086
											79,				//137	79
											80,				//138	80 		6.859
											80,				//139	80
											81,				//140	81 		6.641
											81,				//141	81
											82,				//142	82 		6.43
											82,				//143	82
											83,				//144	83 		6.228
											83,				//145	83
											84,				//146	84 		6.033
											84,				//147	84
											85,				//148	85 		5.844
											85,				//149	85
											86,				//150	86 		5.663
											86,				//151	86
											87,				//152	87 		5.488
											87,				//153	87
											88,				//154	88 		5.32
											88,				//155	88
											89,				//156	89 		5.157
											90,				//157	90 		5
											90,				//158	90
											91,				//159	91 		4.849
											91,				//160	91
											92,				//161	92 		4.703
											92,				//162	92
											93,				//163	93 		4.562
											93,				//164	93
											94,				//165	94 		4.426
											95,				//166	95 		4.294
											95,				//167	95
											96,				//168	96 		4.167
											96,				//169	96
											97,				//170	97 		4.045
											98,				//171	98 		3.927
											98,				//172	98
											99,				//173	99 		3.812
											99,				//174	99
											100,			//175	100		3.702
											101,			//176	101		3.595
											101,			//177	101
											102,			//178	102		3.492
											103,			//179	103		3.392
											103,			//180	103
											104,			//181	104		3.296
											105,			//182	105		3.203
											105,			//183	105
											106,			//184	106		3.113
											107,			//185	107		3.025
											107,			//186	107
											108,			//187	108		2.941
											109,			//188	109		2.86
											109,			//189	109
											110,			//190	110		2.781
											111,			//191	111		2.704
											112,			//192	112		2.63
											112,			//193	112
											113,			//194	113		2.559
											114,			//195	114		2.489
											115,			//196	115		2.422
											116,			//197	116		2.357
											116,			//198	116
											117,			//199	117		2.294
											118,			//200	118		2.233
											119,			//201	119		2.174
											120,			//202	120		2.117
											121,			//203	121		2.061
											122,			//204	122		2.007
											123,			//205	123		1.955
											124,			//206	124		1.905
											125,			//207	125		1.856
											126,			//208	126		1.808
											127,			//209	127		1.762
											128,			//210	128		1.717
											129,			//211	129		1.674
											130,			//212	130		1.632
											135,			//213	135
											136,			//214	136
											137,			//215	137
											138,			//216	138
											140,			//217	140
											141,			//218	141
											142,			//219	142
											144,			//220	144
											145,			//221	145
											147,			//222	147
											148,			//223	148
											150,			//224	150
											152,			//225	152
											153,			//226	153
											155,			//227	155
											157,			//228	157
											159,			//229	159
											161,			//230	161
											163,			//231	163
											165,			//232	165
											168,			//233	168
											170,			//234	170
											173,			//235	173
											175,			//236	175
											178,			//237	178
											181,			//238	181
											185,			//239	185
											188,			//240	188
											192,			//241	192
											196,			//242	196
											201,			//243	201
											206,			//244	206
											211,			//245	211
											218,			//246	218
											225,			//247	225
											233,			//248	233
											243,			//249	243
											254,			//250	254
											255,			//251	269
											255,			//252	289
											255,			//253	318
											255,			//254	367
											255				//255	506
									   };	

const uchar num[] = {	DispA,
						DispB,
						DispC,
						DispD,
						DispE,
						DispF};
	
const	uchar SevenSegTAB[]={                                                
                            0xFC,	//0b11111100,        //0   ABCDEFGH
                            0x60,	//0b01100000,        //1   
                            0xDA,	//0b11011010,        //2   
                            0xF2,	//0b11110010,        //3   
                            0x66,	//0b01100110,        //4   
                            0xB6,	//0b10110110,        //5
                            0xBE,	//0b10111110,        //6
                            0xE0,	//0b11100000,        //7
                            0xFE,	//0b11111110,        //8
                            0xF6,	//0b11110110,        //9
                            0x00,	//0b00000000,        //nothing  10              
                            0x02,	//0b00000010,        //-        11           
                            0x9E,	//0b10011110,        //E        12                  
                            0xCE,	//0b11001110,        //p        13
                            0x7A,	//0b01111010,        //d        14
                            0xEE,	//0b11101110,        //A        15
                            0x3E,	//0b00111110,        //b        16
                            0x9C,	//0b10011100,        //c        17
                            0x8E,	//0b10001110,        //F        18 
                            0x1C,	//0b00011100,        //L        19
                            0x62,	//0b01100010,        //-|       20
                            0x38,	//0b00111000,				 //u        21
                            0x8C,	//0b10001100,				 //T				22 
                            0x0A,	//0b00001010,				 //r				23
                            0x3A,	//0b00111010,				 //o				24
                            0x2A,	//0b00101010,				 //n				25 
                            0x7C,	//0b01111100,				 //U				26
                            0x6E,	//0b01101110,				 //H				27
                        	0x20};	//0b00100000,}; 		 	//i				28 	 
                            
const	uchar	ucLEDH16_10[]=
{
	0x00,
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07,
	0x08,
	0x09,
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x20,
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x30,
	0x31,
	0x32,
	0x33,
	0x34,
	0x35,
	0x36,
	0x37,
	0x38,
	0x39,
	0x40,
	0x41,
	0x42,
	0x43,
	0x44,
	0x45,
	0x46,
	0x47,
	0x48,
	0x49,
	0x50,
	0x51,
	0x52,
	0x53,
	0x54,
	0x55,
	0x56,
	0x57,
	0x58,
	0x59,
	0x60,
	0x61,
	0x62,
	0x63,
	0x64,
	0x65,
	0x66,
	0x67,
	0x68,
	0x69,
	0x70,
	0xBB		//80 显示空
};                            
                            
	                                                      
#else 

extern  const 	uchar number_speed[][21];
extern 	const	U8 BuzTimeTAB[];
extern 	const	U8 BuzFreqTAB[];
extern 	const	U8 SetTempTAB[];
extern  const 	uchar laugh_enable[11];
extern  const	uchar KindTAB[];                 
extern  const 	uchar ucRecAfspeedTAB[];
extern	const  	uchar  ucdefaultPAtable[8]; 
extern	const	uchar SevenSegTAB[29];
extern  const 	uchar num[];
extern	const 	uchar laugh_change_time[SmileFaceTotalFrame];
extern	const 	uchar laugh_Frame_Cnt_outside[SmileFaceTotalFrame];
extern	const 	uchar laugh_Frame_Cnt_inside[SmileFaceTotalFrame];  
extern	const 	uchar laugh_duty_outside[11][36]; 
extern	const 	uchar laugh_duty_inside[4][43];
extern	const 	uchar laugh_speed_outside[3][36];
extern	const 	uchar laugh_speed_inside[7][43];
extern	const 	uchar 	PowerTimeTable[];
extern	const	unsigned char  ucPQTempTab[256];
extern	const 	uchar 	crc8_854_table[];

//extern	const 	uchar 	Power_Cnt_InsideDutyTable[];
//extern	const 	uchar	Power_Cnt_InsidespeedTable[];
//
//extern	const 	uchar	Power_Cnt_outsideDutyTable[];
//extern	const 	uchar	Power_Cnt_outsidespeedTable[];

//extern	const 	uchar 	power_speed_outside[][36];              
//extern	const 	uchar 	power_speed_inside[][43]; 
//            
//extern	const 	uchar 	power_duty_inside[][43];  
//extern	const 	uchar 	power_duty_outside[][36];  
//  
//extern	const 	uchar 	Wet_change_time[];  
//extern	const 	uchar 	Wet_Frame_Cnt_duty[];
//extern	const 	uchar 	heat_change_time[];
//extern	const 	uchar 	heat_Frame_Cnt_duty[];
//extern	const 	uchar 	heat_Frame_Cnt_speed[];
//      
//extern	const 	uchar 	cool_change_time[];
//extern	const 	uchar 	cool_Frame_Cnt_duty[];
//extern	const 	uchar 	cool_Frame_Cnt_speed[];     
  
//extern	const 	uchar 	fan_change_time[];
//extern	const 	uchar 	fan_Frame_Cnt_duty[];
//extern	const 	uchar 	fan_Frame_Cnt_speed[];  
//     
//extern	const 	uchar 	Aoto_change_time[];
//extern	const 	uchar 	Aoto_Frame_Cnt_duty[];
//extern	const 	uchar 	Aoto_Frame_Cnt_speed[];     
//                     
//extern	const 	uchar 	midFan_Frame_Cnt_speed[];                    
                     
//extern	const 	uchar	aotoFan_Frame_Cnt_speed[];                     
//   
//extern	const 	uchar LowFan_Frame_Cnt_speed[];   
//      
//extern	const 	uchar highFan_Frame_Cnt_speed[];      
//        
//extern	const 	uchar add_speed_Time[]; 
//extern	const 	uchar add_speed_duty[];    
                  
//extern	const 	uchar	fanlead_time[];
//extern	const 	uchar	wetmode_speed_duty[][36];
//extern	const	uchar  	dec_speed_table[][36];  
//extern	const 	uchar	inc_speed_table[][36];   
                     
#endif 
#endif





/*********************************************************************
变量定义
*********************************************************************/    

/**** 此处定义FLAG可位选址 ****/
ramExtern TYPE_BYTE		FLAG0;
ramExtern TYPE_BYTE		FLAG1;
ramExtern TYPE_BYTE		FLAG2;
ramExtern TYPE_BYTE		FLAG3;
ramExtern TYPE_BYTE		FLAG4;
ramExtern TYPE_BYTE		FLAG5;
ramExtern TYPE_BYTE		FLAG6;
ramExtern TYPE_BYTE		FLAG7;
ramExtern TYPE_BYTE		FLAG8;
ramExtern TYPE_BYTE		FLAG9;	
ramExtern TYPE_BYTE		FLAGA;
ramExtern TYPE_BYTE		FLAGB;
ramExtern TYPE_BYTE		FLAGC;
ramExtern TYPE_BYTE		FLAGD;
ramExtern TYPE_BYTE		FLAGE;
ramExtern TYPE_BYTE		FLAGF;
ramExtern TYPE_BYTE		FLAGG;
ramExtern TYPE_BYTE		FLAGH;
ramExtern TYPE_BYTE		FLAGI;
ramExtern TYPE_BYTE		FLAGJ;
ramExtern TYPE_BYTE		FLAGK;
ramExtern TYPE_BYTE		FLAGL;
ramExtern TYPE_BYTE		FLAGM;
ramExtern TYPE_BYTE		FLAGN;
ramExtern TYPE_BYTE		FLAGO;
ramExtern TYPE_BYTE		FLAGP;
ramExtern TYPE_BYTE		FLAGQ;
ramExtern TYPE_BYTE		FLAGR;
ramExtern TYPE_BYTE		FLAGS;
ramExtern TYPE_BYTE		FLAGT;
ramExtern TYPE_BYTE		FLAGU;
ramExtern TYPE_BYTE		FLAGV;
ramExtern TYPE_BYTE		FLAGW;
ramExtern TYPE_BYTE		FLAGX;
ramExtern TYPE_BYTE		FLAGY;
ramExtern TYPE_BYTE		FLAGZ;
ramExtern TYPE_BYTE		FLAGA1;
ramExtern TYPE_BYTE		FLAGA2;

ramExtern TYPE_BYTE		FLAG10;
ramExtern TYPE_BYTE		FLAG11;
ramExtern TYPE_BYTE		FLAG12;
ramExtern TYPE_BYTE		FLAG13;

ramExtern	uchar  	Display_get1;	    //显示数据缓存
ramExtern	uchar  	Display_get2;	    //显示数据缓存
ramExtern	uchar  	Display_get3;	    //显示数据缓存
ramExtern	uchar  	Display_get4;	    //显示数据缓存
ramExtern	uchar  	Display_get5;	    //显示数据缓存


ramExtern	uchar  	ucDisplay_1;	    //显示数据刷新缓存
ramExtern	uchar  	ucDisplay_2;	    //显示数据刷新缓存
ramExtern	uchar  	ucDisplay_3;	    //显示数据刷新缓存
ramExtern	uchar  	ucDisplay_4;	    //显示数据刷新缓存
ramExtern	uchar	ucDisplay_5;
ramExtern	uchar	ucT_2min;					//通讯故障2min计时
ramExtern	uchar	ucRecOneTime;

ramExtern 	uint  	uiMeasure_1;  	     		//测量遥控接收宽度1
ramExtern 	uint  	uiMeasure_2;		 		//测量遥控接收宽度2
ramExtern 	uint	uiRecWidth;					//遥控接收宽度



ramExtern	uchar	ucSendBuf[20];		       	//发送数据缓存
ramExtern	uchar	ucRecbuf[20];		       	//UART接收数据
ramExtern 	uchar  	ucTrCount;		           	//发送个数
ramExtern 	uchar	ucSeprate_count;			//遥控接收分隔符数量
ramExtern 	uchar	ucEnterRestCount;			//进入低功耗计时器
ramExtern 	uchar	ucT_CLRTM00;				//遥控接收初始化时间  
ramExtern	uchar	ucBitCount;					//遥控接收位数
ramExtern 	uchar  	ucRecData1;		    		//遥控接收数据
ramExtern 	uchar  	ucRecData2;		    		//遥控接收数据
ramExtern 	uchar  	ucRecData3;		    		//遥控接收数据
ramExtern 	uchar  	ucRecData4;		    		//遥控接收数据
ramExtern 	uchar  	ucRecData5;		    		//遥控接收数据
ramExtern 	uchar  	ucRecData6;		    		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_1;		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_2;		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_3;		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_4;		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_5;		//遥控接收数据
ramExtern 	uchar  	ucRec_data_Frame1_6;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_1;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_2;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_3;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_4;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_5;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame2_6;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_1;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_2;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_3;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_4;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_5;		//遥控接收数据
ramExtern	uchar  	ucRec_data_Frame3_6;		//遥控接收数据
//ramExtern	uchar	i;							//用于中断外面的临时变量
//ramExtern	uchar	j;							//用于中断外面的临时变量
//ramExtern	uchar	k;							//用于中断外面的临时变量
ramExtern	uchar	ucT_80ms;
ramExtern	uchar	ucT_20ms;					//20ms计时
ramExtern	uchar	ucT_10ms;					//4ms计时
ramExtern	uchar	ucpower_1min;				//上电1分钟计时
ramExtern	uchar	ucStopTime1s;				//低功耗1s计时变量  2013071302
ramExtern	uchar	ucT10sBasetime;				//10s 基准时间变量 2013091602
ramExtern	uint	uiPowerOnTime;				//上电时间计时  2014052901
ramExtern	uchar	ucMemoryDisTim;
ramExtern	uchar	ucPowerRemoteCount;
ramExtern	uchar	ucUpDownRemoteCount;
ramExtern	uchar	ucDispCodeRemoteCount;
ramExtern	uchar	ucDispCodeRemoteTime;		//10s内接收到5次屏显信号。


ramExtern	uchar	ucEE_address;				//E方的地址
ramExtern	uint	uiReceiveLength;				//写入E方的长度
ramExtern	uchar	ucT_100ms;					//100ms计时
ramExtern	uchar	ucT_1s;						//1秒计时
ramExtern	uchar	ucSpecilMode;				//显示工程信息
ramExtern	uchar	ucFanSpeedSetGrade;			//风速设定等级1%-100%
ramExtern	uchar	ucFanSpeedSetGradeBack;		//风速设定等级临时变量
//ramExtern	uchar	ucTimeFanSpeedSetState;		//风速设定状态计时
ramExtern	uchar	ucNumberDisp;				//双8显示数据
ramExtern 	uchar	ucNumber1;					//显示数字十位
ramExtern 	uchar	ucNumber2;					//显示数字个位
ramExtern	uchar	ucNumber0;

ramExtern	uchar	ucSetTemp;					//空调设定温度
ramExtern	uchar	ucT1DispSampCount;			//T1温度采样间隔计时器
ramExtern	uchar	ucBarWritePageCount;		//条形码写入E方页计数器
ramExtern	uchar	ucPowerOn_5S;				//上电5秒计时,用于快检
ramExtern	uchar	ucAbilityTestNewData;		//能力测试命令标志字(新方式进入)
ramExtern	uchar	ucAbilityComFreqData;		//能力测试压机频率
ramExtern	uchar	ucAbilityValveData;			//能力测试四通阀状态
ramExtern	uchar	ucAbilityExpandValveData;	//能力测试电子膨胀阀开度
ramExtern	uchar	ucAbilityTempExData;		//能力测试排气目标温度
ramExtern	uchar	ucAbilityInFanSpeedDataL;	//能力测试内风机转速 低字节
ramExtern	uchar	ucAbilityInFanSpeedDataH;	//能力测试内风机转速 高字节
ramExtern	uchar	ucAbilityOutFanSpeedDataL;	//能力测试外风机转速 低字节
ramExtern	uchar	ucAbilityOutFanSpeedDataH;	//能力测试外风机转速 高字节

//ramExtern	uint	uiAbilityInFanSpeedData;	//能力测试内风机转速
//ramExtern	uint	uiAbilityOutFanSpeedData;	//能力测试外风机转速


ramExtern	uchar	ucAbilityHeatFrostFreqData;	//能力测试低温制热化霜频率
ramExtern	uchar	ucAbilityHeatFrostTimeData;	//能力测试低温制热进入时间间隔
ramExtern	uchar	ucAbilityHeatT3Data;		//能力测试低温制热进入T3温度
ramExtern	uchar	ucDispState;			//显示状态 0:正常显示设定温度 1:T1 2：T4 3：显示关?
ramExtern	uchar	ucDispStateBuf;
ramExtern	uchar	ucTimeDispState;			//显示状态5秒延时计时器
ramExtern	uchar	ucTimeDispStateWifi;		//用于关机下wifi图标显示15s的计时变量
ramExtern	uchar	ucTimeDispHumi;				//用于显示设定湿度变量
ramExtern 	uchar	ucT_DisAll_3S;				//上电全显3秒变量
//ramExtern 	uchar	ucError_backup;				//故障备份
ramExtern 	uchar	ucError1Buf;				//故障标志暂存区
ramExtern 	uchar	ucError2Buf;				//故障标志暂存区
ramExtern 	uchar	ucProtect1Buf;				//保护标志暂存区
ramExtern 	uchar	ucProtect2Buf;				//保护标志暂存区
ramExtern 	uchar	ucTimeDispTemperErr;		//传感器故障显示15秒计时
ramExtern 	uchar	ucBuzMusicBac;
ramExtern 	uchar	ucErrorKind;				//错误显示的种类
ramExtern 	uchar	ucLockFlashDispCount;		//锁定闪烁5秒指示计时器
ramExtern 	uchar	ucTemperT1Dis;				//室内环境温度T1,用于显示
ramExtern 	uchar	ucFreqGrade;				//频率条显示
ramExtern 	uchar	ucTemperT4;					//室外环境温度T4
//ramExtern 	uchar	ucRunKind;					//试运行时显示的种类
ramExtern 	uchar	ucTemperT2;					//室内环境温度T2
ramExtern 	uchar	ucTemperT3;					//室内环境温度T3
ramExtern 	uchar	ucTemperTp;					//室外排气温度Tp的AD值
//ramExtern	uchar	uchostID[4];				//主控自身ID
ramExtern	uchar	ucAbilityDispTime;			//能力测试显示"FL"1分钟计时
ramExtern	uchar	ucRF_tunnel;				//射频通道号
//ramExtern	uchar	uctest;						// #test
//ramExtern	uchar	ucT2sMode;					//2秒后确认模式
//ramExtern	uchar	ucTEnalbeDrive;				//2秒后允许风扇负载改变之变量
//ramExtern	uchar	ucSpeedKeySetCount;			//风速键设定次数
//ramExtern	uchar	ucTimeFanSpeedSetState;		//风速设定状态计时
//ramExtern	uchar	ucTClrTestrun1;				//试运行30分钟后退出变量1
//ramExtern	uchar	ucTClrTestRun2;				//试运行30分钟后退出变量2
//ramExtern	uchar	uck6offdelay;				//按键扫描抬起延时
//ramExtern	uchar	uck6ondelay;				//按键扫描延时
//ramExtern	uchar	ucRtempFlashTime1;			//条形码闪动0.5秒计时 
//ramExtern	uchar	uck6offdelay;				//按键扫描抬起延时
//ramExtern	uint	uik6ondelay;				//按键扫描延时


ramExtern	uchar	ucAbilityTestData;			//能力测试(旧方式进入)
ramExtern	uchar	EeCheckDelay;				//读写E方延时100ms
//ramExtern	uchar	uc_radom;					//随机数
ramExtern	uchar	ucT_400ms;					//400ms计时
ramExtern	uchar	ucMainFreTime;				//显示最大频率限制时间
ramExtern	uchar	ucMainFre;					//显示的最大频率
ramExtern	uchar	ucPollingType;				//A9的查询指令
ramExtern	uchar	ucMainTypeTime;				//显示机型时间
ramExtern	uchar	ucMainType;					//显示的机型种类
ramExtern	uchar	ucMachineTypeSet;			//机型种类


//ramExtern	uchar	ucT1s_SleepS;				//舒睡模式秒计时变量
//ramExtern	uchar	ucT1min_SleepMin;				//舒睡模式分钟计时变量
//ramExtern	uchar	ucT1h_SleepHour;				//舒睡模式小时计时变量
ramExtern	uchar	ucSleepTime;				//遥控器设置睡眠时间
ramExtern	uchar	ucSleepTemp1;				//遥控器设置睡眠时间设定温度
ramExtern	uchar	ucSleepTemp2;				//遥控器设置睡眠时间设定温度
ramExtern	uchar	ucSleepTemp3;				//遥控器设置睡眠时间设定温度
ramExtern	uchar	ucSleepTemp4;				//遥控器设置睡眠时间设定温度
ramExtern	uchar	ucSleepTemp5;				//遥控器设置睡眠时间设定温度


ramExtern	uchar	EepErrDispCount;			//E方通讯故障闪烁显示4次计时器
ramExtern	uchar	ucT_TimeToOpenClose_10S;	//定时开关机10秒时基
//ramExtern	uchar	ucFanSpeedSetGradeBack1;	//风速设定等级临时变量
//ramExtern	uchar	ucRecChksum;				//UART接收数据校验和// 2014042401  校验和不放在中断处理
//ramExtern	uchar	ucCycle;					//// 2014042401  校验和不放在中断处理
ramExtern	uchar	ucTypeCmp;					//上电后,获取机型比较值
ramExtern	uchar	ucGetRightFirst;			//上电通讯5次数据计数
ramExtern	uchar	ucTemp_T1;					//室内环境温度T1
//ramExtern	uchar	ucFanSpeed;					//用于控制负载的风速
//ramExtern	uchar	ucFanSpeedCurrentGrade;		//当前风速等级1%-100%
ramExtern	uchar	EeCheckWrSymbol;			//E方通讯故障检测时写入的特殊字节
ramExtern	uchar	EeCheckRdSymbol;			//E方通讯故障检测时读出比较的特殊字节
//ramExtern	uchar	ucRFInitUIDCtn;				//对码限时时间
//ramExtern	uchar	ucRF_data[RF_DATALENTH];	//射频数据寄存器
//ramExtern	uchar	ucRF_dataBuf;
//ramExtern	uchar	ucRF_buffer[RF_PKTLENTH];	//射频数据
//ramExtern	uchar	uchostID_EE[4];				//从E方读出的ID
//ramExtern	uchar	ucRead_count;				//读取次序
//ramExtern	uchar	ucReadErrorCnt;				//置为接收后读出校验计数
//ramExtern	uchar	ucT_Link2S;					//对码响2秒计时
//ramExtern	uchar	ucT_RF_RESET;				//对RF模块进行初始化时间变量
//ramExtern	uchar	ui2scount;					//CC1100 2s溢出计时
//ramExtern	uchar	ucTestLinkTimes;			//连接成功的次数
//ramExtern	uchar	ucrandom0;
//ramExtern	uchar	ucRF_Tx_ADDR;				//遥控器数据接收地址
//ramExtern	uchar	ucPkt_Rx_Type;				//接收数据包类型
//ramExtern	uchar	ucguestID[4];				//线控器ID  2014061903
//ramExtern	uchar	ucPkt_Tx_Type;				//发送数据包类型
ramExtern	uchar	ucT_send;					//发送数据之后,进入接收模式的时间
ramExtern	uchar	ucStrong_count;				//强劲键的次数
ramExtern	uchar	ucStrong_time;				//强劲键次数的时间计时
ramExtern	uchar	ucModeSet_backup;			//设定模式备份
ramExtern	uchar	ucSetTemp_bac;				//设定温度备份
//ramExtern	uchar	ucStSpeed_bac;				//设定风速备份
ramExtern	uchar	ucFanSpeedSetGrade_bac;		//设定级数备份
//ramExtern	uchar	ucT_RF_10S;					//10秒时间计时
ramExtern	uchar	ucBarExitTime;				//按键次数计数
ramExtern	uchar	uckeyCounter;				//按键次数计数	
ramExtern	uchar	uckeyTime10s;				//10秒计时
ramExtern	uchar	ucBarCount;					//条形码显示计数
ramExtern	uchar	ucT100msBarShowTime;

ramExtern	uchar	ucT_60ms;					//60ms计时
ramExtern	uchar	ucIFeel_IDone;				//随身感ID号
ramExtern	uchar	ucIFeel_IDtwo;				//随身感ID号
ramExtern	uchar	ucIFeel_IDthr;
ramExtern	uchar	ucTime_test_5S;				//能力测试关闭显示时,有按键5秒后再熄灭
//ramExtern	uchar	ucIFeel_IDthr;
//ramExtern	uchar	uctimerled;
//ramExtern	uchar	ucledDispType;				//呼吸灯显示类型

ramExtern	uchar	ucSendNoEcoCnt;				//发送三次没有ECO功能计数
//ramExtern	uchar	ucModeStep;

//ramExtern	uchar	ucModeTime;
//ramExtern	uchar	ucmodeFlash;				//模式要演示的动画变量
//ramExtern	uchar	ucfanStep;
//ramExtern	uchar	ucfanTime;
//ramExtern	uchar	ucTempUpTime;
//ramExtern	uchar	ucTempUpStep;
ramExtern	uchar	ucShow5s;					//接收遥控信号显示5s
//ramExtern	uchar	ucfanDirectStep;
ramExtern	uchar	ucremoteclr;
ramExtern	uchar	uctestOneMinute;
ramExtern	uchar	ucDisID_count;	
//ramExtern	uchar	uckeycleanoff_delay;
//ramExtern	uchar	uckeycleanon_delay;
//ramExtern	uchar	uckeywifioff_delay;
//ramExtern	uchar	uckeywifion_delay;
//ramExtern	uchar	ucModeDispbac;
ramExtern	uchar	ucSpecilModeBlinkTime;
ramExtern	uchar	ucDispSpecilMode;
ramExtern	uchar	ucUartSendtype;				//UART发送命令字类型
ramExtern	uchar	ucUartA5count;				//A5命令数据组
ramExtern	uchar	ucUartAFcount;				//AE命令数据组

ramExtern uchar ucSampCnt;
ramExtern uint uiADCSum;
ramExtern uint uiADCMax;
ramExtern uint uiADCMin;
ramExtern uint uiADCSum10;
ramExtern uint uiRTADSamp;
ramExtern uchar	ucADchannel;		//AD采样通道。


ramExtern	uchar	ucsetfre;					//目标频率
ramExtern	uchar	ucrunfre;					//运行频率
//ramExtern	uchar	uctimefan;			
ramExtern	uchar	ucEEVersion;				//室内参数版本号
ramExtern	uchar	ucEEOutVersion;				//室外参数版本号
//ramExtern	uchar	ucWriteEE_IDone;
//ramExtern	uchar	ucWriteEE_IDtwo;
//ramExtern	uchar	ucWriteEE_IDthr;



//ramExtern	uchar	ucRFenable;					//射频允许解码变量
ramExtern	uchar	ucTestDataKind;
//ramExtern	uchar	ucSendSoundCnt;				//蜂鸣器发送声音计数
ramExtern	uchar	ucSendTestKind;
//ramExtern	uchar	ucKeynum;
//ramExtern	uchar	ucKeynumone;
//ramExtern	uchar	ucKeyData;
//ramExtern	uchar	ucKeyn;

ramExtern	uchar	ucT1min_forcet;					//强制制冷30分钟计时变量
ramExtern	uchar	ucforeckeycount;					//按键计数变量
ramExtern	uchar	ucT1s_1min;				//1分钟计时变量 
ramExtern	uchar	ucShowv3sec;			//查询软件版本号3s计时变量

//ramExtern	uchar	ucOff_6S;					//关机的6秒,发送A5四组命令和A2命令						
ramExtern	uchar	ucDisError;
//ramExtern	uchar	ucSoftSleep_IDone;				// 2014061903
//ramExtern	uchar	ucSoftSleep_IDtwo;				// 2014061903
//ramExtern	uchar	ucSoftSleep_IDthr;				// 2014061903
ramExtern	uchar	ucSleepMin;	
ramExtern	uchar	ucSleepHour;
ramExtern	uchar	ucSleep1min;
//ramExtern	uchar	ucSleep3Time;
ramExtern	uchar	ucSleepMode;				//舒睡模式

ramExtern 	uint	uiT_Save;					//省电功能2小时计时
ramExtern 	uint	uiT_TimeToClose;			//定时关时间,10秒一个单位
ramExtern 	uint	uiT_TimeToOpen;				//定时开时间,10秒一个单位
//ramExtern	uint	ucT_RF_initial;				//固定时间对RF模块进行初始化时间变量
ramExtern	uchar	ucSendUartDataCnt;				//发送给主控板数据计数变量
ramExtern	uchar	ucReceUartDataCnt;				//接收到主控板数据计数变量
ramExtern	uchar	ucBarCodeSendArrayCommand;//发给主控的条形码数组
ramExtern   uchar		ucWifiStength;						// 2014062601 wifi信号强度
ramExtern	uchar		ucReceStrenthTime;					//2014062601 接收到信号强度命令计时变量，10分钟没有收到数据默认没有信号
ramExtern	uchar		ucWifiLinkState;
ramExtern	uchar		ucWifiLinkMode;
ramExtern	uint		uiWifiAPModeTime;



ramExtern 	uchar	ucWirte_EE_buf[130];		//遥控器写入E方数据
ramExtern	uchar	ucInDoorBarCodeBuf[BAR_CODE_NUMBER];	//主控条形码数据缓存区


ramExtern	uchar		ucOutCodingData[25];							//室外物料编码和压缩机编码
ramExtern	uchar		ucOutInTimeData[38];							// 3组数据+2=38个
#define 	ucHumidity	ucOutInTimeData[0]
#define 	ucTsc		ucOutInTimeData[1]

ramExtern	uchar		ucOutsetfre;								// 2014042503 室外目标频率

ramExtern	uchar		ucOutInRamData[16];							// 16个ram数据
ramExtern	uchar		ucCheckRamKind;
ramExtern	uchar		ucCheckRamAdd1;
ramExtern	uchar		ucCheckRamAdd2;
ramExtern	uchar		ucCheckRamAdd3;
ramExtern	uchar		ucCheckRamAdd4;
ramExtern	uchar		ucCheckRamLength;


ramExtern	uchar	ucBarCodeData[20];
#define		ucBarCode	ucBarCodeData[0]
#define		ucBarCode1	ucBarCodeData[1]
#define		ucBarCode2	ucBarCodeData[2]
#define		ucBarCode3	ucBarCodeData[3]
#define		ucBarCode4	ucBarCodeData[4]
#define		ucBarCode5	ucBarCodeData[5]
#define		ucBarCode6	ucBarCodeData[6]
#define		ucBarCode7	ucBarCodeData[7]
#define		ucBarCode8	ucBarCodeData[8]
#define		ucBarCode9	ucBarCodeData[9]
#define		ucBarCode10	ucBarCodeData[10]
#define		ucBarCode11	ucBarCodeData[11]
#define		ucBarCode12	ucBarCodeData[12]
#define		ucBarCode13	ucBarCodeData[13]
#define		ucBarCode14	ucBarCodeData[14]
#define		ucBarCode15	ucBarCodeData[15]
#define		ucBarCode16	ucBarCodeData[16]
#define		ucBarCode17	ucBarCodeData[17]
#define		ucBarCode18	ucBarCodeData[18]
#define		ucBarCode19	ucBarCodeData[19]

ramExtern	uchar		ucStepStatePos[15];

#define		ucStepState			ucStepStatePos[0]					//导风条状态 2014030601			
			
#define		ucCoolHorSwLimitDown	ucStepStatePos[1]				//上下导风条制冷摇摆下限 2014030601	
#define		ucCoolHorSwLimitUp	ucStepStatePos[2]					//上下导风条制冷摇摆上限 2014030601	
#define		ucHeatHorLimitDown	ucStepStatePos[3]					//上下导风条下限 2014030601	
#define		ucHeatHorLimitUp	ucStepStatePos[4]					//上下导风条上限 2014030601	
#define		ucStepHorNowTgt		ucStepStatePos[5]					//上下导风条当前角度 2014030601

#define		ucStepVerSwLimitDown	ucStepStatePos[6]					//左右导风条摇摆下限 2014030601	
#define		ucStepVerSwLimitUp 	ucStepStatePos[7]					//左右导风条摇摆上限 2014030601	
#define		ucStepVerNowTgt		ucStepStatePos[8]					//左右导风条当前角度 2014030601	


#define		ucStepUpSwLimitDown	ucStepStatePos[9]					//顶出风导风条摇摆下限 2014030601	
#define		ucStepUpSwLimitUp 		ucStepStatePos[10]					//顶出风导风条摇摆上限 2014030601
#define		ucStepUpNowTgt		ucStepStatePos[11]					//顶出风导风条当前角度 2014030601	

#define		ucStepNextSwLimitDown		ucStepStatePos[12]					//顶出风导风条摇摆下限 2014030601	
#define		ucStepNextSwLimitUp 		ucStepStatePos[13]					//顶出风导风条摇摆上限 2014030601
#define		ucStepNextNowTgt			ucStepStatePos[14]

ramExtern	uchar		ucStepStateSet[12];

#define		ucSetStepState			ucStepStateSet[0]					//设置导风条状态 2014030601						
#define		ucSetStepCoolHorDown	ucStepStateSet[1]					//设置上下导风条摇摆下限 2014030601	
#define		ucSetStepCoolHorUp		ucStepStateSet[2]					//设置上下导风条摇摆上限 2014030601	
#define		ucSetStepHeatHorDown	ucStepStateSet[3]					//设置上下导风条摇摆下限 2014030601	
#define		ucSetStepHeatHorUp		ucStepStateSet[4]	
#define		ucSetStepHorNowTgt		ucStepStateSet[5]					//设置上下导风条当前角度 2014030601	
#define		ucSetStepVerLimitDown	ucStepStateSet[6]					//设置左右导风条摇摆下限 2014030601	
#define		ucSetStepVerLimitUp	ucStepStateSet[7]					//设置左右导风条摇摆上限 2014030601	
#define		ucSetStepVerNowTgt		ucStepStateSet[8]					//设置左右导风条当前角度 2014030601	
#define		ucSetStepUpLimitDown	ucStepStateSet[9]					//设置顶出风导风条摇摆下限 2014030601	
#define		ucSetStepUpLimitUp		ucStepStateSet[10]					//设置顶出风导风条摇摆上限 2014030601	
#define		ucSetStepUpNowTgt		ucStepStateSet[11]					//设置顶出风导风条当前角度 2014030601



//ramExtern	uchar	ucBarCode;		       		// 头码0xbb
//ramExtern	uchar	ucBarCode1;		       		// 数据1
//ramExtern	uchar	ucBarCode2;		       		// 数据2
//ramExtern	uchar	ucBarCode3;		       		// 数据3
//ramExtern	uchar	ucBarCode4;		       		// 数据4
//ramExtern	uchar	ucBarCode5;		       		// 数据5
//ramExtern	uchar	ucBarCode6;		       		// 数据6
//ramExtern	uchar	ucBarCode7;		       		// 数据7
//ramExtern	uchar	ucBarCode8;		       		// 数据8
//ramExtern	uchar	ucBarCode9;		       		// 数据9
//ramExtern	uchar	ucBarCode10;		   		// 数据10
//ramExtern	uchar	ucBarCode11;		   		// 数据11
//ramExtern	uchar	ucBarCode12;		   		// 数据12
//ramExtern	uchar	ucBarCode13;		   		// 数据13
//ramExtern	uchar	ucBarCode14;		   		// 数据14
//ramExtern	uchar	ucBarCode15;		   		// 数据15
//ramExtern	uchar	ucBarCode16;		   		// 数据16
//ramExtern	uchar	ucBarCode17;		   		// 数据17
//ramExtern	uchar	ucBarCode18;		   		// 校验
//ramExtern	uchar	ucBarCode19;		   		// 尾码0x33
//ramExtern	uchar	ucBarCode20;		   		// 空1 0x00
//ramExtern	uchar	ucBarCode21;		   		// 空2 0x00
//ramExtern	uchar	ucBarCode22;		   		// 空3 0x00
//ramExtern	uchar	ucBarCode23;		   		// 空4 0x00

												//条码校验区
ramExtern	uchar	ucBarCodeChk;		   		// 头码0xbb
ramExtern	uchar	ucBarCodeChk1;		   		// 数据1
ramExtern	uchar	ucBarCodeChk2;		   		// 数据2
ramExtern	uchar	ucBarCodeChk3;		   		// 数据3
ramExtern	uchar	ucBarCodeChk4;		   		// 数据4
ramExtern	uchar	ucBarCodeChk5;		   		// 数据5
ramExtern	uchar	ucBarCodeChk6;		   		// 数据6
ramExtern	uchar	ucBarCodeChk7;		   		// 数据7
ramExtern	uchar	ucBarCodeChk8;		   		// 数据8
ramExtern	uchar	ucBarCodeChk9;		   		// 数据9
ramExtern	uchar	ucBarCodeChk10;		   		// 数据10
ramExtern	uchar	ucBarCodeChk11;		   		// 数据11
ramExtern	uchar	ucBarCodeChk12;		   		// 数据12
ramExtern	uchar	ucBarCodeChk13;		   		// 数据13
ramExtern	uchar	ucBarCodeChk14;		   		// 数据14
ramExtern	uchar	ucBarCodeChk15;		   		// 数据15
ramExtern	uchar	ucBarCodeChk16;		   		// 数据16
ramExtern	uchar	ucBarCodeChk17;		   		// 数据17
ramExtern	uchar	ucBarCodeChk18;		   		// 校验
ramExtern	uchar	ucBarCodeChk19;		   		// 尾码0x33
//ramExtern	uchar	ucBarCodeChk20;		   		// 空1 0x00
//ramExtern	uchar	ucBarCodeChk21;		   		// 空2 0x00
//ramExtern	uchar	ucBarCodeChk22;		   		// 空3 0x00
//ramExtern	uchar	ucBarCodeChk23;		   		// 空4 0x00

ramExtern	uchar	ucBarDisp[22];		   		//用于条形码的显示

ramExtern	uchar	SleepTwoTemp[9];			//舒睡2的设定温度

//ramExtern	uchar   ucRF_data_buf[20];			//用于遥控器写E方
ramExtern	uchar	ucT1sResttime;
ramExtern	uchar	ucWriteEEDataGroup;			//写第几组EE数据
ramExtern	uchar	ucT100msDispWriteT;			//写入E方成功或失败显示5s计时变量
ramExtern	uchar	ucTestData[34];
//ramExtern	uchar	ucCurVol;
#define		ucCurVol	ucTestData[4]

ramExtern	uchar	ucWriteEEDataSendCount;		//和主控写EE次数
ramExtern	uchar	ucEepromErrDisCnt;			//E方故障快检时显示次数
ramExtern	uchar	ucT20ms_2sTime;


ramExtern	uchar	ucCurrentVal;
ramExtern	uchar	ucComCount;
ramExtern	uchar	ucTempT1_H;
ramExtern	uchar	ucTempT1_L;
ramExtern	uchar	ucTempT4_H;
ramExtern	uchar	ucTempT4_L;	

ramExtern	uchar	ucTempT1_DispH;	// 2014061902
ramExtern	uchar	ucTempT1_DispL;	// 2014061902
ramExtern	uchar	ucTempT4_DispH;	// 2014061902
ramExtern	uchar	ucTempT4_DispL;	// 2014061902

ramExtern	uchar	ucT1sOutEEtime;			//更改室外E方的时间计时变量  2014040901
ramExtern	uchar	ucWriteOutEELength;		//更改室外E方的行数		2014040901
ramExtern	uchar	ucWriteOutEEFram;		//更改室外E方的帧数		2014040901

ramExtern	uchar	ucTemperFeel;				//接收到随身感温度
ramExtern	uchar	ucTemperT1;					//显示的室内温度变量
ramExtern	uchar	ucFeel7min;					//随身感7分钟计时变量 
ramExtern	uchar	ucTemperT1_ad;				//
ramExtern	uchar	ucDust_ThickL;				//灰尘传感检测浓度低字节
ramExtern	uchar	ucDust_ThickH;				//灰尘传感检测浓度高字节
ramExtern	uchar	ucPMV_Angle;				//电子膨胀阀开度 2013091702
ramExtern	uchar	ucOutFan_Speed;				//室外风机转速	2013091702
ramExtern	uchar	ucInFan_Speed;				//室内风机转速	2013091702
ramExtern	uchar	ucInFan_SpeedAturn;			//室内风机实际转速	2013091702

ramExtern	uchar	ucPMVMode;				//PMV模式 
ramExtern	uchar	ucPMVModeBak;				//PMV模式备份标识

ramExtern	uchar	ucFreMax;				//最大频率限制
ramExtern	uchar	ucModeModify;				//最大频率限制的模式
ramExtern	uchar	ucSendA6A8Count;				//最大频率限制的模式
ramExtern	uchar	ucT100ms_ShowTypeTime;				//显示机型信息2s计时变量
ramExtern	uchar	ucTypeInfor;				//机型信息变量
ramExtern	uchar	ucTimeDispEFErr;			//电表模块故障显示15时间计时
//ramExtern	uchar	ucNaturMode;					//

ramExtern	uchar		Identifier[16];			//2013102301 增加电表模块处理
#define	ucIdentifier Identifier[0]
#define ucEEDayh	Identifier[1]
#define ucEEDay	Identifier[2]
#define ucEEHour	Identifier[3]
#define ucEEMin	Identifier[4]
#define ucEEDay_onh	Identifier[5]		//运行时间日期的高字节
#define ucEEDay_on	Identifier[6]
#define ucEEHour_on	Identifier[7]
#define ucEEMin_on	Identifier[8]

#define ucRunPowerTotal0	Identifier[9]			//累计运行电量
#define ucRunPowerTotal1	Identifier[10]
#define ucRunPowerTotal2	Identifier[11]
#define ucRunPowerTotal3	Identifier[12]

#define ucchecksum	Identifier[15]

ramExtern	uchar	ucPowerConsum[4];
#define ucPowerConsum0	ucPowerConsum[0]			//总耗电量
#define ucPowerConsum1	ucPowerConsum[1]
#define ucPowerConsum2	ucPowerConsum[2]
#define ucPowerConsum3	ucPowerConsum[3]


ramExtern	uchar   ucEEMin_now;                    //本次运行时间
ramExtern	uchar   ucEEHour_now;
ramExtern	uchar   ucEEDay_now;
ramExtern	uchar   ucPowerRealTime0;
ramExtern	uchar   ucPowerRealTime1;
ramExtern	uchar   ucPowerRealTime2;

ramExtern	uchar		ucRunPowerTemp[4];
#define	ucRunPowerTemp0 ucRunPowerTemp[0]       //
#define	ucRunPowerTemp1 ucRunPowerTemp[1]       //
#define	ucRunPowerTemp2 ucRunPowerTemp[2]       //
#define	ucRunPowerTemp3 ucRunPowerTemp[3]       //


ramExtern	uchar		ucRunPowerCon[4];
#define	ucRunPowerCon0 ucRunPowerCon[0]      //本次运行电量
#define	ucRunPowerCon1 ucRunPowerCon[1]       //本次运行电量
#define	ucRunPowerCon2 ucRunPowerCon[2]       //本次运行电量
#define	ucRunPowerCon3 ucRunPowerCon[3]       //本次运行电量

//ramExtern	uchar		ucRunPowerTotal[4];
//#define	ucRunPowerTotal0 ucRunPowerTotal[0]       //累计运行电量
//#define	ucRunPowerTotal1 ucRunPowerTotal[1]       //累计运行电量
//#define	ucRunPowerTotal2 ucRunPowerTotal[2]       //累计运行电量
//#define	ucRunPowerTotal3 ucRunPowerTotal[3]       //累计运行电量

ramExtern	uchar		ucRunPowerTotalTemp[4];
#define	ucRunPowerTotalTemp0 ucRunPowerTotalTemp[0]       //
#define	ucRunPowerTotalTemp1 ucRunPowerTotalTemp[1]       //
#define	ucRunPowerTotalTemp2 ucRunPowerTotalTemp[2]       //
#define	ucRunPowerTotalTemp3 ucRunPowerTotalTemp[3]       //

ramExtern	uchar		ucMemorySetState[MemoryNUM];		//16 BYTES
ramExtern	uchar		ucMemorySetStatebak[MemoryNUM];		//16 BYTES



ramExtern 	uchar *ucRamAddPtr;

ramExtern	uint	uiBuzzerKind;			//蜂鸣器声音种类

ramExtern	uchar	ucT100msSendAFT10s;	// 2014061602
ramExtern	uchar	ucT100msSendA5T5s;		// 2014061603


/*********************************************************************
位定义
*********************************************************************/
#define		fgRecIni		FLAG0.bit.b0     			//遥控器初始化标志 
#define		fgEnterRest     FLAG0.bit.b1				//进入休眠
#define		fgstop			FLAG0.bit.b2				//处于低功耗标志
#define		fgCodeHeader	FLAG0.bit.b3				//接收头码
#define		fgHeaderCodeLow FLAG0.bit.b4				//头码低电平		
#define		fgRecPro		FLAG0.bit.b5				//遥控处理标志
#define		fgMse20			FLAG0.bit.b6				//20ms标志	
#define		fg20mskey		FLAG0.bit.b7				//按键20ms标识。20ms采样一次按键信号 

#define		fgKeyTouchInt	FLAG1.bit.b0				//按键信号初始标识
#define		fgcleankey		FLAG1.bit.b1				//
#define		fg_100ms		FLAG1.bit.b2				//100MS标志
#define		fg1sCheck		FLAG1.bit.b3				//1秒时基
#define		fgTestRun		FLAG1.bit.b4				//试运行标志
#define		fgTimer_noclear		FLAG1.bit.b5				//射频遥控信号的定时信息
#define		fgPtcAssis_noclear	FLAG1.bit.b6				//射频遥控信号的电辅热信号
#define		fgSavePro		FLAG1.bit.b7				//遥控省电处理标志

#define     ucModeSet     	FLAG2.byte 		  			//设定模式
#define     fgHeatMode     	FLAG2.bit.b0	      		//制热模式
#define     fgCoolMode     	FLAG2.bit.b1        		//制冷模式
#define     fgFanMode      	FLAG2.bit.b2       	 		//送风模式
#define     fgDryMode      	FLAG2.bit.b3        		//抽湿模式 				
#define     fgAutoMode     	FLAG2.bit.b4        		//自动模式  
														//剩下的标志位不能使用


#define	 	fgSendABWait	FLAG3.bit.b0     			//发送AB命令标识
#define  	fgSendACWait   FLAG3.bit.b1     			//发送AC命令标识
#define  	fgSendADWait    FLAG3.bit.b2     			//发送AD命令标识
#define  	fgSendAEWait    FLAG3.bit.b3     			//发送AE命令标识
#define  	fgSendAFWait   	FLAG3.bit.b4     		//发送AF命令标识
#define		fgReceADOrder		FLAG3.bit.b5
#define		fgReceACOrder		FLAG3.bit.b6
#define		fgSendAEOrder		FLAG3.bit.b7			//已经接收到Ram数据地址
														

#define		fgImodeResume		FLAG4.bit.b0			//I模式恢复
#define		fg_nocancle_Imode 	FLAG4.bit.b1			//开启I模式,不取消I模式标志
#define		fgFanSpeedChange	FLAG4.bit.b2			//风速改变标志
#define		fgBarCodeDisplay	FLAG4.bit.b3			//1:条码显示
#define		fgFastTest			FLAG4.bit.b4			//快检标志
#define		fgTest2				FLAG4.bit.b5			//快检信号,关机时清零
#define		fg_test_error		FLAG4.bit.b6			//收到快检信号,故障正常处理
#define		fgAbilityRemote		FLAG4.bit.b7			//遥控器能力测试信号



#define		fgTurnOn			FLAG5.bit.b0			//开机标志位
#define		fgAbilityDataSend	FLAG5.bit.b1			//能力测试信息发送标志
#define		fgImodeMem			FLAG5.bit.b2			//I模式记忆
#define		fgCoolReceiveHeat	FLAG5.bit.b3			//单冷机接收到冷暖标志
#define		fgremote_code		FLAG5.bit.b4			//接收到无极风速码标识
#define		fgTimeToOpen		FLAG5.bit.b5			//定时开
#define		fgTimeToClose		FLAG5.bit.b6			//定时关
#define		fgWrithEE_ing		FLAG5.bit.b7			//正在写E方标识

#define		fgSave				FLAG6.bit.b0			//省电
#define		fgLowFreqFan		FLAG6.bit.b1			//睿风
#define		fgTypeHeat			FLAG6.bit.b2			//冷暖标志位
#define		fg_keep_SuperFan	FLAG6.bit.b3			//开启时,不取消强劲标志
#define		fgRemoteDispKey		FLAG6.bit.b4			//遥控屏显键设定标志
#define		fgDryCleanDisplay	FLAG6.bit.b5			//干燥清洁显示标志
#define		fgDispOutTemperEnable FLAG6.bit.b6			//室外环境温度查询使能
#define		fgDryCleanEnable	FLAG6.bit.b7			//干燥允许

#define		ucStSpeed		FLAG7.byte
#define     fgSuperFan     	FLAG7.bit.b0	    		//强劲风
#define     fgQuietFan     	FLAG7.bit.b1	    		//静音风
#define     fgLowFan       	FLAG7.bit.b2	    		//低风 
#define     fgMidFan       	FLAG7.bit.b3	    		//中风
#define     fgHighFan      	FLAG7.bit.b4	    		//高风
#define     fgAutoFan      	FLAG7.bit.b5	    		//自动风
														//剩下的标志位不能使用
												
#define     fgAutoModeCool 	FLAG8.bit.b0	    		//自动模式下的制冷
#define     fgAutoModeHeat 	FLAG8.bit.b1	    		//自动模式下的制热
#define     fgAutoModeFan  	FLAG8.bit.b2	    		//自动模式下的送风  
#define		fgPtcAssis		FLAG8.bit.b3				//电辅热
#define		fgLeftRightFan	FLAG8.bit.b4				//左右风
#define		fgUpdownFan		FLAG8.bit.b5				//上下风
#define		fgDisp3S		FLAG8.bit.b6				//全显3秒标志
#define		fg_DisEE_real	FLAG8.bit.b7

#define		ucError1		FLAG9.byte  	    		//故障标志位寄存器，直接显示
#define   	fgEepromErr   	FLAG9.bit.b0  				//ErrorKind0 E0:EEPROM communication error
#define   	fgTASENSOR    	FLAG9.bit.b1  				//ErrorKind1 E1:T1 error
#define   	fgTESENSOR		FLAG9.bit.b2  				//ErrorKind2 E2:T2 error
#define   	fgTempCSensor  	FLAG9.bit.b3  				//ErrorKind3 E3:T3 error
#define   	fgTempOutSensor FLAG9.bit.b4  				//ErrorKind4 E4:T4 error
#define   	fg_ERROR_EB     FLAG9.bit.b5  				//ErrorKind5 E5:disp and main communication error
#define   	fgOutEepError  FLAG9.bit.b6  				//ErrorKind6 E6:室外E方故障
#define   	fgOutFanErr     FLAG9.bit.b7  				//ErrorKind7 E7:outdoor fan rate error

#define     ucError2		FLAGA.byte  	    		//故障标志位寄存器，直接显示
#define   	fgCOMMALM_SUART	FLAGA.bit.b0  				//ErrorKind8 E8:in and out communication error
#define   	fg_ERROR_E9     FLAGA.bit.b1      			//ErrorKind9 E9:gate running error
#define   	fg_ERROR_EA   	FLAGA.bit.b2  				//ErrorKind10 EA:compress low press error
#define   	fgSpeedError   	FLAGA.bit.b3  				//ErrorKind11 Eb:indoor fanspeed error
#define   	fgZeroError   	FLAGA.bit.b4  				//ErrorKind12 EC:zero detect error
#define   	fg_ERROR_Ed   	FLAGA.bit.b5  				//ErrorKind13 Ed:phase shortage error 
#define   	fg_ERROR_EE   	FLAGA.bit.b6  				//ErrorKind14 EE:phase reverse error
#define   	fgTempPSensor  	FLAGA.bit.b7  				//ErrorKind15 EP:exgas temper(TP) error

#define     ucProtect1		FLAGB.byte     				//严重保护标志位寄存器，直接显示
#define   	fgIPMALM    	FLAGB.bit.b0   				//ErrorKind16 P0:IPM error
#define   	fgOutVolt		FLAGB.bit.b1  				//ErrorKind17 P1:voltage singularity
#define   	fgTOPTEMP		FLAGB.bit.b2   				//ErrorKind18 P2:compress high temperature
#define     fg_ERROR_P3     FLAGB.bit.b3    			//ErrorKind19 P3:out temprature low
#define     fgCOMPOSERR     FLAGB.bit.b4    			//ErrorKind20 P6:position protect
#define     fg_ERROR_P8     FLAGB.bit.b5    			//ErrorKind21 P8:connect more parts erorr
#define     fg_ERROR_PA     FLAGB.bit.b6    			//ErrorKind22 PA:face open protect
#define     fg_ERROR_DisEE	FLAGB.bit.b7				//ErrorKind23 EL:显示板E方故障

#define     ucProtect2     	FLAGC.byte					//严重保护标志位寄存器，直接显示
#define     fg_ERROR_Pb     FLAGC.bit.b0    			//ErrorKind24 Pb:compress low press protect
#define     fg_ERROR_PC     FLAGC.bit.b1    			//ErrorKind25 PC:compress high press protect
#define     fg_ERROR_Pd     FLAGC.bit.b2    			//ErrorKind26 Pd:current protect error
#define     fg_ERROR_RF  	FLAGC.bit.b3    			//ErrorKind27 EH:射频模块故障
#define     fg_NoDemoMain   FLAGC.bit.b4               	//演示样机与主控板配置错误 FA
#define     fgErrorNOGA     FLAGC.bit.b5   				//ErrorKind29 新平台室内机配老平台室外机F9故障
#define		fgCoolantLostNG	FLAGC.bit.b6				//ErrorKind30冷媒泄漏故障                                            			//ErrorKind30 预留 
//#define		fg_ERROR_Power	FLAGC.bit.b7   				//ErrorKind31 电表模块故障   

#define     ucProtectN		FLAGD.byte         			//一般保护标志位寄存器，在试运行下显示
#define   	fg_Data_default	FLAGD.bit.b0   				//E方默认数据
#define   	fgEEerror		FLAGD.bit.b1   				//快检写入E方的EE故障
#define   	fgTestDispT3    FLAGD.bit.b2   				//RunKind2 display T3
#define   	fgTestDispT4    FLAGD.bit.b3   				//RunKind3 display T4
#define   	fg_PROTECT_P4   FLAGD.bit.b4   				//RunKind4 P4:		内管温保护
#define   	fg_PROTECT_P5   FLAGD.bit.b5   				//RunKind5 P5:		外管温保护	
#define     fg_PROTEC_P7    FLAGD.bit.b6   				//RunKind6 P7:		排气高温保护
#define   	fg_PROTECT_P9   FLAGD.bit.b7   				//RunKind7 P9:      防冷风 P9 

#define		ucProtectM		FLAGE.byte     				//一般保护标志位寄存器，在试运行下显示
#define   	fg_PROTECT_Pd   FLAGE.bit.b0   				//RunKind8  		电流保护PD变频用
#define     fg_PROTECT_L0   FLAGE.bit.b1   				//RunKind9  		蒸发器高低温限频(L0变频用) 
#define     fg_PROTECT_L1   FLAGE.bit.b2   				//RunKind10 		冷凝器高温限频(L1变频用)                                         //RunKind9  预留 
#define     fg_PROTECT_L2   FLAGE.bit.b3   				//RunKind11 		压缩机排气高温限频(L2变频用)                                        
#define     fg_PROTECT_L3   FLAGE.bit.b4   				//RunKind12 		电流限频(L3变频用)                                        
#define     fg_PROTECT_L5   FLAGE.bit.b5   				//RunKind13 		电压限频(L5变频用)                                     //RunKind9 预留 
#define     fg_Isd3800Err   FLAGE.bit.b6   				//RunKind13 	????????                                                                                 
#define     fg_Isd3800RealErr   FLAGE.bit.b7                                           				//RunKind15 ?? 
                                                                                 
                                           				//RunKind15 预留 

#define		fgSingleTemperErr	FLAGF.bit.b0			//出现单一传感器故障标志	
#define		fgErrProtDisp		FLAGF.bit.b1			//故障和严重保护显示状态
#define		fg100msCheck		FLAGF.bit.b2			//100ms时基
#define		fgDisp0_5			FLAGF.bit.b3			//0.5显示
#define		fgSetDispNoDot		FLAGF.bit.b4			//温度查询的时候需要显示小数点
#define		fgShowBarCodeLastBit	FLAGF.bit.b5			//显示最后一个条形码数据标识
#define		fgBarCodeReady		FLAGF.bit.b6			//条形码存储好标识
#define		fgShowBarCode		FLAGF.bit.b7			//保存条形码标识

#define		fgkeysound_uart		FLAGG.bit.b0			//串口接收到按键信号
#define		fgEepComErrDisp		FLAGG.bit.b1			//E方通讯故障显示标志
#define		fgkeysoundone		FLAGG.bit.b2			//蜂鸣器响用于发送判断是否接收遥控信号，处理数显功能
#define		fgSoftSleepbak		FLAGG.bit.b3			//舒睡开备份标识用于在接收到模式吗后再判断是否舒睡功能开启
#define		fgkeysound			FLAGG.bit.b4			//接收到遥控信号蜂鸣器响声音
#define		fgSoftSleep			FLAGG.bit.b5			//舒睡标识
#define		fgcleanpro			FLAGG.bit.b6			//强制清洁按键标识
#define		fgDisplayT1			FLAGG.bit.b7			//进入低功耗退出后,允许显示T1标志

#define		fgDefrost			FLAGH.bit.b0			//正在化霜标志
#define		fgFeel				FLAGH.bit.b1			//随身感功能开启标识
#define		fgSendA3Wait		FLAGH.bit.b2			//发送A3命令标识	
#define		fgLongSound			FLAGH.bit.b3			//对码蜂鸣器长响标识
#define		fgModechange_noFeel	FLAGH.bit.b4			//接收到射频随身感信号标识
#define		fgFeelControl		FLAGH.bit.b5			//随身感功能
#define		fgFeelOwn			FLAGH.bit.b6			//本机随身感
#define		fgSoftSleepOwn		FLAGH.bit.b7			//本机舒睡

#define		fgDustClear			FLAGI.bit.b0			//净化功能
#define		fgSoftSleep_old		FLAGI.bit.b1			//舒睡功能备份
#define		fgECONFGS			FLAGI.bit.b2			//舒睡1小时计时到标识
#define		fg20msCheck			FLAGI.bit.b3			//20ms时基		
#define		fg1minCheck			FLAGI.bit.b4			//1分钟时基
#define		fgShowV				FLAGI.bit.b5			//查询软件版本号标识
#define		fgShowCode		FLAGI.bit.b6			// 2014062303 接收到工装遥控器的时候显示条形码
#define		fgPtcAssisBak			FLAGI.bit.b7			//电辅热功能备份标识 2014061603


#define		fgRestComDisable	FLAGJ.bit.b0			//休眠状态下通讯禁止标志，防止无效的触发退出休眠时
#define		fgcleanSel			FLAGJ.bit.b1			//净化功能选择位		
#define		fgEepErrCheckIni	FLAGJ.bit.b2			//E方通讯故障检测初始化标志
#define		fgECOSel			FLAGJ.bit.b3			//ECO功能选择位
#define		fgAbTestDispSet		FLAGJ.bit.b4			//能力测试显示
#define		fgRestPowerOn		FLAGJ.bit.b5			//上电第一次进入休眠状态标志
#define		fgKeyResonponse		FLAGJ.bit.b6			//接收到主控板按键信号
#define		fgKeyBusy			FLAGJ.bit.b7			//

#define		fgRecOne		FLAGK.bit.b0				//低功耗接收到数据标识
#define		fg400ms				FLAGK.bit.b1			//400ms标志,用于UART
#define		fgforcekeycool		FLAGK.bit.b2			//强制制冷标识
#define		fgforcekeyauto	 	FLAGK.bit.b3			//强制自动标识
#define		fgPreHeatOrCool		FLAGK.bit.b4			//预冷预热
#define		fgExchangeSel		FLAGK.bit.b5			//换气功能选择位
#define		fgExchangeAir		FLAGK.bit.b6			//换气功能标识位
#define		fg_out_volLow		FLAGK.bit.b7			//电压过低保护

#define		fg_out_volHigh		FLAGL.bit.b0			//电压过高保护
#define		fg_top_protect		FLAGL.bit.b1			//室外压缩机顶部温度保护
#define		fgImodeResumeSend	FLAGL.bit.b2			//I模式记恢复发送完成标志
#define		fgImodeMemSend		FLAGL.bit.b3			//I模式记忆发送完成标志
#define		fgAbilityDataSendOk	FLAGL.bit.b4			//能力测试信息发送标志
#define		fgReceive			FLAGL.bit.b5			//数据正确标志
#define		fgTypeOk			FLAGL.bit.b6			//上电机型参数获取完成标志
#define		fgRecFirst			FLAGL.bit.b7			//上电第一次通讯上


#define		fgRestSendAnswer	FLAGM.bit.b0			//下位机进入休眠应答信号
#define		fg_RF_Imode			FLAGM.bit.b1			//射频遥控器I模式标志
#define		fgHorLeftSwing		FLAGM.bit.b2	
#define		fgNoAck				FLAGM.bit.b3			//无应答标志
#define		fgReceStrenth		FLAGM.bit.b4			//接收到信号强度命令标识
#define		fgNotCreateLink		FLAGM.bit.b5			//地址激活标志， 1--主控地址已激活	0--主控地址未激活
#define		fg_read				FLAGM.bit.b6			//读取数据标志
#define		fgCLearPower		FLAGM.bit.b7			// 清除电表模块标识


#define		fgSetHumiChange			FLAGO.bit.b0			//正在发送数据标志
#define		fgCLearPowerSend	FLAGO.bit.b1			//已经发送清除电表数据的标识
#define		fgDisplayHumity			FLAGO.bit.b2			//接收到湿度信号
#define		fgSetFanSeedChange FLAGO.bit.b3			//设定风速发送改变标识
#define		fgModeChange		FLAGO.bit.b4			//数据接收就绪标志
#define		fgTurnOnChange		FLAGO.bit.b5			//有效控制指令标志，为1时要求主控必须处理
#define		fgNaturalFanBak		FLAGO.bit.b6			//自然风备份
#define		fgSendWifiColse	FLAGO.bit.b7			//2014071601 发送wifi关闭开启的标识

#define		fgWifiDisp			FLAGP.bit.b0		//Wifi图标显示标识 2014071603
#define		fgSendWifiColseOrder		FLAGP.bit.b1	// 发送wifi模块关闭开启命令 2014071601
#define		fgReceWifiData			FLAGP.bit.b2			//上电后能够接收到Wifi信号标识 2014071501
#define		fg_20ms				FLAGP.bit.b3			//20ms标志

#define		fg_buz_Repeat		FLAGP.bit.b4		//接收到蜂鸣器处理bit7标识位 2014042502

#define		fg_mode_change		FLAGP.bit.b5			//模式改变标志
#define		fgTSPTest			FLAGP.bit.b6			//测试堆栈标识
#define		fgModifSoftMemory		FLAGP.bit.b7		//遥控器更改掉电记忆功能标识


#define		fgMemoryWriteEnable	FLAGR.bit.b0			//掉电记忆功能写入E方标识
#define		fg_PowerOn_First		FLAGR.bit.b1			//初次上电标识 2014071501
#define		fg_buz_enFirst		FLAGR.bit.b2			//蜂鸣器判断标识，当为0的时候不需要判断bit7是否改变，判断是否重发的信息 2014042502
#define		fg_receive_strong	FLAGR.bit.b3			//接收到强劲风信号
#define		fg_keep_save		FLAGR.bit.b4			//开启时,不取消省电标志
#define		fg_keep_LowFreqFan	FLAGR.bit.b5			//开启时,不取消睿风标志
#define		fgReceiveKey		FLAGR.bit.b6			//接收到主控按键信号标识
#define		fgSendA8Wait			FLAGR.bit.b7			//发送A8指令标识


#define		fgBarCodeRead			FLAGS.bit.b0		//1:条码读
#define	fgBarCodeReadCompareEn		FLAGS.bit.b1		//读条码辅助标志，为0时，barCode与barCodeChk不需要校验
#define	fgBarCodeDispStateConsult	FLAGS.bit.b2		//1：条码查询显示状态 0：受到条码写入E方显示最后一个条码状态
#define	fgBarCodeDecode				FLAGS.bit.b3		//条码数据解码标志
#define		fg_read_error			FLAGS.bit.b4		//E方错误时,进行读出E方
#define		fgClean					FLAGS.bit.b5		//关机下的清洁按键
#define		fgK6come				FLAGS.bit.b6		//60ms标志
#define		fgShortkey				FLAGS.bit.b7		//短按按键按下


#define		fgTestSendFan			FLAGT.bit.b0		//总装快检标识
#define		fg_out_eerror			FLAGT.bit.b1
#define		fg_dcProtect			FLAGT.bit.b2
#define		fgMain_Drive_ComErr		FLAGT.bit.b3
#define		fg_CompSampleCurrent	FLAGT.bit.b4
#define		fgPowerKey		FLAGT.bit.b5				//强制按键信号标识
#define		fgFanLeadKey1		FLAGT.bit.b6			//条形码按键信号标识
#define		fgMinus					FLAGT.bit.b7		//负号显示

#define		fgEco_old				FLAGU.bit.b0		//ECO功能备份
#define		fgEco					FLAGU.bit.b1		//ECO功能开启标识
#define		fgTurnOnBackup			FLAGU.bit.b2
#define		fgEco_noclear			FLAGU.bit.b3		//接收到射频ECO功能，不清除ECO功能	
#define		fg80ms					FLAGU.bit.b4
#define		fgWriteEERem			FLAGU.bit.b5		//红外写入E方遥控信号
#define		fg_out_start			FLAGU.bit.b6
#define		fgLowFreqFan_old			FLAGU.bit.b7		//睿风功能备份


#define		fgFlashDis				FLAGV.bit.b0		//1HZ闪烁标识
#define		fgErrorDis				FLAGV.bit.b1		//E方故障快速显示标识
#define		fgSendA6Wait			FLAGV.bit.b2		//发送A6命令
#define		fg_ERROR_Power				FLAGV.bit.b3		// 2014040902 电表模块处理与灰尘传感器处理一致
#define		fgoldSuperFan			FLAGV.bit.b4		//强劲功能备份
#define		fgFeel_old				FLAGV.bit.b5		//随身感功能备份
#define		fgBarCodeStorSend		FLAGV.bit.b6		//存储条形码标识
#define		fg_out_openphase		FLAGV.bit.b7		//

#define		fgremoteNoleader		FLAGW.bit.b0		//红外低功耗不判断头码
#define		_TPPHIGHFG				FLAGW.bit.b1		//压缩机排气高温保护
#define		fg_ERROR_Dust  			FLAGW.bit.b2        // 2014030902 灰尘传感器故障
#define		fg_ERROR_DustReal				FLAGW.bit.b3	// 2014030902 灰尘传感器故障
#define		fg_current_protect		FLAGW.bit.b4		//室外机电流保护
#define		_TEHIGHFG				FLAGW.bit.b5		//蒸发器高温保护
#define		_TELOWFG				FLAGW.bit.b6		//蒸发器防冻结保护
#define		fg_volt_limit			FLAGW.bit.b7		//电压限频

#define		fg_current_limit		FLAGX.bit.b0		//电流限频
#define		_TPPHIGH1FG				FLAGX.bit.b1		//排气高温限频
#define		_TPHIGH1FG				FLAGX.bit.b2		//冷凝器高温限频
#define		_TCHOLDFG				FLAGX.bit.b3		//冷凝器高温限频
#define		_TELOW1FG				FLAGX.bit.b4		//蒸发器温度限频
#define		_TEHIGH1FG				FLAGX.bit.b5		//蒸发器温度限频
#define		fg_PFC_limit			FLAGX.bit.b6		//PFC故障限频 L6
#define		fgTpHighPro				FLAGX.bit.b7		//冷凝器高温保护


#define		fg80mscheck				FLAGY.bit.b0		//80ms
#define		fgWriteEEOwn			FLAGY.bit.b1		//本机写EE
#define		fgEepromSysnc			FLAGY.bit.b2		//EEPEOM数据同步标志
#define		fgWriteEEAllow			FLAGY.bit.b3		//开始写主控EE数据
#define		fgResetsinal			FLAGY.bit.b4
#define		fgWriteEESucess			FLAGY.bit.b5
#define		fgWriteEEDataSendOk		FLAGY.bit.b6
#define		fgPtcLoad				FLAGY.bit.b7		//电辅热负载状态	


#define		fgPtcEnable				FLAGZ.bit.b0		//开机制热或模式切换默认开启电辅热标志
#define		fgShowType				FLAGZ.bit.b1		//显示机型信息2s
#define		fgWriteEEFail			FLAGZ.bit.b2		//写入E方失败标识
#define		fgMainIFeel				FLAGZ.bit.b3		//主控板随身感功能是否开启标识
#define		fgHave_Left_Right		FLAGZ.bit.b4		//主控板的左右摆叶功能十分开启标识
#define		fg_comp_zerospeed		FLAGZ.bit.b5
#define		fg_out_341sync			FLAGZ.bit.b6
#define		fg_comp_speed			FLAGZ.bit.b7

#define		fg_IPDU_lock			FLAGA1.bit.b0
#define		fg_IPDU_openloop		FLAGA1.bit.b1
#define		fg_PFC_stop				FLAGA1.bit.b2
#define		fg_comp_overload		FLAGA1.bit.b3
#define		fg_IPDU_Sample			FLAGA1.bit.b4
#define		fg_receiveonce			FLAGA1.bit.b5		//接收一次
#define		fgSendWifiMode			FLAGA1.bit.b6		// 2014071501
#define		fg_ERROR_RF_Real		FLAGA1.bit.b7

#define		fgWriteEECodeErr		FLAGA2.bit.b0		//更改室外E方的时候，编码错误报警。2014043001

#define		fg_341_MCE				FLAGA2.bit.b1
#define		fgfirstSend				FLAGA2.bit.b2
#define		fgElectronTest			FLAGA2.bit.b3		//电子快检标识

#define		fgReceOutData			FLAGA2.bit.b4		//接收到室外参数标识，用于发送5组参数数据给射频遥控器 2013091601
#define		fgCOMMALM_SuartOnce		FLAGA2.bit.b5	//室内外通信故障工程模式一次就报 2013091603
#define		fgOutFanErrOnce			FLAGA2.bit.b6		//室外风机失速故障工程模式一次就报 2013091603		
#define		fgIPMALMOnece			FLAGA2.bit.b7		//室外IPM模块保护工程模式一次就报 2013091603		

#define		fg_ERROR_PowerReal		FLAG10.bit.b0		//电表模块故障标识
#define		fgWrithOutEE_ing		FLAG10.bit.b1		//写入室外E方标识 2014040901

#define		fgReceive_Data			FLAG10.bit.b2		// 显示板接收完成主控板数据标识 2014042401

#define		fgFastEAError			FLAG10.bit.b3		//EA故障的时候不接收快检遥控信号
#define		fg_ERROR_DryReal	FLAG10.bit.b3		// 2014040902 湿度传感器故障处理
#define		fg_ERROR_Dry			FLAG10.bit.b4		// 2014040902 湿度传感器故障处理
#define		fgSendB0Wait		FLAG10.bit.b5		// 准备发送B0命令 2014042202
#define		fgWriteEE			FLAG10.bit.b6		//写入电表数据标识
#define		fgTunrn_on_power	FLAG10.bit.b7		//开关机切换标识

#define		fgMemoryError		FLAG11.bit.b0		//掉电记忆读取E方数据错误标识
#define		fgSendB4Wait		FLAG11.bit.b1		// 2014040901 接收到室外更改E方数据，准备发送命令给主控板
#define    	fg10ms				FLAG11.bit.b2			//	   10ms标识
#define		fg10mscheck			FLAG11.bit.b3	//	//4ms标识 中断使用
#define		fgWriteOutEESendOk			FLAG11.bit.b4		// 2014040901 发送室外E方标识 数据发送完成的时候置一
#define     fgDustFullClear			FLAG11.bit.b5		//清除风机运行时间标识
#define     fgMemoryReadEnable		FLAG11.bit.b6		//读取掉电记忆数据标识
#define     fgDustFull			FLAG11.bit.b7		//尘满标识

		
#define		fgNaturalFanSel		FLAG12.bit.b0			//自然风功能选择位
#define		fgNaturalFan		FLAG12.bit.b1			//自然风功能标识
#define		fgPMVSel			FLAG12.bit.b2			//PMV功能选择位
#define		fgCatchColdSel		FLAG12.bit.b3			//防着凉功能选择位
#define		fgCatchCold			FLAG12.bit.b4			//防着凉功能标识
#define		fgNightLight		FLAG12.bit.b5			//小夜灯功能标识
#define		fgDryCleanDisplayBak	FLAG12.bit.b6
#define		fgPeakEletric		FLAG12.bit.b7			//峰谷用电功能标识

#define		fgSendMarstOrder			FLAG13.bit.b0			//主动上传wifi位置命令请求
#define		fgSendMarstOrder04			FLAG13.bit.b1			//主动上传04命令请求
#define		fgSendMarstOrder05			FLAG13.bit.b2			//主动上传05命令请求
#define		fghumiditySel				FLAG13.bit.b3			//湿度传感器选择位
#define		fgErrProtDispBak			FLAG13.bit.b4			//故障备份标识
#define		fgSendA7Wait				FLAG13.bit.b5			//小夜灯功能标识
#define		fgSendMarstCheckOrder				FLAG13.bit.b6			//净化负载开启的标识  2014062601
#define		fgReceWifiOrder				FLAG13.bit.b7			//接收到wifi信号标识

//wifi 变量定义

#define UART_REC_INIT		0
#define UART_RECING			1
#define UART_REC_END		2
#define UART_SEND_INIT		3
#define UART_SENDING		4
#define UART_SEND_END		5
#define UART_SEND_HALT		6	//发送空闲状态

#define U8_FALL				0
#define U8_PASS				1
#define U8_PASS_NO_RETURN	2	// 2014042402

#define	U8_UART_LENGTH		64

#define	U8_UART_WIFI_HEAD	0xaa
#define	U8_UART_WIFI_AIRCON 0xac	//空调设备

#define	U8_UART_WIFI_DRIVE 0xFF	//查询空调设备

#define U8_WIFI_FIND_ORDER	0X01
#define U8_WIFI_CON_ORDER	0x02
#define U8_WIFI_CHECK_ORDER	0X03
#define U8_MARST_CHECK_DATA	0X04
#define U8_MARST_CHECK_MODE	0X05

#define U8_WIFI_ID_ORDER	0X0f
#define U8_MARST_Wifi_Init		0X64	//WIFI主动上传配置命令
#define U8_MARST_Wifi_COLSE	0X68	// WIFI关闭命令 2014071601
#define	U8_WIFI_CLOSEOPEN 		0X03


#define U8_MARST_Wifi_CHECK_STRENGTH	0X63	//WIFI主动上传查询信号强度命令
#define	U8_RF_MODE				0x00		// RF模块
#define U8_WIFI_MODE			0x01		// WIFI模块

#define U8_Wifi_CHECK_DRIVE	0X65	//WIFI查询设备指令

#define U8_Wifi_BROADCAST_DRIVE	0X0D	//WIFI广播命令指令	广播命令更改为0d命令 2014062601
#define U8_WIFI_FIND_SLAVE		0X01
#define U8_WIFI_CON_SLAVE		0x02
#define U8_WIFI_CHECK_SLAVE	0X03

#define U8_WIFI_CON			0x40
#define U8_WIFI_CHECK		0x41

#define U8_WIFI_CON2_SLAVE	0xC0
#define U8_WIFI_CHECK2_SLAVE	0xC1
#define U8_BAR_CODE		0X80


#define U8_CON_COMMAND		0X01	//回复控制命令
#define	U8_CHECK_COMMAND 	0X02	//回复查看控制命令
#define U8_CHECK_DATA		0X03	//回复小板数据等命令
#define U8_WRITE_DATA		0x04	//
#define U8_CHECK_BAR_COMMAND 0X05 //回复条形码数据命令
#define U8_RECE_BAR_COMMAND	0x06 //回复设置条形码数据命令
#define U8_BAR_CODE_READ		0x07	//读取条形码命令
#define U8_BAR_CODE_WRITE		0x08	//写入条形码命令



#define U8_UART_DELAY_TIME_30ms 3		//30ms
#define U8_UART_IMIT_TIME_3s	30		//3s


#define	UART_MASTER			0		//主设备
#define	UART_SLAVE			1		//从设备

#define	U8_T30MS			3
#define U8_UART_DELAY_TIME_500ms 5		//500ms
#define U8_UART_DELAY_TIME_3s 	30		//3000ms
#define U8_UART_DELAY_TIME_3500ms 	35		//3500ms
#define U8_UART_DELAY_TIME_4500ms 	45		//4500ms

#define	U8_UART_DELAY_TIME_1000ms	10	// 1s  串口接收到数据后最少延时1s才能够主动上传数据
#define	U8_T30S					30		//30s  2014042301
#define	U8_T3S					30		// 3s 2014042502 3s时间到清除蜂鸣器响应比较标识

#define WifiUartSendByte(x)		((TXBUF2) = (x))  			//送入第一个字节	
#define	WifisUartGetByte(x)		((x) = (RXBUF2))

#define U8_MARST_05_ORDER			1		// 2014062601
#define U8_MARST_04_ORDER			2		// 2014062601
#define U8_MARST_CONFIGURE_ORDER	3		// WIFI配置命令 2014062601
#define	U8_MARST_CHECK_STRENGTH	4		//主动查询信号强度命令 2014062601
#define	U8_MARST_CLOSE_OPEN		5		// 主动发送关闭开启wifi命令 2014071601

#define	U8_TIME_10MIN				10		//  2014062601 10分钟


#define U8_CLIENT_MODE			0X01		//正常工作模式 2014071501
#define	U8_CONFIGURATION_MODE 0X02		//配置模式    2014071501
#define U8_AP_MODE				0X03		//AP模式      2014071501

ramExtern 	uchar	ucSendBufWifi[U8_UART_LENGTH];			//wifi发送数据缓冲区
ramExtern 	uchar	ucRecBufWifi[U8_UART_LENGTH];			//wifi接收数据缓冲区
ramExtern	uchar	ucSendCountWifi;			//发送字节计数变量
ramExtern	uchar	ucRecCountWifi;				//发送字节计数变量
ramExtern	uchar	ucSendTotalCnt;				//发送总的字节长度
//ramExtern	TYPE_UART	WifiComm;
ramExtern	uchar	ucSendKindMarst;				//主动上传类型变量
ramExtern	uchar	ucSendRecKind;					//WIFI接收到数据上传命令种类
ramExtern	uchar	ucSendKindMarstCnt;			//主动上传类型发送的计数
ramExtern	uchar	ucReceState;					//接收的状态
ramExtern	uchar	ucSendState;					//发送的状态
ramExtern	uchar	ucWifiRecFinishTime;			
ramExtern	uchar	ucWifiRecDataTime;				//接收到一个字节的时间计时变量
ramExtern	uchar	ucWifiSendDelayTime;
ramExtern	uchar	ucReceEndToSend;				//接收完成准备发送  2014042301
ramExtern	uchar	ucWifiNoRecDataInt;				//连续一段时间没有接收到串口数据就信息接收初始化处理 2014042301
ramExtern	uchar	ucWifiTimeOut;					//主动双传数据超时时间计时
ramExtern	uchar	ucTime30Min;

ramExtern	uchar	ucPowerSetKind;				// 2014042202
ramExtern	uchar	ucPowerSetMode;
ramExtern	uchar	ucPowerSetTime;
ramExtern	uchar	ucDustJSX;						// 灰尘浓度等级
ramExtern	uchar	ucSendMarstMake;
ramExtern	uchar	ucSendMarstTime;
ramExtern	uchar	ucSendMarstCount;
//ramExtern	uchar	ucT100ms_ReceBuzTime;					//接收到数据

ramExtern	uchar	ucFrameBak;					//帧序号备份标识 2014042604
ramExtern	uchar	ucSendClearPowerCnt;			// 2014071603 清除电表处理
ramExtern	uchar	ucSetHumidity;
ramExtern	uchar	ucSetHumidityBak;







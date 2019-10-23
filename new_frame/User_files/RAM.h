
/************************************************/
/*	RAM��FLAG����				*/
/************************************************/
#ifndef RAM
#define RAM

#ifdef root								//����main.c�ж��壬����.c�в�Ҫ#define֮
#define ramExtern 	 					//��main.c�м���"#define root", �� ramExtern ������Ϊ�գ�
#else				
#define ramExtern extern				//��������.c�ļ���û��"#define root",Ҳ�������ļ�ʱ�� ramExtern ������Ϊ"extern����������ض�������⡣
#endif									//(�����ÿ�������Ķ���ǰ��������� ramExtern



/*********************************************
��������
*********************************************/
#define 	u8_SOFTWARE_VERSION	1		//��ʾ������汾�� 
#define		u8_PROTOC0L_VERSION	2		//������Э��汾��
#define		u8_FRAME_VERSION	0		//���������Э��汾��

#define		u8_Item_Code_H			0x01 			//���ϱ��� P73001577018 PDM:	
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
#define     DeviceWrite			0xA0				// д
#define     DeviceRead			0xA1				// ��
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

#define     EeData      		0x80			//������ݴ洢��λ��


enum{MemoryState,MemoryFanSpeedGrade,Symbol,MemoryMode,MemorySetTemp,MemorySetFanSpeed,MemoryAssis,NUM17,NUM18,NUM19,NUM1A,NUM1B,NUM1C,NUM1D,NUM1E,MemorySum};

#define			MemorySetTim_equ	200			//200*100MS=20000MS=20S   �ϵ�20S�ڿ���ͨ��ң���������رյ������
#define			MemoryDisTim_equ  	50			//50*100ms=5000ms=5s			������������Ҫ��˸5��
#define			MemorySaveAddress	0x10
#define			Symbol_equ			0x6A
#define			MemoryNUM			16			//  2014042103

#define		MACHINE_TYPE		1				//��ѯ���ݵ�����
#define		FREMAXHAET			2
#define		FREMAXCOOL			3
#define		RFID				4				//��ѯID��


#define		RF_Eeprom_Addr		0x70	//RF���� E����ڵ�ַ
#define		EEPROM_DataLenth	0x0c	//RF���� ���ݳ��� 

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

#define	RF_SYNC_CREATLINK1		0xA5	//�������ͬ����
#define	RF_SYNC_CREATLINK0		0xB3

#define	RF_SYNC_HOST_NORMAL1	0xB5	//���س������ͬ����
#define	RF_SYNC_HOST_NORMAL0	0x5A
#define RF_GDO4RX				0x06	//GDO����ΪRX ���յ�ͬ����ʱ�任�����ݽ�����Ϸ��任

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

#define RF_CHANNEL				21		//ͨ��Ƶ��    
#define	RF_HOST_NORMALADDR		0xAC	//���س�����յ�ַ

#define	RF_SYNC_GUESTCTRL1		0xE6	//ң�ؿ��Ʒ���ͬ����
#define	RF_SYNC_GUESTCTRL0		0xE7	

#define 	RF_DATALENTH		20		//���ݰ�����
#define 	RF_PKTLENTH			29		//���ݰ�����
#define 	RF_GDO4TX			0x06	//GDO����ΪTX
#define 	RF_PKTLEN_SHORT		30		//��ָ������� 30�ֽ�


#define	AIRCONDITIONER_TYPE		0x03	//�յ��������ͣ�


#define	POWER_FOR_CREATLINK_STEP0	0x15	//�����һ�׶ι���	-15dBmW
#define	POWER_FOR_CREATLINK_STEP1	0x12	//�����һ�׶ι���	5dBmW	
#define	POWER_FOR_WORK				0x10	//������������		10dBmW

#define	CreateLinkTotalTime		20
#define	CreateLinkFinshTime		3


#define	RF_code_db	0x15				//���빦��



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

#define     ForceKeyEqu         1                  //ǿ�ư���
#define     CleanKeyEqu         2                  //��ఴ��
#define     NoKeyEqu            0                  //û�а�������


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

#define 	clrb(x,y) 	(x&=~(1<<y))  	//λ��0
#define 	setb(x,y) 	(x|= (1<<y))  	//λ��1
#define 	getb(x,y) 	(x&(1<<y))    	//λ�ж�
#define 	xorb(x,y) 	(x^=(1<<y))   	//λȡ��


#define     Delay1Us()      asm("nop"); asm("nop"); asm("nop"); asm("nop")
#define     NOP()           asm("nop")

#ifdef 		root

const	uchar BuzTimeTAB[]={0,0,0,0,0,0,0,0,1,0,        //��������
	                        4,6,4,6,4,6,4,50,1,0,    	//�ϵ������ʱ���  1,1��ʾ������һ��; 1,0����������                           
                            1,1,3,4,3,4,3,50,1,0,       //����������ʱ���
                            1,1,3,4,3,4,3,50,1,0,       //�ػ�������ʱ���
                            1,1,1,1,1,1,4,50,1,0,       //һ�������ʱ���
                            1,1,2,4,2,3,2,50,1,0,       //����������ʱ���
                            1,1,2,4,2,3,2,50,1,0,     	//�½�������ʱ���
                            3,4,3,4,3,4,3,50,1,0,};     //���������ʱ���  3/4��  	
 
const	uchar BuzFreqTAB[]={0,0,0,0,                   	//��������
	                        69,61,53,45,               	//�ϵ������Ƶ�ʱ�
	                        0,61,57,53,                	//����������Ƶ�ʱ�
	                        0,45,53,61,                	//�ػ�������Ƶ�ʱ�
                            0,0,0,53,                  	//һ�������Ƶ�ʱ�       
                            0,77,69,61,                	//����������Ƶ�ʱ�     
                            0,61,69,77,             	//�½�������Ƶ�ʱ� 
                            85,75,65,55,}; 		  		//���������Ƶ�ʱ�    7

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
                           	0x0E,};  		//�ͷ�  
                           	
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

const  uchar  ucdefaultPAtable[8] = {	0xc0,	0xc8,	0x84,	0x60,	0x34,	0x1d,	0x0e,	0x12};		//Ĭ��PA���
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


const	unsigned char  ucPQTempTab[256] = { //�¶�ֵ	    ADֵ	�¶�ֵ	����ֵ
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
	0xBB		//80 ��ʾ��
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
��������
*********************************************************************/    

/**** �˴�����FLAG��λѡַ ****/
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

ramExtern	uchar  	Display_get1;	    //��ʾ���ݻ���
ramExtern	uchar  	Display_get2;	    //��ʾ���ݻ���
ramExtern	uchar  	Display_get3;	    //��ʾ���ݻ���
ramExtern	uchar  	Display_get4;	    //��ʾ���ݻ���
ramExtern	uchar  	Display_get5;	    //��ʾ���ݻ���


ramExtern	uchar  	ucDisplay_1;	    //��ʾ����ˢ�»���
ramExtern	uchar  	ucDisplay_2;	    //��ʾ����ˢ�»���
ramExtern	uchar  	ucDisplay_3;	    //��ʾ����ˢ�»���
ramExtern	uchar  	ucDisplay_4;	    //��ʾ����ˢ�»���
ramExtern	uchar	ucDisplay_5;
ramExtern	uchar	ucT_2min;					//ͨѶ����2min��ʱ
ramExtern	uchar	ucRecOneTime;

ramExtern 	uint  	uiMeasure_1;  	     		//����ң�ؽ��տ��1
ramExtern 	uint  	uiMeasure_2;		 		//����ң�ؽ��տ��2
ramExtern 	uint	uiRecWidth;					//ң�ؽ��տ��



ramExtern	uchar	ucSendBuf[20];		       	//�������ݻ���
ramExtern	uchar	ucRecbuf[20];		       	//UART��������
ramExtern 	uchar  	ucTrCount;		           	//���͸���
ramExtern 	uchar	ucSeprate_count;			//ң�ؽ��շָ�������
ramExtern 	uchar	ucEnterRestCount;			//����͹��ļ�ʱ��
ramExtern 	uchar	ucT_CLRTM00;				//ң�ؽ��ճ�ʼ��ʱ��  
ramExtern	uchar	ucBitCount;					//ң�ؽ���λ��
ramExtern 	uchar  	ucRecData1;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRecData2;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRecData3;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRecData4;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRecData5;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRecData6;		    		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_1;		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_2;		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_3;		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_4;		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_5;		//ң�ؽ�������
ramExtern 	uchar  	ucRec_data_Frame1_6;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_1;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_2;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_3;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_4;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_5;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame2_6;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_1;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_2;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_3;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_4;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_5;		//ң�ؽ�������
ramExtern	uchar  	ucRec_data_Frame3_6;		//ң�ؽ�������
//ramExtern	uchar	i;							//�����ж��������ʱ����
//ramExtern	uchar	j;							//�����ж��������ʱ����
//ramExtern	uchar	k;							//�����ж��������ʱ����
ramExtern	uchar	ucT_80ms;
ramExtern	uchar	ucT_20ms;					//20ms��ʱ
ramExtern	uchar	ucT_10ms;					//4ms��ʱ
ramExtern	uchar	ucpower_1min;				//�ϵ�1���Ӽ�ʱ
ramExtern	uchar	ucStopTime1s;				//�͹���1s��ʱ����  2013071302
ramExtern	uchar	ucT10sBasetime;				//10s ��׼ʱ����� 2013091602
ramExtern	uint	uiPowerOnTime;				//�ϵ�ʱ���ʱ  2014052901
ramExtern	uchar	ucMemoryDisTim;
ramExtern	uchar	ucPowerRemoteCount;
ramExtern	uchar	ucUpDownRemoteCount;
ramExtern	uchar	ucDispCodeRemoteCount;
ramExtern	uchar	ucDispCodeRemoteTime;		//10s�ڽ��յ�5�������źš�


ramExtern	uchar	ucEE_address;				//E���ĵ�ַ
ramExtern	uint	uiReceiveLength;				//д��E���ĳ���
ramExtern	uchar	ucT_100ms;					//100ms��ʱ
ramExtern	uchar	ucT_1s;						//1���ʱ
ramExtern	uchar	ucSpecilMode;				//��ʾ������Ϣ
ramExtern	uchar	ucFanSpeedSetGrade;			//�����趨�ȼ�1%-100%
ramExtern	uchar	ucFanSpeedSetGradeBack;		//�����趨�ȼ���ʱ����
//ramExtern	uchar	ucTimeFanSpeedSetState;		//�����趨״̬��ʱ
ramExtern	uchar	ucNumberDisp;				//˫8��ʾ����
ramExtern 	uchar	ucNumber1;					//��ʾ����ʮλ
ramExtern 	uchar	ucNumber2;					//��ʾ���ָ�λ
ramExtern	uchar	ucNumber0;

ramExtern	uchar	ucSetTemp;					//�յ��趨�¶�
ramExtern	uchar	ucT1DispSampCount;			//T1�¶Ȳ��������ʱ��
ramExtern	uchar	ucBarWritePageCount;		//������д��E��ҳ������
ramExtern	uchar	ucPowerOn_5S;				//�ϵ�5���ʱ,���ڿ��
ramExtern	uchar	ucAbilityTestNewData;		//�������������־��(�·�ʽ����)
ramExtern	uchar	ucAbilityComFreqData;		//��������ѹ��Ƶ��
ramExtern	uchar	ucAbilityValveData;			//����������ͨ��״̬
ramExtern	uchar	ucAbilityExpandValveData;	//�������Ե������ͷ�����
ramExtern	uchar	ucAbilityTempExData;		//������������Ŀ���¶�
ramExtern	uchar	ucAbilityInFanSpeedDataL;	//���������ڷ��ת�� ���ֽ�
ramExtern	uchar	ucAbilityInFanSpeedDataH;	//���������ڷ��ת�� ���ֽ�
ramExtern	uchar	ucAbilityOutFanSpeedDataL;	//������������ת�� ���ֽ�
ramExtern	uchar	ucAbilityOutFanSpeedDataH;	//������������ת�� ���ֽ�

//ramExtern	uint	uiAbilityInFanSpeedData;	//���������ڷ��ת��
//ramExtern	uint	uiAbilityOutFanSpeedData;	//������������ת��


ramExtern	uchar	ucAbilityHeatFrostFreqData;	//�������Ե������Ȼ�˪Ƶ��
ramExtern	uchar	ucAbilityHeatFrostTimeData;	//�������Ե������Ƚ���ʱ����
ramExtern	uchar	ucAbilityHeatT3Data;		//�������Ե������Ƚ���T3�¶�
ramExtern	uchar	ucDispState;			//��ʾ״̬ 0:������ʾ�趨�¶� 1:T1 2��T4 3����ʾ��?
ramExtern	uchar	ucDispStateBuf;
ramExtern	uchar	ucTimeDispState;			//��ʾ״̬5����ʱ��ʱ��
ramExtern	uchar	ucTimeDispStateWifi;		//���ڹػ���wifiͼ����ʾ15s�ļ�ʱ����
ramExtern	uchar	ucTimeDispHumi;				//������ʾ�趨ʪ�ȱ���
ramExtern 	uchar	ucT_DisAll_3S;				//�ϵ�ȫ��3�����
//ramExtern 	uchar	ucError_backup;				//���ϱ���
ramExtern 	uchar	ucError1Buf;				//���ϱ�־�ݴ���
ramExtern 	uchar	ucError2Buf;				//���ϱ�־�ݴ���
ramExtern 	uchar	ucProtect1Buf;				//������־�ݴ���
ramExtern 	uchar	ucProtect2Buf;				//������־�ݴ���
ramExtern 	uchar	ucTimeDispTemperErr;		//������������ʾ15���ʱ
ramExtern 	uchar	ucBuzMusicBac;
ramExtern 	uchar	ucErrorKind;				//������ʾ������
ramExtern 	uchar	ucLockFlashDispCount;		//������˸5��ָʾ��ʱ��
ramExtern 	uchar	ucTemperT1Dis;				//���ڻ����¶�T1,������ʾ
ramExtern 	uchar	ucFreqGrade;				//Ƶ������ʾ
ramExtern 	uchar	ucTemperT4;					//���⻷���¶�T4
//ramExtern 	uchar	ucRunKind;					//������ʱ��ʾ������
ramExtern 	uchar	ucTemperT2;					//���ڻ����¶�T2
ramExtern 	uchar	ucTemperT3;					//���ڻ����¶�T3
ramExtern 	uchar	ucTemperTp;					//���������¶�Tp��ADֵ
//ramExtern	uchar	uchostID[4];				//��������ID
ramExtern	uchar	ucAbilityDispTime;			//����������ʾ"FL"1���Ӽ�ʱ
ramExtern	uchar	ucRF_tunnel;				//��Ƶͨ����
//ramExtern	uchar	uctest;						// #test
//ramExtern	uchar	ucT2sMode;					//2���ȷ��ģʽ
//ramExtern	uchar	ucTEnalbeDrive;				//2���������ȸ��ظı�֮����
//ramExtern	uchar	ucSpeedKeySetCount;			//���ټ��趨����
//ramExtern	uchar	ucTimeFanSpeedSetState;		//�����趨״̬��ʱ
//ramExtern	uchar	ucTClrTestrun1;				//������30���Ӻ��˳�����1
//ramExtern	uchar	ucTClrTestRun2;				//������30���Ӻ��˳�����2
//ramExtern	uchar	uck6offdelay;				//����ɨ��̧����ʱ
//ramExtern	uchar	uck6ondelay;				//����ɨ����ʱ
//ramExtern	uchar	ucRtempFlashTime1;			//����������0.5���ʱ 
//ramExtern	uchar	uck6offdelay;				//����ɨ��̧����ʱ
//ramExtern	uint	uik6ondelay;				//����ɨ����ʱ


ramExtern	uchar	ucAbilityTestData;			//��������(�ɷ�ʽ����)
ramExtern	uchar	EeCheckDelay;				//��дE����ʱ100ms
//ramExtern	uchar	uc_radom;					//�����
ramExtern	uchar	ucT_400ms;					//400ms��ʱ
ramExtern	uchar	ucMainFreTime;				//��ʾ���Ƶ������ʱ��
ramExtern	uchar	ucMainFre;					//��ʾ�����Ƶ��
ramExtern	uchar	ucPollingType;				//A9�Ĳ�ѯָ��
ramExtern	uchar	ucMainTypeTime;				//��ʾ����ʱ��
ramExtern	uchar	ucMainType;					//��ʾ�Ļ�������
ramExtern	uchar	ucMachineTypeSet;			//��������


//ramExtern	uchar	ucT1s_SleepS;				//��˯ģʽ���ʱ����
//ramExtern	uchar	ucT1min_SleepMin;				//��˯ģʽ���Ӽ�ʱ����
//ramExtern	uchar	ucT1h_SleepHour;				//��˯ģʽСʱ��ʱ����
ramExtern	uchar	ucSleepTime;				//ң��������˯��ʱ��
ramExtern	uchar	ucSleepTemp1;				//ң��������˯��ʱ���趨�¶�
ramExtern	uchar	ucSleepTemp2;				//ң��������˯��ʱ���趨�¶�
ramExtern	uchar	ucSleepTemp3;				//ң��������˯��ʱ���趨�¶�
ramExtern	uchar	ucSleepTemp4;				//ң��������˯��ʱ���趨�¶�
ramExtern	uchar	ucSleepTemp5;				//ң��������˯��ʱ���趨�¶�


ramExtern	uchar	EepErrDispCount;			//E��ͨѶ������˸��ʾ4�μ�ʱ��
ramExtern	uchar	ucT_TimeToOpenClose_10S;	//��ʱ���ػ�10��ʱ��
//ramExtern	uchar	ucFanSpeedSetGradeBack1;	//�����趨�ȼ���ʱ����
//ramExtern	uchar	ucRecChksum;				//UART��������У���// 2014042401  У��Ͳ������жϴ���
//ramExtern	uchar	ucCycle;					//// 2014042401  У��Ͳ������жϴ���
ramExtern	uchar	ucTypeCmp;					//�ϵ��,��ȡ���ͱȽ�ֵ
ramExtern	uchar	ucGetRightFirst;			//�ϵ�ͨѶ5�����ݼ���
ramExtern	uchar	ucTemp_T1;					//���ڻ����¶�T1
//ramExtern	uchar	ucFanSpeed;					//���ڿ��Ƹ��صķ���
//ramExtern	uchar	ucFanSpeedCurrentGrade;		//��ǰ���ٵȼ�1%-100%
ramExtern	uchar	EeCheckWrSymbol;			//E��ͨѶ���ϼ��ʱд��������ֽ�
ramExtern	uchar	EeCheckRdSymbol;			//E��ͨѶ���ϼ��ʱ�����Ƚϵ������ֽ�
//ramExtern	uchar	ucRFInitUIDCtn;				//������ʱʱ��
//ramExtern	uchar	ucRF_data[RF_DATALENTH];	//��Ƶ���ݼĴ���
//ramExtern	uchar	ucRF_dataBuf;
//ramExtern	uchar	ucRF_buffer[RF_PKTLENTH];	//��Ƶ����
//ramExtern	uchar	uchostID_EE[4];				//��E��������ID
//ramExtern	uchar	ucRead_count;				//��ȡ����
//ramExtern	uchar	ucReadErrorCnt;				//��Ϊ���պ����У�����
//ramExtern	uchar	ucT_Link2S;					//������2���ʱ
//ramExtern	uchar	ucT_RF_RESET;				//��RFģ����г�ʼ��ʱ�����
//ramExtern	uchar	ui2scount;					//CC1100 2s�����ʱ
//ramExtern	uchar	ucTestLinkTimes;			//���ӳɹ��Ĵ���
//ramExtern	uchar	ucrandom0;
//ramExtern	uchar	ucRF_Tx_ADDR;				//ң�������ݽ��յ�ַ
//ramExtern	uchar	ucPkt_Rx_Type;				//�������ݰ�����
//ramExtern	uchar	ucguestID[4];				//�߿���ID  2014061903
//ramExtern	uchar	ucPkt_Tx_Type;				//�������ݰ�����
ramExtern	uchar	ucT_send;					//��������֮��,�������ģʽ��ʱ��
ramExtern	uchar	ucStrong_count;				//ǿ�����Ĵ���
ramExtern	uchar	ucStrong_time;				//ǿ����������ʱ���ʱ
ramExtern	uchar	ucModeSet_backup;			//�趨ģʽ����
ramExtern	uchar	ucSetTemp_bac;				//�趨�¶ȱ���
//ramExtern	uchar	ucStSpeed_bac;				//�趨���ٱ���
ramExtern	uchar	ucFanSpeedSetGrade_bac;		//�趨��������
//ramExtern	uchar	ucT_RF_10S;					//10��ʱ���ʱ
ramExtern	uchar	ucBarExitTime;				//������������
ramExtern	uchar	uckeyCounter;				//������������	
ramExtern	uchar	uckeyTime10s;				//10���ʱ
ramExtern	uchar	ucBarCount;					//��������ʾ����
ramExtern	uchar	ucT100msBarShowTime;

ramExtern	uchar	ucT_60ms;					//60ms��ʱ
ramExtern	uchar	ucIFeel_IDone;				//�����ID��
ramExtern	uchar	ucIFeel_IDtwo;				//�����ID��
ramExtern	uchar	ucIFeel_IDthr;
ramExtern	uchar	ucTime_test_5S;				//�������Թر���ʾʱ,�а���5�����Ϩ��
//ramExtern	uchar	ucIFeel_IDthr;
//ramExtern	uchar	uctimerled;
//ramExtern	uchar	ucledDispType;				//��������ʾ����

ramExtern	uchar	ucSendNoEcoCnt;				//��������û��ECO���ܼ���
//ramExtern	uchar	ucModeStep;

//ramExtern	uchar	ucModeTime;
//ramExtern	uchar	ucmodeFlash;				//ģʽҪ��ʾ�Ķ�������
//ramExtern	uchar	ucfanStep;
//ramExtern	uchar	ucfanTime;
//ramExtern	uchar	ucTempUpTime;
//ramExtern	uchar	ucTempUpStep;
ramExtern	uchar	ucShow5s;					//����ң���ź���ʾ5s
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
ramExtern	uchar	ucUartSendtype;				//UART��������������
ramExtern	uchar	ucUartA5count;				//A5����������
ramExtern	uchar	ucUartAFcount;				//AE����������

ramExtern uchar ucSampCnt;
ramExtern uint uiADCSum;
ramExtern uint uiADCMax;
ramExtern uint uiADCMin;
ramExtern uint uiADCSum10;
ramExtern uint uiRTADSamp;
ramExtern uchar	ucADchannel;		//AD����ͨ����


ramExtern	uchar	ucsetfre;					//Ŀ��Ƶ��
ramExtern	uchar	ucrunfre;					//����Ƶ��
//ramExtern	uchar	uctimefan;			
ramExtern	uchar	ucEEVersion;				//���ڲ����汾��
ramExtern	uchar	ucEEOutVersion;				//��������汾��
//ramExtern	uchar	ucWriteEE_IDone;
//ramExtern	uchar	ucWriteEE_IDtwo;
//ramExtern	uchar	ucWriteEE_IDthr;



//ramExtern	uchar	ucRFenable;					//��Ƶ����������
ramExtern	uchar	ucTestDataKind;
//ramExtern	uchar	ucSendSoundCnt;				//������������������
ramExtern	uchar	ucSendTestKind;
//ramExtern	uchar	ucKeynum;
//ramExtern	uchar	ucKeynumone;
//ramExtern	uchar	ucKeyData;
//ramExtern	uchar	ucKeyn;

ramExtern	uchar	ucT1min_forcet;					//ǿ������30���Ӽ�ʱ����
ramExtern	uchar	ucforeckeycount;					//������������
ramExtern	uchar	ucT1s_1min;				//1���Ӽ�ʱ���� 
ramExtern	uchar	ucShowv3sec;			//��ѯ����汾��3s��ʱ����

//ramExtern	uchar	ucOff_6S;					//�ػ���6��,����A5���������A2����						
ramExtern	uchar	ucDisError;
//ramExtern	uchar	ucSoftSleep_IDone;				// 2014061903
//ramExtern	uchar	ucSoftSleep_IDtwo;				// 2014061903
//ramExtern	uchar	ucSoftSleep_IDthr;				// 2014061903
ramExtern	uchar	ucSleepMin;	
ramExtern	uchar	ucSleepHour;
ramExtern	uchar	ucSleep1min;
//ramExtern	uchar	ucSleep3Time;
ramExtern	uchar	ucSleepMode;				//��˯ģʽ

ramExtern 	uint	uiT_Save;					//ʡ�繦��2Сʱ��ʱ
ramExtern 	uint	uiT_TimeToClose;			//��ʱ��ʱ��,10��һ����λ
ramExtern 	uint	uiT_TimeToOpen;				//��ʱ��ʱ��,10��һ����λ
//ramExtern	uint	ucT_RF_initial;				//�̶�ʱ���RFģ����г�ʼ��ʱ�����
ramExtern	uchar	ucSendUartDataCnt;				//���͸����ذ����ݼ�������
ramExtern	uchar	ucReceUartDataCnt;				//���յ����ذ����ݼ�������
ramExtern	uchar	ucBarCodeSendArrayCommand;//�������ص�����������
ramExtern   uchar		ucWifiStength;						// 2014062601 wifi�ź�ǿ��
ramExtern	uchar		ucReceStrenthTime;					//2014062601 ���յ��ź�ǿ�������ʱ������10����û���յ�����Ĭ��û���ź�
ramExtern	uchar		ucWifiLinkState;
ramExtern	uchar		ucWifiLinkMode;
ramExtern	uint		uiWifiAPModeTime;



ramExtern 	uchar	ucWirte_EE_buf[130];		//ң����д��E������
ramExtern	uchar	ucInDoorBarCodeBuf[BAR_CODE_NUMBER];	//�������������ݻ�����


ramExtern	uchar		ucOutCodingData[25];							//�������ϱ����ѹ��������
ramExtern	uchar		ucOutInTimeData[38];							// 3������+2=38��
#define 	ucHumidity	ucOutInTimeData[0]
#define 	ucTsc		ucOutInTimeData[1]

ramExtern	uchar		ucOutsetfre;								// 2014042503 ����Ŀ��Ƶ��

ramExtern	uchar		ucOutInRamData[16];							// 16��ram����
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

#define		ucStepState			ucStepStatePos[0]					//������״̬ 2014030601			
			
#define		ucCoolHorSwLimitDown	ucStepStatePos[1]				//���µ���������ҡ������ 2014030601	
#define		ucCoolHorSwLimitUp	ucStepStatePos[2]					//���µ���������ҡ������ 2014030601	
#define		ucHeatHorLimitDown	ucStepStatePos[3]					//���µ��������� 2014030601	
#define		ucHeatHorLimitUp	ucStepStatePos[4]					//���µ��������� 2014030601	
#define		ucStepHorNowTgt		ucStepStatePos[5]					//���µ�������ǰ�Ƕ� 2014030601

#define		ucStepVerSwLimitDown	ucStepStatePos[6]					//���ҵ�����ҡ������ 2014030601	
#define		ucStepVerSwLimitUp 	ucStepStatePos[7]					//���ҵ�����ҡ������ 2014030601	
#define		ucStepVerNowTgt		ucStepStatePos[8]					//���ҵ�������ǰ�Ƕ� 2014030601	


#define		ucStepUpSwLimitDown	ucStepStatePos[9]					//�����絼����ҡ������ 2014030601	
#define		ucStepUpSwLimitUp 		ucStepStatePos[10]					//�����絼����ҡ������ 2014030601
#define		ucStepUpNowTgt		ucStepStatePos[11]					//�����絼������ǰ�Ƕ� 2014030601	

#define		ucStepNextSwLimitDown		ucStepStatePos[12]					//�����絼����ҡ������ 2014030601	
#define		ucStepNextSwLimitUp 		ucStepStatePos[13]					//�����絼����ҡ������ 2014030601
#define		ucStepNextNowTgt			ucStepStatePos[14]

ramExtern	uchar		ucStepStateSet[12];

#define		ucSetStepState			ucStepStateSet[0]					//���õ�����״̬ 2014030601						
#define		ucSetStepCoolHorDown	ucStepStateSet[1]					//�������µ�����ҡ������ 2014030601	
#define		ucSetStepCoolHorUp		ucStepStateSet[2]					//�������µ�����ҡ������ 2014030601	
#define		ucSetStepHeatHorDown	ucStepStateSet[3]					//�������µ�����ҡ������ 2014030601	
#define		ucSetStepHeatHorUp		ucStepStateSet[4]	
#define		ucSetStepHorNowTgt		ucStepStateSet[5]					//�������µ�������ǰ�Ƕ� 2014030601	
#define		ucSetStepVerLimitDown	ucStepStateSet[6]					//�������ҵ�����ҡ������ 2014030601	
#define		ucSetStepVerLimitUp	ucStepStateSet[7]					//�������ҵ�����ҡ������ 2014030601	
#define		ucSetStepVerNowTgt		ucStepStateSet[8]					//�������ҵ�������ǰ�Ƕ� 2014030601	
#define		ucSetStepUpLimitDown	ucStepStateSet[9]					//���ö����絼����ҡ������ 2014030601	
#define		ucSetStepUpLimitUp		ucStepStateSet[10]					//���ö����絼����ҡ������ 2014030601	
#define		ucSetStepUpNowTgt		ucStepStateSet[11]					//���ö����絼������ǰ�Ƕ� 2014030601



//ramExtern	uchar	ucBarCode;		       		// ͷ��0xbb
//ramExtern	uchar	ucBarCode1;		       		// ����1
//ramExtern	uchar	ucBarCode2;		       		// ����2
//ramExtern	uchar	ucBarCode3;		       		// ����3
//ramExtern	uchar	ucBarCode4;		       		// ����4
//ramExtern	uchar	ucBarCode5;		       		// ����5
//ramExtern	uchar	ucBarCode6;		       		// ����6
//ramExtern	uchar	ucBarCode7;		       		// ����7
//ramExtern	uchar	ucBarCode8;		       		// ����8
//ramExtern	uchar	ucBarCode9;		       		// ����9
//ramExtern	uchar	ucBarCode10;		   		// ����10
//ramExtern	uchar	ucBarCode11;		   		// ����11
//ramExtern	uchar	ucBarCode12;		   		// ����12
//ramExtern	uchar	ucBarCode13;		   		// ����13
//ramExtern	uchar	ucBarCode14;		   		// ����14
//ramExtern	uchar	ucBarCode15;		   		// ����15
//ramExtern	uchar	ucBarCode16;		   		// ����16
//ramExtern	uchar	ucBarCode17;		   		// ����17
//ramExtern	uchar	ucBarCode18;		   		// У��
//ramExtern	uchar	ucBarCode19;		   		// β��0x33
//ramExtern	uchar	ucBarCode20;		   		// ��1 0x00
//ramExtern	uchar	ucBarCode21;		   		// ��2 0x00
//ramExtern	uchar	ucBarCode22;		   		// ��3 0x00
//ramExtern	uchar	ucBarCode23;		   		// ��4 0x00

												//����У����
ramExtern	uchar	ucBarCodeChk;		   		// ͷ��0xbb
ramExtern	uchar	ucBarCodeChk1;		   		// ����1
ramExtern	uchar	ucBarCodeChk2;		   		// ����2
ramExtern	uchar	ucBarCodeChk3;		   		// ����3
ramExtern	uchar	ucBarCodeChk4;		   		// ����4
ramExtern	uchar	ucBarCodeChk5;		   		// ����5
ramExtern	uchar	ucBarCodeChk6;		   		// ����6
ramExtern	uchar	ucBarCodeChk7;		   		// ����7
ramExtern	uchar	ucBarCodeChk8;		   		// ����8
ramExtern	uchar	ucBarCodeChk9;		   		// ����9
ramExtern	uchar	ucBarCodeChk10;		   		// ����10
ramExtern	uchar	ucBarCodeChk11;		   		// ����11
ramExtern	uchar	ucBarCodeChk12;		   		// ����12
ramExtern	uchar	ucBarCodeChk13;		   		// ����13
ramExtern	uchar	ucBarCodeChk14;		   		// ����14
ramExtern	uchar	ucBarCodeChk15;		   		// ����15
ramExtern	uchar	ucBarCodeChk16;		   		// ����16
ramExtern	uchar	ucBarCodeChk17;		   		// ����17
ramExtern	uchar	ucBarCodeChk18;		   		// У��
ramExtern	uchar	ucBarCodeChk19;		   		// β��0x33
//ramExtern	uchar	ucBarCodeChk20;		   		// ��1 0x00
//ramExtern	uchar	ucBarCodeChk21;		   		// ��2 0x00
//ramExtern	uchar	ucBarCodeChk22;		   		// ��3 0x00
//ramExtern	uchar	ucBarCodeChk23;		   		// ��4 0x00

ramExtern	uchar	ucBarDisp[22];		   		//�������������ʾ

ramExtern	uchar	SleepTwoTemp[9];			//��˯2���趨�¶�

//ramExtern	uchar   ucRF_data_buf[20];			//����ң����дE��
ramExtern	uchar	ucT1sResttime;
ramExtern	uchar	ucWriteEEDataGroup;			//д�ڼ���EE����
ramExtern	uchar	ucT100msDispWriteT;			//д��E���ɹ���ʧ����ʾ5s��ʱ����
ramExtern	uchar	ucTestData[34];
//ramExtern	uchar	ucCurVol;
#define		ucCurVol	ucTestData[4]

ramExtern	uchar	ucWriteEEDataSendCount;		//������дEE����
ramExtern	uchar	ucEepromErrDisCnt;			//E�����Ͽ��ʱ��ʾ����
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

ramExtern	uchar	ucT1sOutEEtime;			//��������E����ʱ���ʱ����  2014040901
ramExtern	uchar	ucWriteOutEELength;		//��������E��������		2014040901
ramExtern	uchar	ucWriteOutEEFram;		//��������E����֡��		2014040901

ramExtern	uchar	ucTemperFeel;				//���յ�������¶�
ramExtern	uchar	ucTemperT1;					//��ʾ�������¶ȱ���
ramExtern	uchar	ucFeel7min;					//�����7���Ӽ�ʱ���� 
ramExtern	uchar	ucTemperT1_ad;				//
ramExtern	uchar	ucDust_ThickL;				//�ҳ����м��Ũ�ȵ��ֽ�
ramExtern	uchar	ucDust_ThickH;				//�ҳ����м��Ũ�ȸ��ֽ�
ramExtern	uchar	ucPMV_Angle;				//�������ͷ����� 2013091702
ramExtern	uchar	ucOutFan_Speed;				//������ת��	2013091702
ramExtern	uchar	ucInFan_Speed;				//���ڷ��ת��	2013091702
ramExtern	uchar	ucInFan_SpeedAturn;			//���ڷ��ʵ��ת��	2013091702

ramExtern	uchar	ucPMVMode;				//PMVģʽ 
ramExtern	uchar	ucPMVModeBak;				//PMVģʽ���ݱ�ʶ

ramExtern	uchar	ucFreMax;				//���Ƶ������
ramExtern	uchar	ucModeModify;				//���Ƶ�����Ƶ�ģʽ
ramExtern	uchar	ucSendA6A8Count;				//���Ƶ�����Ƶ�ģʽ
ramExtern	uchar	ucT100ms_ShowTypeTime;				//��ʾ������Ϣ2s��ʱ����
ramExtern	uchar	ucTypeInfor;				//������Ϣ����
ramExtern	uchar	ucTimeDispEFErr;			//���ģ�������ʾ15ʱ���ʱ
//ramExtern	uchar	ucNaturMode;					//

ramExtern	uchar		Identifier[16];			//2013102301 ���ӵ��ģ�鴦��
#define	ucIdentifier Identifier[0]
#define ucEEDayh	Identifier[1]
#define ucEEDay	Identifier[2]
#define ucEEHour	Identifier[3]
#define ucEEMin	Identifier[4]
#define ucEEDay_onh	Identifier[5]		//����ʱ�����ڵĸ��ֽ�
#define ucEEDay_on	Identifier[6]
#define ucEEHour_on	Identifier[7]
#define ucEEMin_on	Identifier[8]

#define ucRunPowerTotal0	Identifier[9]			//�ۼ����е���
#define ucRunPowerTotal1	Identifier[10]
#define ucRunPowerTotal2	Identifier[11]
#define ucRunPowerTotal3	Identifier[12]

#define ucchecksum	Identifier[15]

ramExtern	uchar	ucPowerConsum[4];
#define ucPowerConsum0	ucPowerConsum[0]			//�ܺĵ���
#define ucPowerConsum1	ucPowerConsum[1]
#define ucPowerConsum2	ucPowerConsum[2]
#define ucPowerConsum3	ucPowerConsum[3]


ramExtern	uchar   ucEEMin_now;                    //��������ʱ��
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
#define	ucRunPowerCon0 ucRunPowerCon[0]      //�������е���
#define	ucRunPowerCon1 ucRunPowerCon[1]       //�������е���
#define	ucRunPowerCon2 ucRunPowerCon[2]       //�������е���
#define	ucRunPowerCon3 ucRunPowerCon[3]       //�������е���

//ramExtern	uchar		ucRunPowerTotal[4];
//#define	ucRunPowerTotal0 ucRunPowerTotal[0]       //�ۼ����е���
//#define	ucRunPowerTotal1 ucRunPowerTotal[1]       //�ۼ����е���
//#define	ucRunPowerTotal2 ucRunPowerTotal[2]       //�ۼ����е���
//#define	ucRunPowerTotal3 ucRunPowerTotal[3]       //�ۼ����е���

ramExtern	uchar		ucRunPowerTotalTemp[4];
#define	ucRunPowerTotalTemp0 ucRunPowerTotalTemp[0]       //
#define	ucRunPowerTotalTemp1 ucRunPowerTotalTemp[1]       //
#define	ucRunPowerTotalTemp2 ucRunPowerTotalTemp[2]       //
#define	ucRunPowerTotalTemp3 ucRunPowerTotalTemp[3]       //

ramExtern	uchar		ucMemorySetState[MemoryNUM];		//16 BYTES
ramExtern	uchar		ucMemorySetStatebak[MemoryNUM];		//16 BYTES



ramExtern 	uchar *ucRamAddPtr;

ramExtern	uint	uiBuzzerKind;			//��������������

ramExtern	uchar	ucT100msSendAFT10s;	// 2014061602
ramExtern	uchar	ucT100msSendA5T5s;		// 2014061603


/*********************************************************************
λ����
*********************************************************************/
#define		fgRecIni		FLAG0.bit.b0     			//ң������ʼ����־ 
#define		fgEnterRest     FLAG0.bit.b1				//��������
#define		fgstop			FLAG0.bit.b2				//���ڵ͹��ı�־
#define		fgCodeHeader	FLAG0.bit.b3				//����ͷ��
#define		fgHeaderCodeLow FLAG0.bit.b4				//ͷ��͵�ƽ		
#define		fgRecPro		FLAG0.bit.b5				//ң�ش����־
#define		fgMse20			FLAG0.bit.b6				//20ms��־	
#define		fg20mskey		FLAG0.bit.b7				//����20ms��ʶ��20ms����һ�ΰ����ź� 

#define		fgKeyTouchInt	FLAG1.bit.b0				//�����źų�ʼ��ʶ
#define		fgcleankey		FLAG1.bit.b1				//
#define		fg_100ms		FLAG1.bit.b2				//100MS��־
#define		fg1sCheck		FLAG1.bit.b3				//1��ʱ��
#define		fgTestRun		FLAG1.bit.b4				//�����б�־
#define		fgTimer_noclear		FLAG1.bit.b5				//��Ƶң���źŵĶ�ʱ��Ϣ
#define		fgPtcAssis_noclear	FLAG1.bit.b6				//��Ƶң���źŵĵ縨���ź�
#define		fgSavePro		FLAG1.bit.b7				//ң��ʡ�紦���־

#define     ucModeSet     	FLAG2.byte 		  			//�趨ģʽ
#define     fgHeatMode     	FLAG2.bit.b0	      		//����ģʽ
#define     fgCoolMode     	FLAG2.bit.b1        		//����ģʽ
#define     fgFanMode      	FLAG2.bit.b2       	 		//�ͷ�ģʽ
#define     fgDryMode      	FLAG2.bit.b3        		//��ʪģʽ 				
#define     fgAutoMode     	FLAG2.bit.b4        		//�Զ�ģʽ  
														//ʣ�µı�־λ����ʹ��


#define	 	fgSendABWait	FLAG3.bit.b0     			//����AB�����ʶ
#define  	fgSendACWait   FLAG3.bit.b1     			//����AC�����ʶ
#define  	fgSendADWait    FLAG3.bit.b2     			//����AD�����ʶ
#define  	fgSendAEWait    FLAG3.bit.b3     			//����AE�����ʶ
#define  	fgSendAFWait   	FLAG3.bit.b4     		//����AF�����ʶ
#define		fgReceADOrder		FLAG3.bit.b5
#define		fgReceACOrder		FLAG3.bit.b6
#define		fgSendAEOrder		FLAG3.bit.b7			//�Ѿ����յ�Ram���ݵ�ַ
														

#define		fgImodeResume		FLAG4.bit.b0			//Iģʽ�ָ�
#define		fg_nocancle_Imode 	FLAG4.bit.b1			//����Iģʽ,��ȡ��Iģʽ��־
#define		fgFanSpeedChange	FLAG4.bit.b2			//���ٸı��־
#define		fgBarCodeDisplay	FLAG4.bit.b3			//1:������ʾ
#define		fgFastTest			FLAG4.bit.b4			//����־
#define		fgTest2				FLAG4.bit.b5			//����ź�,�ػ�ʱ����
#define		fg_test_error		FLAG4.bit.b6			//�յ�����ź�,������������
#define		fgAbilityRemote		FLAG4.bit.b7			//ң�������������ź�



#define		fgTurnOn			FLAG5.bit.b0			//������־λ
#define		fgAbilityDataSend	FLAG5.bit.b1			//����������Ϣ���ͱ�־
#define		fgImodeMem			FLAG5.bit.b2			//Iģʽ����
#define		fgCoolReceiveHeat	FLAG5.bit.b3			//��������յ���ů��־
#define		fgremote_code		FLAG5.bit.b4			//���յ��޼��������ʶ
#define		fgTimeToOpen		FLAG5.bit.b5			//��ʱ��
#define		fgTimeToClose		FLAG5.bit.b6			//��ʱ��
#define		fgWrithEE_ing		FLAG5.bit.b7			//����дE����ʶ

#define		fgSave				FLAG6.bit.b0			//ʡ��
#define		fgLowFreqFan		FLAG6.bit.b1			//�
#define		fgTypeHeat			FLAG6.bit.b2			//��ů��־λ
#define		fg_keep_SuperFan	FLAG6.bit.b3			//����ʱ,��ȡ��ǿ����־
#define		fgRemoteDispKey		FLAG6.bit.b4			//ң�����Լ��趨��־
#define		fgDryCleanDisplay	FLAG6.bit.b5			//���������ʾ��־
#define		fgDispOutTemperEnable FLAG6.bit.b6			//���⻷���¶Ȳ�ѯʹ��
#define		fgDryCleanEnable	FLAG6.bit.b7			//��������

#define		ucStSpeed		FLAG7.byte
#define     fgSuperFan     	FLAG7.bit.b0	    		//ǿ����
#define     fgQuietFan     	FLAG7.bit.b1	    		//������
#define     fgLowFan       	FLAG7.bit.b2	    		//�ͷ� 
#define     fgMidFan       	FLAG7.bit.b3	    		//�з�
#define     fgHighFan      	FLAG7.bit.b4	    		//�߷�
#define     fgAutoFan      	FLAG7.bit.b5	    		//�Զ���
														//ʣ�µı�־λ����ʹ��
												
#define     fgAutoModeCool 	FLAG8.bit.b0	    		//�Զ�ģʽ�µ�����
#define     fgAutoModeHeat 	FLAG8.bit.b1	    		//�Զ�ģʽ�µ�����
#define     fgAutoModeFan  	FLAG8.bit.b2	    		//�Զ�ģʽ�µ��ͷ�  
#define		fgPtcAssis		FLAG8.bit.b3				//�縨��
#define		fgLeftRightFan	FLAG8.bit.b4				//���ҷ�
#define		fgUpdownFan		FLAG8.bit.b5				//���·�
#define		fgDisp3S		FLAG8.bit.b6				//ȫ��3���־
#define		fg_DisEE_real	FLAG8.bit.b7

#define		ucError1		FLAG9.byte  	    		//���ϱ�־λ�Ĵ�����ֱ����ʾ
#define   	fgEepromErr   	FLAG9.bit.b0  				//ErrorKind0 E0:EEPROM communication error
#define   	fgTASENSOR    	FLAG9.bit.b1  				//ErrorKind1 E1:T1 error
#define   	fgTESENSOR		FLAG9.bit.b2  				//ErrorKind2 E2:T2 error
#define   	fgTempCSensor  	FLAG9.bit.b3  				//ErrorKind3 E3:T3 error
#define   	fgTempOutSensor FLAG9.bit.b4  				//ErrorKind4 E4:T4 error
#define   	fg_ERROR_EB     FLAG9.bit.b5  				//ErrorKind5 E5:disp and main communication error
#define   	fgOutEepError  FLAG9.bit.b6  				//ErrorKind6 E6:����E������
#define   	fgOutFanErr     FLAG9.bit.b7  				//ErrorKind7 E7:outdoor fan rate error

#define     ucError2		FLAGA.byte  	    		//���ϱ�־λ�Ĵ�����ֱ����ʾ
#define   	fgCOMMALM_SUART	FLAGA.bit.b0  				//ErrorKind8 E8:in and out communication error
#define   	fg_ERROR_E9     FLAGA.bit.b1      			//ErrorKind9 E9:gate running error
#define   	fg_ERROR_EA   	FLAGA.bit.b2  				//ErrorKind10 EA:compress low press error
#define   	fgSpeedError   	FLAGA.bit.b3  				//ErrorKind11 Eb:indoor fanspeed error
#define   	fgZeroError   	FLAGA.bit.b4  				//ErrorKind12 EC:zero detect error
#define   	fg_ERROR_Ed   	FLAGA.bit.b5  				//ErrorKind13 Ed:phase shortage error 
#define   	fg_ERROR_EE   	FLAGA.bit.b6  				//ErrorKind14 EE:phase reverse error
#define   	fgTempPSensor  	FLAGA.bit.b7  				//ErrorKind15 EP:exgas temper(TP) error

#define     ucProtect1		FLAGB.byte     				//���ر�����־λ�Ĵ�����ֱ����ʾ
#define   	fgIPMALM    	FLAGB.bit.b0   				//ErrorKind16 P0:IPM error
#define   	fgOutVolt		FLAGB.bit.b1  				//ErrorKind17 P1:voltage singularity
#define   	fgTOPTEMP		FLAGB.bit.b2   				//ErrorKind18 P2:compress high temperature
#define     fg_ERROR_P3     FLAGB.bit.b3    			//ErrorKind19 P3:out temprature low
#define     fgCOMPOSERR     FLAGB.bit.b4    			//ErrorKind20 P6:position protect
#define     fg_ERROR_P8     FLAGB.bit.b5    			//ErrorKind21 P8:connect more parts erorr
#define     fg_ERROR_PA     FLAGB.bit.b6    			//ErrorKind22 PA:face open protect
#define     fg_ERROR_DisEE	FLAGB.bit.b7				//ErrorKind23 EL:��ʾ��E������

#define     ucProtect2     	FLAGC.byte					//���ر�����־λ�Ĵ�����ֱ����ʾ
#define     fg_ERROR_Pb     FLAGC.bit.b0    			//ErrorKind24 Pb:compress low press protect
#define     fg_ERROR_PC     FLAGC.bit.b1    			//ErrorKind25 PC:compress high press protect
#define     fg_ERROR_Pd     FLAGC.bit.b2    			//ErrorKind26 Pd:current protect error
#define     fg_ERROR_RF  	FLAGC.bit.b3    			//ErrorKind27 EH:��Ƶģ�����
#define     fg_NoDemoMain   FLAGC.bit.b4               	//��ʾ���������ذ����ô��� FA
#define     fgErrorNOGA     FLAGC.bit.b5   				//ErrorKind29 ��ƽ̨���ڻ�����ƽ̨�����F9����
#define		fgCoolantLostNG	FLAGC.bit.b6				//ErrorKind30��ýй©����                                            			//ErrorKind30 Ԥ�� 
//#define		fg_ERROR_Power	FLAGC.bit.b7   				//ErrorKind31 ���ģ�����   

#define     ucProtectN		FLAGD.byte         			//һ�㱣����־λ�Ĵ�����������������ʾ
#define   	fg_Data_default	FLAGD.bit.b0   				//E��Ĭ������
#define   	fgEEerror		FLAGD.bit.b1   				//���д��E����EE����
#define   	fgTestDispT3    FLAGD.bit.b2   				//RunKind2 display T3
#define   	fgTestDispT4    FLAGD.bit.b3   				//RunKind3 display T4
#define   	fg_PROTECT_P4   FLAGD.bit.b4   				//RunKind4 P4:		�ڹ��±���
#define   	fg_PROTECT_P5   FLAGD.bit.b5   				//RunKind5 P5:		����±���	
#define     fg_PROTEC_P7    FLAGD.bit.b6   				//RunKind6 P7:		�������±���
#define   	fg_PROTECT_P9   FLAGD.bit.b7   				//RunKind7 P9:      ����� P9 

#define		ucProtectM		FLAGE.byte     				//һ�㱣����־λ�Ĵ�����������������ʾ
#define   	fg_PROTECT_Pd   FLAGE.bit.b0   				//RunKind8  		��������PD��Ƶ��
#define     fg_PROTECT_L0   FLAGE.bit.b1   				//RunKind9  		�������ߵ�����Ƶ(L0��Ƶ��) 
#define     fg_PROTECT_L1   FLAGE.bit.b2   				//RunKind10 		������������Ƶ(L1��Ƶ��)                                         //RunKind9  Ԥ�� 
#define     fg_PROTECT_L2   FLAGE.bit.b3   				//RunKind11 		ѹ��������������Ƶ(L2��Ƶ��)                                        
#define     fg_PROTECT_L3   FLAGE.bit.b4   				//RunKind12 		������Ƶ(L3��Ƶ��)                                        
#define     fg_PROTECT_L5   FLAGE.bit.b5   				//RunKind13 		��ѹ��Ƶ(L5��Ƶ��)                                     //RunKind9 Ԥ�� 
#define     fg_Isd3800Err   FLAGE.bit.b6   				//RunKind13 	????????                                                                                 
#define     fg_Isd3800RealErr   FLAGE.bit.b7                                           				//RunKind15 ?? 
                                                                                 
                                           				//RunKind15 Ԥ�� 

#define		fgSingleTemperErr	FLAGF.bit.b0			//���ֵ�һ���������ϱ�־	
#define		fgErrProtDisp		FLAGF.bit.b1			//���Ϻ����ر�����ʾ״̬
#define		fg100msCheck		FLAGF.bit.b2			//100msʱ��
#define		fgDisp0_5			FLAGF.bit.b3			//0.5��ʾ
#define		fgSetDispNoDot		FLAGF.bit.b4			//�¶Ȳ�ѯ��ʱ����Ҫ��ʾС����
#define		fgShowBarCodeLastBit	FLAGF.bit.b5			//��ʾ���һ�����������ݱ�ʶ
#define		fgBarCodeReady		FLAGF.bit.b6			//������洢�ñ�ʶ
#define		fgShowBarCode		FLAGF.bit.b7			//�����������ʶ

#define		fgkeysound_uart		FLAGG.bit.b0			//���ڽ��յ������ź�
#define		fgEepComErrDisp		FLAGG.bit.b1			//E��ͨѶ������ʾ��־
#define		fgkeysoundone		FLAGG.bit.b2			//�����������ڷ����ж��Ƿ����ң���źţ��������Թ���
#define		fgSoftSleepbak		FLAGG.bit.b3			//��˯�����ݱ�ʶ�����ڽ��յ�ģʽ������ж��Ƿ���˯���ܿ���
#define		fgkeysound			FLAGG.bit.b4			//���յ�ң���źŷ�����������
#define		fgSoftSleep			FLAGG.bit.b5			//��˯��ʶ
#define		fgcleanpro			FLAGG.bit.b6			//ǿ����ఴ����ʶ
#define		fgDisplayT1			FLAGG.bit.b7			//����͹����˳���,������ʾT1��־

#define		fgDefrost			FLAGH.bit.b0			//���ڻ�˪��־
#define		fgFeel				FLAGH.bit.b1			//����й��ܿ�����ʶ
#define		fgSendA3Wait		FLAGH.bit.b2			//����A3�����ʶ	
#define		fgLongSound			FLAGH.bit.b3			//��������������ʶ
#define		fgModechange_noFeel	FLAGH.bit.b4			//���յ���Ƶ������źű�ʶ
#define		fgFeelControl		FLAGH.bit.b5			//����й���
#define		fgFeelOwn			FLAGH.bit.b6			//���������
#define		fgSoftSleepOwn		FLAGH.bit.b7			//������˯

#define		fgDustClear			FLAGI.bit.b0			//��������
#define		fgSoftSleep_old		FLAGI.bit.b1			//��˯���ܱ���
#define		fgECONFGS			FLAGI.bit.b2			//��˯1Сʱ��ʱ����ʶ
#define		fg20msCheck			FLAGI.bit.b3			//20msʱ��		
#define		fg1minCheck			FLAGI.bit.b4			//1����ʱ��
#define		fgShowV				FLAGI.bit.b5			//��ѯ����汾�ű�ʶ
#define		fgShowCode		FLAGI.bit.b6			// 2014062303 ���յ���װң������ʱ����ʾ������
#define		fgPtcAssisBak			FLAGI.bit.b7			//�縨�ȹ��ܱ��ݱ�ʶ 2014061603


#define		fgRestComDisable	FLAGJ.bit.b0			//����״̬��ͨѶ��ֹ��־����ֹ��Ч�Ĵ����˳�����ʱ
#define		fgcleanSel			FLAGJ.bit.b1			//��������ѡ��λ		
#define		fgEepErrCheckIni	FLAGJ.bit.b2			//E��ͨѶ���ϼ���ʼ����־
#define		fgECOSel			FLAGJ.bit.b3			//ECO����ѡ��λ
#define		fgAbTestDispSet		FLAGJ.bit.b4			//����������ʾ
#define		fgRestPowerOn		FLAGJ.bit.b5			//�ϵ��һ�ν�������״̬��־
#define		fgKeyResonponse		FLAGJ.bit.b6			//���յ����ذ尴���ź�
#define		fgKeyBusy			FLAGJ.bit.b7			//

#define		fgRecOne		FLAGK.bit.b0				//�͹��Ľ��յ����ݱ�ʶ
#define		fg400ms				FLAGK.bit.b1			//400ms��־,����UART
#define		fgforcekeycool		FLAGK.bit.b2			//ǿ�������ʶ
#define		fgforcekeyauto	 	FLAGK.bit.b3			//ǿ���Զ���ʶ
#define		fgPreHeatOrCool		FLAGK.bit.b4			//Ԥ��Ԥ��
#define		fgExchangeSel		FLAGK.bit.b5			//��������ѡ��λ
#define		fgExchangeAir		FLAGK.bit.b6			//�������ܱ�ʶλ
#define		fg_out_volLow		FLAGK.bit.b7			//��ѹ���ͱ���

#define		fg_out_volHigh		FLAGL.bit.b0			//��ѹ���߱���
#define		fg_top_protect		FLAGL.bit.b1			//����ѹ���������¶ȱ���
#define		fgImodeResumeSend	FLAGL.bit.b2			//Iģʽ�ǻָ�������ɱ�־
#define		fgImodeMemSend		FLAGL.bit.b3			//Iģʽ���䷢����ɱ�־
#define		fgAbilityDataSendOk	FLAGL.bit.b4			//����������Ϣ���ͱ�־
#define		fgReceive			FLAGL.bit.b5			//������ȷ��־
#define		fgTypeOk			FLAGL.bit.b6			//�ϵ���Ͳ�����ȡ��ɱ�־
#define		fgRecFirst			FLAGL.bit.b7			//�ϵ��һ��ͨѶ��


#define		fgRestSendAnswer	FLAGM.bit.b0			//��λ����������Ӧ���ź�
#define		fg_RF_Imode			FLAGM.bit.b1			//��Ƶң����Iģʽ��־
#define		fgHorLeftSwing		FLAGM.bit.b2	
#define		fgNoAck				FLAGM.bit.b3			//��Ӧ���־
#define		fgReceStrenth		FLAGM.bit.b4			//���յ��ź�ǿ�������ʶ
#define		fgNotCreateLink		FLAGM.bit.b5			//��ַ�����־�� 1--���ص�ַ�Ѽ���	0--���ص�ַδ����
#define		fg_read				FLAGM.bit.b6			//��ȡ���ݱ�־
#define		fgCLearPower		FLAGM.bit.b7			// ������ģ���ʶ


#define		fgSetHumiChange			FLAGO.bit.b0			//���ڷ������ݱ�־
#define		fgCLearPowerSend	FLAGO.bit.b1			//�Ѿ��������������ݵı�ʶ
#define		fgDisplayHumity			FLAGO.bit.b2			//���յ�ʪ���ź�
#define		fgSetFanSeedChange FLAGO.bit.b3			//�趨���ٷ��͸ı��ʶ
#define		fgModeChange		FLAGO.bit.b4			//���ݽ��վ�����־
#define		fgTurnOnChange		FLAGO.bit.b5			//��Ч����ָ���־��Ϊ1ʱҪ�����ر��봦��
#define		fgNaturalFanBak		FLAGO.bit.b6			//��Ȼ�籸��
#define		fgSendWifiColse	FLAGO.bit.b7			//2014071601 ����wifi�رտ����ı�ʶ

#define		fgWifiDisp			FLAGP.bit.b0		//Wifiͼ����ʾ��ʶ 2014071603
#define		fgSendWifiColseOrder		FLAGP.bit.b1	// ����wifiģ��رտ������� 2014071601
#define		fgReceWifiData			FLAGP.bit.b2			//�ϵ���ܹ����յ�Wifi�źű�ʶ 2014071501
#define		fg_20ms				FLAGP.bit.b3			//20ms��־

#define		fg_buz_Repeat		FLAGP.bit.b4		//���յ�����������bit7��ʶλ 2014042502

#define		fg_mode_change		FLAGP.bit.b5			//ģʽ�ı��־
#define		fgTSPTest			FLAGP.bit.b6			//���Զ�ջ��ʶ
#define		fgModifSoftMemory		FLAGP.bit.b7		//ң�������ĵ�����书�ܱ�ʶ


#define		fgMemoryWriteEnable	FLAGR.bit.b0			//������书��д��E����ʶ
#define		fg_PowerOn_First		FLAGR.bit.b1			//�����ϵ��ʶ 2014071501
#define		fg_buz_enFirst		FLAGR.bit.b2			//�������жϱ�ʶ����Ϊ0��ʱ����Ҫ�ж�bit7�Ƿ�ı䣬�ж��Ƿ��ط�����Ϣ 2014042502
#define		fg_receive_strong	FLAGR.bit.b3			//���յ�ǿ�����ź�
#define		fg_keep_save		FLAGR.bit.b4			//����ʱ,��ȡ��ʡ���־
#define		fg_keep_LowFreqFan	FLAGR.bit.b5			//����ʱ,��ȡ����־
#define		fgReceiveKey		FLAGR.bit.b6			//���յ����ذ����źű�ʶ
#define		fgSendA8Wait			FLAGR.bit.b7			//����A8ָ���ʶ


#define		fgBarCodeRead			FLAGS.bit.b0		//1:�����
#define	fgBarCodeReadCompareEn		FLAGS.bit.b1		//�����븨����־��Ϊ0ʱ��barCode��barCodeChk����ҪУ��
#define	fgBarCodeDispStateConsult	FLAGS.bit.b2		//1�������ѯ��ʾ״̬ 0���ܵ�����д��E����ʾ���һ������״̬
#define	fgBarCodeDecode				FLAGS.bit.b3		//�������ݽ����־
#define		fg_read_error			FLAGS.bit.b4		//E������ʱ,���ж���E��
#define		fgClean					FLAGS.bit.b5		//�ػ��µ���ఴ��
#define		fgK6come				FLAGS.bit.b6		//60ms��־
#define		fgShortkey				FLAGS.bit.b7		//�̰���������


#define		fgTestSendFan			FLAGT.bit.b0		//��װ����ʶ
#define		fg_out_eerror			FLAGT.bit.b1
#define		fg_dcProtect			FLAGT.bit.b2
#define		fgMain_Drive_ComErr		FLAGT.bit.b3
#define		fg_CompSampleCurrent	FLAGT.bit.b4
#define		fgPowerKey		FLAGT.bit.b5				//ǿ�ư����źű�ʶ
#define		fgFanLeadKey1		FLAGT.bit.b6			//�����밴���źű�ʶ
#define		fgMinus					FLAGT.bit.b7		//������ʾ

#define		fgEco_old				FLAGU.bit.b0		//ECO���ܱ���
#define		fgEco					FLAGU.bit.b1		//ECO���ܿ�����ʶ
#define		fgTurnOnBackup			FLAGU.bit.b2
#define		fgEco_noclear			FLAGU.bit.b3		//���յ���ƵECO���ܣ������ECO����	
#define		fg80ms					FLAGU.bit.b4
#define		fgWriteEERem			FLAGU.bit.b5		//����д��E��ң���ź�
#define		fg_out_start			FLAGU.bit.b6
#define		fgLowFreqFan_old			FLAGU.bit.b7		//繦�ܱ���


#define		fgFlashDis				FLAGV.bit.b0		//1HZ��˸��ʶ
#define		fgErrorDis				FLAGV.bit.b1		//E�����Ͽ�����ʾ��ʶ
#define		fgSendA6Wait			FLAGV.bit.b2		//����A6����
#define		fg_ERROR_Power				FLAGV.bit.b3		// 2014040902 ���ģ�鴦����ҳ�����������һ��
#define		fgoldSuperFan			FLAGV.bit.b4		//ǿ�����ܱ���
#define		fgFeel_old				FLAGV.bit.b5		//����й��ܱ���
#define		fgBarCodeStorSend		FLAGV.bit.b6		//�洢�������ʶ
#define		fg_out_openphase		FLAGV.bit.b7		//

#define		fgremoteNoleader		FLAGW.bit.b0		//����͹��Ĳ��ж�ͷ��
#define		_TPPHIGHFG				FLAGW.bit.b1		//ѹ�����������±���
#define		fg_ERROR_Dust  			FLAGW.bit.b2        // 2014030902 �ҳ�����������
#define		fg_ERROR_DustReal				FLAGW.bit.b3	// 2014030902 �ҳ�����������
#define		fg_current_protect		FLAGW.bit.b4		//�������������
#define		_TEHIGHFG				FLAGW.bit.b5		//���������±���
#define		_TELOWFG				FLAGW.bit.b6		//�����������ᱣ��
#define		fg_volt_limit			FLAGW.bit.b7		//��ѹ��Ƶ

#define		fg_current_limit		FLAGX.bit.b0		//������Ƶ
#define		_TPPHIGH1FG				FLAGX.bit.b1		//����������Ƶ
#define		_TPHIGH1FG				FLAGX.bit.b2		//������������Ƶ
#define		_TCHOLDFG				FLAGX.bit.b3		//������������Ƶ
#define		_TELOW1FG				FLAGX.bit.b4		//�������¶���Ƶ
#define		_TEHIGH1FG				FLAGX.bit.b5		//�������¶���Ƶ
#define		fg_PFC_limit			FLAGX.bit.b6		//PFC������Ƶ L6
#define		fgTpHighPro				FLAGX.bit.b7		//���������±���


#define		fg80mscheck				FLAGY.bit.b0		//80ms
#define		fgWriteEEOwn			FLAGY.bit.b1		//����дEE
#define		fgEepromSysnc			FLAGY.bit.b2		//EEPEOM����ͬ����־
#define		fgWriteEEAllow			FLAGY.bit.b3		//��ʼд����EE����
#define		fgResetsinal			FLAGY.bit.b4
#define		fgWriteEESucess			FLAGY.bit.b5
#define		fgWriteEEDataSendOk		FLAGY.bit.b6
#define		fgPtcLoad				FLAGY.bit.b7		//�縨�ȸ���״̬	


#define		fgPtcEnable				FLAGZ.bit.b0		//�������Ȼ�ģʽ�л�Ĭ�Ͽ����縨�ȱ�־
#define		fgShowType				FLAGZ.bit.b1		//��ʾ������Ϣ2s
#define		fgWriteEEFail			FLAGZ.bit.b2		//д��E��ʧ�ܱ�ʶ
#define		fgMainIFeel				FLAGZ.bit.b3		//���ذ�����й����Ƿ�����ʶ
#define		fgHave_Left_Right		FLAGZ.bit.b4		//���ذ�����Ұ�Ҷ����ʮ�ֿ�����ʶ
#define		fg_comp_zerospeed		FLAGZ.bit.b5
#define		fg_out_341sync			FLAGZ.bit.b6
#define		fg_comp_speed			FLAGZ.bit.b7

#define		fg_IPDU_lock			FLAGA1.bit.b0
#define		fg_IPDU_openloop		FLAGA1.bit.b1
#define		fg_PFC_stop				FLAGA1.bit.b2
#define		fg_comp_overload		FLAGA1.bit.b3
#define		fg_IPDU_Sample			FLAGA1.bit.b4
#define		fg_receiveonce			FLAGA1.bit.b5		//����һ��
#define		fgSendWifiMode			FLAGA1.bit.b6		// 2014071501
#define		fg_ERROR_RF_Real		FLAGA1.bit.b7

#define		fgWriteEECodeErr		FLAGA2.bit.b0		//��������E����ʱ�򣬱�����󱨾���2014043001

#define		fg_341_MCE				FLAGA2.bit.b1
#define		fgfirstSend				FLAGA2.bit.b2
#define		fgElectronTest			FLAGA2.bit.b3		//���ӿ���ʶ

#define		fgReceOutData			FLAGA2.bit.b4		//���յ����������ʶ�����ڷ���5��������ݸ���Ƶң���� 2013091601
#define		fgCOMMALM_SuartOnce		FLAGA2.bit.b5	//������ͨ�Ź��Ϲ���ģʽһ�ξͱ� 2013091603
#define		fgOutFanErrOnce			FLAGA2.bit.b6		//������ʧ�ٹ��Ϲ���ģʽһ�ξͱ� 2013091603		
#define		fgIPMALMOnece			FLAGA2.bit.b7		//����IPMģ�鱣������ģʽһ�ξͱ� 2013091603		

#define		fg_ERROR_PowerReal		FLAG10.bit.b0		//���ģ����ϱ�ʶ
#define		fgWrithOutEE_ing		FLAG10.bit.b1		//д������E����ʶ 2014040901

#define		fgReceive_Data			FLAG10.bit.b2		// ��ʾ�����������ذ����ݱ�ʶ 2014042401

#define		fgFastEAError			FLAG10.bit.b3		//EA���ϵ�ʱ�򲻽��տ��ң���ź�
#define		fg_ERROR_DryReal	FLAG10.bit.b3		// 2014040902 ʪ�ȴ��������ϴ���
#define		fg_ERROR_Dry			FLAG10.bit.b4		// 2014040902 ʪ�ȴ��������ϴ���
#define		fgSendB0Wait		FLAG10.bit.b5		// ׼������B0���� 2014042202
#define		fgWriteEE			FLAG10.bit.b6		//д�������ݱ�ʶ
#define		fgTunrn_on_power	FLAG10.bit.b7		//���ػ��л���ʶ

#define		fgMemoryError		FLAG11.bit.b0		//��������ȡE�����ݴ����ʶ
#define		fgSendB4Wait		FLAG11.bit.b1		// 2014040901 ���յ��������E�����ݣ�׼��������������ذ�
#define    	fg10ms				FLAG11.bit.b2			//	   10ms��ʶ
#define		fg10mscheck			FLAG11.bit.b3	//	//4ms��ʶ �ж�ʹ��
#define		fgWriteOutEESendOk			FLAG11.bit.b4		// 2014040901 ��������E����ʶ ���ݷ�����ɵ�ʱ����һ
#define     fgDustFullClear			FLAG11.bit.b5		//����������ʱ���ʶ
#define     fgMemoryReadEnable		FLAG11.bit.b6		//��ȡ����������ݱ�ʶ
#define     fgDustFull			FLAG11.bit.b7		//������ʶ

		
#define		fgNaturalFanSel		FLAG12.bit.b0			//��Ȼ�繦��ѡ��λ
#define		fgNaturalFan		FLAG12.bit.b1			//��Ȼ�繦�ܱ�ʶ
#define		fgPMVSel			FLAG12.bit.b2			//PMV����ѡ��λ
#define		fgCatchColdSel		FLAG12.bit.b3			//����������ѡ��λ
#define		fgCatchCold			FLAG12.bit.b4			//���������ܱ�ʶ
#define		fgNightLight		FLAG12.bit.b5			//Сҹ�ƹ��ܱ�ʶ
#define		fgDryCleanDisplayBak	FLAG12.bit.b6
#define		fgPeakEletric		FLAG12.bit.b7			//����õ繦�ܱ�ʶ

#define		fgSendMarstOrder			FLAG13.bit.b0			//�����ϴ�wifiλ����������
#define		fgSendMarstOrder04			FLAG13.bit.b1			//�����ϴ�04��������
#define		fgSendMarstOrder05			FLAG13.bit.b2			//�����ϴ�05��������
#define		fghumiditySel				FLAG13.bit.b3			//ʪ�ȴ�����ѡ��λ
#define		fgErrProtDispBak			FLAG13.bit.b4			//���ϱ��ݱ�ʶ
#define		fgSendA7Wait				FLAG13.bit.b5			//Сҹ�ƹ��ܱ�ʶ
#define		fgSendMarstCheckOrder				FLAG13.bit.b6			//�������ؿ����ı�ʶ  2014062601
#define		fgReceWifiOrder				FLAG13.bit.b7			//���յ�wifi�źű�ʶ

//wifi ��������

#define UART_REC_INIT		0
#define UART_RECING			1
#define UART_REC_END		2
#define UART_SEND_INIT		3
#define UART_SENDING		4
#define UART_SEND_END		5
#define UART_SEND_HALT		6	//���Ϳ���״̬

#define U8_FALL				0
#define U8_PASS				1
#define U8_PASS_NO_RETURN	2	// 2014042402

#define	U8_UART_LENGTH		64

#define	U8_UART_WIFI_HEAD	0xaa
#define	U8_UART_WIFI_AIRCON 0xac	//�յ��豸

#define	U8_UART_WIFI_DRIVE 0xFF	//��ѯ�յ��豸

#define U8_WIFI_FIND_ORDER	0X01
#define U8_WIFI_CON_ORDER	0x02
#define U8_WIFI_CHECK_ORDER	0X03
#define U8_MARST_CHECK_DATA	0X04
#define U8_MARST_CHECK_MODE	0X05

#define U8_WIFI_ID_ORDER	0X0f
#define U8_MARST_Wifi_Init		0X64	//WIFI�����ϴ���������
#define U8_MARST_Wifi_COLSE	0X68	// WIFI�ر����� 2014071601
#define	U8_WIFI_CLOSEOPEN 		0X03


#define U8_MARST_Wifi_CHECK_STRENGTH	0X63	//WIFI�����ϴ���ѯ�ź�ǿ������
#define	U8_RF_MODE				0x00		// RFģ��
#define U8_WIFI_MODE			0x01		// WIFIģ��

#define U8_Wifi_CHECK_DRIVE	0X65	//WIFI��ѯ�豸ָ��

#define U8_Wifi_BROADCAST_DRIVE	0X0D	//WIFI�㲥����ָ��	�㲥�������Ϊ0d���� 2014062601
#define U8_WIFI_FIND_SLAVE		0X01
#define U8_WIFI_CON_SLAVE		0x02
#define U8_WIFI_CHECK_SLAVE	0X03

#define U8_WIFI_CON			0x40
#define U8_WIFI_CHECK		0x41

#define U8_WIFI_CON2_SLAVE	0xC0
#define U8_WIFI_CHECK2_SLAVE	0xC1
#define U8_BAR_CODE		0X80


#define U8_CON_COMMAND		0X01	//�ظ���������
#define	U8_CHECK_COMMAND 	0X02	//�ظ��鿴��������
#define U8_CHECK_DATA		0X03	//�ظ�С�����ݵ�����
#define U8_WRITE_DATA		0x04	//
#define U8_CHECK_BAR_COMMAND 0X05 //�ظ���������������
#define U8_RECE_BAR_COMMAND	0x06 //�ظ�������������������
#define U8_BAR_CODE_READ		0x07	//��ȡ����������
#define U8_BAR_CODE_WRITE		0x08	//д������������



#define U8_UART_DELAY_TIME_30ms 3		//30ms
#define U8_UART_IMIT_TIME_3s	30		//3s


#define	UART_MASTER			0		//���豸
#define	UART_SLAVE			1		//���豸

#define	U8_T30MS			3
#define U8_UART_DELAY_TIME_500ms 5		//500ms
#define U8_UART_DELAY_TIME_3s 	30		//3000ms
#define U8_UART_DELAY_TIME_3500ms 	35		//3500ms
#define U8_UART_DELAY_TIME_4500ms 	45		//4500ms

#define	U8_UART_DELAY_TIME_1000ms	10	// 1s  ���ڽ��յ����ݺ�������ʱ1s���ܹ������ϴ�����
#define	U8_T30S					30		//30s  2014042301
#define	U8_T3S					30		// 3s 2014042502 3sʱ�䵽�����������Ӧ�Ƚϱ�ʶ

#define WifiUartSendByte(x)		((TXBUF2) = (x))  			//�����һ���ֽ�	
#define	WifisUartGetByte(x)		((x) = (RXBUF2))

#define U8_MARST_05_ORDER			1		// 2014062601
#define U8_MARST_04_ORDER			2		// 2014062601
#define U8_MARST_CONFIGURE_ORDER	3		// WIFI�������� 2014062601
#define	U8_MARST_CHECK_STRENGTH	4		//������ѯ�ź�ǿ������ 2014062601
#define	U8_MARST_CLOSE_OPEN		5		// �������͹رտ���wifi���� 2014071601

#define	U8_TIME_10MIN				10		//  2014062601 10����


#define U8_CLIENT_MODE			0X01		//��������ģʽ 2014071501
#define	U8_CONFIGURATION_MODE 0X02		//����ģʽ    2014071501
#define U8_AP_MODE				0X03		//APģʽ      2014071501

ramExtern 	uchar	ucSendBufWifi[U8_UART_LENGTH];			//wifi�������ݻ�����
ramExtern 	uchar	ucRecBufWifi[U8_UART_LENGTH];			//wifi�������ݻ�����
ramExtern	uchar	ucSendCountWifi;			//�����ֽڼ�������
ramExtern	uchar	ucRecCountWifi;				//�����ֽڼ�������
ramExtern	uchar	ucSendTotalCnt;				//�����ܵ��ֽڳ���
//ramExtern	TYPE_UART	WifiComm;
ramExtern	uchar	ucSendKindMarst;				//�����ϴ����ͱ���
ramExtern	uchar	ucSendRecKind;					//WIFI���յ������ϴ���������
ramExtern	uchar	ucSendKindMarstCnt;			//�����ϴ����ͷ��͵ļ���
ramExtern	uchar	ucReceState;					//���յ�״̬
ramExtern	uchar	ucSendState;					//���͵�״̬
ramExtern	uchar	ucWifiRecFinishTime;			
ramExtern	uchar	ucWifiRecDataTime;				//���յ�һ���ֽڵ�ʱ���ʱ����
ramExtern	uchar	ucWifiSendDelayTime;
ramExtern	uchar	ucReceEndToSend;				//�������׼������  2014042301
ramExtern	uchar	ucWifiNoRecDataInt;				//����һ��ʱ��û�н��յ��������ݾ���Ϣ���ճ�ʼ������ 2014042301
ramExtern	uchar	ucWifiTimeOut;					//����˫�����ݳ�ʱʱ���ʱ
ramExtern	uchar	ucTime30Min;

ramExtern	uchar	ucPowerSetKind;				// 2014042202
ramExtern	uchar	ucPowerSetMode;
ramExtern	uchar	ucPowerSetTime;
ramExtern	uchar	ucDustJSX;						// �ҳ�Ũ�ȵȼ�
ramExtern	uchar	ucSendMarstMake;
ramExtern	uchar	ucSendMarstTime;
ramExtern	uchar	ucSendMarstCount;
//ramExtern	uchar	ucT100ms_ReceBuzTime;					//���յ�����

ramExtern	uchar	ucFrameBak;					//֡��ű��ݱ�ʶ 2014042604
ramExtern	uchar	ucSendClearPowerCnt;			// 2014071603 ��������
ramExtern	uchar	ucSetHumidity;
ramExtern	uchar	ucSetHumidityBak;







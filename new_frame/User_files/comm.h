/******************************************************************/
/* company: topband	                                           */
/* designer: dengyingbin                                          */
/* date:  2016/1/20                                                */
/******************************************************************/
#ifndef _COMM_H_
#define _COMM_H_

#define _COMM_FUN_
#ifdef _COMM_FUN_	
	typedef enum {FALSE = 0, TRUE = 1} bool;
	#define nullptr     0

	/* Disable all maskable interrupts */
	#define  DISABLEINT asm (" and 0b00001111,PSW \n")	
	/*	Enable the interrupt 				*/
	#define  ENABLEINT	asm (" or 0b01110000,PSW \n")	

	#define u8	unsigned char
	#define s8    	signed char
	#define u32  	unsigned long
	#define u16   	unsigned short
	#define s16  	signed short
	#define s32	long
	#define KEY_CODE 	u32

	#define PRO_HEAD_INSHOT	0xCC	//即热模块报文头
	#define PRO_HEAD1_TEST	0xFE	//测试模块报文头1
	#define PRO_HEAD2_TEST	0x01	//测试模块报文头2

	extern bool gTestLock_f;
	extern void commRx(u8 data);
	extern void commRxDeal(void);
	extern void commTx(void);
	extern void commTxDeal(void);
	extern void sendInstantHotTemp(u8 on, u16 temp);
	extern void commTxAvail(void);
	extern void sendHandCmd(void);
	extern void commTestDelay(void);
	extern void testPulseIRQ(void);
	extern u16 adcSample(u8 chnl);
	
	#define COMM_RX(x)  		commRx(x)
	#define COMM_RX_DEAL() 	commRxDeal()
	#define COMM_TX()	 		commTx()
	#define COMM_TX_DEAL()	commTxDeal() 
	#define SEND_INSTANTHOT_TEMP(on, temp)		sendInstantHotTemp(on,  temp)
	#define COMM_TX_AVAIL()	commTxAvail()
	#define COMM_TEST_DELAY()	commTestDelay()
	#define TESTPULSEIRQ() 	testPulseIRQ()
	//#define ADCSAMPLE() 		adcSample()
	#define TEST_LOCK_START	if(!gTestLock_f) {
	#define TEST_LOCK_END  		}
#else
	#define COMM_RX(x)
	#define COMM_RX_DEAL()
	#define COMM_TX()
	#define COMM_TX_DEAL()
	#define SEND_INSTANTHOT_TEMP(on, temp)	
	#define COMM_TX_AVAIL()
	#define COMM_TEST_DELAY()	
	#define TESTPULSEIRQ() 
	//#define ADCSAMPLE() 	
	#define TEST_LOCK_START			
	#define TEST_LOCK_END
#endif

#endif


/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.01.00.01 [26 Jul 2013]
* Device(s)    : R5F100AA
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2019-9-5
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
#include "pfdl.h"
/* Start user code for include. Do not edit comment generated here */
#include "R_main.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
init_CB init;
timer_CB timer;
SeatCircle_CB SeatCircle;
SeatCover_CB SeatCover;
Status_CB Status;
adc_CB ADC; 
IR_CB IR;
SendData_CB SendData;
Seat_CB	Seat;
Cover_CB	Cover;
PcbTest_CB PcbTest;

uint8_t  g_read_value[10]  = {0};
uint8_t  g_write_value[10] = {0};//= 0x00;
uint16_t g_write_address = TARGET_BLOCK * BLOCK_SIZE;
uint8_t text[20] = {"hello world"};
void delay_us(uint16_t num)
{
	while(num --);
}

void printStr(char const * ch)
{		
	R_UART0_Send(ch, strlen(ch));//发送字符串

	while(g_uart0_tx_count);//等待数据发送完成
}

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
uint16_t ad_val = 0;
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	uint16_t chBuf[32]={0};
    R_MAIN_UserInit();
	R_FDL_Init();                                                        /* Initialize EEL */
    R_FDL_Read();                                                        /* Data read */     
    PFDL_Close();                                                        /* Close FDL */
    /* Start user code. Do not edit comment generated here */
    while (1U)
    {
	 	SeatCircleMotorUp(80);
		ReadADC(_13_AD_INPUT_CHANNEL_19);
		sprintf(chBuf, "%d \r\n", ADC.adc_vale_buf);//将数字转换为字符
		printStr(&chBuf);
		delay_us(50000);
		delay_us(50000);
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
	DI();
/*	R_CGC_Create();
	WDTIMK = 1U;   			 /*------disable INTWDTI interrupt */
  // 	WDTIIF = 0U;    			/*------ clear INTWDTI interrupt flag */	
//	WDTE=0xAC;
//	R_PORT_Create();			//-----------IO 初始化	
//	R_TAU0_Create();			//----------定时器初始化
	R_TAU0_Channel0_Start();
	R_TAU0_Channel2_Start();
	Raminitial();
	R_UART0_Start();
    /* Start user code. Do not edit comment generated here */
    EI();
    
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

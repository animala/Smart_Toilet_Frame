#ifndef _INSTANT_HEAT_H
#define _INSTANT_HEAT_H

#include "MN101AF50D.h"
#include "main.h"

#define Data_size  13     //即热模块数据长度

//------------串口号
#define	UART0_CH	0x00
#define	UART1_CH	0x01

//-----------定义串口发送缓存寄存器
#define	Tx0_buf_reg	TXBUF0	

#define	Tx1_buf_reg	TXBUF1

//-----------定义串口接收缓存寄存器
#define	Rx0_buf_reg	RXBUF0	

#define	Rx1_buf_reg	RXBUF1




typedef struct{

	uint_8 ch;			//通道
	uint_8 len;			//数据长度
	uint_8 index;       //发送索引
	uint_8 Tx_flag;		//发送标志
	uint_8 Rx_flag;		//接收标志
	uint_8 Tx_buff[Data_size];	//发送缓存
	uint_8 Tx_data[Data_size];	//发送数据处理
	uint_8 Rx_buff[Data_size];	//接收缓存
	uint_8 Rx_data[Data_size];	//接收数据处理
	uint_8 Data_count;	//数据计数
}uart_str;
extern uart_str Uart_CB[2];   //声明串口结构体数组
extern uart_str UART_0;
extern uart_str UART_1;

void Urat0_Init(void);
void Water_Temp_Deal(uart_str *p);
void ReadRespRx0(uart_str *p);
void Uart0_send_data(uart_str *p);
void Uart_TX_Byte(uart_str *p);




#endif 


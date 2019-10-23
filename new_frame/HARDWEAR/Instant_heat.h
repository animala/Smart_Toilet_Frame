#ifndef _INSTANT_HEAT_H
#define _INSTANT_HEAT_H

#include "MN101AF50D.h"
#include "main.h"

#define Data_size  13     //����ģ�����ݳ���

//------------���ں�
#define	UART0_CH	0x00
#define	UART1_CH	0x01

//-----------���崮�ڷ��ͻ���Ĵ���
#define	Tx0_buf_reg	TXBUF0	

#define	Tx1_buf_reg	TXBUF1

//-----------���崮�ڽ��ջ���Ĵ���
#define	Rx0_buf_reg	RXBUF0	

#define	Rx1_buf_reg	RXBUF1




typedef struct{

	uint_8 ch;			//ͨ��
	uint_8 len;			//���ݳ���
	uint_8 index;       //��������
	uint_8 Tx_flag;		//���ͱ�־
	uint_8 Rx_flag;		//���ձ�־
	uint_8 Tx_buff[Data_size];	//���ͻ���
	uint_8 Tx_data[Data_size];	//�������ݴ���
	uint_8 Rx_buff[Data_size];	//���ջ���
	uint_8 Rx_data[Data_size];	//�������ݴ���
	uint_8 Data_count;	//���ݼ���
}uart_str;
extern uart_str Uart_CB[2];   //�������ڽṹ������
extern uart_str UART_0;
extern uart_str UART_1;

void Urat0_Init(void);
void Water_Temp_Deal(uart_str *p);
void ReadRespRx0(uart_str *p);
void Uart0_send_data(uart_str *p);
void Uart_TX_Byte(uart_str *p);




#endif 


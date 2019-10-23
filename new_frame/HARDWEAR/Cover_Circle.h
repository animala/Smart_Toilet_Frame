#ifndef _COVER_CIRCLE_H
#define _COVER_CIRCLE_H


#include "MN101AF50D.h"
#include "main.h"


#define	FG_DataSize			5
#define	User_FG_DataSize	5
#define SendDataBuffSize    5

extern unsigned char   Send_Data_buff[SendDataBuffSize];



void Cover_receive(void);

void Cover_Opreation(void);

void Cover_SendData(void);

void Cover_send_datadeal(void);


#endif


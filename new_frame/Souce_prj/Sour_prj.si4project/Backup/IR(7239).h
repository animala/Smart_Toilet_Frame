#ifndef _IR_H
#define _IR_H

#include "MN101AF50D.h"
#include "main.h"

#define  Wash_ajust    0x18   //冲洗调节 （位置/水量）
#define  Pra_ajust     0x19  //参数调节（水温/风温/座温/夜灯/节能）

//----定义一个功能枚举
typedef enum {
 	Stop = 0x00,	//停止
 	Hip_clean,	 //臀洗
 	Auto_s,		 //自动
 	Wem_clean,	 //妇洗
 	Dring,		 //暖风烘干
 	Purge,       //通便
	Massage,	 //按摩
	Turn_cover,  //翻盖
	Deodorzation, //除臭
	Auto_clean,  //自洁
	Flush,		 //冲水
	Turn_circle, //翻圈
	Power,		 //电源
	Auto_flush,  //自动冲水
} Func;

//----------档位调节枚举

typedef enum{

	Gear_0 = 0,
	Gear_1,
	Gear_2,
	Gear_3,
	Gear_4,
}Gear;


void IR_receive(void);

void IR_Opration(void);



#endif

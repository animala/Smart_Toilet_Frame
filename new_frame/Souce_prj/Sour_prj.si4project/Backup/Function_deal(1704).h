#ifndef	 _Func_H
#define	 _Func_H


#include "MN101AF50D.h"
#include "main.h"

void Close_all_function(void);
void TunBuWashEnable(void);
void NvXingWashEnable(void);
void ChuChouDeal(void);
void ChongShuiBanDeal(void);
void Wash_deal(uint_8 select);
void Water_change(uint_8 select);
uint_8 Gear_deal(uint_8 select);
void Zuo_Check(void);
void DringPwmDeal(void);
void DringWorkEnable(void);



#endif


#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)//读取按键0 GREEN
#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)//读取按键1 BULE
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)//读取按键3 YELLOW

#define KEY0_PRES 	2	//green
#define KEY1_PRES	  3	//blue
#define KEY2_PRES	  4	//开关
#define KEY3_PRES   1 //yellow

void key_Init(void);//IO初始化
u8 key_Scan(u8 mode);  	//按键扫描函数					   

#endif

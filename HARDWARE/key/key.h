#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)//��ȡ����0 GREEN
#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)//��ȡ����1 BULE
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)//��ȡ����2
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7)//��ȡ����3 YELLOW

#define KEY0_PRES 	2	//green
#define KEY1_PRES	  3	//blue
#define KEY2_PRES	  4	//����
#define KEY3_PRES   1 //yellow

void key_Init(void);//IO��ʼ��
u8 key_Scan(u8 mode);  	//����ɨ�躯��					   

#endif

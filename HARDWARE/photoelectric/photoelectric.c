#include <photoelectric.h>

//初始化函数
void photoelectric_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOA3
}

unsigned char dis_measuring(void)
{
	unsigned char flag_dis_temp=0;
	
	flag_dis_temp=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5); //laser_val[0]=laser_val[0]^0x01;
	return flag_dis_temp;
}


//unsigned char contactless_switch(void)
//{	 
//	static unsigned char switch_off=1;//按键按松开标志
//	if(switch_off&&contactless)
//	{
//		delay_ms(10);//去抖动 
//		switch_off=0;
//		return 1;
//	}
//	else if(contactless==0)
//	{	
//		switch_off=1; 	    
//	}
//	return 0;
//}

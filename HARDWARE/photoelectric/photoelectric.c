#include <photoelectric.h>

//��ʼ������
void photoelectric_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIOA3
}

unsigned char dis_measuring(void)
{
	unsigned char flag_dis_temp=0;
	
	flag_dis_temp=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5); //laser_val[0]=laser_val[0]^0x01;
	return flag_dis_temp;
}


//unsigned char contactless_switch(void)
//{	 
//	static unsigned char switch_off=1;//�������ɿ���־
//	if(switch_off&&contactless)
//	{
//		delay_ms(10);//ȥ���� 
//		switch_off=0;
//		return 1;
//	}
//	else if(contactless==0)
//	{	
//		switch_off=1; 	    
//	}
//	return 0;
//}

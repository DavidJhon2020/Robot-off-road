#include <laser.h>

extern unsigned char laser_val[9];
extern unsigned char laser_count;
extern int state_now;
//int laser_weight[9]={-4,-3,-2,-1,0,1,2,3,4};
int laser_weight[9]={0,3,5,7,8,9,11,13,16};

void laser_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能PORTA,PORTE时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOA3
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOA3
}

void read_laser(void)
{
	int i;
	int state_temp=0;
	unsigned char count=0;
	
	laser_val[0]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0); laser_val[0]=laser_val[0]^0x01;
	laser_val[1]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1);	laser_val[1]=laser_val[1]^0x01;
	laser_val[2]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2); laser_val[2]=laser_val[2]^0x01;
	laser_val[3]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3); laser_val[3]=laser_val[3]^0x01;
	laser_val[4]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4); laser_val[4]=laser_val[4]^0x01;
	laser_val[5]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5); laser_val[5]=laser_val[5]^0x01;
	laser_val[6]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6); laser_val[6]=laser_val[6]^0x01;
	laser_val[7]=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7); laser_val[7]=laser_val[7]^0x01;
	laser_val[8]=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9); laser_val[8]=laser_val[8]^0x01;
	for(i=0;i<9;i++)  count+=laser_val[i];
	//for(i=0;i<9;i++)  state_temp+=((int)laser_val[8-i])*laser_weight[i];
	for(i=0;i<9;i++)  
	{
		if((int)laser_val[i]==1)
		{
			state_temp = i;
		}
	}
	if(count >=3)
	{
		state_now = 9;
	}
//	if(count==1)
//	{
//		state_now=state_temp;
//	}
	if(count==1)
	{
		state_now=state_temp;
	}
	laser_count=count;
}

int right_angle(void)
{
	unsigned char count_letf=0;
	int i;
	int right_angle_flag=0;
	for(i=8;i>=4;i--)  
		count_letf+=laser_val[i];
	if(count_letf>=3)
		right_angle_flag=1;
	else
		right_angle_flag=0;
	return right_angle_flag;
}

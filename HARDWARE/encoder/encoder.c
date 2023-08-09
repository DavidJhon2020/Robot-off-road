#include <encoder.h>

extern int Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back;

void motor_encoder_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_ICInitTypeDef        TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);//重映射需打开
	
	//PA0 TIM5_CH1 PA1 TIM5_CH2 
	//PA15 JTDI->TIM2_CH1 PB3 JTDO->TIM2_CH2
	//PA6 TIM3_CH1 PA7 TIM3_CH2
	//PB6 TIM4_CH1 PB7 TIM4_CH2
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
	TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;////TIM向上计数  
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	
	TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 10;
	
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
  TIM_ICInit(TIM3, &TIM_ICInitStructure);  
	TIM_ICInit(TIM4, &TIM_ICInitStructure);  
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ClearFlag(TIM5, TIM_FLAG_Update);//清除TIM的更新标志位
	
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM2,0);
	TIM_SetCounter(TIM3,0);
	TIM_SetCounter(TIM4,0);
	TIM_SetCounter(TIM5,0);
	
	TIM_Cmd(TIM2, ENABLE); 
  TIM_Cmd(TIM3, ENABLE); 
  TIM_Cmd(TIM4, ENABLE); 
  TIM_Cmd(TIM5, ENABLE); 
}

int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=0;break;
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}

void read_encoder_value(void)
{
	Encoder_Left_front=-Read_Encoder(4);
	Encoder_Left_back=-Read_Encoder(5);
	Encoder_Right_front=Read_Encoder(2);
	Encoder_Right_back=Read_Encoder(3);
}

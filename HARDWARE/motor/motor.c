#include <motor.h>

//PC6 PC7 PC8 PC9 PE9 PE11 PE13 PE14

void motor_pwm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);//��ӳ�����
	
	//TIM1_CH1-4
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE); //��ȫ��ӳ��	
	
	//TIM8_CH1-4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  //��ʼ��TIM1 TIM8
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM1 TIM8 CH1-4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //��ʼ������OC
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��CCR�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//�߼��Ĵ�������
	TIM_CtrlPWMOutputs(TIM8, ENABLE);	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8
}

void motor_run_left(int v_front,int v_back)
{
	if(v_front>=0)
	{
		TIM8->CCR3=0;
		TIM8->CCR4=v_front;
	}
	else
	{
		TIM8->CCR3=-v_front;
		TIM8->CCR4=0;
	}
	if(v_back>=0)
	{
		TIM1->CCR1=0;
		TIM1->CCR2=v_back;
	}
	else
	{
		TIM1->CCR1=-v_back;
		TIM1->CCR2=0;
	}
}

void motor_run_right(int v_front,int v_back)
{
	if(v_front>=0)
	{
		TIM8->CCR1=v_front;
		TIM8->CCR2=0;
	}
	else
	{
		TIM8->CCR1=0;
		TIM8->CCR2=-v_front;
	}
	if(v_back>=0)
	{
		TIM1->CCR3=v_back;
		TIM1->CCR4=0;
	}
	else
	{
		TIM1->CCR3=0;
		TIM1->CCR4=-v_back;
	}
}

void motor_stop(void)
{
	motor_run_left(0,0);
	motor_run_right(0,0);
}

#include <motor.h>

//PC6 PC7 PC8 PC9 PE9 PE11 PE13 PE14

void motor_pwm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);//重映射需打开
	
	//TIM1_CH1-4
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE); //完全重映射	
	
	//TIM8_CH1-4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

  //初始化TIM1 TIM8
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM1 TIM8 CH1-4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //初始化外设OC
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); 

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能CCR上的预装载寄存器
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//高级寄存器才用
	TIM_CtrlPWMOutputs(TIM8, ENABLE);	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8
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

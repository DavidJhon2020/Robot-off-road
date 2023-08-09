#include "timer.h"
#include "mpu6050.h"
#include "encoder.h"
#include "led.h"
#include "motor.h"
#include "DataScope.h"
#include "speedcontrol.h"
#include "laser.h"
#include <photoelectric.h>
#include <element_id.h>
#include "beep.h"

/*********************������*******************/
extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����
extern float angle;
/**********************************************/

/*********************���*********************/
extern int Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back;
extern int pwm_lf,pwm_lb,pwm_rf,pwm_rb;
extern int v_target;
int v_target_lb=0;
/**********************************************/

/***********************����*******************/
extern unsigned char counter_tim6;
extern u8 flag_50ms,flag_5ms;
extern u8 flag_run;
extern float start_speed_weight;
extern unsigned char contactless;
extern unsigned char avoid_mistake;//�޽Ӵ����ط���
extern int end_flag;
/**********************************************/

/***********************Ѱ��*******************/
extern int v_basic,speed_ajust,state_now;
extern int v_ajust;
extern unsigned char trace_on;
extern unsigned char laser_val[9];
extern unsigned char laser_count;
unsigned char search_on=0;//����1��ʼ��ѯ
extern int error_state,last_error_state,prev_error_state;
/**********************************************/

/**********************Ԫ�ؼ��*****************/
extern unsigned char flag_dis;
extern float v_coefficient;
extern unsigned char stage,stage_count;
extern unsigned char circle,way;
extern int flag_r_angle;
/***********************************************/

void TIM6_Init(u16 arr,u16 psc)
{
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx					 
}

void TIM6_IRQHandler(void)   //TIM3�ж�
{

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIMx�����жϱ�־ 
    counter_tim6++;
		flag_5ms=1;
		if(counter_tim6%2==0)
		{
			Get_Angle();
			read_encoder_value();
			read_laser();
			flag_dis=dis_measuring();
			flag_r_angle=right_angle();
			//���Գ��������
//			pwm_lf=update_pwm_lf(Encoder_Left_front,20);
//			pwm_lb=update_pwm_lb(Encoder_Left_back,20);
//			pwm_rf=update_pwm_rf(Encoder_Right_front,20);
//			pwm_rb=update_pwm_rb(Encoder_Right_back,20);

//			trace(state_now);
//			//v_ajust=state_now-4;
			if(counter_tim6%20==0) 
				stage_count++;  //0.1s��һ��
			
			if(flag_run==1)
			{ 
			  switch(way)
			{   
					case 1:
					{
					switch (state_now)
					{
						case 0:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(2500,2500);
							break;
						case 1:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(2500,2500);
							break;
						case 2:     //ֹͣ		
							motor_run_left(-1000*1.5,-1000*1.5);
							motor_run_right(2500,2500);
							break;
						case 3:     //ֹͣ		
							motor_run_left(2000*1.5,2000*1.5);
							motor_run_right(2500,2500);
							break;
						case 4:     //ֹͣ		
							motor_run_left(2500*1.5,2500*1.5);
							motor_run_right(2500,2500);
							break;
						case 5:     //ֹͣ		
							motor_run_left(2500*1.5,2500*1.5);
							motor_run_right(1000,1000);
							break;
						case 6:     //ֹͣ		
							motor_run_left(2500*1.5,2500*1.5);
							motor_run_right(-1000,-1000);
							break;
						case 7:     //ֹͣ		
							motor_run_left(2500*1.5,2500*1.5);
							motor_run_right(-2000,-2000);
							break;
						case 8:     //ֹͣ		
							motor_run_left(2500*1.5,2500*1.5);
							motor_run_right(-2000,-2000);
							break;
						case 9:
						    if(state_now!=9)
							{
						    motor_run_left(-4500*1.5,-4500*1.5);
							motor_run_right(-4000,-4000);
						    }
							else
							{
							motor_run_left(-2000,-2000);
							motor_run_right(1500,1500);
							}
						    break;
							
					}
					
					if(stage_count>220)
					{
						motor_stop();
						end_flag=0;
					}
				}
			
						case 2:
						{
							switch (state_now)
					{
						case 0:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(3000,3000);
							break;
						case 1:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(3500,3500);
							break;
						case 2:     //ֹͣ		
							motor_run_left(-1000*1.5,-1000*1.5);
							motor_run_right(3500,3500);
							break;
						case 3:     //ֹͣ		
							motor_run_left(1500*1.5,1500*1.5);
							motor_run_right(3500,3500);
							break;
						case 4:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(3500,3500);
							break;
						case 5:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(1500,1500);
							break;
						case 6:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(-1000,-1000);
							break;
						case 7:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(-2000,-2000);
							break;
						case 8:     //ֹͣ		
							motor_run_left(3000*1.5,3000*1.5);
							motor_run_right(-2500,-2500);
							break;
						case 9:
						    if(state_now!=9)
							{
						    motor_run_left(-4000*1.5,-4000*1.5);
							  motor_run_right(-3500,-3500);
						    }
							else
							{
							motor_run_left(-2000,-2000);
							motor_run_right(1500,1500);
							}
						    break;
							
					}
					
					if(stage_count>230)
					{
						motor_stop();
						end_flag=0;
					}
				}
						case 3:
						{
							switch (state_now)
					{
						case 0:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(3000,3000);
							break;
						case 1:     //ֹͣ		
							motor_run_left(-2000*1.5,-2000*1.5);
							motor_run_right(3500,3500);
							break;
						case 2:     //ֹͣ		
							motor_run_left(-1000*1.5,-1000*1.5);
							motor_run_right(3500,3500);
							break;
						case 3:     //ֹͣ		
							motor_run_left(1500*1.5,1500*1.5);
							motor_run_right(3500,3500);
							break;
						case 4:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(3500,3500);
							break;
						case 5:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(1500,1500);
							break;
						case 6:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(-1000,-1000);
							break;
						case 7:     //ֹͣ		
							motor_run_left(3500*1.5,3500*1.5);
							motor_run_right(-2000,-2000);
							break;
						case 8:     //ֹͣ		
							motor_run_left(3000*1.5,3000*1.5);
							motor_run_right(-2500,-2500);
							break;
						case 9:
						    if(state_now!=9)
							{
						    motor_run_left(-4000*1.5,-4000*1.5);
							  motor_run_right(-3500,-3500);
						    }
							else
							{
							motor_run_left(-2000,-2000);
							motor_run_right(1500,1500);
							}
						    break;
							
					}
					
					if(stage_count>255)
					{
						motor_stop();
						end_flag=0;
					}
			}
		}

			

			}
		}
		if(counter_tim6%10==0)
			flag_50ms=1;
//		if(counter_tim6==100)//LED1s��һ��
//		{
//			counter_tim6=0;
//			LED=~LED;
//		}
		if(v_ajust!=0)
			LED=0;//LED=0��
		else
			LED=1;
	}
}

#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "usart3.h"
#include "stdio.h"

#include "beep.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "mpu6050.h"
#include "timer.h"
#include "encoder.h"
#include "motor.h"
#include "speedcontrol.h"
#include "DataScope.h"
#include <laser.h>
#include <photoelectric.h>


int end_flag;
/*********************������*******************/
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
float angle;
/**********************************************/

/*********************���*********************/
int pwm_lf=0,pwm_lb=0,pwm_rf=0,pwm_rb=0;//motor_run��ֵ
int pwm_1=0,pwm_2=0,pwm_3=0,pwm_4=0;//����ջ������м���
int v_target=0;
int Encoder_Left_front=0,Encoder_Right_front=0,Encoder_Left_back=0,Encoder_Right_back=0;
/**********************************************/

/*********************����*********************/
u8 key=0;
unsigned char counter_tim6=0;
u8 flag_50ms,flag_5ms;
char flag_run=0;
float start_speed_weight=0; //���ٶ�ϵ��
unsigned char contactless=0;
unsigned char lock=0;  //1���� 0����
unsigned char avoid_mistake=0;//�޽Ӵ����ط���

/**********************************************/

/*********************Ѱ��**********************/
unsigned char laser_val[9]={0};
unsigned char laser_count=0;
int state_now=8;
int speed_ajust=0;
int v_basic=100;
int v_ajust=0;
unsigned char trace_on=1;
int error_state=0,last_error_state=0,prev_error_state=0;
/**********************************************/

/**********************Ԫ�ؼ��*****************/
unsigned char flag_dis=0;
unsigned char flag_bluetooth=0;
unsigned char flag_start=0;
float v_coefficient=1;
unsigned char stage=0,stage_count=0;
unsigned char circle=0,way=1;    //�ڵ�Ϊ1
int flag_r_angle=0;
/***********************************************/

int main(void)
{	
//	char string[100];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	delay_init();
	delay_ms(1000);
	beep_Init();	//��ʼ��
	led_Init();
	key_Init();
	TIM6_Init(49,7199);//5ms
	//motor_encoder_init();
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
    OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	motor_pwm_Init(3599,0);
	MPU_Init();					//��ʼ��MPU6050
	laser_Init();
	photoelectric_Init();
	uart_init(9600);
//	uart_init(115200);
//	uart3_init(9600);
	
	end_flag=1;
	while(end_flag)
	{
		key=key_Scan(0);	//�õ���ֵ
		if(key==1)
			//v_target+=10;
//			v_basic+=10;
		{
			BEEP=1;
			delay_ms(100);
			BEEP=0;
			way = 1;
		}

		if(key==2)
		{
			BEEP=1;
			delay_ms(100);
			BEEP=0;
			way = 2;
		}
		if(key==4)
		{
			BEEP=1;
			delay_ms(100);
			BEEP=0;
			way = 2;
		}
		if(key==3) 
		{
			BEEP=1;
			delay_ms(100);
			BEEP=0;
			way = 3;
		}
		contactless=(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)^0x01);
		if((GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)^0x01)==1)
		{
			contactless=1;

		}
		
      key=key_Scan(0);	//�õ���ֵ
//		if(key!=0)
//		{
//			BEEP=1;
//			delay_ms(100);
//			BEEP=0;
//		}
//		if(flag_5ms==1)
//		{
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
//			flag_5ms=0;
//		}
//		if(flag_50ms==1)
//			{
//			flag_50ms=0;
//			oled_display();
//			//Send_2_DataScope();	
//			}
		
//		if(lock==0) flag_run=0;
//		if(contactless==1&&lock==1&&avoid_mistake==0)
		if(contactless==1)
		{
			//avoid_mistake=1;
			//flag_run=flag_run^0x01;//ĳλ��1���ȡ������0��򲻱�
			
		    
			flag_run = 1;
			BEEP=1;
      delay_ms(100);
      BEEP=0;
			//pwm_1=0,pwm_2=0,pwm_3=0,pwm_4=0;speed_ajust=0;
			//start_speed_weight=0;
			//stage=flag_run;
			//if(stage==1) {BEEP=0;circle=0;}
			//if(flag_run==1) {BEEP=0;circle=0;}
			//delay_ms(10);
			//contactless=0;
			//error_state=0;last_error_state=0;prev_error_state=0;
			//trace_on=1;
		}

//		sprintf(string,"lf:%6d rf:%6d lb:%6d rb:%6d\r\n",Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back);
//		printf("%s",string);
//		sprintf(string,"aacx:%6d aacy:%6d aacz:%6d gyrx:%6d gyry:%6d gyrz:%6d\r\n",aacx,aacy,aacz,gyrox,gyroy,gyroz);
//		sprintf(string,"%f\r\n",angle);
//		printf("%s",string);
	}
}

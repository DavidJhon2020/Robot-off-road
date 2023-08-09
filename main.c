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
/*********************陀螺仪*******************/
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
float angle;
/**********************************************/

/*********************电机*********************/
int pwm_lf=0,pwm_lb=0,pwm_rf=0,pwm_rb=0;//motor_run赋值
int pwm_1=0,pwm_2=0,pwm_3=0,pwm_4=0;//电机闭环函数中间量
int v_target=0;
int Encoder_Left_front=0,Encoder_Right_front=0,Encoder_Left_back=0,Encoder_Right_back=0;
/**********************************************/

/*********************控制*********************/
u8 key=0;
unsigned char counter_tim6=0;
u8 flag_50ms,flag_5ms;
char flag_run=0;
float start_speed_weight=0; //起步速度系数
unsigned char contactless=0;
unsigned char lock=0;  //1解锁 0上锁
unsigned char avoid_mistake=0;//无接触开关防误触

/**********************************************/

/*********************寻迹**********************/
unsigned char laser_val[9]={0};
unsigned char laser_count=0;
int state_now=8;
int speed_ajust=0;
int v_basic=100;
int v_ajust=0;
unsigned char trace_on=1;
int error_state=0,last_error_state=0,prev_error_state=0;
/**********************************************/

/**********************元素检测*****************/
unsigned char flag_dis=0;
unsigned char flag_bluetooth=0;
unsigned char flag_start=0;
float v_coefficient=1;
unsigned char stage=0,stage_count=0;
unsigned char circle=0,way=1;    //内道为1
int flag_r_angle=0;
/***********************************************/

int main(void)
{	
//	char string[100];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	delay_init();
	delay_ms(1000);
	beep_Init();	//初始化
	led_Init();
	key_Init();
	TIM6_Init(49,7199);//5ms
	//motor_encoder_init();
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	motor_pwm_Init(3599,0);
	MPU_Init();					//初始化MPU6050
	laser_Init();
	photoelectric_Init();
	uart_init(9600);
//	uart_init(115200);
//	uart3_init(9600);
	
	end_flag=1;
	while(end_flag)
	{
		key=key_Scan(0);	//得到键值
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
		
      key=key_Scan(0);	//得到键值
//		if(key!=0)
//		{
//			BEEP=1;
//			delay_ms(100);
//			BEEP=0;
//		}
//		if(flag_5ms==1)
//		{
//			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
//			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
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
			//flag_run=flag_run^0x01;//某位与1异或取反，与0异或不变
			
		    
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

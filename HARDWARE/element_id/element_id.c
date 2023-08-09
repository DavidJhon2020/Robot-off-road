#include <element_id.h>
#include "speedcontrol.h"

extern int Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back;
extern int pwm_lf,pwm_lb,pwm_rf,pwm_rb;
extern float v_coefficient;

void normal(void)
{
	v_coefficient=1;
}

void normal_1(void)
{
	v_coefficient=1.2;
}

void cliff(void)
{
	v_coefficient=0.75;
}


void hump(void)
{
	v_coefficient=0.8;
}

void hump_stair(void)
{
	v_coefficient=0.7;
}

void stair_low(void)
{
	v_coefficient=0.2;//0.7可以但是不稳
}

void stair_high(void)
{
	v_coefficient=0.65;//0.7可以但是不稳
}

//内道
void before_r_angle(void)
{
	v_coefficient=0.5;
}

void before_finger(void)
{
	v_coefficient=0.65;
}
	

void finger_plate(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,52);
	pwm_lb=update_pwm_lb(Encoder_Left_back,52);
	pwm_rf=update_pwm_rf(Encoder_Right_front,50);
	pwm_rb=update_pwm_rb(Encoder_Right_back,50);
}
	
void r_angle(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,-5);
	pwm_lb=update_pwm_lb(Encoder_Left_back,-5);
	pwm_rf=update_pwm_rf(Encoder_Right_front,85);
	pwm_rb=update_pwm_rb(Encoder_Right_back,85);
}

void r_angle_straight(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,50);
	pwm_lb=update_pwm_lb(Encoder_Left_back,50);
	pwm_rf=update_pwm_rf(Encoder_Right_front,50);
	pwm_rb=update_pwm_rb(Encoder_Right_back,50);
}

void search_right(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,35);
	pwm_lb=update_pwm_lb(Encoder_Left_back,35);
	pwm_rf=update_pwm_rf(Encoder_Right_front,15);
	pwm_rb=update_pwm_rb(Encoder_Right_back,15);
}


//void search_left(void)
//{
//	pwm_lf=update_pwm_lf(Encoder_Left_front,25);
//	pwm_lb=update_pwm_lb(Encoder_Left_back,25);
//	pwm_rf=update_pwm_rf(Encoder_Right_front,55);
//	pwm_rb=update_pwm_rb(Encoder_Right_back,55);
//}

void search_left(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,15);
	pwm_lb=update_pwm_lb(Encoder_Left_back,15);
	pwm_rf=update_pwm_rf(Encoder_Right_front,35);
	pwm_rb=update_pwm_rb(Encoder_Right_back,35);
}

void search_back_left(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,-15);
	pwm_lb=update_pwm_lb(Encoder_Left_back,-15);
	pwm_rf=update_pwm_rf(Encoder_Right_front,-35);
	pwm_rb=update_pwm_rb(Encoder_Right_back,-35);
}

void search_back_right(void)
{
	pwm_lf=update_pwm_lf(Encoder_Left_front,-35);
	pwm_lb=update_pwm_lb(Encoder_Left_back,-35);
	pwm_rf=update_pwm_rf(Encoder_Right_front,-15);
	pwm_rb=update_pwm_rb(Encoder_Right_back,-15);
}

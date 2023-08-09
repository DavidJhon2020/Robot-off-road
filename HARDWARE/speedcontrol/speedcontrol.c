#include "speedcontrol.h"
/******************����ջ�********************/
extern int Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back;
extern int pwm_1,pwm_2,pwm_3,pwm_4;
float kp_lf =5,ki_lf =2.2,kd_lf = 0.3;
float kp_lb =5,ki_lb =2.2,kd_lb = 0.3;
float kp_rf =5,ki_rf =2.2,kd_rf = 0.3;
float kp_rb =5,ki_rb =2.2,kd_rb = 0.3;
/**********************************************/

/**********************ѭ��********************/
int kp_state =500,ki_state =0,kd_state =2000;//�ɹ�
extern int speed_ajust;
extern int error_state,last_error_state,prev_error_state;  //��̬�������ڳ���ȫ���ڣ�
/**********************************************/

/********************Ԫ�ؼ��******************/
extern unsigned char flag_start;
/**********************************************/

int update_pwm_lf(int current_speed,int target_speed)      //����PID���ٴ��룬����
{
	static float error_lf,last_error_lf,prev_error_lf;  //��̬�������ڳ���ȫ���ڣ�
  error_lf=target_speed-current_speed;    //���㱾��ƫ��e(k)
  pwm_1+=(int)(kp_lf*(error_lf-last_error_lf)+ki_lf*error_lf+kd_lf*(error_lf-2*last_error_lf+prev_error_lf));   //����ʽPID������
  prev_error_lf=last_error_lf;  //�������ϴ�ƫ��
  last_error_lf=error_lf;     //������һ��ƫ��
  if(pwm_1>3400)  pwm_1= 3400;  
  if(pwm_1<-3400) pwm_1= -3400;
  return pwm_1;
}

int update_pwm_lb(int current_speed,int target_speed)      //����PID���ٴ��룬����
{
	static float error_lf,last_error_lf,prev_error_lf;  //��̬�������ڳ���ȫ���ڣ�
  error_lf=target_speed-current_speed;    //���㱾��ƫ��e(k)
  pwm_2+=(int)(kp_lb*(error_lf-last_error_lf)+ki_lb*error_lf+kd_lb*(error_lf-2*last_error_lf+prev_error_lf));   //����ʽPID������
  prev_error_lf=last_error_lf;  //�������ϴ�ƫ��
  last_error_lf=error_lf;     //������һ��ƫ��
  if(pwm_2>3400)  pwm_2= 3400;  
  if(pwm_2<-3400) pwm_2= -3400;
  return pwm_2;
}

int update_pwm_rf(int current_speed,int target_speed)      //����PID���ٴ��룬����
{
	static float error_lf,last_error_lf,prev_error_lf;  //��̬�������ڳ���ȫ���ڣ�
  error_lf=target_speed-current_speed;    //���㱾��ƫ��e(k)
  pwm_3+=(int)(kp_rf*(error_lf-last_error_lf)+ki_rf*error_lf+kd_rf*(error_lf-2*last_error_lf+prev_error_lf));   //����ʽPID������
  prev_error_lf=last_error_lf;  //�������ϴ�ƫ��
  last_error_lf=error_lf;     //������һ��ƫ��
  if(pwm_3>3400)  pwm_3= 3400;  
  if(pwm_3<-3400) pwm_3= -3400;
  return pwm_3;
}

int update_pwm_rb(int current_speed,int target_speed)      //����PID���ٴ��룬����
{
	static float error_lf,last_error_lf,prev_error_lf;  //��̬�������ڳ���ȫ���ڣ�
  error_lf=target_speed-current_speed;    //���㱾��ƫ��e(k)
  pwm_4+=(int)(kp_rb*(error_lf-last_error_lf)+ki_rb*error_lf+kd_rb*(error_lf-2*last_error_lf+prev_error_lf));   //����ʽPID������
  prev_error_lf=last_error_lf;  //�������ϴ�ƫ��
  last_error_lf=error_lf;     //������һ��ƫ��
  if(pwm_4>3400)  pwm_4= 3400;  
  if(pwm_4<-3400) pwm_4= -3400;
  return pwm_4;
}

int trace(int state)
{
	int ajust_temp=0;
  error_state=8-state;    //���㱾��ƫ��e(k)
  speed_ajust+=(kp_state*(error_state-last_error_state)+ki_state*error_state+kd_state*(error_state-2*last_error_state+prev_error_state));   //����ʽPID������
  prev_error_state=last_error_state;  //�������ϴ�ƫ��
  last_error_state=error_state;     //������һ��ƫ��
	ajust_temp=speed_ajust/100;
	if(ajust_temp>50)  ajust_temp=50;
	if(ajust_temp<-50) ajust_temp= -50;
  return ajust_temp;
}

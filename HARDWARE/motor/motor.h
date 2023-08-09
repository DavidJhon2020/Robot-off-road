#ifndef __motor_H
#define __motor_H	 
#include <sys.h>

void motor_pwm_Init(u16 arr,u16 psc);
void motor_run_left(int v_front,int v_back);
void motor_run_right(int v_front,int v_back);
void motor_stop(void);

#endif

#ifndef __SPEEDCONTROL_H_
#define __SPEEDCONTROL_H_
#include "speedcontrol.h"
#include "sys.h"

int update_pwm_lf(int current_speed,int target_speed);
int update_pwm_lb(int current_speed,int target_speed);
int update_pwm_rf(int current_speed,int target_speed);
int update_pwm_rb(int current_speed,int target_speed);
int trace(int state);

#endif

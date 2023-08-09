#ifndef __ENCODER_H
#define __ENCODER_H	 
#include "sys.h"

void motor_encoder_init(void);
int Read_Encoder(u8 TIMX);
void read_encoder_value(void);

#endif

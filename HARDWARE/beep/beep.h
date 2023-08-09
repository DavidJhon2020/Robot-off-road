#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"

#define BEEP PBout(8)	// BEEP,蜂鸣器接口		   

void beep_Init(void);	//初始化
		 				    
#endif

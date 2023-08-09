#ifndef __MPU6050IIC_H
#define __MPU6050IIC_H
#include "sys.h"
 	   		   
//IO��������
#define MPU_SDA_IN()  {GPIOF->CRL&=0XFFFFFFF0;GPIOF->CRL|=8<<0;}
#define MPU_SDA_OUT() {GPIOF->CRL&=0XFFFFFFF0;GPIOF->CRL|=3<<0;}

//IO��������	 
#define MPU_IIC_SCL    PFout(1) 		//SCL
#define MPU_IIC_SDA    PFout(0) 		//SDA	 
#define MPU_READ_SDA   PFin(0) 		//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif











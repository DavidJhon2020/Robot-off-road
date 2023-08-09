#include "DataScope.h"
unsigned char DataScope_OutPut_Buffer[42] = {0};	   //���ڷ��ͻ�����
unsigned char i;          //��λ����������
unsigned char Send_Count; //��λ��������Ҫ���͵����ݸ���

/***********************************���***************************************/
extern int Encoder_Left_front,Encoder_Right_front,Encoder_Left_back,Encoder_Right_back;
extern int v_target;
extern u8 flag_run;
/******************************************************************************/

extern short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
extern short gyrox,gyroy,gyroz;	//������ԭʼ����

//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ 
//����˵�����û�����ֱ�Ӳ����˺��� 
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
//�����޷��� 
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}
 
//����˵������������ͨ���ĵ����ȸ�������д�뷢�ͻ�����
//Data��ͨ������
//Channel��ѡ��ͨ����1-10��
//�����޷��� 
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
	if ( (Channel > 10) || (Channel == 0) ) return;  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {
     switch (Channel)
		{
      case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
      case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
		}
  }	 
}

//����˵�������� DataScopeV1.0 ����ȷʶ���֡��ʽ
//Channel_Number����Ҫ���͵�ͨ������
//���ط��ͻ��������ݸ���
//����0��ʾ֡��ʽ����ʧ�� 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //ͨ����������10�����0��ֱ����������ִ�к���
  else
  {	
	 DataScope_OutPut_Buffer[0] = '$';  //֡ͷ
		
	 switch(Channel_Number)   
   { 
		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6;  
		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10;
		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; 
		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18;
		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22;  
		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26;
		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; 
		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; 
		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38;
     case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; 
   }	 
  }
	return 0;
}

void Send_2_DataScope(void)
{
		DataScope_Get_Channel_Data(Encoder_Left_front,1);
		DataScope_Get_Channel_Data(Encoder_Right_front,2);
		DataScope_Get_Channel_Data(Encoder_Left_back,3);
		DataScope_Get_Channel_Data(Encoder_Right_back,4);
		DataScope_Get_Channel_Data(v_target,5);
		DataScope_Get_Channel_Data(flag_run,6);
		DataScope_Get_Channel_Data(gyrox,7);
		DataScope_Get_Channel_Data(gyroy,8);
		DataScope_Get_Channel_Data(gyroz,9);
		Send_Count = DataScope_Data_Generate(9);
		for( i = 0 ; i < Send_Count; i++) 
		{
			while((USART1->SR&0X40)==0);  
			USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
}

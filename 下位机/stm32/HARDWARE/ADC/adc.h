#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 

#define adc_ch   ADC_Channel_15
 					
#define Low_Vol  10.8

void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(void); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  

float Get_Bat_Vol(void);//��ȡ��ص�ѹ����
//�͵�ѹ����
void Low_Voltage_Alarm(void);
#endif 
















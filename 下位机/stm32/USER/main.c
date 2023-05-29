#include "sys.h"
#include "stdio.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "propeller.h"
#include "beep.h" 
#include "433m.h" 
#include "bno055.h" 
#include "dac.h"
#include "hp20x.h"
#include "api.h" 
#include "timer.h"
#include "adc.h"
#include "exti.h"
#include "servo.h" 


extern u8 RX_STATE;
extern u8 Packet_433M[10];
extern u8 gyr_state;
extern u8 GYR_Response[8];
extern u8 RecU5;

#include "sys.h"
#include "stdio.h"
#include "delay.h"
#include "api.h" 
#include "external.h" 
#include "api.h"
#include "propeller.h"


/**

    �������ӿ�   ������T2������     ������T3������

                 ������T6������     ������T7������

                 ������T1������     ������T4������
								  ������1�˿ڡ� �Ҷ����3�˿ڡ�
								  ��ȴ�������2���˿�
									��ݮ��USB�Ӷ˸�ROV�ӿ�
									����ͷ������ݮ�ɻ����ز�����ͷ�ӿ�
									ע�⣺��ݮ�ɴ��ڷ���ָ����Ҫ��AMA0�ĳ�USB0��Ȼ���������ز����м���
								˳ʱ�뽰Ҷ��תΪ��������ʱ����ת��ˮΪ����**/
								
void Forward(int sudu1,int sudu4)//ǰ��
{   
    TJQ_Control(T1,sudu1,0);//���
    TJQ_Control(T2,0,1);//��ǰ
    TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,sudu4,1);//�Һ� 


}

void TurnLeft(int sudu2,int sudu4)//��ת
{
    TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,sudu2,1);//��ǰ
    TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,sudu4,1);//�Һ� 

}


void TurnRight(int sudu1,int sudu3)//��ת
{
    TJQ_Control(T1,sudu1,0);//���
    TJQ_Control(T2,0,1);//��ǰ
    TJQ_Control(T3,sudu3,0);//��ǰ
    TJQ_Control(T4,0,1);//�Һ� 

}
void Downwater(float sudu5,float sudu6)//��Ǳ
{
//    TJQ_Control(T1,0,0);//���
//    TJQ_Control(T2,0,1);//��ǰ
//	  TJQ_Control(T3,0,0);//��ǰ
//    TJQ_Control(T4,0,1);//�Һ�
    TJQ_Control(T6,sudu5,0);//����
    TJQ_Control(T7,sudu6,1);//����
}
void LeftPY(int sudu7,int sudu8)//��ƽ��
{
   
    TJQ_Control(T1,sudu7,0);//���
    TJQ_Control(T2,sudu8,1);//��ǰ
	  TJQ_Control(T3,0,0);//��ǰ
    TJQ_Control(T4,0,1);//�Һ�
}
void RightPY(int sudu9,int sudu10)//��ƽ��
{
    TJQ_Control(T1,0,0);//���
    TJQ_Control(T2,0,1);//��ǰ
    TJQ_Control(T3,sudu9,0);//��ǰ
    TJQ_Control(T4,sudu10,1);//�Һ�
}

void Stop()//ֹͣ
{
    TJQ_Control(T1,0,1);//���
    TJQ_Control(T2,0,1);//��ǰ
    TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,0,1);//�Һ� 
    TJQ_Control(T6,0,1);//����
    TJQ_Control(T7,0,1);//����
}
void clear()//���
{
  Servo_Set(1,60); //�м���
}

void collect()//�ռ�
{
  Servo_Set(2,90); //����
	Servo_Set(3,180); //�Ҷ��
}
void duojichushihua()//��ʼ�����
{
 Servo_Set(1,140); //�м���
	Servo_Set(2,180); //����
	Servo_Set(3,90); //�Ҷ��
	Visual_Alarm_Light(0,0,0);
}

int main(void)

{ 
	
	float sudu5=0;
  float sudu6=0;
	int yaw1=0;
	int ycha=0;
	int jishutt=50;
	delay_init(180);		    //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
  SCC_TO_HUB_Init(9600);//��Ƭ����USB HUBͨѶ�˿ڳ�ʼ��
	Internal_System_Init();//��ʼ�����򣬿�����api��c�ļ����ҵ�
  Sensor_HP20X_Init();//��ȴ�������ʼ��
	Servo_Set(1,0); //�����ʼ�Ƕ�
	Servo_Set(3,180); //�����ʼ�Ƕ�
  //delay_ms(100);          //��ʱ100ms
	while(jishutt>0)//�����ѭ����ȡ
	{
	jishutt=jishutt-1;
	Euler_Angle_Read();//����ǻ�ȡ
	yaw1=yaw;//��ȡ���������
	}
	while(1)
	{  
		Euler_Angle_Read();//����ǻ�ȡ
		ycha=yaw-yaw1;//��ǰλ�����ʼλ�õĲ�ֵ
		if(ycha<=80&&ycha>=-20)//ǳˮ��
		{
		Downwater(0,0); //��Ǳ�ƽ���ֹͣ
		}
		else if(ycha<=170&&ycha>80)//������
		{
		Downwater(70,70); //��Ǳ
		}
		else if(ycha<=360&&ycha>170)//��ˮ��
		{
    if(Sensor_HP20X_GetDepth()<100)
		{// ���С��10����
		  Downwater(90,90); //������Ǳ
		 }
		 else if(Sensor_HP20X_GetDepth()<150)
		{// ���С��15����
		  Downwater(70,70); //��Ǳ�ƽ���70%pwm�ƽ�
		 }
		 else if(Sensor_HP20X_GetDepth()<350)
		{// ���С��35����
		  Downwater(60,60);
		} 
			else if(Sensor_HP20X_GetDepth()<450)
		{// ���С��45����
		  Downwater(50,50); 
		 }
		else
		 {
		  Downwater(0,0); //��Ǳ�ƽ���ֹͣ
		 }				
		}	
	}
}		 
			 








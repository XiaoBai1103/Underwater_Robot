/*
	T4��ǰ  T1��ǰ
	T3���  T2�Һ�
	2021/7/26 zxq
*/
#include "external.h" 
#include "api.h"
#include "propeller.h"
#include "servo.h" 
#include "buoyancy.h" 
#include "sys.h"

//USBͨѶ���Ʊ�̽���
int jsq=0;//����������
int yuan=0;//����������
int fang=0;//����������
int cha=0;//��ֵ����
//��ʼ�˶��ٶ�
float one=50;//1��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float two=40;//2��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float three=30;//3��ƫ�Ʒ��ȵ����˳�ʼ�ٶ�
float four=20;//4��ƫ�Ʒ��ȵ�����̬��ʼ�ٶ�
float mind=50;//ǰ����ʼ�ٶ�



	void URAT8_DATA_Analysis(u8 data)
{
	switch(data)
	{
		case 'A' :
		{//��תoneת��
     jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,one,1);
	  TJQ_Control(T3,0,1);
    TJQ_Control(T4,one,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);	
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'S' :
		{//��ת230
      //ִ�����
     jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,two,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,two,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'D' :
		{//��ת100
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,three,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,three,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'F' :
		{//��ת50
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Buoyancy_GPIO_Control(Hold);//LOW
		}
	  TJQ_Control(T1,0,0);
    TJQ_Control(T2,four,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,four,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,90); 
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'G' :
		{
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		 Buoyancy_GPIO_Control(Hold);//LOW
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,mind+2,1);//�Һ�
	  TJQ_Control(T3,mind,0);//���
    TJQ_Control(T4,0,0);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,0);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'H' :
		{//��ת50�ٶ�
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		 Buoyancy_GPIO_Control(Hold);//LOW
		}
		TJQ_Control(T1,four,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,four,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,90);
	//	Buoyancy_GPIO_Control(Hold);//LOW
		
			break;
		}
		case 'J' :
		{//��ת100�ٶ�
			//ִ�����
		jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,three,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,three,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'K' :
		{//��ת200�ٶ�
			//ִ�����
    jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,two,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,two,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'L' :
		{//��ת400�ٶ�
			//ִ�����
	   jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,one,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,one,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
			case 'q' :
		{//��⵽����-���Ƶ���
			//ִ�����
			if(jsq<=0)
			{
					
			Visual_Alarm_Light(0,255,0);//G R 
				
				jsq=15;//�������õƵ�����ʱ�
			Buoyancy_GPIO_Control(Come_up);//�ռ�
		  
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
			}
			break;
		}
		case 'y' :
		{//��⵽Բ��-��Ƶ���
			//ִ�����
			if(jsq<=0)
			{
			Visual_Alarm_Light(0,255,0);
			jsq=15;//�������õƵ�����ʱ��
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//�������Ƶ�Ϩ���ʱ��
			}
			break;
		}
		case 'z' :
		{//��⵽w
			//ִ�����
			mind=mind+1;
			break;
		}
		case 'x' :
		{//��⵽w
			//ִ�����
			mind=mind-1;
			break;
		}
		case 'w' :
		{//��⵽w
			//ִ�����
			one=one-1;
			break;
		}
		case 'e' :
		{//��⵽e
			//ִ�����
			two=two-1;
			break;
		}
	  case 'r' :
		{//��⵽r
			//ִ�����
			three=three-1;
			break;
		}
		case 't' :
		{//��⵽t
			//ִ�����
			four=four-1;
			break;
		}
		case 'p' :
		{//��⵽p
			//ִ�����
			one=50;//1��ƫ�Ʒ��ȵ�����̬����ٶ�
      two=40;//2��ƫ�Ʒ��ȵ�����̬����ٶ�
      three=30;//3��ƫ�Ʒ��ȵ�����̬����ٶ�
      four=50;//4��ƫ�Ʒ��ȵ�����̬����ٶ�
      mind=50;////ǰ������ٶ�;//�ٶȸ�λ
			break;
		}
		case 'V'://ֹͣ
		{
    TJQ_Control(T1,0,0);//���
    TJQ_Control(T2,0,1);//��ǰ
	  TJQ_Control(T3,0,1);//��ǰ
    TJQ_Control(T4,0,1);//�Һ�
    TJQ_Control(T6,0,0);//����
    TJQ_Control(T7,0,1);//����
		Buoyancy_GPIO_Control(Hold);//LOW
		}
		case 'M':
		{
			Buoyancy_GPIO_Control(Hold);//LOW
		}
		case 'N':
		{
			Buoyancy_GPIO_Control(Come_up);//++ HIGH
		}
		default:
		{
			//ִ�����
			
			break;
		}
	}
}

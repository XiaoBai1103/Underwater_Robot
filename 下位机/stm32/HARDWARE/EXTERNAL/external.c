/*
	T4左前  T1右前
	T3左后  T2右后
	2021/7/26 zxq
*/
#include "external.h" 
#include "api.h"
#include "propeller.h"
#include "servo.h" 
#include "buoyancy.h" 
#include "sys.h"

//USB通讯控制编程界面
int jsq=0;//计数器变量
int yuan=0;//计数器变量
int fang=0;//计数器变量
int cha=0;//差值变量
//初始运动速度
float one=50;//1级偏移幅度调整姿态初始速度
float two=40;//2级偏移幅度调整姿态初始速度
float three=30;//3级偏移幅度调整姿初始速度
float four=20;//4级偏移幅度调整姿态初始速度
float mind=50;//前进初始速度



	void URAT8_DATA_Analysis(u8 data)
{
	switch(data)
	{
		case 'A' :
		{//左转one转速
     jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//左转230
      //执行语句
     jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//左转100
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//左转50
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
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
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		 Buoyancy_GPIO_Control(Hold);//LOW
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,mind+2,1);//右后
	  TJQ_Control(T3,mind,0);//左后
    TJQ_Control(T4,0,0);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,0);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'H' :
		{//右转50速度
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//右转100速度
			//执行语句
		jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//右转200速度
			//执行语句
    jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//右转400速度
			//执行语句
	   jsq=jsq-1;//用来控制灯熄灭的时间
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
		{//检测到方块-蓝灯点亮
			//执行语句
			if(jsq<=0)
			{
					
			Visual_Alarm_Light(0,255,0);//G R 
				
				jsq=15;//用来设置灯点亮的时�
			Buoyancy_GPIO_Control(Come_up);//收集
		  
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//用来控制灯熄灭的时间
			}
			break;
		}
		case 'y' :
		{//检测到圆形-红灯点亮
			//执行语句
			if(jsq<=0)
			{
			Visual_Alarm_Light(0,255,0);
			jsq=15;//用来设置灯点亮的时间
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//用来控制灯熄灭的时间
			}
			break;
		}
		case 'z' :
		{//检测到w
			//执行语句
			mind=mind+1;
			break;
		}
		case 'x' :
		{//检测到w
			//执行语句
			mind=mind-1;
			break;
		}
		case 'w' :
		{//检测到w
			//执行语句
			one=one-1;
			break;
		}
		case 'e' :
		{//检测到e
			//执行语句
			two=two-1;
			break;
		}
	  case 'r' :
		{//检测到r
			//执行语句
			three=three-1;
			break;
		}
		case 't' :
		{//检测到t
			//执行语句
			four=four-1;
			break;
		}
		case 'p' :
		{//检测到p
			//执行语句
			one=50;//1级偏移幅度调整姿态最大速度
      two=40;//2级偏移幅度调整姿态最大速度
      three=30;//3级偏移幅度调整姿态最大速度
      four=50;//4级偏移幅度调整姿态最大速度
      mind=50;////前进最大速度;//速度复位
			break;
		}
		case 'V'://停止
		{
    TJQ_Control(T1,0,0);//左后
    TJQ_Control(T2,0,1);//左前
	  TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,0,1);//右后
    TJQ_Control(T6,0,0);//左中
    TJQ_Control(T7,0,1);//右中
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
			//执行语句
			
			break;
		}
	}
}

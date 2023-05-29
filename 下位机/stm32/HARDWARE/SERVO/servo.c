#include "servo.h" 
#include "pwm.h" 

static u8 Servo_Init_1=0;
static u8 Servo_Init_2=0;
static u8 Servo_Init_3=0;
static u8 Servo_Init_4=0;
static u8 Servo_Init_5=0;
static u8 Servo_Init_6=0;
static u8 Servo_Init_7=0;
static u8 Servo_Init_10=0;
static u8 Servo_Init_11=0;


//��ʼ������ӿ�
//���г�ʼ����1�������г�ʼ����0
void Servo_PWM_Init(u8 s1,u8 s3,u8 s4,u8 s5,u8 s6,u8 s7,u8 s10)
{    	 
  TIM1_PWM_Init(s4,s5,s6,s10);//����ִ��4������ִ��5������ִ��6������ִ��10
  TIM9_PWM_Init(s3,s7);//����ִ��3������ִ��7
  TIM11_PWM_Init(s1);//����ִ��1
}

void Servo_PWM_Control(u8 port,u8 angle)
{
  u16 PWM_angle;
  PWM_angle=(u16)angle*angletopwm_mul+pwm_angle_0;
  switch(port)
  {
    case servo1:
    {
      TIM_SetCompare1(TIM11,PWM_angle);
      break;
    }
    case servo3:
    {
      TIM_SetCompare1(TIM9,PWM_angle);
      break;
    }
    case servo4:
    {
      TIM_SetCompare4(TIM1,PWM_angle);
      break;
    }
    case servo5:
    {
      TIM_SetCompare3(TIM1,PWM_angle);
      break;
    }
    case servo6:
    {
      TIM_SetCompare2(TIM1,PWM_angle);
      break;
    }
    case servo7:
    {
      TIM_SetCompare2(TIM9,PWM_angle);
      break;
    }
    case servo10:
    {
      TIM_SetCompare1(TIM1,PWM_angle);
      break;
    }
    default:break;
  }
}
//�����ʼ�����ú���
void Servo_Analysis(u8 port,u8 angle)
{
  u16 PWM_angle;
  PWM_angle=(u16)angle*angletopwm_mul+pwm_angle_0;
  
  switch(port)
  {
    case servo1:
    {
      if(Servo_Init_1==0)
      {
         TIM11_PWM_Init(!Servo_Init_1);
         Servo_Init_1=1;
      }
      TIM_SetCompare1(TIM11,PWM_angle);
      break;
    }
    case servo2:
    {
      if(Servo_Init_2==0)
      {
        TIM4_PWM_Init(!Servo_Init_2);
         Servo_Init_2=1;
      }
      TIM_SetCompare2(TIM4,PWM_angle);
      break;
    }
    case servo3:
    {
      if(Servo_Init_3==0)
      {
        TIM9_PWM_Init(!Servo_Init_3,0);
         Servo_Init_3=1;
      }
      TIM_SetCompare1(TIM9,PWM_angle);
      break;
    }
    case servo4:
    {
      if(Servo_Init_4==0)
      {
        TIM1_PWM_Init(!Servo_Init_4,0,0,0);
         Servo_Init_4=1;
      }
      TIM_SetCompare4(TIM1,PWM_angle);
      break;
    }
    case servo5:
    {
      if(Servo_Init_5==0)
      {
        TIM1_PWM_Init(0,!Servo_Init_5,0,0);
         Servo_Init_5=1;
      }
       TIM_SetCompare3(TIM1,PWM_angle);
      break;
    }
    case servo6:
    {
      if(Servo_Init_6==0)
      {
         TIM1_PWM_Init(0,0,!Servo_Init_6,0);
         Servo_Init_6=1;
      }
      TIM_SetCompare2(TIM1,PWM_angle);
      break;
    }
    case servo7:
    {
      if(Servo_Init_7==0)
      {
        TIM9_PWM_Init(0,!Servo_Init_7);
         Servo_Init_7=1;
      }
      TIM_SetCompare2(TIM9,PWM_angle);
      break;
    }
    case servo10:
    {
      if(Servo_Init_10==0)
      {
        TIM1_PWM_Init(0,0,0,!Servo_Init_10);
         Servo_Init_10=1;
      }
       TIM_SetCompare1(TIM1,PWM_angle);
      break;
    }
    case servo11:
    {
      if(Servo_Init_11==0)
      {
        TIM2_PWM_Init(!Servo_Init_11);
         Servo_Init_11=1;
      }
      TIM_SetCompare1(TIM2,PWM_angle);
      break;
    }
    default:break;
  }
}  



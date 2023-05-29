#include "propeller.h"
#include "stdio.h"
void T_DIR_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC
	
	GPIO_SetBits(GPIOC,GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

}
//�ƽ������ƺ�����t_num �ƽ������1-8��t_speed �ƽ����ٶ� 0-499��t_dir �ƽ������� 0 1
void Propeller_Set(u8 t_num,u16 t_speed,u8 t_dir)
{    	 
    switch(t_num)
    {
      case T1:
        {
          if(t_dir>0)
          {            
              TD1=1;
          }
          else
          {             
              TD1=0;
          }
          TIM_SetCompare1(TIM3,t_speed);
          break;
        }
       case T2:
        {
          if(t_dir>0)
          {            
              TD2=1;
          }
          else
          {             
              TD2=0;
          }
          TIM_SetCompare2(TIM3,t_speed);
          break;
        }
       case T3:
        {
          if(t_dir>0)
          {            
              TD3=1;
          }
          else
          {             
              TD3=0;
          }
          TIM_SetCompare4(TIM8,t_speed);
          break;
        }
       case T4:
        {
          if(t_dir>0)
          {            
              TD4=1;
          }
          else
          {             
              TD4=0;
          }
          TIM_SetCompare3(TIM8,t_speed);
          break;
        }
       case T5:
        {
          if(t_dir>0)
          {            
              TD5=1;
          }
          else
          {             
              TD5=0;
          }
          TIM_SetCompare3(TIM3,t_speed);
          break;
        }
       case T6:
        {
          if(t_dir>0)
          {            
              TD6=1;
          }
          else
          {             
              TD6=0;
          }
          TIM_SetCompare4(TIM3,t_speed);
          break;
        }
       case T7:
        {
          if(t_dir>0)
          {            
              TD7=1;
          }
          else
          {             
              TD7=0;
          }
          TIM_SetCompare2(TIM8,t_speed);
          break;
        }
       case T8:
        {
          if(t_dir>0)
          {            
              TD8=1;
          }
          else
          {             
              TD8=0;
          }
          TIM_SetCompare1(TIM8,t_speed);
          break;
        }
        default:break;
    }
}
float incr_KP=0.088;
float incr_KI=0;//0.0005
float incr_KD=0;

u16 target_pwm=0;

u16 PWM_Calculate(u16 target_v,u16 current_v)
{
	 if((target_v - current_v)>0)
	 {
		  if((target_v - current_v)>40)
			{
				target_pwm+=(target_v - current_v)*0.09;
			}
			else 
			{
			   target_pwm+=(target_v - current_v)*0.025;
			}
	 }
	 else
	 {
		 if((current_v - target_v)>40)
		 {
				target_pwm-=(current_v-target_v)*0.09;
		 }
		 else
		 {
		    target_pwm-=(current_v-target_v)*0.025;
		 }
	 }
	 if(target_pwm>499)
	 {
			target_pwm=499;
	 }
	 else if(target_pwm<0)
	 {
			target_pwm=0;
	 }
   return target_pwm;
}








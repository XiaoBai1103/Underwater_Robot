#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "beep.h"
#include "stdio.h"

 u16 Sensor_State_All=0x0FFF;           //�������崫��״̬����


//����״̬��1����
void Senser_State_Set(u8 Sensor_num)
{
  Sensor_State_All |=(0x0001<<(Sensor_num-1)); 
}

//����״̬��0����
void Sensor_State_Reset(u8 Sensor_num)
{
  Sensor_State_All &=~(0x0001<<(Sensor_num-1)); 
}



//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//����Sensor_1
/******************************����1******************************/   
	if(Sensor_State_1)	  
	{
		Senser_State_Set(Sensor_1);  
	}		 
  else
  {   
    Sensor_State_Reset(Sensor_1);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_1); //���LINE2�ϵ��жϱ�־λ 
/****************************************************************/   
}	
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//����
/******************************����3******************************/   
	if(Sensor_State_3)	  
	{
		Senser_State_Set(Sensor_3);  
	}		 
  else 
  {
    Sensor_State_Reset(Sensor_3);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_3);//���LINE4�ϵ��жϱ�־λ  
/****************************************************************/   
}

//�ⲿ�ж�0�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
/******************************����9******************************/ 
	if(Sensor_State_9)	  
	{
		Senser_State_Set(Sensor_9);  
	}		 
  else 
  {
    Sensor_State_Reset(Sensor_9);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_9); //���LINE0�ϵ��жϱ�־λ 
/****************************************************************/ 
}	

//�ⲿ�ж�4�������
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//����
/******************************����8******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_8))  
  {
    if(Sensor_State_8)	  
    {
      Senser_State_Set(Sensor_8);    
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_8);//���LINE4�ϵ��жϱ�־λ    
    }		 
    else if(!Sensor_State_8)
    {
       Sensor_State_Reset(Sensor_8);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_8);//���LINE4�ϵ��жϱ�־λ
    }
  }
/****************************************************************/    
/******************************����2******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_2))  
  {
    if(Sensor_State_2)	  
    {
      Senser_State_Set(Sensor_2);  
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_2);//���LINE4�ϵ��жϱ�־λ  
    }		 
    else if(!Sensor_State_2)
    {
       Sensor_State_Reset(Sensor_2); 
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_2);//���LINE4�ϵ��жϱ�־λ      
    }
  }
  
/****************************************************************/    
/******************************����11******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_11))  
  {
    if(Sensor_State_11)	  
    {
      Senser_State_Set(Sensor_11); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_11);//���LINE4�ϵ��жϱ�־λ    
    }		 
    else if(!Sensor_State_11)
    {
       Sensor_State_Reset(Sensor_11);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_11);//���LINE4�ϵ��жϱ�־λ
    }
  }
     
/****************************************************************/    
/******************************����10******************************/  
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_10))  
  {  
    if(Sensor_State_10)	  
    {
      Senser_State_Set(Sensor_10); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_10);//���LINE4�ϵ��жϱ�־λ     
    }		 
    else if(!Sensor_State_10)
    {
       Sensor_State_Reset(Sensor_10);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_10);//���LINE4�ϵ��жϱ�־λ 
    }
  }    
/****************************************************************/    
}
//�ⲿ�ж�0�������
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//����
/******************************����5******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_5))
  {
    if(Sensor_State_5)	  
    {
      Senser_State_Set(Sensor_5);  
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_5);//���LINE5�ϵ��жϱ�־λ 
    }		 
    else if(!Sensor_State_5)
    {
       Sensor_State_Reset(Sensor_5);	    
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_5);//���LINE5�ϵ��жϱ�־λ 
    }
  }
/****************************************************************/    
/******************************����6******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_6))  
  {
    if(Sensor_State_6)	  
    {
      Senser_State_Set(Sensor_6);  
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_6);//���LINE4�ϵ��жϱ�־λ
    }		 
    else if(!Sensor_State_6)
    {
       Sensor_State_Reset(Sensor_6);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_6);//���LINE4�ϵ��жϱ�־λ
    }
  }
/****************************************************************/    
/******************************����7******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_7))  
  {
    if(Sensor_State_7)	  
    {
      Senser_State_Set(Sensor_7); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_7);//���LINE4�ϵ��жϱ�־λ    
    }		 
    else if(!Sensor_State_7)
    {
       Sensor_State_Reset(Sensor_7);  
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_7);//���LINE4�ϵ��жϱ�־λ
    }
 } 
/****************************************************************/    
/******************************����4******************************/    
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_4))  
  {
    if(Sensor_State_4)	  
    {
      Senser_State_Set(Sensor_4);    
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_4);//���LINE4�ϵ��жϱ�־λ    
    }		 
    else if(!Sensor_State_4)
    {
       Sensor_State_Reset(Sensor_4);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_4);//���LINE4�ϵ��жϱ�־λ 
    }
  }
/****************************************************************/
}	


//�ⲿ�жϳ�ʼ������
void EXTIX_Indepent_Init(u8 port)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��

  switch(port)
  {
    case Sensor_1:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2
        
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2); //PE2   ���ӵ��ж���2   ����1
        /* ����EXTI_Line0 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE2
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش��� 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE2
      EXTI_Init(&EXTI_InitStructure);//����
  
      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
      
      if(!Sensor_State_1)
      {
        Sensor_State_Reset(Sensor_1);
      }
      
      break;
    }
    case Sensor_2:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB6
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6); //PB6   ���ӵ��ж���6   ����2
      	/* ����EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line6;//LINE6
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
      
//      #ifndef  __EXTI9_5_IRQn
//      #define  __EXTI9_5_IRQn
     	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�6
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
//      #endif
       
      if(!Sensor_State_2)
      {
        Sensor_State_Reset(Sensor_2);
      } 
       
      break;
    }
    case Sensor_3:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE3
      
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3); //PE3   ���ӵ��ж���3   ����3
      
        	/* ����EXTI_Line0 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LINE3
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش��� 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE3
      EXTI_Init(&EXTI_InitStructure);//����
      
     	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
      
      if(!Sensor_State_3)
      {
        Sensor_State_Reset(Sensor_3);
      }
      
      break;
    }  
    case Sensor_4:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE15
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);//PE15  ���ӵ��ж���15  ����4
      
      	/* ����EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line15;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
      
//      #ifndef __EXTI15_10_IRQn
//      #define __EXTI15_10_IRQn      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
//      #endif      
      if(!Sensor_State_4)
      {
        Sensor_State_Reset(Sensor_4);
      }      
      break;
    }  
    case Sensor_5:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ����ģʽ
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE12
			GPIO_SetBits(GPIOE,GPIO_Pin_12);
           
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource12);//PE12  ���ӵ��ж���12  ����5          
        	/* ����EXTI_Line12 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line12;//LINE12
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش��� 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE12
      EXTI_Init(&EXTI_InitStructure);//����
        
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�12
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
 
      if(!Sensor_State_5)
      {
        Sensor_State_Reset(Sensor_5);
      }  
      break;     
    }
    case Sensor_6:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE10
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);//PE10  ���ӵ��ж���10  ����6      
      	/* ����EXTI_Line10 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line10;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
          
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�10
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
      
      if(!Sensor_State_6)
      {
        Sensor_State_Reset(Sensor_6);
      }
      break;           
    }
    case Sensor_7:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC13
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);//PC13  ���ӵ��ж���13  ����7
      
        	/* ����EXTI_Line13 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE13
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش��� 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE13
      EXTI_Init(&EXTI_InitStructure);//����
          
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�13
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
      
      if(!Sensor_State_7)
      {
        Sensor_State_Reset(Sensor_7);
      }
      break; 
    }
    case Sensor_8:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD5
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5); //PD5   ���ӵ��ж���5   ����8
    
        /* ����EXTI_Line5 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line5;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
    
     if(!Sensor_State_8)
     {
       Sensor_State_Reset(Sensor_8);
     }
     
      break;      
    }
    case Sensor_9:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC4
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4); //PC4   ���ӵ��ж���4   ����9
      
        /* ����EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE4
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش��� 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE4
      EXTI_Init(&EXTI_InitStructure);//����
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
    
      if(!Sensor_State_9)
      {
        Sensor_State_Reset(Sensor_9);
      }
      break;     
    }
    case Sensor_10:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE8
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8); //PE8   ���ӵ��ж���8   ����10
    
        /* ����EXTI_Line8 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line8;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�8
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����

      if(!Sensor_State_10)
      {
        Sensor_State_Reset(Sensor_10);
      }
      break;      
    }
    case Sensor_11:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // ��Ӧ����
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
      GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE7
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7); //PE7   ���ӵ��ж���7   ����11
    
        /* ����EXTI_Line7 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line7;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //������/�½��ش���
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
      EXTI_Init(&EXTI_InitStructure);//����
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�7
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
      NVIC_Init(&NVIC_InitStructure);//����
     
     if(!Sensor_State_11)
     {
       Sensor_State_Reset(Sensor_11);
     }
      break;
    }
    default:break;  
  }

}



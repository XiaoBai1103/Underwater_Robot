#include "pwm.h"
#include "led.h"
#include "usart.h"
 

//TIM3 PWM��ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTBʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA6����Ϊ��ʱ��3
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0����Ϊ��ʱ��3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA6.7
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB0.1
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM3 Channel1-4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
  
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC4

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
 
										  
}  

//TIM8 PWM��ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM8_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);   	//TIM8ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
  
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOC6����Ϊ��ʱ��8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); //GPIOC7����Ϊ��ʱ��8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); //GPIOC8����Ϊ��ʱ��8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); //GPIOC9����Ϊ��ʱ��8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PC6.7.8.9
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//��ʼ����ʱ��8
	
	//��ʼ��TIM8 Channel1-4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
  
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC1
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC2
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC3
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC4

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPEʹ�� 
	TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8								  
}  

void TIM1_PWM_Init(u8 s4,u8 s5,u8 s6,u8 s10)//����ִ��4������ִ��5������ִ��6������ִ��10
{		 					 
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

		if(s4+s5+s6+s10)
		{
			TIM_Cmd(TIM1, DISABLE);  //ʧ��TIM1
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTEʱ��	
			
			if(s10)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOE9����Ϊ��ʱ��1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOE9
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
			}
			if(s4)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); //GPIOE14����Ϊ��ʱ��1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOE14
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
			}
			if(s5)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); //GPIOE13����Ϊ��ʱ��1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           //GPIOE13
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
			}
			if(s6)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOE11����Ϊ��ʱ��1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //GPIOE11
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
			}
			
			TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //��ʱ����Ƶ
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
			TIM_TimeBaseStructure.TIM_Period=40000-1;   //�Զ���װ��ֵ
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
			
			//��ʼ��TIM1 Channel1-4 PWMģʽ	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
			TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
			
			if(s10)
			{
				TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC1
				TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
			}
			if(s6)
			{
				 TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC2
				 TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
			}
			if(s5)
			{
				TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC3
				TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
			}
			if(s4)
			{
				TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1OC4
				TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR4�ϵ�Ԥװ�ؼĴ���
			}    
			 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
			
			TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
		} 										  
}  
void TIM9_PWM_Init(u8 s3,u8 s7)//����ִ��3������ִ��7
{		 		
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(s3+s7)
  {
    TIM_Cmd(TIM9, DISABLE);  //ʧ��TIM9
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9ʱ��ʹ��    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTEʱ��	
    
    if(s3)
    {
      GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); //GPIOE5����Ϊ��ʱ��9
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOE5
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
      GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
    }
    if(s7)
    {
      GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOE6����Ϊ��ʱ��9
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOE6
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
      GPIO_Init(GPIOE,&GPIO_InitStructure);               //��ʼ��
    }
    TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��9
    
    //��ʼ��TIM9 Channel1-4 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    
    if(s3)
    {
      TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM9OC1
      TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM9��CCR1�ϵ�Ԥװ�ؼĴ���
    }
    if(s7)
    {
       TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM9OC2
       TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM9��CCR1�ϵ�Ԥװ�ؼĴ���
    }  	
    TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPEʹ�� 
    
    TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM9
  }										  
}  
void TIM11_PWM_Init(u8 s1)//����ִ��1
{		 					  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  if(s1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  	//TIM11ʱ��ʹ��    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTBʱ��	
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); //GPIOB9����Ϊ��ʱ��11
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOB9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB9
      
    TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);//��ʼ����ʱ��11
    
    //��ʼ��TIM11 Channel1-4 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    
    TIM_OC1Init(TIM11, &TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM11OC1

    TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);  //ʹ��TIM11��CCR1�ϵ�Ԥװ�ؼĴ���

    TIM_ARRPreloadConfig(TIM11,ENABLE);//ARPEʹ��
     
     TIM_Cmd(TIM11, ENABLE);  //ʹ��TIM11
 }
 
}  

void TIM2_PWM_Init(u8 s11)//����ִ��11
{		 				
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(s11)
  {       
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2ʱ��ʹ��    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); //GPIOA5����Ϊ��ʱ��2
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOA,&GPIO_InitStructure);               //��ʼ��
    
    TIM_TimeBaseStructure.TIM_Prescaler=45-1;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��2
    
    //��ʼ��TIM2 Channel1-4 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2OC1
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
      
    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ�� 
    
    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
  }   
} 
void TIM4_PWM_Init(u8 s2)//����ִ��2
{		 				
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  if(s2)
  {
    TIM_Cmd(TIM4, DISABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ��    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTBʱ��	
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); //GPIOB7����Ϊ��ʱ��3
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOB7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
    GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB7
      
    TIM_TimeBaseStructure.TIM_Prescaler=45-1;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
    
    //��ʼ��TIM4 Channel1-4 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3OC1

    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���

    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
    
    TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4  
  }
}   

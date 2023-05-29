#include "timer.h" 
#include "stdio.h"
#include "delay.h" 
#include "propeller.h"
#include "adc.h"

u8 NUM[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
u8 speed[]={0x00,0x00,0x00,0x00};

u8 sp[4]={0x00,0x40,0x06,0x6D}; //SP-X

u8 di[4]={0X00,0X40,0X06,0X5E}; //DI-X
u8 fx[2]={0x71,0x37};
int i=0,j_num=0,z_num=0,tempnum=0;
float TEMP=0;



TIM_ICInitTypeDef  TIM5_ICInitStructure;
//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //PA1����λ��ʱ��5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); //PA2����λ��ʱ��5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); //PA3����λ��ʱ��5
  
	 //TIM_DeInit(TIM5);  
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;
//��ʱ��4ͨ��1-4���벶������
//arr���Զ���װֵ(TIM4��16λ��)
//psc��ʱ��Ԥ��Ƶ��
void TIM4_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //GPIOD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PD

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //PA12����λ��ʱ��5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //PA13����λ��ʱ��5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //PA14����λ��ʱ��5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //PA15����λ��ʱ��5
  
	 //TIM_DeInit(TIM4);  
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM4���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��4

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	
}

static int32_t TIM5IC_ReadValue1_ch1, TIM5IC_ReadValue2_ch1;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM5CaptureNumber_ch1 = 0;    //��¼�������
static int64_t TIM5Capture_ch1 = 0;         //���ղ�������ֵ
static int32_t TIM5Cnt_ch1 = 0;   
int64_t TIM5TotalCapture_ch1 = 0;   

static int32_t TIM5IC_ReadValue1_ch2, TIM5IC_ReadValue2_ch2;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM5CaptureNumber_ch2 = 0;    //��¼�������
static int64_t TIM5Capture_ch2 = 0;         //���ղ�������ֵ
static int32_t TIM5Cnt_ch2 = 0;   
int64_t TIM5TotalCapture_ch2 = 0;   

static int32_t TIM5IC_ReadValue1_ch3, TIM5IC_ReadValue2_ch3;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM5CaptureNumber_ch3 = 0;    //��¼�������
static int64_t TIM5Capture_ch3 = 0;         //���ղ�������ֵ
static int32_t TIM5Cnt_ch3 = 0;   
int64_t TIM5TotalCapture_ch3 = 0;   

static int32_t TIM5IC_ReadValue1_ch4, TIM5IC_ReadValue2_ch4;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM5CaptureNumber_ch4 = 0;    //��¼�������
static int64_t TIM5Capture_ch4 = 0;         //���ղ�������ֵ
static int32_t TIM5Cnt_ch4 = 0;   
int64_t TIM5TotalCapture_ch4 = 0;   
  
/*
********************************************************************************
** �������� �� void TIM5_IRQHandler(void)
** �������� �� ���벶��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void TIM5_IRQHandler(void)
{
	
	//������յ�������
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC1)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
		
			if(TIM5CaptureNumber_ch1==0)
			{
					TIM5IC_ReadValue1_ch1 = TIM_GetCapture1(TIM5);
					TIM5CaptureNumber_ch1 = 1;
			}
			else if(TIM5CaptureNumber_ch1==1)
			{
					TIM5IC_ReadValue2_ch1 = TIM_GetCapture1(TIM5);
				
				  if(TIM5IC_ReadValue2_ch1 > TIM5IC_ReadValue1_ch1)
					{
							TIM5Capture_ch1 += (TIM5IC_ReadValue2_ch1 - TIM5IC_ReadValue1_ch1);	
					}
					else
					{
							TIM5Capture_ch1 += ((0xFFFF - TIM5IC_ReadValue1_ch1) + TIM5IC_ReadValue2_ch1);
					}
					
					if(++TIM5Cnt_ch1 == 6)
					{
						TIM5TotalCapture_ch1 = TIM5Capture_ch1 ;
						TIM5Capture_ch1 		 = 0;
						TIM5Cnt_ch1					 = 0;
					}
					
					TIM5CaptureNumber_ch1 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC2)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
		
			if(TIM5CaptureNumber_ch2==0)
			{
					TIM5IC_ReadValue1_ch2 = TIM_GetCapture2(TIM5);
					TIM5CaptureNumber_ch2 = 1;
			}
			else if(TIM5CaptureNumber_ch2==1)
			{
					TIM5IC_ReadValue2_ch2 = TIM_GetCapture2(TIM5);
				
				  if(TIM5IC_ReadValue2_ch2 > TIM5IC_ReadValue1_ch2)
					{
							TIM5Capture_ch2 += (TIM5IC_ReadValue2_ch2 - TIM5IC_ReadValue1_ch2);	
					}
					else
					{
							TIM5Capture_ch2 += ((0xFFFF - TIM5IC_ReadValue1_ch2) + TIM5IC_ReadValue2_ch2);
					}
					
					if(++TIM5Cnt_ch2 == 60)
					{
						TIM5TotalCapture_ch2 = TIM5Capture_ch2 / 10;
						TIM5Capture_ch2 		 = 0;
						TIM5Cnt_ch2					 = 0;
					}
					
					TIM5CaptureNumber_ch2 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC3)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
		
			if(TIM5CaptureNumber_ch3==0)
			{
					TIM5IC_ReadValue1_ch3 = TIM_GetCapture3(TIM5);
					TIM5CaptureNumber_ch3 = 1;
			}
			else if(TIM5CaptureNumber_ch3==1)
			{
					TIM5IC_ReadValue2_ch3 = TIM_GetCapture3(TIM5);
				
				  if(TIM5IC_ReadValue2_ch3 > TIM5IC_ReadValue1_ch3)
					{
							TIM5Capture_ch3 += (TIM5IC_ReadValue2_ch3 - TIM5IC_ReadValue1_ch3);	
					}
					else
					{
							TIM5Capture_ch3 += ((0xFFFF - TIM5IC_ReadValue1_ch3) + TIM5IC_ReadValue2_ch3);
					}
					
					if(++TIM5Cnt_ch3 == 60)
					{
						TIM5TotalCapture_ch3 = TIM5Capture_ch3 / 10;
						TIM5Capture_ch3 		 = 0;
						TIM5Cnt_ch3					 = 0;
					}
					
					TIM5CaptureNumber_ch3 = 0;
			}
	}
  else if(TIM_GetITStatus(TIM5, TIM_IT_CC4)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
		
			if(TIM5CaptureNumber_ch4==0)
			{
					TIM5IC_ReadValue1_ch4 = TIM_GetCapture4(TIM5);
					TIM5CaptureNumber_ch4 = 1;
			}
			else if(TIM5CaptureNumber_ch4==1)
			{
					TIM5IC_ReadValue2_ch4 = TIM_GetCapture4(TIM5);
				
				  if(TIM5IC_ReadValue2_ch4 > TIM5IC_ReadValue1_ch4)
					{
							TIM5Capture_ch4 += (TIM5IC_ReadValue2_ch4 - TIM5IC_ReadValue1_ch4);	
					}
					else
					{
							TIM5Capture_ch4 += ((0xFFFF - TIM5IC_ReadValue1_ch4) + TIM5IC_ReadValue2_ch4);
					}
					
					if(++TIM5Cnt_ch4 == 60)
					{
						TIM5TotalCapture_ch4 = TIM5Capture_ch4 / 10;
						TIM5Capture_ch4 		 = 0;
						TIM5Cnt_ch4					 = 0;
					}
					
					TIM5CaptureNumber_ch4 = 0;
			}
	}
	  	
}

static int32_t TIM4IC_ReadValue1_ch1, TIM4IC_ReadValue2_ch1;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM4CaptureNumber_ch1 = 0;    //��¼�������
static int64_t TIM4Capture_ch1 = 0;         //���ղ�������ֵ
static int32_t TIM4Cnt_ch1 = 0;   
int64_t TIM4TotalCapture_ch1 = 0;   

static int32_t TIM4IC_ReadValue1_ch2, TIM4IC_ReadValue2_ch2;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM4CaptureNumber_ch2 = 0;    //��¼�������
static int64_t TIM4Capture_ch2 = 0;         //���ղ�������ֵ
static int32_t TIM4Cnt_ch2 = 0;   
int64_t TIM4TotalCapture_ch2 = 0;   

static int32_t TIM4IC_ReadValue1_ch3, TIM4IC_ReadValue2_ch3;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM4CaptureNumber_ch3 = 0;    //��¼�������
static int64_t TIM4Capture_ch3 = 0;         //���ղ�������ֵ
static int32_t TIM4Cnt_ch3 = 0;   
int64_t TIM4TotalCapture_ch3 = 0;   

static int32_t TIM4IC_ReadValue1_ch4, TIM4IC_ReadValue2_ch4;  //��¼ͨ���Ĳ���ֵ
static int32_t TIM4CaptureNumber_ch4 = 0;    //��¼�������
static int64_t TIM4Capture_ch4 = 0;         //���ղ�������ֵ
static int32_t TIM4Cnt_ch4 = 0;   
int64_t TIM4TotalCapture_ch4 = 0;   

/*
********************************************************************************
** �������� �� void TIM4_IRQHandler(void)
** �������� �� ��ʱ���ж�
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void TIM4_IRQHandler(void)
{
	
	//������յ�������
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC1)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		
			if(TIM4CaptureNumber_ch1==0)
			{
					TIM4IC_ReadValue1_ch1 = TIM_GetCapture1(TIM4);
					TIM4CaptureNumber_ch1 = 1;
			}
			else if(TIM4CaptureNumber_ch1==1)
			{
					TIM4IC_ReadValue2_ch1 = TIM_GetCapture1(TIM4);
				
				  if(TIM4IC_ReadValue2_ch1 > TIM4IC_ReadValue1_ch1)
					{
							TIM4Capture_ch1 += (TIM4IC_ReadValue2_ch1 - TIM4IC_ReadValue1_ch1);	
					}
					else
					{
							TIM4Capture_ch1 += ((0xFFFF - TIM4IC_ReadValue1_ch1) + TIM4IC_ReadValue2_ch1);
					}
					
					if(++TIM4Cnt_ch1 == 60)
					{
						TIM4TotalCapture_ch1 = TIM4Capture_ch1 / 10;
						TIM4Capture_ch1 		 = 0;
						TIM4Cnt_ch1					 = 0;
					}
					
					TIM4CaptureNumber_ch1 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC2)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
		
			if(TIM4CaptureNumber_ch2==0)
			{
					TIM4IC_ReadValue1_ch2 = TIM_GetCapture2(TIM4);
					TIM4CaptureNumber_ch2 = 1;
			}
			else if(TIM4CaptureNumber_ch2==1)
			{
					TIM4IC_ReadValue2_ch2 = TIM_GetCapture2(TIM4);
				
				  if(TIM4IC_ReadValue2_ch2 > TIM4IC_ReadValue1_ch2)
					{
							TIM4Capture_ch2 += (TIM4IC_ReadValue2_ch2 - TIM4IC_ReadValue1_ch2);	
					}
					else
					{
							TIM4Capture_ch2 += ((0xFFFF - TIM4IC_ReadValue1_ch2) + TIM4IC_ReadValue2_ch2);
					}
					
					if(++TIM4Cnt_ch2 == 60)
					{
						TIM4TotalCapture_ch2 = TIM4Capture_ch2 / 10;
						TIM4Capture_ch2 		 = 0;
						TIM4Cnt_ch2					 = 0;
					}
					
					TIM4CaptureNumber_ch2 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC3)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
		
			if(TIM4CaptureNumber_ch3==0)
			{
					TIM4IC_ReadValue1_ch3 = TIM_GetCapture3(TIM4);
					TIM4CaptureNumber_ch3 = 1;
			}
			else if(TIM4CaptureNumber_ch3==1)
			{
					TIM4IC_ReadValue2_ch3 = TIM_GetCapture3(TIM4);
				
				  if(TIM4IC_ReadValue2_ch3 > TIM4IC_ReadValue1_ch3)
					{
							TIM4Capture_ch3 += (TIM4IC_ReadValue2_ch3 - TIM4IC_ReadValue1_ch3);	
					}
					else
					{
							TIM4Capture_ch3 += ((0xFFFF - TIM4IC_ReadValue1_ch3) + TIM4IC_ReadValue2_ch3);
					}
					
					if(++TIM4Cnt_ch3 == 60)
					{
						TIM4TotalCapture_ch3 = TIM4Capture_ch3/10 ;
						TIM4Capture_ch3 		 = 0;
						TIM4Cnt_ch3					 = 0;
					}
					
					TIM4CaptureNumber_ch3 = 0;
			}
	}
  else if(TIM_GetITStatus(TIM4, TIM_IT_CC4)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
		
			if(TIM4CaptureNumber_ch4==0)
			{
					TIM4IC_ReadValue1_ch4 = TIM_GetCapture4(TIM4);
					TIM4CaptureNumber_ch4 = 1;
			}
			else if(TIM4CaptureNumber_ch4==1)
			{
					TIM4IC_ReadValue2_ch4 = TIM_GetCapture4(TIM4);
				
				  if(TIM4IC_ReadValue2_ch4 > TIM4IC_ReadValue1_ch4)
					{
							TIM4Capture_ch4 += (TIM4IC_ReadValue2_ch4 - TIM4IC_ReadValue1_ch4);	
					}
					else
					{
							TIM4Capture_ch4 += ((0xFFFF - TIM4IC_ReadValue1_ch4) + TIM4IC_ReadValue2_ch4);
					}
					
					if(++TIM4Cnt_ch4 == 60)
					{
						TIM4TotalCapture_ch4 = TIM4Capture_ch4 / 10;
						TIM4Capture_ch4 		 = 0;
						TIM4Cnt_ch4					 = 0;
					}
					
					TIM4CaptureNumber_ch4 = 0;
			}
	}
	  	
}


void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM7��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM7, ENABLE);  //ʹ��TIMx					 
}

u16 T1_Speed=0;
u16 T2_Speed=0;
u16 T3_Speed=0;
u16 T4_Speed=0;
u16 T5_Speed=0;
u16 T6_Speed=0;
u16 T7_Speed=0;
u16 T8_Speed=0;

//��ʱ��7�жϷ������
void TIM7_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
      TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIMx�����жϱ�־     

 
      T1_Speed= 1000000 / TIM5TotalCapture_ch1 * 60;
      T2_Speed= 1000000 / TIM5TotalCapture_ch2 * 60;
      T3_Speed= 1000000 / TIM4TotalCapture_ch4 * 60;
      T4_Speed= 1000000 / TIM4TotalCapture_ch3 * 60;
      T5_Speed= 1000000 / TIM5TotalCapture_ch3 * 60;
      T6_Speed= 1000000 / TIM5TotalCapture_ch4 * 60;
      T7_Speed= 1000000 / TIM4TotalCapture_ch2 * 60;
      T8_Speed= 1000000 / TIM4TotalCapture_ch1 * 60;
      
      
//      printf("T1:%d\t",T1_Speed);
//      printf("T2:%d\t",T2_Speed);
//      printf("T3:%d\t",T3_Speed);
//      printf("T4:%d\t",T4_Speed);
//      printf("T5:%d\t",T5_Speed);
//      printf("T6:%d\t",T6_Speed);
//      printf("T7:%d\t",T7_Speed);
//      printf("T8:%d\t\n\n",T8_Speed);
      
      TIM5TotalCapture_ch1=0 ;
      TIM5TotalCapture_ch2=0 ;
      TIM5TotalCapture_ch3=0 ;
      TIM5TotalCapture_ch4=0 ;
      TIM4TotalCapture_ch1=0 ;
      TIM4TotalCapture_ch2=0 ;
      TIM4TotalCapture_ch3=0 ;
      TIM4TotalCapture_ch4=0 ;

		}
}

u16 TJQ_FB_Read(u8 t_num)
{
     switch(t_num)
     {
       case T1:
       {
          return T1_Speed;
 //         break;
       }
       case T2:
       {
          return T2_Speed;
 //         break;
       }
       case T3:
       {
          return T3_Speed;
 //         break;
       }
       case T4:
       {
          return T4_Speed;
 //         break;
       }
       case T5:
       {
          return T5_Speed;
 //         break;
       }
       case T6:
       {
          return T6_Speed;
 //         break;
       }
       case T7:
       {
          return T7_Speed;
 //         break;
       }
       case T8:
       {
          return T8_Speed;
 //         break;
       }
       default:
       {
        return 0;
         break;
       }
     }
}  



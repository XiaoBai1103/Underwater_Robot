#include "led.h" 
#include "delay.h"
//����RGB��ֵ���� 
u8 g_ledDataBuffer[24];
//RGB�˿ڳ�ʼ��
void RGB_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RGB_ClockCmd();            //ʹ��RGB GPIOʱ��

  GPIO_InitStructure.GPIO_Pin = RGB_PIN;//��ʼ��RGB_PIN
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(RGB_GPIO, &GPIO_InitStructure);//��ʼ��GPIO
	
  RGB_LED_LOW;                           //RGB���ƹܽ����õ�		 
}

/********************************************************/
//
/********************************************************/
//RGBд����ֵ0
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
  
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
}

/********************************************************/
//
/********************************************************/
//RGBд����ֵ1
void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 

	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();   
}
//RGB��λ
void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(20);
}
//RGBд��1���ֽ�����
void RGB_LED_Write_Byte(u8 byte)
{
	u8 i;

	for(i=0;i<8;i++)
		{
			if(byte&0x80)
				{
					RGB_LED_Write1();
			}
			else
				{
					RGB_LED_Write0();
			}
		byte <<= 1;
	}
}
//����RGB������ɫ
void RGB_LED_Write_24Bits(u8 green,u8 red,u8 blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);

  
}


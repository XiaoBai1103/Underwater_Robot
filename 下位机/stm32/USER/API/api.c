#include "api.h" 
#include "pwm.h"
#include "exti.h"
#include "led.h"
#include "propeller.h"
#include "433m.h" 
#include "usart.h"	
#include "bno055.h" 
#include "beep.h" 
#include "delay.h" 
#include "hp20x.h"
#include "dac.h"
#include "timer.h"
#include "adc.h"
#include "buoyancy.h" 
#include "servo.h"


/** NO.0001
   *ϵͳ�ڲ���ʼ������
   */
void Internal_System_Init(void)
{
	//Exti_Port_Init(11);
  //433M����
  WM_433M_Init(9600);//ң����433ģ���ʼ��
  WM_433M_SET("AT+C012");//ң����433ģ��ͨѶID��
  //��̬����������
  Sensor_BNO055_Init(115200,OPERATION_MODE_NDOF);
  //�ƽ�����ʼ��
  TJQ_Init();
  //��������ʼ��
  Buzzer_Init();
  //��ص�ѹ����ʼ��
  Bat_Vol_Det_Init();
  //�ƹⱨ��ģ���ʼ��
  Visual_Alarm_Light_Init();
  //�ƹⱨ��ģ����ʾ�׹�
  Visual_Alarm_Light(255,255,255);
	Buoyancy_GPIO_Init();
	
	Exti_Port_Init(1);
  //��ʼ����ɷ�����������ʾ
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);  
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);   
}
/*********************************������*********************************/
/**
 *ʹ��ʱͳһ��ʼ�����û��ɵ���Ӧ�ú���ʵ�ֹ���
 *
 */
/** NO.0002
   *433Mģ��˿ڳ�ʼ������
   */
void WM_433M_Init(u32 bound)
{
   SET433MPIN_Init();   //433M������������ �ߵ�ƽ͸��ģʽ/�͵�ƽ����ģʽ
   uart_init(bound);     //433M   ����1ͨѶ��ʼ��
}
/** NO.0003
   *433Mģ��Ƶ�����ú���
   */
void WM_433M_SET(char *AT)
{
	SET_433M(AT);
}

/** NO.0004
   *������BNO055�˿ڳ�ʼ������
   */
void Sensor_BNO055_Init(u32 bound,u8 mode)
{
	u8 BNO055_Init_Result=3;
	
	uart5_init(bound);    //BNO055 ����5ͨѶ��ʼ��
	
	delay_ms(1000);
  while(BNO055_Init_Result != Init_Successful)
  {
      BNO055_Init_Result=BNO055_Init(mode);//BNO055��ʼ������
    
    USART_SendData(USART1, BNO055_Init_Result);         //�򴮿�1��������
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
  }
}
/** NO.0005
   *������BNO055���ݶ�ȡ����
   */
void Sensor_BNO055_READ(u8 addr,u8 length)
{
	BNO055_READ(addr,length);
}
/** NO.0006
   *������BNO055����д�뺯��
   */
void Sensor_BNO055_Write(u8 addr,u8 data)
{
	BNO055_WRITE(addr,data);
}

/** NO.0007
   *������BNO055���ݽ�������
   */
u8 Sensor_BNO055_Response_Analysis(u8 *Res_data,u8 bit_num)//���ݰ��׵�ַ �ڼ�λ����  ����
{
   BNO055_Response_Analysis(Res_data,bit_num);//���ݰ��׵�ַ �ڼ�λ����  ����
}

/** NO.0008
   *������BNO055��ȡŷ��������(ֱ�ӵ���yaw��roll��pitch)
   */
void Euler_Angle_Read(void)
{
   BNO055_Euler_Angle_Read(BNO055_Response);
}

/** NO.0009
   *�ƽ����˿ڳ�ʼ��
   */
void TJQ_Init(void)
{
//�������ų�ʼ��  
  T_DIR_Init();
//�ٶ����ų�ʼ��  
  TIM3_PWM_Init(100-1,45-1);	//90M/90=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz
  TIM8_PWM_Init(100-1,45-1);  
//�������ų�ʼ��  
  TIM4_Cap_Init(65536-1,90-1);   //��1Mhz��Ƶ�ʼ���
  TIM5_Cap_Init(0XFFFFFFFF,90-1);//��1Mhz��Ƶ�ʼ���
//��ʱ����ʼ��  
  TIM7_Int_Init(5000-1,9000-1);	//��ʱ��ʱ��90M����Ƶϵ��9000������90M/9000=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms   
}
/** NO.0010
   *�ƽ�������       ������3   ���     �ٶ�     ����
   *������Χ         ��        1-8     0-499    0-1
   */
void TJQ_Control(u8 t_num,u16 t_speed,u8 t_dir)
{
  Propeller_Set(t_num,t_speed,t_dir);
}
/** NO.0011
   *�ƽ�������       ������1   ���         
   *������Χ         ��        1-8       
   */
u16 TJQ_RateFB_Read(u8 t_num)
{
  return TJQ_FB_Read(t_num);
}
/** NO.0012
   *�ƽ����ٶȿ���   ������3   ���     ת��     ����
   *������Χ         ��        1-8     0-5000    0-1
   */
void TJQ_Speed_Control(u8 t_num,u16 target_v,u8 t_dir)
{
   Propeller_Set(t_num,PWM_Calculate(target_v,TJQ_RateFB_Read(t_num)),t_dir);
}
/** NO.0013
   *�������˿ڳ�ʼ��
   */
void Buzzer_Init(void)
{
   BEEP_Init();
}
/** NO.0014
   *��������
   */
void Buzzer_Ring(void)
{
   BEEP=1;
}
/** NO.0015
   *����������
   */
void Buzzer_No_Ring(void)
{
   BEEP=0;
}
/** NO.0016
   *�ƹⱨ����ʼ��   
   */
void Visual_Alarm_Light_Init(void)
{
  RGB_LED_Init();
}
/** NO.0017
   *�ƹⱨ������     ������3   �̹�     ���    ����
   *������Χ         ��        0~255    0~255   0~255
   */
void Visual_Alarm_Light(u8 green,u8 red,u8 blue)
{
	RGB_LED_Write_24Bits(green,red,blue);
}
//������ɫ�趨��������ɫ�Դ�����
/** NO.0018
   *�ƹⱨ�����
   */
void RGB_LED_Red(void)//���
{ 
	RGB_LED_Write_24Bits(0, 0xff, 0);
}
/** NO.0019
   *�ƹⱨ���̹�
   */
void RGB_LED_Green(void)//�̹�
{
	RGB_LED_Write_24Bits(0xff, 0, 0);
}
/** NO.0020
   *�ƹⱨ������
   */
void RGB_LED_Blue(void)//����
{
	RGB_LED_Write_24Bits(0, 0, 0xff);
}
/** NO.0021
   *�ƹⱨ��Ϩ��
   */
void RGB_LED_Off(void)//Ϩ��
{
	RGB_LED_Write_24Bits(0, 0, 0);
}
/** NO.0022
   *��ص�ѹ��ȡ��ʼ��            
   */
void Bat_Vol_Det_Init(void)
{
   Adc_Init();
}
/** NO.0023
   *��ص�ѹ���ݶ�ȡ             
   */
float Battery_Voltage_Detection(void)
{
  return Get_Bat_Vol();
}
/** NO.0024
   *ң�ذ��������ж�   ������1   1~20 
   *����ֵ��1~16���� 1�����£� 0���ɿ�����17~20 ����ң����ֵ   
   */
/*
#define BT_UP            1
#define BT_DOWN          2
#define BT_LEFT          3
#define BT_RIGHT         4

#define BT_TRIANGLE      5
#define BT_CROSS         6
#define BT_SQUARE        7
#define BT_CIRCLE        8

#define BT_L1            9
#define BT_L2            10
#define BT_R1            11
#define BT_R2            12
#define BT_L3            13
#define BT_R3            14

#define BT_SELECT        15
#define BT_START         16

#define BT_LX            17
#define BT_LY            18
#define BT_RX            19
#define BT_RY            20

*/
u8 Remote_Control(u8 button)
{
  return Remote_Control_Button(button);
}
/** NO.0025
   *��Ƭ����USB HUBͨѶ�˿ڳ�ʼ��             
   */
void SCC_TO_HUB_Init(u32 bound)
{
	uart8_init(bound);          
}
/************************************************************************/
/*********************************��չ��*********************************/
/**�û��ɸ����ṩ�ĺ�������Ӧ�ã�Ҳ�ɸ����Լ�����������������
 *
 *
 */

/** NO.1001
   *�����սӿڳ�ʼ��             
   */

void Buoyancy_Init(u8 type)//�¾ɰ汾ѡ��
{
  switch(type)
  {
    case GPIO_Ver:
    {
      Buoyancy_GPIO_Init();
      break;
    }
    case UART_Ver:
    {
      //������
      break;
    }   
    default:break;
  }
}
/** NO.1002
   *������״̬����             
   */  
void Buoyancy_Control(u8 state)
{
  Buoyancy_GPIO_Control(state);
}  
/** NO.1003
   *����Ƕ�����             
   */
void Servo_Set(u8 port,u8 angle)
{
  Servo_Analysis(port,angle);
}
/** NO.1004
   *�ⲿ�ж϶�����ʼ��     ������1   port             
   *������Χ              ��        Sensor_1~Sensor_11(1~11)      
   */
void Exti_Port_Init(u8 port)
{
   EXTIX_Indepent_Init(port);
}
/** NO.1005
	 * ���������       :�ֽ�4 ���⴫����״̬����⵽��״̬Ϊ0
	 * �ֽ�λ          :  bit15   bit14   bit13   bit12   bit11   bit10   bit9   bit8   bit7   bit6   bit5   bit4   bit3   bit2   bit1   bit0    
	 * <�ӿ�>
	 *      S1        :   -       -       -       -       -       0       0      0      0      0      0      0      0      0      0      1     
	 *      S2        :   -       -       -       -       -       0       0      0      0      0      0      0      0      0      1      0
	 *      S3        :   -       -       -       -       -       0       0      0      0      0      0      0      0      1      0      0
	 *      S4        :   -       -       -       -       -       0       0      0      0      0      0      0      1      0      0      0
	 *      S5        :   -       -       -       -       -       0       0      0      0      0      0      1      0      0      0      0
	 *      S6        :   -       -       -       -       -       0       0      0      0      0      1      0      0      0      0      0     
	 *      S7        :   -       -       -       -       -       0       0      0      0      1      0      0      0      0      0      0
	 *      S8        :   -       -       -       -       -       0       0      0      1      0      0      0      0      0      0      0
	 *      S9        :   -       -       -       -       -       0       0      1      0      0      0      0      0      0      0      0
	 *      S10       :   -       -       -       -       -       0       1      0      0      0      0      0      0      0      0      0
	 *      S11       :   -       -       -       -       -       1       0      0      0      0      0      0      0      0      0      0
	 */

u8 Sensor_State_Analysis(u8 Sensor_num)
{
	u8 turn_place=0;
  u8 Sensor_State_Check=0;    
  u16 Sensor_State_analy=0;
	
	turn_place=Sensor_num-1;
  Sensor_State_analy=Sensor_State_All&(0x0001<<turn_place);
	Sensor_State_analy=Sensor_State_analy>>turn_place;
  Sensor_State_Check=(u8)Sensor_State_analy;
  return Sensor_State_Check;
}
/** NO.1006
   *��ȴ�������ʼ��
   */
void Sensor_HP20X_Init(void)
{
  HP20X_GPIO_Init();
	HP20X_Init();
}
/** NO.1007
   *��ȴ�����������ݶ�ȡ
   */
float Sensor_HP20X_GetDepth(void)
{
    float Depth_Value;
    Depth_Value=HP20X_getDepth();
		return Depth_Value;
}
/** NO.1008
   *̽�յ����Ե����ʼ��      ������2   sl1      sl2    
   *������Χ                  ��        0~1      0~1   
   */
void Searchlight_Init(u8 sl1,u8 sl2)
{
	if(sl1==1)
	{
		Dac1_Init();//̽�յƽӿ�1��ʼ��
	}
	if(sl2==1)
	{
		Dac2_Init();//̽�յƽӿ�2��ʼ�� 
	}
}
/** NO.1009
   *̽�յ����Ե�������      ������1   vol             
   *������Χ                ��        300~2800        
   */
void Searchlight_1_Set(u16 vol)
{	
	if(vol>2800)
	{
	  vol=2800;
	}
	Dac1_Set_Vol(vol);
}
/** NO.1010
   *̽�յ����Ե�������      ������1   vol             
   *������Χ               ��        300~2800      
   */
void Searchlight_2_Set(u16 vol)
{	
	if(vol>2800)
	{
	  vol=2800;
	}
	Dac2_Set_Vol(vol);
}
/************************************************************************/

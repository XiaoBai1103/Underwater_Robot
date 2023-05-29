#ifndef __API_H
#define __API_H
#include "sys.h"


#define GPIO_Ver     1
#define UART_Ver     2

void Internal_System_Init(void);//ϵͳ�ڲ���ʼ��

void WM_433M_Init(u32 bound);//433Mģ��˿ڳ�ʼ������
void WM_433M_SET(char *AT);//433Mģ��Ƶ�����ú���

void Sensor_BNO055_Init(u32 bound,u8 mode);//������BNO055�˿ڳ�ʼ������
void Sensor_BNO055_READ(u8 addr,u8 length);//������BNO055���ݶ�ȡ����
void Sensor_BNO055_Write(u8 addr,u8 data);//������BNO055����д�뺯��
u8 Sensor_BNO055_Response_Analysis(u8 *Res_data,u8 bit_num);//���ݰ��׵�ַ �ڼ�λ����  ����
void Euler_Angle_Read(void);//������BNO055��ȡŷ��������(ֱ�ӵ���yaw��roll��pitch)


void TJQ_Init(void);//�ƽ����˿ڳ�ʼ��
void TJQ_Control(u8 t_num,u16 t_speed,u8 t_dir);//�ƽ������ƺ���
u16 TJQ_RateFB_Read(u8 t_num);//�ƽ������ٺ��� ������
void TJQ_Speed_Control(u8 t_num,u16 target_v,u8 t_dir);


void Buzzer_Init(void);//�������˿ڳ�ʼ��

u8 Sensor_State_Analysis(u8 Sensor_num);//���нӿ�״̬��������

//void RGB_Init(void);
//void RGB_Set(u8 R_color,u8 G_color,u8 B_color);
void Visual_Alarm_Light_Init(void);//�ƹⱨ����ʼ��              
void Visual_Alarm_Light(u8 green,u8 red,u8 blue);//�ƹⱨ��ģ����ɫ���ã���ɫ����ɫ����ɫ��0~255/0x00~0xff            
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);//�ƹⱨ����ʾ��ɫ  
void RGB_LED_Off(void);//�ƹⱨ��Ϩ��

void Sensor_HP20X_Init(void);//��ȴ�������ʼ��
float Sensor_HP20X_GetDepth(void);//��ȴ�����������ݶ�ȡ

void Searchlight_Init(u8 sl1,u8 sl2);//̽�յ����Ե����ʼ��
void Searchlight_1_Set(u16 vol);//̽�յ����Ե�������
void Searchlight_2_Set(u16 vol);//̽�յ����Ե�������

void Internal_Temp_And_Humi_Init(void);//�ڲ���ʪ�ȴ�������ʼ��
u8 Internal_Temp_Read(void);//�ڲ���ʪ�ȴ������¶����ݶ�ȡ             
u8 Internal_Humi_Read(void);//�ڲ���ʪ�ȴ�����ʪ�����ݶ�ȡ 

void Bat_Vol_Det_Init(void);//��ص�ѹ����ʼ��
float Battery_Voltage_Detection(void);

u8 Remote_Control(u8 button);//ң�ذ��������ж�

void SCC_TO_HUB_Init(u32 bound);


void Servo_Set(u8 port,u8 angle);

void Exti_Port_Init(u8 port);
void Exti_SET(u8 state);
u8 Sensor_State_Analysis(u8 Sensor_num);
              
#endif

#include "bno055.h" 
#include "usart.h"	
#include "delay.h"
#include "stdio.h"

u8 BNO055_Read_Command[4]= {BNO055_Start_Byte,BNO055_Read_Order,0x00,0x01};//��ʼλ ��ȡ ��ַ ����
u8 BNO055_Write_Command[5]={BNO055_Start_Byte,BNO055_Write_Order,0x00,0x01,0x00};//��ʼλ д�� ��ַ ���� ����
u8 BNO055_Response[8];//0xBB length data1 data2 data3 data4 data5 data6 
u8 Receive_Buffer[8];

static u8 count_n=0;
static u8 state_res=0;
static u8 data_recevie_ok=0;//���ݽ�����ɱ�־λ


u8 id=0;
  /* Init(set mode) */
u8 BNO055_Init(u8 mode)
{ 
  BNO055_WRITE(BNO055_OPR_MODE_ADDR,OPERATION_MODE_CONFIG);
  delay_ms(10);
  
  BNO055_READ(BNO055_CHIP_ID_ADDR,0x01);
  delay_ms(100); 
  
  id = BNO055_Response_Analysis(BNO055_Response,0x03);
//  USART_SendData(USART1, id);         //�򴮿�1��������
//  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
  if(id != BNO055_ID)
  {
     // hold on for boot
    BNO055_READ(BNO055_CHIP_ID_ADDR,0x01);
    delay_ms(100);
    id = BNO055_Response_Analysis(BNO055_Response,0x03);
    if(id != BNO055_ID) 
    {
      return Init_Failure;  // still not? ok bail
    }
  }
  /* Switch to config mode (just in case since this is the default) */
  BNO055_WRITE(BNO055_OPR_MODE_ADDR,OPERATION_MODE_CONFIG);
  delay_ms(20);
  /* Reset */
  BNO055_WRITE(BNO055_SYS_TRIGGER_ADDR,0x20);
  delay_ms(1000);
  BNO055_READ(BNO055_CHIP_ID_ADDR,0x01);
  delay_ms(100);
  id = BNO055_Response_Analysis(BNO055_Response,0x03);
  
//  USART_SendData(USART1, id);         //�򴮿�1��������
//  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
    if(id != BNO055_ID)
  {
     // hold on for boot
    BNO055_READ(BNO055_CHIP_ID_ADDR,0x01);
    delay_ms(100);
    id = BNO055_Response_Analysis(BNO055_Response,0x03);
    if(id != BNO055_ID) 
    {
      return Init_Failure;  // still not? ok bail
    }
  }  
//  delay_ms(50);
  /* Set to normal power mode */
  BNO055_WRITE(BNO055_PWR_MODE_ADDR,POWER_MODE_NORMAL);
  delay_ms(10);
  BNO055_WRITE(BNO055_PAGE_ID_ADDR,0x00);
  delay_ms(10);
  BNO055_WRITE(BNO055_SYS_TRIGGER_ADDR,0x00);
  delay_ms(10);
  /* Set the requested operating mode (see section 3.3) */
  BNO055_WRITE(BNO055_OPR_MODE_ADDR,mode);
  delay_ms(20);
//  printf("BNO055 Successful Set !");
  return Init_Successful;
}

//��BNO055�Ĵ���д��һ������
void BNO055_WRITE(u8 addr,u8 data)
{
  u8 num;
  
//  BNO055_Write_Command[0]=BNO055_Start_Byte;    //��ʼλ
//  BNO055_Write_Command[1]=BNO055_Write_Order;   //дָ��
  BNO055_Write_Command[2]=addr;   //��ַ
//  BNO055_Write_Command[3]=0x01;   //���ݳ���
  BNO055_Write_Command[4]=data;   //����
  if(BNO055_Write_Command[0]==BNO055_Start_Byte)
  {
    for(num=0;num<5;num++)
    {
       USART_SendData(UART5, BNO055_Write_Command[num]);         //�򴮿�5��������
       while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET){};   //�ȴ����ͽ���
    }     
  }
}  
//��BNO055�Ĵ�����ȡ����
void BNO055_READ(u8 addr,u8 length)
{
  u8 num=0;
  
//  BNO055_Read_Command[0]=BNO055_Start_Byte;    //��ʼλ
//  BNO055_Read_Command[1]=BNO055_Read_Order;    //��ָ��
  BNO055_Read_Command[2]=addr;    //��ַ
  BNO055_Read_Command[3]=length;  //���ݳ���
  if(BNO055_Read_Command[0]==BNO055_Start_Byte)
  {
    for(num=0;num<4;num++)
    {
      USART_SendData(UART5, BNO055_Read_Command[num]);         //�򴮿�1��������
      while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET){};  //�ȴ����ͽ���
    }    
  }  
}  


//BNO055�������ݽ��պ���
void BNO055_Response_Receive(u8 Rec_data)
{
  if(data_recevie_ok==0)   //�ж������Ƿ��ѱ���ȡ
  {
     Receive_Buffer[count_n]=Rec_data;
     count_n++;
     if(state_res==0)
     {
       if( Receive_Buffer[0]==Read_Success_Res_Byte||BNO055_Response[0]==Ack_Res_Header)   //�ж�Ӧ����ʼλ�Ƿ���ȷ
       {
         state_res=1;
       }
       else
       {
          Receive_Buffer[0]=0;                                                             //
          count_n=0;
       }
     }
     else if(state_res==1)
     {
       if(Receive_Buffer[0]==Ack_Res_Header&&count_n==8)
       {
          data_recevie_ok=1;    
          state_res=0;
          count_n=0;
       }
       else if((Receive_Buffer[1]+2)==count_n) //����  ����λ+����λ
       {
          data_recevie_ok=1;    
          state_res=0;
          count_n=0;
       }      
      }  

  }
    if(data_recevie_ok==1)                                   //�жϽ�����ɱ�־
  {
     for(id=0;id<8;id++)
    {
      
      BNO055_Response[id]=Receive_Buffer[id];
//      USART_SendData(USART1, BNO055_Response[id]);         //�򴮿�1��������
//      while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
    }
  }
}


/************************BNO055�������ݽ�������**********************************/
u8 BNO055_Response_Analysis(u8 *Res_data,u8 bit_num)//���ݰ��׵�ַ �ڼ�λ����  ����
{
  if(data_recevie_ok==1)                                   //�жϽ�����ɱ�־
  {
//     for(id=0;id<8;id++)
//    {
//      
//      BNO055_Response[id]=Receive_Buffer[id];
//      USART_SendData(USART1, BNO055_Response[id]);         //�򴮿�1��������
//      while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
//    }
    
     data_recevie_ok=0;                                    //���������ɱ�־
     if(*Res_data==Read_Success_Res_Byte)
     {
       Res_data=Res_data+bit_num-1;
       return *Res_data;
     }
     else if(*Res_data==Ack_Res_Header)                     //дӦ��/������Ӧ��
     {       
       Res_data++;
       return *Res_data;
     }
     else   return WRONG_START_BYTE;              //������ʼλ
  }
  else return Receive_Outstanding;                   //����δ���
}

u16 yaw=0;
int roll=0;
int pitch=0;

u8 BNO055_Euler_Angle_Read(u8 *Res_data)
{
	BNO055_READ(BNO055_EULER_H_LSB_ADDR,0x06);
	delay_ms(10);
	 
	if(data_recevie_ok==1)                                   //�жϽ�����ɱ�־
  {
     data_recevie_ok=0;                                    //���������ɱ�־
     if(*Res_data==Read_Success_Res_Byte)
     {
			 Res_data+=2;
       yaw=((*(Res_data+1))<<8)|(*Res_data);
			 if(*(Res_data+3)>0x05)
			 {
					roll=((*(Res_data+3))<<8)|(*(Res_data+2));
				  roll-=0xFFFF;
			 }
			 else 
			 {
					roll=((*(Res_data+3))<<8)|(*(Res_data+2));//��� 0 - 90 - 0  0x0000-0x05A0-0x0000,�Ҳ� 0 - -90 - 0  0xFFFF-0xFA5F-0xFFFF
			 }
			 if(*(Res_data+5)>0xB0)
			 {
				  pitch=((*(Res_data+5))<<8)|(*(Res_data+4));
				  pitch-=0xFFFF;
			 }
			 else
			 {
					pitch=((*(Res_data+5))<<8)|(*(Res_data+4));//0-180�� ��Ӧ0x0000-0x0B40  0--180�� ��Ӧ0x0000-0xF4BF
			 }
					 
			 yaw=yaw/LSBTODegree;	
			 roll=roll/LSBTODegree;
			 pitch=pitch/LSBTODegree;
			 
			 
				if(yaw>180)
				{
					yaw=yaw-180;
				}
				else
				{
					yaw=yaw+180;
				}
				roll=0-roll;
				if(pitch>0)
				{
					pitch=180-pitch;
				}
				else
				{
					pitch=-180-pitch;
				}
			 
			 
       return 0;
     }
     else   return 1;              //������ʼλ
  }
  else return 1;                   //����δ���
}	








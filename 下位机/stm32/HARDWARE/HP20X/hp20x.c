#include "hp20x.h"
#include "delay.h"



/**************************************************
**************************************************/
char F_VarIT_I2cAck;
unsigned long PressBuf;
long AltitudeBuf;
long TemperatureBuf;

float SensorData_P;
float SensorData_T;
float SensorData_A;
float __SENSOR_P__;


unsigned char Read_TPH;

//��ȡ�������
float HP20X_getDepth(void)
{
//  Hp20x_ReadPressureAndTemperature();
  Hp20x_ReadPressure();
  return ((SensorData_P - __SENSOR_P__) * 100) / 9.8;
}

//��ȴ�������ȡ
void HP20X_READ(void)
{
  switch(Read_TPH)   //�ж�ģʽ��־λ��ֵ.
  {
    case 0:
      Hp20x_ReadPressureAndTemperature();	//read temp/press/alt
      Hp20x_ReadAltitude();
      break;
    case 1:
      Hp20x_ReadPressure();     //only read press
      break;
    case 2:
      Hp20x_ReadTemperature();     //only read temp
      break;
    case 3:
      Hp20x_ReadAlt();     //only read alt
      break;
    default:break;
  }
}
//��ȴ������˿ڳ�ʼ��
void HP20X_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  HP20X_GPIO_CLOCK_Init() ;

  //GPIOE10,E11��ʼ������
  GPIO_InitStructure.GPIO_Pin = HP20X_SCL_PIN | HP20X_SDA_PIN;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(HP20X_I2C_PORT, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_SetBits(HP20X_I2C_PORT,HP20X_SCL_PIN | HP20X_SDA_PIN);//GPIOE10,E11���ø�
 
}
//��ȴ�������ʼ��
void HP20X_Init(void)
{
  HP20X_GPIO_Init();
  
  Hp20X_WriteCmd(0x06);
	delay_ms(100);			//delay 100ms
  Hp20x_ReadPressure();
  Hp20x_ReadPressure();
  __SENSOR_P__=SensorData_P;
  
}

/*******************************************************************
---Function Description: 
*******************************************************************/
//��ȴ�������ȡѹ��ֵ
void Hp20x_ReadPressure(void)
{
	unsigned long temp_Buf;
	
	Hp20X_WriteCmd(0x40|0x08);				//������ 1024
	delay_ms(40);				//delay 40ms����

	//Hp20X_WriteCmd(0x40|0x00);				//������ 4096
	//delay_ms(140);				//delay 140ms

	Hp20X_WriteCmd(0x30);
	I2c_Start();
	I2c_WriteByte(0xed);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}
	
	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(0);
	I2c_Stop();
	PressBuf = temp_Buf;
  SensorData_P=PressBuf/100.0;
}

/*******************************************************************
---Function Description: 
*******************************************************************/
//��ȴ�������ȡ�¶�ֵ
void Hp20x_ReadTemperature(void)
{
	unsigned long temp_Buf;
	
	Hp20X_WriteCmd(0x40|0x08);				//������ 1024
	delay_ms(20);				//delay 20ms����

	//Hp20X_WriteCmd(0x40|0x00);				//������ 4096
	//delay_ms(70);				//delay 70ms

	Hp20X_WriteCmd(0x32);
	I2c_Start();
	I2c_WriteByte(0xed);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}
	
	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(0);
	I2c_Stop();
	if(temp_Buf & 0x800000)
		temp_Buf |= 0xff000000;

	TemperatureBuf = temp_Buf;
  SensorData_T=TemperatureBuf/100.0;
}

/*******************************************************************
---Function Description: 
*******************************************************************/
//��ȴ�������ȡ�߶�����
void Hp20x_ReadAlt(void)
{
	unsigned long temp_Buf;
	
	Hp20X_WriteCmd(0x40|0x08);				//������ 1024
	delay_ms(40);				//delay 40ms����

	//Hp20X_WriteCmd(0x40|0x00);				//������ 4096
	//delay_ms(140);				//delay 140ms

	Hp20X_WriteCmd(0x31);
	I2c_Start();
	I2c_WriteByte(0xed);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}

	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(0);
	I2c_Stop();
	if(temp_Buf & 0x800000)
		temp_Buf |= 0xff000000;

	AltitudeBuf = temp_Buf;
  SensorData_A=AltitudeBuf/100.0;
}

/*******************************************************************
---Function Description:  hp20x write command
*******************************************************************/
//��ȴ���������¶���ֵ
void Hp20x_ReadPressureAndTemperature(void)
{
	unsigned long temp_Buf;
	
	Hp20X_WriteCmd(0x40|0x08);				//������ 1024
	delay_ms(40);				//delay 40ms����

	//Hp20X_WriteCmd(0x40|0x00);				//������ 4096
	//delay_ms(140);				//delay 140ms

	Hp20X_WriteCmd(0x10);
	I2c_Start();
	I2c_WriteByte(0xed);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}

	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	if(temp_Buf & 0x800000)
		temp_Buf |= 0xff000000;

	TemperatureBuf = temp_Buf;
  SensorData_T=TemperatureBuf/100.0;
	
	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(0);
	I2c_Stop();
	PressBuf = temp_Buf;
  SensorData_P=PressBuf/100.0;
}

/*******************************************************************
---Function Description:  hp20x write command
*******************************************************************/
void Hp20x_ReadAltitude(void)
{
	unsigned long temp_Buf;

	Hp20X_WriteCmd(0x31);
	I2c_Start();
	I2c_WriteByte(0xed);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}

	temp_Buf = I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(1);
	temp_Buf <<= 8;
	temp_Buf |= I2c_ReadByte(0);
	I2c_Stop();
	if(temp_Buf & 0x800000)
		temp_Buf |= 0xff000000;

	AltitudeBuf = temp_Buf;
}

/*******************************************************************
---Function Description:  hp20x write command
*******************************************************************/
void Hp20X_WriteCmd(unsigned char uCmd)
{
	I2c_Start();
	I2c_WriteByte(0xec);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}
	I2c_WriteByte(uCmd);
	if(F_VarIT_I2cAck==0) {I2c_Error();return;}
	I2c_Stop();
}

/*******************************************************************
---Function Description:  write i2c data	����:0ʧ��,��0����
*******************************************************************/
void I2c_WriteByte(unsigned char databuf)
{
	unsigned char i;

   delay_us(2);       // ��ֹ��оƬ�����ͻ
//	PB_DDR |= 0x04;		//SDA��Ϊ���ģʽ
  HP20X_SDA_OUT();
	for(i=0;i<8;i++)
	{
		if(databuf&0x80)
		{
			SDA_OUT = 1;
			delay_us(19);
		}
		else
		{
			SDA_OUT = 0;
			delay_us(18);
		}
		SCL_OUT = 1;
		databuf <<= 1;
		delay_us(20);
		SCL_OUT = 0;
	}
	delay_us(2);       // ��ֹ��оƬ�����ͻ
//	PB_DDR &= 0xfb;		//SDA��Ϊ����ģʽ
  HP20X_SDA_IN();
	delay_us(19);
	F_VarIT_I2cAck = 0;
	SCL_OUT = 1;			//ACK����
	//-------------------------------------
	for(i=0;i<20;i++)			//��ʱ
 	{
		if(!SDA_IN) {F_VarIT_I2cAck = 1; break;}	//������Ӧ��
 	}
 	//-------------------------------------
 	delay_us(19);
	SCL_OUT = 0;
	delay_us(2);       // ��ֹ��оƬ�����ͻ
//	PB_DDR |= 0x04;		//SDA��Ϊ���ģʽ
  HP20X_SDA_OUT();
	SDA_OUT = 1;
}

/*******************************************************************
---Function Description:  read i2c data	0���1�ֽ� ��0Ϊ�����1�ֽ�
*******************************************************************/
unsigned char I2c_ReadByte(unsigned char endbyte)
{
	unsigned char xx;
	unsigned char i;

	delay_us(10);
//	PB_DDR &= 0xfb;		//SDA��Ϊ����ģʽ
  HP20X_SDA_IN();
	delay_us(10);
	for(i=0;i<8;i++)
	{
		xx = xx << 1;
		SCL_OUT = 1;
		delay_us(19);
		if(SDA_IN)
			xx |= 0x01;
		else
			;
		SCL_OUT = 0;
		delay_us(20);

	}

	delay_us(2);       // ��ֹ��оƬ�����ͻ
//	PB_DDR |= 0x04;	  //SDA��Ϊ���ģʽ
	HP20X_SDA_OUT();
	if(endbyte != 0)
 		I2c_Ack();
 	else
  		I2c_NoAck();
	return xx;
}

/*******************************************************************
---Function Description:  Start I2c bus signal program
*******************************************************************/
void I2c_Start(void)
{
	SDA_OUT = 1;
	delay_us(20);
	SCL_OUT = 1;			//������ʼ�����������ź�	
	delay_us(20);
	SDA_OUT = 0;
	delay_us(20);
	SCL_OUT = 0;
	delay_us(18);
}

/*******************************************************************
---Function Description:  stop I2c bus signal program
*******************************************************************/
void I2c_Stop(void)
{
	SCL_OUT = 0;			//���ͽ��������������ź� 
	delay_us(20);
	SDA_OUT = 0;			//���ͽ��������������ź� 
	delay_us(20);
	SCL_OUT = 1;
	delay_us(20);
	SDA_OUT = 1;
	delay_us(18);
}

/*******************************************************************
---Function Description:  error I2c bus signal program
*******************************************************************/
void I2c_Error(void)
{
	SDA_OUT = 0;
	delay_us(20);
	SCL_OUT = 1;			//������ʼ�����������ź�	
	delay_us(20);
	SDA_OUT = 1;
	delay_us(18);
}

/*******************************************************************
---Function Description:  Write check ack I2c bus signal program
*******************************************************************/
void I2c_Ack(void)
{
	delay_us(2);   // ��ֹ��оƬ�����ͻ
	SDA_OUT = 0;
	delay_us(20);
	SCL_OUT = 1;
	delay_us(20);
	SCL_OUT = 0;
	delay_us(20);
}

/*******************************************************************
---Function Description:  Read Ack I2c bus signal program  
---	�ȴ�slave��ack�ظ�
---	�ڶ�����ʱ��ack���ظ�
*******************************************************************/
void I2c_NoAck(void)
{
	SDA_OUT = 1;
	delay_us(20);
	SCL_OUT = 1;
	delay_us(20);
	SCL_OUT = 0;
	delay_us(20);
}



#include "buoyancy.h" 
 

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void Buoyancy_GPIO_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��

  //GPIOD8,D9,D10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	
  //GPIO_SetBits(GPIOD,GPIO_Pin_10);//�ߵ�ƽ
	GPIO_WriteBit(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10,Bit_RESET);//�͵�ƽ
}
//GPIO9Ϊʹ���źţ���ʼֵΪLOW,GPIO9==HIGHʱ������������

void Buoyancy_GPIO_Control(u8 state)
{
  switch(state)
  {
    case Hold://����������
    {
      GPIO_SetBits(GPIOD,GPIO_Pin_9);//high
      GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
      break;
    }
    case Come_up://������++
    {
			GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9);//high
      break;
    }
    case Dive://��Ǳ״̬
    {
       GPIO_SetBits(GPIOD,GPIO_Pin_9);
      break;
    }
		/*case Shangfu:
		{
			
		}*/
    default:break;
  }
}


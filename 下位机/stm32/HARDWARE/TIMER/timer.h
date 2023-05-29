#ifndef __TIMER_H
#define __TIMER_H	 
#include "sys.h"

extern u16 T1_Speed;
extern u16 T2_Speed;
extern u16 T3_Speed;
extern u16 T4_Speed;
extern u16 T5_Speed;
extern u16 T6_Speed;
extern u16 T7_Speed;
extern u16 T8_Speed;


//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM5_Cap_Init(u32 arr,u16 psc);
//��ʱ��4ͨ��1-4���벶������
//arr���Զ���װֵ(TIM4��16λ��)
//psc��ʱ��Ԥ��Ƶ��
void TIM4_Cap_Init(u16 arr,u16 psc);

void TIM7_Int_Init(u16 arr,u16 psc);

u16 TJQ_FB_Read(u8 t_num);
#endif



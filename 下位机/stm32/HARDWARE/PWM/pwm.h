#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
	

void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM8_PWM_Init(u32 arr,u32 psc);

void TIM1_PWM_Init(u8 s4,u8 s5,u8 s6,u8 s10);//����ִ��4������ִ��5������ִ��6������ִ��10
void TIM9_PWM_Init(u8 s3,u8 s7);//����ִ��3������ִ��7
void TIM11_PWM_Init(u8 s1);//����ִ��1
void TIM2_PWM_Init(u8 s11);//����ִ��11
void TIM4_PWM_Init(u8 s2);//����ִ��2

#endif

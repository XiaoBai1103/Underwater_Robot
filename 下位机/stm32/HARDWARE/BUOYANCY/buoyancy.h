#ifndef _BUOYANCY_H
#define _BUOYANCY_H
#include "sys.h"

#define Vent_Valve     PDout(10) //������
#define Vacuum_Pump    PDout(9)  //��ձ�
#define Inlet_Valve    PDout(8)  //������

#define Hold           0         //����״̬
#define Come_up        1         //�ϸ�״̬
#define Dive           2         //��Ǳ״̬

void Buoyancy_GPIO_Init(void);
void Buoyancy_GPIO_Control(u8 state);
#endif

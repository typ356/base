#ifndef __pit_H
#define __pit_H
#include "includes.h"


extern u32 haomiao_xitong;
extern u32 haomiao_xitong_old;
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//Tclk=72000000��  72����΢��
//����ʹ�õ��Ƕ�ʱ��6!
void TIM4_Init(u16 arr,u16 psc);//Tout�����ʱ�䣩=��ARR+1)(PSC+1)/Tclk 
 
#endif

#include "led.h"


void LED_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);	 //ʹ��PC�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//LED--PC13
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC0-7
	 GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //GPIOC0-7 �����


	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);	 //ʹ��PC�˿�ʱ��

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC0-7
	 GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);	
}


#include "key.h"

s8 key=0;
								    
//������ʼ������
void Key_Scan_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//KEY1-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}

//������ʼ������
void Key_Exit_Init(void) //IO��ʼ��
{ 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

     Key_Scan_Init();


  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    //GPIOA.0 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	   //KEY1
  	EXTI_Init(&EXTI_InitStructure);	 	

   //GPIOA.1	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			  //ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

     NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			  //ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//-1��û���κΰ�������
//1��KEY1����
//2��KEY2����


//ע��˺�������Ӧ���ȼ�,WK_UP>KEY1>KEY2>KEY3
s8 KEY_Scan(u8 mode)
{	 
	static s8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)      return KEY1_PRES;
		else if(KEY2==0) return KEY2_PRES;
	}
     else if(KEY1==1&&KEY2==1)
          key_up=1; 	    
 	return -1;// �ް�������
}


//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
          haomiao_xitong_old=haomiao_xitong;
          while(haomiao_xitong-haomiao_xitong_old<10);//ȥ����
		if(KEY1==0)	 	
		{				 
			LED8=!LED8;	
		}
		EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
     }
}
 
//�ⲿ�ж�2�������
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{
          haomiao_xitong_old=haomiao_xitong;
          while(haomiao_xitong-haomiao_xitong_old<10);//ȥ����
		if(KEY2==0)	 
		{
			LED9=!LED9;
		}		 
		EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE1�ϵ��жϱ�־λ
     }  
}

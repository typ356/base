
#include "key.h"

s8 key=0;
								    
//按键初始化函数
void Key_Scan_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;//KEY1-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}

//按键初始化函数
void Key_Exit_Init(void) //IO初始化
{ 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

     Key_Scan_Init();


  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;

    //GPIOA.0 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	   //KEY1
  	EXTI_Init(&EXTI_InitStructure);	 	

   //GPIOA.1	  中断线以及中断初始化配置 下降沿触发 //KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			  //使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

     NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			  //使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;  //抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;		  //子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//-1，没有任何按键按下
//1，KEY1按下
//2，KEY2按下


//注意此函数有响应优先级,WK_UP>KEY1>KEY2>KEY3
s8 KEY_Scan(u8 mode)
{	 
	static s8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)      return KEY1_PRES;
		else if(KEY2==0) return KEY2_PRES;
	}
     else if(KEY1==1&&KEY2==1)
          key_up=1; 	    
 	return -1;// 无按键按下
}


//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
          haomiao_xitong_old=haomiao_xitong;
          while(haomiao_xitong-haomiao_xitong_old<10);//去抖动
		if(KEY1==0)	 	
		{				 
			LED8=!LED8;	
		}
		EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
     }
}
 
//外部中断2服务程序
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{
          haomiao_xitong_old=haomiao_xitong;
          while(haomiao_xitong-haomiao_xitong_old<10);//去抖动
		if(KEY2==0)	 
		{
			LED9=!LED9;
		}		 
		EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE1上的中断标志位
     }  
}

#ifndef __KEY_H
#define __KEY_H	 
#include "includes.h"

extern s8 key; 	 


#define KEY1 PAin(0)   	
#define KEY2 PAin(1)	



#define KEY1_PRES 	1	//KEY1按下
#define KEY2_PRES	2	//KEY2按下

void Key_Scan_Init(void);//IO初始化
void Key_Exit_Init(void);
s8 KEY_Scan(u8);  	//按键扫描函数					    
#endif

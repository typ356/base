#ifndef __KEY_H
#define __KEY_H	 
#include "includes.h"

extern s8 key; 	 


#define KEY1 PAin(0)   	
#define KEY2 PAin(1)	



#define KEY1_PRES 	1	//KEY1����
#define KEY2_PRES	2	//KEY2����

void Key_Scan_Init(void);//IO��ʼ��
void Key_Exit_Init(void);
s8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif

#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define    USART2_MAX_RECV_LEN		800			//�����ջ����ֽ���
#define    USART2_MAX_SEND_LEN		200			//����ͻ����ֽ���
extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern u16 USART2_RX_STA;         		               //����״̬���	


void USART2_Init(u32 bound,u8 chongyingshe);
#endif

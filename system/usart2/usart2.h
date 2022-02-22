#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define    USART2_MAX_RECV_LEN		800			//最大接收缓存字节数
#define    USART2_MAX_SEND_LEN		200			//最大发送缓存字节数
extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern u16 USART2_RX_STA;         		               //接收状态标记	


void USART2_Init(u32 bound,u8 chongyingshe);
#endif

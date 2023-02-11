#ifndef _usart2_H
#define _usart2_H

#include "system.h" 
#include "stdio.h" 


#define USART2_REC_LEN		256  	//定义最大接收字节数 200
#define BUFLEN 256      //数组缓存大小

typedef struct _UART_BUF
{
    char buf [USART2_REC_LEN+1];               
    unsigned int index ;
}UART_BUF;

extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;       

extern UART_BUF buf_uart2;     //NBIOT

void USART2_Init(u32 bound);
void UART2_send_byte(char data);
void Uart2_SendStr(char*SendBuf);

#endif



#ifndef _usart2_H
#define _usart2_H

#include "system.h" 
#include "stdio.h" 


#define USART2_REC_LEN		256  	//�����������ֽ��� 200
#define BUFLEN 256      //���黺���С

typedef struct _UART_BUF
{
    char buf [USART2_REC_LEN+1];               
    unsigned int index ;
}UART_BUF;

extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;       

extern UART_BUF buf_uart2;     //NBIOT

void USART2_Init(u32 bound);
void UART2_send_byte(char data);
void Uart2_SendStr(char*SendBuf);

#endif



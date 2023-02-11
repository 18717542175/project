#ifndef _usart_H
#define _usart_H

#include "system.h" 
#include "stdio.h" 
#include "usart2.h"
#include "string.h"
#include "SysTick.h"

#define USART1_REC_LEN		200  	//�����������ֽ��� 200

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���

extern UART_BUF buf_uart1;     //CH340   Lora

void USART1_Init(u32 bound);
void Uart1_SendStr(char*SendBuf);
void Clear_Buffer1(void);


#endif



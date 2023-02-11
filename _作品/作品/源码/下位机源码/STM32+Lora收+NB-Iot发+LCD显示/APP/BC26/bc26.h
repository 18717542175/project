#ifndef _BC26_H
#define _BC26_H

#include "system.h" 
#include "SysTick.h"
#include "usart2.h"
#include "string.h"
#include "usart.h"

void Clear_Buffer(void);//��ջ���	
int  BC26_Init(void);
void BC26_PDPACT(void);
void BC26_ConLWM2M(void);
void BC26_RECData(void);
void BC26_Senddata(int data);
typedef struct
{
   uint8_t CSQ;    
   uint8_t Socketnum;   //���
   uint8_t reclen[10];   //��ȡ�����ݵĳ���
   uint8_t res;      
   uint8_t recdatalen[10];
   uint8_t recdata[100];
} BC26;




#endif

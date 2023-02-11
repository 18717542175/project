#include "usart2.h"

//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记

UART_BUF buf_uart2;     //NBIOT

void UART2_send_byte(char data)
{
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, data);
}


void Uart2_SendStr(char*SendBuf)//串口2打印数据代码
{
    while(*SendBuf)
    {
        while((USART2->SR&0X40)==0)
        {
        }//等待发送完成
        USART2->DR = (u8) *SendBuf; 
        SendBuf++;
    }
}

void USART2_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOA,D时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOA,C时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //PD7端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//复位串口2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//停止复位
 
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据长度
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;///奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_Init(USART2, &USART_InitStructure); ; //初始化串口
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART2, ENABLE);                    //使能串口 
}



void nbiot_receive_process_event(unsigned char ch )     //串口2给nbiot用
{
    if(buf_uart2.index >= BUFLEN)
    {
        buf_uart2.index = 0 ;
    }
    else
    {
        buf_uart2.buf[buf_uart2.index++] = ch;
    }
}

void USART2_IRQHandler(void)                            //串口2接收函数
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)
    {
        nbiot_receive_process_event(USART_ReceiveData(USART2));
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }

    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
        nbiot_receive_process_event(USART_ReceiveData(USART2));
        USART_ClearFlag(USART2,USART_FLAG_ORE);
    }
}




#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "key.h"
#include "rs485.h"
#include "adc.h"
#include "ds18b20.h"
#include "pwm.h"
		/* 变量初始化 */
float vol;
float temp;
u16 value=0;
u8 i=0;
u8 len=0;
u8 j=0;
u8 rs485buf[8]={0x09,0x03,0x00,0x1E,0x00,0x03,0x64,0x85};
u16 N_value,P_value,K_value;
u8 rs485buf_RX[13];
//09 03 00 1e 00 03 64 85

u8 Target[10]={0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11};
void Data_Process(u8 Target[],u16 *N_value,u16 *P_value,u16 *K_value,float *temp,float *vol);
int main()
{
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	USART1_Init(9600);
	RS485_Init(9600);
	ADC1_Init();					//ADC 初始化	    PA1   土壤温度采集
	DS18B20_Init();				//DS18B20初始化  PB12  土壤温度采集
		/*****不要用CCR1------>>>>PB4******/
	TIM3_PWM_Init(1000-1,72-1);   //水泵PWM波初始化 1000Hz
	TIM3->CCR1=900;
	TIM3->CCR2=900;
	TIM3->CCR3=900;
	TIM3->CCR4=900;
	
	
	while(1)
	{	
		delay_ms(10);
		i++;
		value=Get_ADC_Value(ADC_Channel_1,20);
		temp=DS18B20_GetTemperture();
		vol=1-(float)value/4096;
		if(i%20==0)
		{
			RS485_Send_Data(rs485buf,8);
			delay_ms(10);
//			printf("土壤氮含量为: %d mg/kg\r\n",N_value);
//			printf("土壤磷含量为: %d mg/kg\r\n",P_value);
//			printf("土壤钾含量为: %d mg/kg\r\n",K_value);
//			printf("土壤湿度为: %.2f%%RH 温度为: %.1f C\r\n",100*vol,temp);
//			printf("水泵1功率为: %2d %%\r\n水泵2功率为: %2d %%\r\n水泵3功率为: %2d %%\r\n水泵4功率为: %2d %%\r\n",
//						(1000-TIM3->CCR1)/10,(1000-TIM3->CCR2)/10,(1000-TIM3->CCR4)/10,(1000-TIM4->CCR4)/10);
	//		printf("\r\n");
		}		
		RS485_Receive_Data(rs485buf_RX,&len);
		N_value=10000+rs485buf_RX[3]*256+rs485buf_RX[4];
		P_value=20000+rs485buf_RX[5]*256+rs485buf_RX[6];
		K_value=30000+rs485buf_RX[7]*256+rs485buf_RX[8];
		if(i%10==0){
			temp=4000+temp;
			vol=500+vol*100;
			Data_Process(Target,&N_value,&P_value,&K_value,&temp,&vol);
			printf("%s\r\n",Target);
		}		
		delay_ms(10);
	}
}


void Data_Process(u8 Target[],u16 *N_value,u16 *P_value,u16 *K_value,float *temp,float *vol)
{
	u8 i=0;
	Target[i++]=(u8)(*N_value/256);
	Target[i++]=(u8)(*N_value%256);
	Target[i++]=(u8)(*P_value/256);
	Target[i++]=(u8)(*P_value%256);
	Target[i++]=(u8)(*K_value/256);
	Target[i++]=(u8)(*K_value%256);
	
	Target[i++]=(u8)(*temp * 10/256);
	Target[i++]=(u8)((int)(*temp*10)%256);

	Target[i++]=(u8)(*vol * 100/256);
	Target[i++]=(u8)((int)(*vol*100)%256);
}




















#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "lora.h"
#include "usart2.h"
#include "bc26.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "stdlib.h"

u16 N_value,P_value,K_value,temp,vol;
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                            O\ = /O
//                        ____/`---'\____
//                      .   ' \\| |// `.
//                       / \\||| : |||// \
//                     / _||||| -:- |||||- \
//                       | | \\\ - /// | |
//                     | \_| ''\---/'' | |
//                      \ .-\__ `-` ___/-. /
//                   ___`. .' /--.--\ `. . __
//                ."" '< `.___\_<|>_/___.' >'"".
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |
//                 \ \ `-. \_ __\ /__ _/ .-` / /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//
//         .............................................
//                  佛祖镇楼                 BUG退避
/*******************数据发送*****************************
DATA：
	10000<=DATA<20000			10000+氮含量  eg：10371   1—氮代号   0371-371		mg/kg
	20000<=DATA<30000			20000+磷
	30000<=DATA<40000			30000+钾
	40000<=DATA<50000			40000+温度*10	  eg：40192   4—温度代号   192-19.2 度	
 	50000<=DATA						50000+湿度*100	eg：55678   5—湿度代号   5678-56.78 %RH

*********************************************************/
int main()
{
	u8 i=0; 
	int DATA;
//	u8 len;
	u8 buffer[12];
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	LED_Init();
	Lcd_Init();	
	LCD_LED_SET;//通过IO控制背光亮
  QDTFT_Test_Demo();
//	Gui_DrawFont_GBK16(10,0,BLUE,GRAY0,"西安科技大学");
	Gui_DrawFont_GBK16(0,30-16,BLUE,GRAY0,"氮含量:    mg/kg");
	Gui_DrawFont_GBK16(0,46-16,BLUE,GRAY0,"磷含量:    mg/kg");
	Gui_DrawFont_GBK16(0,62-16,BLUE,GRAY0,"钾含量:    mg/kg");
	Gui_DrawFont_GBK16(0,78-16,BLUE,GRAY0,"温度  :       度");
	Gui_DrawFont_GBK16(0,94-16,BLUE,GRAY0,"湿度  :      %RH");
	
//	Gui_DrawFont_GBK16(0,112-16,BLUE,GRAY0,"水泵功率:");
//	Gui_DrawFont_GBK16(0,128-16,BLUE,GRAY0,"氮泵功率:");
//	Gui_DrawFont_GBK16(0,144-16,BLUE,GRAY0,"磷泵功率:");
//	Gui_DrawFont_GBK16(0,160-16,BLUE,GRAY0,"钾泵功率:");

	
	
	USART1_Init(9600);
	USART2_Init(115200);
	printf("串口初始化完成\r\n");
	BC26_Init();
	BC26_PDPACT();
	BC26_ConLWM2M();
	
	while(1)
	{
		i++;
		if(i%50==0)
		{
			
//			len = rand()%256;
//			sprintf(buffer,"%4d",len);
//			Gui_DrawFont_GBK16(0,135,BLUE,GRAY0,buffer);
			
			N_value=buf_uart1.buf[0]*256+buf_uart1.buf[1];
			DATA=N_value;	
 // DATA=10000+len;
			if(DATA>10000){
				sprintf(buffer,"氮含量:%4dmg/kg",DATA-10000);
				Gui_DrawFont_GBK16(0,30-16,BLUE,GRAY0,buffer);			
				BC26_Senddata(DATA);			
			}

			
			P_value=buf_uart1.buf[2]*256+buf_uart1.buf[3];
		  DATA=P_value;			
 //	 DATA=20000+len;	
			if(DATA>20000){
				sprintf(buffer,"磷含量:%4dmg/kg",DATA-20000);
				Gui_DrawFont_GBK16(0,46-16,BLUE,GRAY0,buffer);		
				BC26_Senddata(DATA);			
			}
				
			
			K_value=buf_uart1.buf[4]*256+buf_uart1.buf[5];
			DATA=K_value;			
// DATA=30000+len;
			if(DATA>30000){
				sprintf(buffer,"钾含量:%4dmg/kg",DATA-30000);
				Gui_DrawFont_GBK16(0,62-16,BLUE,GRAY0,buffer);			
				BC26_Senddata(DATA);				
			}

			
			temp=buf_uart1.buf[6]*256+buf_uart1.buf[7];
			DATA=temp;		
//  DATA=40000+len;	
			if(DATA>40000){
				sprintf(buffer,"温度  :   %2.1f度",(float)(DATA-40000)/10);
				Gui_DrawFont_GBK16(0,78-16,BLUE,GRAY0,buffer);
				BC26_Senddata(DATA);			
			}


			vol=buf_uart1.buf[8]*256+buf_uart1.buf[9];
			DATA=vol;		
 // DATA=50000+len;
			if(DATA>50000){
				sprintf(buffer,"湿度  : %.2f%%RH ",(float)(DATA-50000)/100);
				Gui_DrawFont_GBK16(0,94-16,BLUE,GRAY0,buffer);
				BC26_Senddata(DATA);			
			}
		
			delay_ms(10);			

			Clear_Buffer1();
			
		}
		delay_ms(10);
	}
}

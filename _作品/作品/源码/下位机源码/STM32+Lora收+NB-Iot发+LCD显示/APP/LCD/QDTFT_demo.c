/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "SysTick.h"
#include "Picture.h"
#include "QDTFT_demo.h"
//#include "Font.h"
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Һ�����Գ���");

	DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,40,YELLOW,GRAY0,"��ɫ������");

	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"������ʾ����");

	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,100,RED,GRAY0,"ͼƬ��ʾ����");
	delay_ms(1500);
}

void Num_Test(void)
{
	u8 i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i+1]);
	delay_ms(100);
	}
	
}

void Font_Test(void)
{
	Lcd_Clear(GRAY0);

	delay_ms(1000);
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,30,BLUE,GRAY0,"�����Ƽ���ѧ");
	Gui_DrawFont_GBK16(16,50,BLUE,GRAY0,"ͨ�ſƴ���");
	Gui_DrawFont_GBK16(16,70,RED,GRAY0, "������СС��");
	Gui_DrawFont_GBK16(0,100,BLUE,GRAY0,"Tel:19373518729");
	Gui_DrawFont_GBK16(0,130,RED,GRAY0, "QQ:1476481915");	
	delay_ms(1800);	
}

void Color_Test(void)
{
	u8 i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
	delay_ms(200);

	while(i--)
	{
		Lcd_Clear(WHITE);
		Lcd_Clear(BLACK);
		Lcd_Clear(RED);
	  Lcd_Clear(GREEN);
	  Lcd_Clear(BLUE);
	}		
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾ40*40 QQͼƬ
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����  
	
	Lcd_SetRegion(128*j,128*k,128*j+127,128*k+127);		//��������
	for(i=0;i<128*128;i++)
 {	
	picL=*(p+i*2);	//���ݵ�λ��ǰ
	picH=*(p+i*2+1);				
	LCD_WriteData_16Bit(picH<<8|picL);  						
 }		
}
void QDTFT_Test_Demo(void)
{
//	Lcd_Init();
//	LCD_LED_SET;//ͨ��IO���Ʊ�����		
//	showimage(gImage_XXB);//ͼƬ��ʾʾ��
//	delay_ms(10000);	
//	Redraw_Mainmenu();//�������˵�(�����������ڷֱ��ʳ�������ֵ�����޷���ʾ)
//	showimage(gImage_XXB);//ͼƬ��ʾʾ��
//	delay_ms(10000);
//	Color_Test();//�򵥴�ɫ������
//	showimage(gImage_XXB);//ͼƬ��ʾʾ��
//	delay_ms(10000);
//	Num_Test();//������������
//	Font_Test();//��Ӣ����ʾ����		
	showimage(gImage_XXB);//ͼƬ��ʾʾ��
//	delay_ms(10000);
//	LCD_LED_CLR;//IO���Ʊ�����	
	
}

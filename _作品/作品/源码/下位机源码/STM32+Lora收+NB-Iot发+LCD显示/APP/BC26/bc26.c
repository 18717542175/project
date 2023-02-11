#include "bc26.h"


char *strx,*extstrx;
char atstr[USART2_REC_LEN];
int err;    //全局变量
char atbuf[USART2_REC_LEN];
char objtnum[USART2_REC_LEN];//观察号
char distnum[USART2_REC_LEN];//观察号
BC26 BC26_Status;



void Clear_Buffer(void)//清空串口2缓存
{
//    printf(buf_uart2.buf);  //清空前打印信息
    Delay(300);
    buf_uart2.index=0;
    memset(buf_uart2.buf,0,USART2_REC_LEN);
}


int BC26_Init(void)
{
	int errcount = 0;
	err = 0;    //判断模块卡是否就绪最重要
	printf("start init BC26\r\n");
	Clear_Buffer();
	Uart2_SendStr("ATI\r\n");
	Delay(3000);
	printf(buf_uart2.buf);      //打印收到的串口信息
	printf("get back BC26\r\n");
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
	while(strx==NULL)
	{
			printf("\r\n单片机正在连接到模块...\r\n");
			Clear_Buffer();	
			Uart2_SendStr("ATI\r\n");
			Delay(300);
			strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
	}
	Uart2_SendStr("AT+CIMI\r\n");//获取卡号，类似是否存在卡的意思，比较重要。
  Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"ERROR");//只要卡不错误 基本就成功
	if(strx==NULL)
	{
			printf("我的卡号是 : %s \r\n",&buf_uart2.buf[8]);
			Clear_Buffer();	
			Delay(300);
	}
	else
	{
			err = 1;
			printf("卡错误 : %s \r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CGSN=1\r\n");//激活网络，PDP
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返OK
	Clear_Buffer();		
	if(strx)
	{
			Clear_Buffer();	
			printf("GET IMEI OK\r\n");
			Delay(300);
	}
	Uart2_SendStr("AT+CGATT?\r\n");//查询激活状态
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//返1 表明激活成功 获取到IP地址了
	Clear_Buffer();	
	errcount = 0;
	while(strx==NULL)
	{
			errcount++;
			Clear_Buffer();	
			Uart2_SendStr("AT+CGATT?\r\n");//获取激活状态
			Delay(300);
			strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//返回1,表明注网成功
			if(errcount>100)     //防止死循环
			{
					err=1;
					errcount = 0;
					break;
			}
	}
	Uart2_SendStr("AT+QBAND?\r\n"); //允许错误值
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
	if(strx)
	{
			printf("========BAND========= \r\n %s \r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CSQ\r\n");//查看获取CSQ值
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CSQ");//返回CSQ
	if(strx)
	{
			printf("信号质量:%s\r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CEREG?\r\n");
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 0,1");//返回注册状态
	extstrx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 1,1");//返回注册状态
	Clear_Buffer();	
	errcount = 0;
	while(strx==NULL&&extstrx==NULL)//两个返回值都没有
	{
		errcount++;
		Clear_Buffer();
		Uart2_SendStr("AT+CEREG?\r\n");//判断运营商
		Delay(300);
		strx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 0,1");//返回注册状态
		extstrx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 1,1");//返回注册状态
		if(errcount>100)     //防止死循环
		{
				err=1;
				errcount = 0;
				break;
		}
	}
	return err;	
}

 void BC26_PDPACT(void)//激活场景，为连接服务器做准备
{
    int errcount = 0;
    Uart2_SendStr("AT+CGPADDR=1\r\n");//激活场景
    Delay(300);
    Clear_Buffer();
    Uart2_SendStr("AT+CGSN=1\r\n");//激活场景
    Delay(300);
    Clear_Buffer();
    Uart2_SendStr("AT+CGATT?\r\n");//激活场景
    Delay(30);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//注册上网络信息
    Clear_Buffer();	
    while(strx==NULL)
    {
        errcount++;
        Clear_Buffer();
        Uart2_SendStr("AT+CGATT?\r\n");//激活场景
        Delay(300);
        strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//一定要终端入网
        if(errcount>100)     //防止死循环
        {
            errcount = 0;
            break;
        }
    }
    Uart2_SendStr("AT+MIPLCLOSE=0\r\n");//Send a deregister request to OneNET platform
    Delay(300);
    Clear_Buffer();	
    Delay(300);
		Uart2_SendStr("AT+MIPLDELETE=0\r\n");//Send a deregister request to OneNET platform
    Delay(300);
    Clear_Buffer();	
    Delay(300);
    printf("\r\njust close old socket\r\n");
}


void BC26_ConLWM2M(void)
{
    int errcount = 0;
    int i=0;
    Uart2_SendStr("AT+MIPLCREATE\r\n"); //+MIPLCREATE: 0
    Delay(300);
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");
    if(strx==NULL)
    {
        printf("启动LWM2M协议失败\r\n");
        Clear_Buffer();
        Uart2_SendStr("AT+MIPLCREATE\r\n"); //+MIPLCREATE: 0
        Delay(300);
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");
        if(strx)
        {
            printf("启动LWM2M协议成功\r\n");
        }
        else
        {
//					printf("启动LWM2M协议失败\r\n");
//					Uart2_SendStr("AT+QRST=1\r\n"); //AT+QRST=1 重启模块
//					Delay(300);
//					Delay(300);
//					BC26_PDPACT();
//					BC26_ConLWM2M();
					strx=strstr((const char*)buf_uart2.buf,(const char*)"ERROR: 653");
					if(strx)
            {
//                GPIO_SetBits(GPIOC,GPIO_Pin_7);		//模块重启
							Uart2_SendStr("AT+QRST=1\r\n"); //AT+QRST=1 重启模块
                Delay(500);
//                GPIO_ResetBits(GPIOC,GPIO_Pin_7);
                Delay(300);
                NVIC_SystemReset();	//没有创建TCP SOCKET就重启系统等到服务器就绪
                                                                                                                                                                                                                                                                                                                                         }
        }
         Clear_Buffer();
    }
    Clear_Buffer();

    Uart2_SendStr("AT+MIPLADDOBJ=0,3303,1,1,1,0\r\n");//温度实例
    Delay(300);
    Clear_Buffer();
    Delay(300);

    Uart2_SendStr("AT+MIPLOPEN=0,86400\r\n");//打开
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLOBSERVE");//反馈观察号
    memset(atbuf,0,USART2_REC_LEN);
    memset(objtnum,0,USART2_REC_LEN);
    while(1)
    {
        Delay(100);
        if(strlen((const char *)buf_uart2.buf) > 0)
        {
            strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLOBSERVE");//检测到观察号结束
            if(strx)
            {
                sprintf(atbuf,"%s",buf_uart2.buf);
                strx=strstr((const char*)strx+1,(const char*)",");
                for(i=0;;i++)   //查询观察号
                {
                    if(strx[i+1]==',')
                    break;
                    objtnum[i]=strx[i+1];
                }
                printf("得到AT命令:atbuf = %s \r\n",atbuf);
                printf("得到观察号:objtnum = %s \r\n",objtnum);
                break;
            }
            else    //如果没有找到目标就清空反馈的数组，找到了就跳出来
            {
                printf("连接反馈:%s\r\n",buf_uart2.buf);
                Clear_Buffer();
            }
        }
    }
    Clear_Buffer();

    printf("object number = %s\r\n",objtnum);
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLOBSERVERSP=0,%s,1\r\n",objtnum);
    Uart2_SendStr(atstr);//发送观察命令
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLDISCOVER");//返回OK
    memset(atbuf,0,USART2_REC_LEN);
    memset(distnum,0,USART2_REC_LEN);
    while(1)
    {
        Delay(100);
        if(strlen((const char *)buf_uart2.buf) > 0)
        {
            strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLDISCOVER");//检测到观察号结束
            if(strx)
            {
                sprintf(atbuf,"%s",buf_uart2.buf);
                strx=strstr((const char*)strx+1,(const char*)",");
                for(i=0;;i++)   //查询观察号
                {
                    if(strx[i+1]==',')
                    break;
                    distnum[i]=strx[i+1];
                }
                printf("得到AT命令:atbuf = %s \r\n",atbuf);
                printf("得到资源号:distnum = %s \r\n",distnum);
                break;
            }
            else    //如果没有找到目标就清空反馈的数组，找到了就跳出来
            {
                Clear_Buffer();
            }
        }
    }
    Clear_Buffer();

    printf("discover number = %s\r\n",distnum);
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLDISCOVERRSP=0,%s,1,4,\"5700\"\r\n",distnum);
    Uart2_SendStr(atstr);//发送资源命令
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
    while(strx==NULL)
    {
        errcount++;
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
        if(errcount>100)     //防止死循环
        {
            errcount = 0;
            break;
        }
    }
    Clear_Buffer();
}

int val = 100;

/*******************数据发送*****************************
DATA：
	10000<=DATA<20000			10000+氮含量  eg：10371   1—氮代号   0371-371		mg/kg
	20000<=DATA<30000			20000+磷
	30000<=DATA<40000			30000+钾
	40000<=DATA<50000			40000+温度*10	  eg：40192   4—温度代号   192-19.2 度	
 	50000<=DATA						50000+湿度*100	eg：55678   5—湿度代号   5678-56.78 %RH

*********************************************************/


void BC26_Senddata(int data)
{
    int errcount=0;
    val++;
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLNOTIFY=0,%s,3303,0,5700,4,4,%d,0,0\r\n",objtnum,data);
    Uart2_SendStr(atstr);//发送0 socketIP和端口后面跟对应数据长度以及数据
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
    while(strx==NULL)
    {
        errcount++;
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//返回OK
        if(errcount>100)     //防止死循环
        {
            errcount = 0;
            break;
        }
    }

    Clear_Buffer();	
}





#include "bc26.h"


char *strx,*extstrx;
char atstr[USART2_REC_LEN];
int err;    //ȫ�ֱ���
char atbuf[USART2_REC_LEN];
char objtnum[USART2_REC_LEN];//�۲��
char distnum[USART2_REC_LEN];//�۲��
BC26 BC26_Status;



void Clear_Buffer(void)//��մ���2����
{
//    printf(buf_uart2.buf);  //���ǰ��ӡ��Ϣ
    Delay(300);
    buf_uart2.index=0;
    memset(buf_uart2.buf,0,USART2_REC_LEN);
}


int BC26_Init(void)
{
	int errcount = 0;
	err = 0;    //�ж�ģ�鿨�Ƿ��������Ҫ
	printf("start init BC26\r\n");
	Clear_Buffer();
	Uart2_SendStr("ATI\r\n");
	Delay(3000);
	printf(buf_uart2.buf);      //��ӡ�յ��Ĵ�����Ϣ
	printf("get back BC26\r\n");
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
	while(strx==NULL)
	{
			printf("\r\n��Ƭ���������ӵ�ģ��...\r\n");
			Clear_Buffer();	
			Uart2_SendStr("ATI\r\n");
			Delay(300);
			strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
	}
	Uart2_SendStr("AT+CIMI\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
  Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"ERROR");//ֻҪ�������� �����ͳɹ�
	if(strx==NULL)
	{
			printf("�ҵĿ����� : %s \r\n",&buf_uart2.buf[8]);
			Clear_Buffer();	
			Delay(300);
	}
	else
	{
			err = 1;
			printf("������ : %s \r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CGSN=1\r\n");//�������磬PDP
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//��OK
	Clear_Buffer();		
	if(strx)
	{
			Clear_Buffer();	
			printf("GET IMEI OK\r\n");
			Delay(300);
	}
	Uart2_SendStr("AT+CGATT?\r\n");//��ѯ����״̬
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//��1 ��������ɹ� ��ȡ��IP��ַ��
	Clear_Buffer();	
	errcount = 0;
	while(strx==NULL)
	{
			errcount++;
			Clear_Buffer();	
			Uart2_SendStr("AT+CGATT?\r\n");//��ȡ����״̬
			Delay(300);
			strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//����1,����ע���ɹ�
			if(errcount>100)     //��ֹ��ѭ��
			{
					err=1;
					errcount = 0;
					break;
			}
	}
	Uart2_SendStr("AT+QBAND?\r\n"); //�������ֵ
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
	if(strx)
	{
			printf("========BAND========= \r\n %s \r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CSQ\r\n");//�鿴��ȡCSQֵ
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CSQ");//����CSQ
	if(strx)
	{
			printf("�ź�����:%s\r\n",buf_uart2.buf);
			Clear_Buffer();
			Delay(300);
	}
	Uart2_SendStr("AT+CEREG?\r\n");
	Delay(300);
	strx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 0,1");//����ע��״̬
	extstrx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 1,1");//����ע��״̬
	Clear_Buffer();	
	errcount = 0;
	while(strx==NULL&&extstrx==NULL)//��������ֵ��û��
	{
		errcount++;
		Clear_Buffer();
		Uart2_SendStr("AT+CEREG?\r\n");//�ж���Ӫ��
		Delay(300);
		strx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 0,1");//����ע��״̬
		extstrx=strstr((const char*)buf_uart2.buf,(const char*)"+CEREG: 1,1");//����ע��״̬
		if(errcount>100)     //��ֹ��ѭ��
		{
				err=1;
				errcount = 0;
				break;
		}
	}
	return err;	
}

 void BC26_PDPACT(void)//�������Ϊ���ӷ�������׼��
{
    int errcount = 0;
    Uart2_SendStr("AT+CGPADDR=1\r\n");//�����
    Delay(300);
    Clear_Buffer();
    Uart2_SendStr("AT+CGSN=1\r\n");//�����
    Delay(300);
    Clear_Buffer();
    Uart2_SendStr("AT+CGATT?\r\n");//�����
    Delay(30);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//ע����������Ϣ
    Clear_Buffer();	
    while(strx==NULL)
    {
        errcount++;
        Clear_Buffer();
        Uart2_SendStr("AT+CGATT?\r\n");//�����
        Delay(300);
        strx=strstr((const char*)buf_uart2.buf,(const char*)"+CGATT: 1");//һ��Ҫ�ն�����
        if(errcount>100)     //��ֹ��ѭ��
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
        printf("����LWM2MЭ��ʧ��\r\n");
        Clear_Buffer();
        Uart2_SendStr("AT+MIPLCREATE\r\n"); //+MIPLCREATE: 0
        Delay(300);
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");
        if(strx)
        {
            printf("����LWM2MЭ��ɹ�\r\n");
        }
        else
        {
//					printf("����LWM2MЭ��ʧ��\r\n");
//					Uart2_SendStr("AT+QRST=1\r\n"); //AT+QRST=1 ����ģ��
//					Delay(300);
//					Delay(300);
//					BC26_PDPACT();
//					BC26_ConLWM2M();
					strx=strstr((const char*)buf_uart2.buf,(const char*)"ERROR: 653");
					if(strx)
            {
//                GPIO_SetBits(GPIOC,GPIO_Pin_7);		//ģ������
							Uart2_SendStr("AT+QRST=1\r\n"); //AT+QRST=1 ����ģ��
                Delay(500);
//                GPIO_ResetBits(GPIOC,GPIO_Pin_7);
                Delay(300);
                NVIC_SystemReset();	//û�д���TCP SOCKET������ϵͳ�ȵ�����������
                                                                                                                                                                                                                                                                                                                                         }
        }
         Clear_Buffer();
    }
    Clear_Buffer();

    Uart2_SendStr("AT+MIPLADDOBJ=0,3303,1,1,1,0\r\n");//�¶�ʵ��
    Delay(300);
    Clear_Buffer();
    Delay(300);

    Uart2_SendStr("AT+MIPLOPEN=0,86400\r\n");//��
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLOBSERVE");//�����۲��
    memset(atbuf,0,USART2_REC_LEN);
    memset(objtnum,0,USART2_REC_LEN);
    while(1)
    {
        Delay(100);
        if(strlen((const char *)buf_uart2.buf) > 0)
        {
            strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLOBSERVE");//��⵽�۲�Ž���
            if(strx)
            {
                sprintf(atbuf,"%s",buf_uart2.buf);
                strx=strstr((const char*)strx+1,(const char*)",");
                for(i=0;;i++)   //��ѯ�۲��
                {
                    if(strx[i+1]==',')
                    break;
                    objtnum[i]=strx[i+1];
                }
                printf("�õ�AT����:atbuf = %s \r\n",atbuf);
                printf("�õ��۲��:objtnum = %s \r\n",objtnum);
                break;
            }
            else    //���û���ҵ�Ŀ�����շ��������飬�ҵ��˾�������
            {
                printf("���ӷ���:%s\r\n",buf_uart2.buf);
                Clear_Buffer();
            }
        }
    }
    Clear_Buffer();

    printf("object number = %s\r\n",objtnum);
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLOBSERVERSP=0,%s,1\r\n",objtnum);
    Uart2_SendStr(atstr);//���͹۲�����
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLDISCOVER");//����OK
    memset(atbuf,0,USART2_REC_LEN);
    memset(distnum,0,USART2_REC_LEN);
    while(1)
    {
        Delay(100);
        if(strlen((const char *)buf_uart2.buf) > 0)
        {
            strx=strstr((const char*)buf_uart2.buf,(const char*)"+MIPLDISCOVER");//��⵽�۲�Ž���
            if(strx)
            {
                sprintf(atbuf,"%s",buf_uart2.buf);
                strx=strstr((const char*)strx+1,(const char*)",");
                for(i=0;;i++)   //��ѯ�۲��
                {
                    if(strx[i+1]==',')
                    break;
                    distnum[i]=strx[i+1];
                }
                printf("�õ�AT����:atbuf = %s \r\n",atbuf);
                printf("�õ���Դ��:distnum = %s \r\n",distnum);
                break;
            }
            else    //���û���ҵ�Ŀ�����շ��������飬�ҵ��˾�������
            {
                Clear_Buffer();
            }
        }
    }
    Clear_Buffer();

    printf("discover number = %s\r\n",distnum);
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLDISCOVERRSP=0,%s,1,4,\"5700\"\r\n",distnum);
    Uart2_SendStr(atstr);//������Դ����
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
    while(strx==NULL)
    {
        errcount++;
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
        if(errcount>100)     //��ֹ��ѭ��
        {
            errcount = 0;
            break;
        }
    }
    Clear_Buffer();
}

int val = 100;

/*******************���ݷ���*****************************
DATA��
	10000<=DATA<20000			10000+������  eg��10371   1��������   0371-371		mg/kg
	20000<=DATA<30000			20000+��
	30000<=DATA<40000			30000+��
	40000<=DATA<50000			40000+�¶�*10	  eg��40192   4���¶ȴ���   192-19.2 ��	
 	50000<=DATA						50000+ʪ��*100	eg��55678   5��ʪ�ȴ���   5678-56.78 %RH

*********************************************************/


void BC26_Senddata(int data)
{
    int errcount=0;
    val++;
    memset(atstr,0,USART2_REC_LEN);
    sprintf(atstr,"AT+MIPLNOTIFY=0,%s,3303,0,5700,4,4,%d,0,0\r\n",objtnum,data);
    Uart2_SendStr(atstr);//����0 socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����
    Delay(300);
    strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
    while(strx==NULL)
    {
        errcount++;
        strx=strstr((const char*)buf_uart2.buf,(const char*)"OK");//����OK
        if(errcount>100)     //��ֹ��ѭ��
        {
            errcount = 0;
            break;
        }
    }

    Clear_Buffer();	
}





#include "Wifi.h"



/* wifi configuration and modes */
void Wifi_Init(Config_Mode Configmode)
{
	Uart_Init(UART_0,9600);
	
	switch(Configmode)
	{
		case Station:
			Uart_SendStr(UART_0,"AT+CWMODE_CUR=1\r\n");
		break;
		case AccessPoint:
			Uart_SendStr(UART_0,"AT+CWMODE_CUR=2\r\n");
		break;
		case Both_Sta_Ap:
			Uart_SendStr(UART_0,"AT+CWMODE_CUR=3\r\n");
		break;
	}
	_delay_ms(1000);
	
}
void Wifi_EchoMode(EchoMode echomode)
{
	switch(echomode)
	{
		case Echo:
			Uart_SendStr(UART_0,"ATE1\r\n");
		break;
		case NoEcho:
			Uart_SendStr(UART_0,"ATE0\r\n");
		break;
	}
	_delay_ms(1000);
}
void Wifi_AP_Connect(INT8U* username, INT8U* password)
{
	INT8U str[60]= {'0'};
	sprintf(str,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",username,password);
	Uart_SendStr(UART_0,str);	
}


/*  TCP/IP configurations */

void Wifi_ConnectionMode(Connection_TCPMode Connmode)
{
	switch (Connmode)
	{
		case single:
			Uart_SendStr(UART_0,"AT+CIPMUX=0\r\n");
		break;
		case multiple:
			Uart_SendStr(UART_0,"AT+CIPMUX=1\r\n");
		break;
	}
	_delay_ms(2000);
}
void Wifi_StartTCP_Conn(INT8U* ipAdress, INT8U* portNo , INT8U* keepAlive)
{
	INT8U str[50]={'0'};
	sprintf(str,"AT+CIPSTART=\"TCP\",\"%s\",%s,%s\r\n",ipAdress,portNo,keepAlive);
	Uart_SendStr(UART_0,str);
}

void Wifi_SendStr(INT8U* pu8msg)
{
	Uart_SendStr(UART_0,"AT+CIPSENDEX=30");
	_delay_ms(500);
}

Bool Wifi_Expected_Response(INT8U* pu8resp,INT16U Expected_Timeout_ms)
{
	INT8U Recieved_Response[100] = {'0'};
	INT8U index = 0;
	INT16U Timeout = 0;
	Bool result = FALSE;
	while(Timeout < Expected_Timeout_ms)
	{
		if(Uart_ReceiveByte_Unblock(UART_0,&Recieved_Response[index]))
		{
			if (strstr(Recieved_Response,pu8resp))
			{
				result = TRUE;
				break;
			}
			index++;
		}else
		{
			_delay_ms(1);
			Timeout++;
		}
			
		
	}
	return result;
	
}

void Wifi_Sendex_Command(INT8U length)
{
	
	INT8U str[20]={'0'};
	sprintf(str,"AT+CIPSENDEX=%d\r\n",length);
	Uart_SendStr(UART_0,str);
	_delay_ms(500);
}

void Wifi_Stop_Sending(void)
{
	Uart_SendStr(UART_0,"\\0\r\n");	
}

Bool Wifi_Recieve_Byte_unblock(INT8U* pu8data)
{
	return Uart_ReceiveByte_Unblock(UART_0,pu8data);
}


INT8U TCP_GetStatus(void)
{
	Uart_SendStr(UART_0,"AT+CIPSTATUS\r\n");
	Response Resp = WaitingForResponse;
	TCP_Error_code code = UnknownError;
	INT8U index = 0;
	INT8U data = 0;
	while(index < 12)
	{
		
		switch(Resp)
		{
			case WaitingForResponse:
			data = Uart_ReceiveByte(UART_0);
			if (data == ':')
			{
				index = 0;
				data = Uart_ReceiveByte(UART_0);
				Resp = Response_Recieved;
			}
			
			break;
			case Response_Recieved:

				if(data == '2')
				{
					code = Connection_Success;
					
				}else if(data == '3')
				{
					code = Connection_Created;
					
				}else if(data == '4')
				{
					code = Connection_fail;
					
				}else if(data == '5')
				{
					code = NoWifi_Connection;				
				}
			break;
		}
		index++;	
	}
	return code;
}
/*
* mqtt.c
*
* Created: 7/19/2020 11:13:02 AM
*  Author: H
*/

#include "mqtt.h"

const INT8U proName[] = "MQTT";
INT16U packetIdent = 0x0001;

void MQTT_Init(void){
	Wifi_Init(Station);
	//Uart_Init(UART_0, 9600);
}
void MQTT_Connect(INT8U* pu8ID){
	INT8U remLen = (2+strlen(proName)) + 1 + 1 + 2 + (2 + strlen(pu8ID));
	Uart_SendStr(UART_0,"AT+CIPSENDEX=30\r\n");
	_delay_ms(100);
	Uart_SendByte(UART_0, 0x10);		/*Packet Type*/
	Uart_SendByte(UART_0, remLen);		/*Remaining Length*/
	encodeUTFStr(proName);				/*Protocol Name*/
	Uart_SendByte(UART_0, 0x04);		/*Protocol Level*/
	Uart_SendByte(UART_0, 0x02);		/*Flags*/
	Uart_SendByte(UART_0, 0xFF);		/*KAT MSB*/
	Uart_SendByte(UART_0, 0xFF);		/*KAT LSB*/
	encodeUTFStr(pu8ID);				/*Client ID*/
	Uart_SendStr(UART_0,"\\0\r\n");
}

void MQTT_Subscribe(INT8U* topic){
	INT8U remLen = 2 + (2 + strlen(topic)) + 1; /*packetID + len of topic + Requested QoS*/
	Uart_SendStr(UART_0,"AT+CIPSENDEX=30\r\n");
	_delay_ms(100);
	Uart_SendByte(UART_0, 0x82);				/*Packet Type*/
	Uart_SendByte(UART_0, remLen);				/*Remaining Length*/
	Uart_SendByte(UART_0, (packetIdent>>8));		/*PacketID MSB*/
	Uart_SendByte(UART_0, packetIdent);				/*PacketID LSB*/
	packetIdent++;
	encodeUTFStr(topic);							/*Topic*/
	Uart_SendByte(UART_0, 0x01);					/*Requested QoS*/
	Uart_SendStr(UART_0,"\\0\r\n");
}

void MQTT_Publish(INT8U* topic, INT8U* pu8msg, INT8U u8msgSize, INT8U QoS){
	INT8U count = 0;
	INT8U remLen = (2+strlen(topic)) + u8msgSize;
	Uart_SendStr(UART_0,"AT+CIPSENDEX=30\r\n");
	_delay_ms(100);
	if(QoS > 0)
	{
		Uart_SendByte(UART_0, 0x32);		/*Packet Type + QoS*/
		remLen = remLen + 2;
	}
	else
	{
		Uart_SendByte(UART_0, 0x30);		/*Packet Type + QoS*/
	}
	Uart_SendByte(UART_0, remLen);				/*Remaining Length*/
	encodeUTFStr(topic);							/*Topic*/
	
	if(QoS > 0){
		Uart_SendByte(UART_0, (packetIdent>>8));		/*PacketID MSB*/
		Uart_SendByte(UART_0, packetIdent);				/*PacketID LSB*/
		packetIdent++;
	}
	
	for (count = 0; count < u8msgSize; count++)
	{
		Uart_SendByte(UART_0, pu8msg[count]);		/*Send byte by byte*/
	}
	Uart_SendStr(UART_0,"\\0\r\n");
}

void MQTT_PubAck(INT8U u8PcktIDMSB, INT8U u8PcktIDLSB){
	Uart_SendStr(UART_0,"AT+CIPSENDEX=30\r\n");
	_delay_ms(100);
	Uart_SendByte(UART_0, 0x40);				/*Packet Type*/
	Uart_SendByte(UART_0, 0x02);				/*Remaining Length (Always 2)*/
	Uart_SendByte(UART_0, u8PcktIDMSB);		/*PacketID MSB*/
	Uart_SendByte(UART_0, u8PcktIDLSB);				/*PacketID LSB*/
	Uart_SendStr(UART_0,"\\0\r\n");
}

void encodeUTFStr(INT8U* str){
	Uart_SendByte(UART_0, 0x00);			/*Len High Byte*/
	Uart_SendByte(UART_0, strlen(str));		/*Len Low Byte*/
	Uart_SendStr(UART_0, str);
}
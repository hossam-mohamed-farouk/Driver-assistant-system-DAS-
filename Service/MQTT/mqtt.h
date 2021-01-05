/*
 * mqtt.h
 *
 * Created: 7/19/2020 11:12:48 AM
 *  Author: H
 */ 


#ifndef MQTT_H_
#define MQTT_H_

#ifndef F_CPU
#define F_CPU	8000000UL
#endif


#include	"avr/io.h"
#include	"data_types.h"
#include	"bit_handle.h"
#include	"util/delay.h"
#include	"avr/interrupt.h"
#include	"Wifi.h"

#include	"uart.h"
#include	"string.h"

void MQTT_Init(void);
void MQTT_Connect(INT8U* pu8ID);
void MQTT_Subscribe(INT8U* topic);
void MQTT_Publish(INT8U* topic, INT8U* pu8msg, INT8U u8msgSize, INT8U QoS);
void MQTT_PubAck(INT8U u8PcktIDMSB, INT8U u8PcktIDLSB);
void encodeUTFStr(INT8U* str);


#endif /* MQTT_H_ */
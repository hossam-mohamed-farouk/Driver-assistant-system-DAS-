/*
 * BlueTooth.h
 *
 * Created: 8/4/2020 5:19:14 PM
 *  Author: H
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "uart.h"


void  BT_Init(UART_Type uartNum, INT32U u32Baud);
INT8U BT_ReceiveByte(UART_Type uartNum);
Bool  BT_ReceiveByte_Unblock(UART_Type uartNum, INT8U* pu8Data);





#endif /* BLUETOOTH_H_ */
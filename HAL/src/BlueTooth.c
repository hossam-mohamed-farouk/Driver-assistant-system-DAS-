/*
 * BlueTooth.c
 *
 * Created: 8/4/2020 5:19:27 PM
 *  Author: H
 */ 
#include "BlueTooth.h"

void  BT_Init(UART_Type uartNum, INT32U u32Baud)
{
	Uart_Init(uartNum, u32Baud);
}
INT8U BT_ReceiveByte(UART_Type uartNum)
{
	return Uart_ReceiveByte(uartNum);
}
Bool  BT_ReceiveByte_Unblock(UART_Type uartNum, INT8U* pu8Data)
{
	return Uart_ReceiveByte_Unblock(uartNum, pu8Data);
}

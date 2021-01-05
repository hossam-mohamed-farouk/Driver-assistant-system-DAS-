
#include "max7219.h"
#include "FreeRTOS.h"
#include "task.h"

static void Max72191_SendByte(INT8U reg, INT8U u8Data);
//------------------------------------------------------------------------------

void Max7219_Init(void)
{
	SPI_Init(MODE_MASTER);
	setBit(SPI_DDR, SPI_SS);			//Make SS O/P
	
	Max72191_SendByte(MAX7219_REG_DECODEMODE,	0x00);	//No Decode
	Max72191_SendByte(MAX7219_REG_SCANLIMIT,	0x07);	//Scan the 8 digits of data
	Max72191_SendByte(MAX7219_REG_INTENSITY,	0x0f);	//Maximum Intensity
	Max72191_SendByte(MAX7219_REG_DISPLAYTEST,	0x00);	//All O/Ps Off
	Max72191_SendByte(MAX7219_REG_SHUTDOWN,		0x01);	//Not Shutdown

}
/* Used to init the system. As we have to use _delay_ms before starting RTOS */
void Max72191_SendByte(INT8U reg, INT8U u8Data)
{
	setBit(SPI_PORT, SPI_SS);
	SPI_Tranceive(reg);
	SPI_Tranceive(u8Data);
	clearBit(SPI_PORT, SPI_SS);
	_delay_ms(10);
}
/* RTOS Compliant. We could use vTaskDelay */
void Max7219_SendByte(INT8U reg, INT8U u8Data)
{
	setBit(SPI_PORT, SPI_SS);
	SPI_Tranceive(reg);
	SPI_Tranceive(u8Data);
	clearBit(SPI_PORT, SPI_SS);
	vTaskDelay(1);
}
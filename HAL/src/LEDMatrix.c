
#include "LEDMatrix.h"


void LEDMatrix_Init(void)
{
	Max7219_Init();
}

void LEDMatrix_AllOn(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 8; col++)
	{
		Max7219_SendByte( col + 1, 0xFF );
	}
}

void LEDMatrix_AllOff(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 8; col++)
	{
		Max7219_SendByte( col + 1, 0x00 );
	}
}

void LEDMatrix_AllDim(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 8; col += 2)
	{
		Max7219_SendByte( col + 1, 0xAA );
	}
	for(col = 1; col < 8; col += 2)
	{
		Max7219_SendByte( col + 1, 0x55 );
	}
}

void LEDMatrix_MidOff(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 2; col++)
	{
		Max7219_SendByte( col + 1, 0xFF );
	}
	for(col = 2; col < 6; col++)
	{
		Max7219_SendByte( col + 1, 0x00 );
	}
	for(col = 6; col < 8; col++)
	{
		Max7219_SendByte( col + 1, 0xFF );
	}
}

void LEDMatrix_RightHalf(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 4; col++)
	{
		Max7219_SendByte( col + 1, 0xAA );
	}
	for(col = 4; col < 8; col++)
	{
		Max7219_SendByte( col + 1, 0xFF );
	}
}

void LEDMatrix_LeftHalf(void)
{
	INT8U col = 0;
	
	for(col = 0; col < 4; col++)
	{
		Max7219_SendByte( col + 1, 0xFF );
	}
	for(col = 4; col < 8; col++)
	{
		Max7219_SendByte( col + 1, 0xAA );
	}
}


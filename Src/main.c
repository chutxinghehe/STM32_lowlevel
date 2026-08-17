#include <stdio.h>
#include <stdint.h>
#include "RCC.h"
#include "GPIO.h"
#include "SPI.h"
#include "TIME.h"
#include "ST7789.h"
#include "I2C.h"


int main() 
{	
	RCC_Enable_PortB();  
	RCC_Enable_PortA();  
	RCC_Enable_SPI1();   
	RCC_Enable_I2C1();
	RCC_Enable_TIM2();
	
	SPI1_Init_Master();

	initTFT();
	
	
	while (1)
	{
		fullDisplay(COLOR_MAGENTA);
		delay_ms(500);
		drawChar(40, 50, 'c', Font_7x10, COLOR_BLACK, COLOR_WHITE);
		drawString(10, 10, "chutxinh", Font_7x10, COLOR_BLUE, COLOR_RED);
	}
}

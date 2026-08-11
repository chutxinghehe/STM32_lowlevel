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
	
	I2C_Init_Master();

	while (1)
	{
		I2C_Start();
		I2C_Send_Address(0x11, 0);
		I2C_Send_Data(0x22);
		I2C_Stop();
		delay_ms(50);
	}
}

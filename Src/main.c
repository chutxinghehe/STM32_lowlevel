#include <stdio.h>
#include <stdint.h>
#include "RCC.h"
#include "GPIO.h"
#include "SPI.h"
#include "TIME.h"
#include "ST7789.h"
#include "I2C.h"
#include "DS3231.h"


uint8_t hour = 0;
uint8_t min = 0;
uint8_t sec = 0;

int main() 
{	
	RCC_Enable_PortB();  
	RCC_Enable_PortA();  
	RCC_Enable_SPI1();   
	RCC_Enable_I2C1();
	RCC_Enable_TIM2();
	
	set_time(5, 10, 0);
	
	while (1)
	{
		get_time(&hour, &min, &sec);
		delay_ms(500);
	}
}

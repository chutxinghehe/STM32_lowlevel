#include <stdio.h>
#include <stdint.h>
#include <RCC.h>
#include <GPIO.h>
#include <EXTI.h>


void mDelay(volatile uint32_t time) {
    while(time--);
}


int main() 
{
	RCC_Config_72Mhz();
	
    RCC_Enable_PortA();
	RCC_Enable_PortC();
	
    
	GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_Mode_Input_PD);
	GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_Mode_Output_OD);

	EXTI0_Init();
	//EXTI0_IRQHandler();
	
	while (1)
	{
		
	}
}

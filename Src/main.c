#include <stdio.h>
#include <stdint.h>
#include <RCC.h>
#include <GPIO.h>
#include <EXTI.h>
#include <TIME.h>


void mDelay(volatile uint32_t time) {
    while(time--);
}


int main() 
{	
    //RCC_Enable_PortA();
	RCC_Enable_PortC();
	RCC_Enable_TIM2();
	
    
	//GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_Mode_Input_PD);
	GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_Mode_Output_OD);

	//EXTI0_Init();
	//EXTI0_IRQHandler();
	TIME2_Init_IT();
	
	while (1)
	{
		if (blink_state)
		{
			GPIO_Write(GPIOC, GPIO_PIN_13, 0);
		}
		else
		{
			GPIO_Write(GPIOC, GPIO_PIN_13, 1);
		}
		
	}
}

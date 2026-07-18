#include "TIME.h"
#include "EXTI.h"

uint8_t blink_state = 0;

void TIME2_Init_IT()
{
	TIM2_PSC = 7999;
	TIM2_ARR = 999;
	TIM2_DIER |= (1 << 0);
	TIM2_CR1 |= (1 << 0);
	NVIC_ISR0 |= (1 << 28);
}

void TIM2_IRQHandler()
{
	if(TIM2_SR & 0x01){
		//doing sth
		if (blink_state == 0)
		{
			blink_state = 1;
		}
		else
		{
			blink_state = 0;
		}
		
		TIM2_SR &= ~(uint32_t)(1 << 0);
	}
}







#include <UART.h>
#include <GPIO.h>
#include <TIME.h>
#include <EXTI.h>

void USART1_IRQHandler()
{
	if (UART1_SR & (1 << 5))
	{
		char c = (char) (UART1_DR &  0xFF);
		
		UART_SendChar(c);	// gui tu vdk len maytinh nguoclai
	}
}

void UART_Init()
{
	GPIO_Config(UART1_Port_TX, UART1_Pin_TX, GPIO_Mode_AF_PP);
	GPIO_Config(UART1_Port_RX, UART1_Pin_RX, GPIO_Mode_Input_Floating);
	
	UART1_CR1 |= (1 << 13);
	UART1_BRR = 0x0341;
	UART1_CR1 |= (1 << 3);
	UART1_CR1 |= (1 << 2);
	
	UART1_CR1 |= (1 << 5);
	EN_NVIC_UART1();
}


void UART_SendChar(char c)
{
	while (!(UART1_SR & (1 << 7)))
	{}
		
	UART1_DR = c;	
}


void UART_SendString(const char* str)
{
	while (*str != '\0')
	{
		UART_SendChar(*str);
		str += 1;
	}
}

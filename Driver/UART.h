#ifndef __UART_H
#define __UART_H


#include <stdint.h>

#define		UART1_Port_TX		GPIOA
#define		UART1_Port_RX		GPIOA

#define		UART1_Pin_TX		GPIO_PIN_9
#define		UART1_Pin_RX		GPIO_PIN_10

//#define		UART1_Mode_TX		
//#define		UART1_Mode_RX		

//=================================================================================
//							Address bass uart
//=================================================================================
#define		UART1_ADDR_BASE		0x40013800
#define		UART2_ADDR_BASE		0x40004400
#define		UART3_ADDR_BASE		0x40004800


//=================================================================================
//							Address Reg
//=================================================================================
#define		UART_SR					0x00
#define		UART_DR					0x04
#define		UART_BRR				0x08
#define		UART_CR1				0x0C
#define		UART_CR2				0x10
#define		UART_CR3				0x14
#define		UART_GTPR				0x18


//=================================================================================
//							UART1
//=================================================================================
#define		UART1_SR				(*((volatile uint32_t*)(UART_SR	 + UART1_ADDR_BASE)))
#define		UART1_DR				(*((volatile uint32_t*)(UART_DR	 + UART1_ADDR_BASE)))
#define		UART1_BRR				(*((volatile uint32_t*)(UART_BRR + UART1_ADDR_BASE)))
#define		UART1_CR1				(*((volatile uint32_t*)(UART_CR1 + UART1_ADDR_BASE)))
#define		UART1_CR2				(*((volatile uint32_t*)(UART_CR2 + UART1_ADDR_BASE)))
#define		UART1_CR3				(*((volatile uint32_t*)(UART_CR3 + UART1_ADDR_BASE)))
#define		UART1_GTPR				(*((volatile uint32_t*)(UART_GTPR + UART1_ADDR_BASE)))	


//=================================================================================
//							API
//=================================================================================
void UART_Init();
void UART_SendChar(char c);
void UART_SendString(const char* str);
void USART1_IRQHandler();



#endif
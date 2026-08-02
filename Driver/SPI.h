#ifndef	__SPI_H
#define	__SPI_H

#include <stdint.h>

//==================================================
//				address base spi
//==================================================
#define		SPI1_Addr_Base			0x40013000


//--------------------------------------------------
#define 	MISO_Port		GPIOA	
#define 	MISO_Pin		GPIO_PIN_6
#define		MOSI_Port		GPIOA
#define 	MOSI_Pin		GPIO_PIN_7
#define 	CS_Port			GPIOA
#define 	CS_Pin			GPIO_PIN_4
#define 	SCK_Port		GPIOA	
#define 	SCK_Pin			GPIO_PIN_5	


//==================================================
//				offset spi
//==================================================
#define		SPI_CR1					0x00
#define		SPI_CR2					0x04
#define		SPI_SR					0x08
#define		SPI_DR					0x0C
#define		SPI_CRCPR				0x10
#define		SPI_RXCRCR				0x14
#define		SPI_TXCRCR				0x18
#define		SPI_I2SCFGF				0x1C
#define		SPI_I2SPR				0x20


//==================================================
//				   spi1
//==================================================
#define		SPI1_CR1			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_CR1)) )
#define		SPI1_CR2			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_CR2)) )
#define		SPI1_SR				( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_SR)) )
#define		SPI1_DR				( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_DR)) )
#define		SPI1_CRCPR			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_CRCPR	)) )
#define		SPI1_RXCRCR			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_RXCRCR)) )
#define		SPI1_TXCRCR			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_TXCRCR)) )
#define		SPI1_I2SCFGF		( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_I2SCFGF)) )
#define		SPI1_I2SPR			( *((volatile uint32_t*)(SPI1_Addr_Base + SPI_I2SPR	)) )


//==================================================
//				   api
//==================================================
void SPI1_Init_Master();
void SPI1_Send(uint8_t data);

#endif
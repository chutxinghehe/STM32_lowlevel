#include <SPI.h>
#include <GPIO.h>


void SPI1_Init_Master()
{
	GPIO_Config (MISO_Port, MISO_Pin, GPIO_Mode_Input_Floating);
	GPIO_Config (MOSI_Port, MOSI_Pin, GPIO_Mode_AF_PP);
	GPIO_Config (SCK_Port, SCK_Pin, GPIO_Mode_AF_PP);
	
	// CS pin removed - each device (LCD, SD, etc.) manages its own CS
	
	SPI1_CR1 = 0;
	SPI1_CR1 |= ((1 << 8) | (1 << 9));  // SSM, SSI - Software slave management
	SPI1_CR1 |= ((1 << 2) | (1 << 6));  // MSTR, SPE - Master mode, SPI enable
}


void SPI1_Send(uint8_t data)
{
	// CS should be controlled by higher layer (LCD, SD Card, etc.)
	// Not here in SPI driver
	
	while (!(SPI1_SR & (1 << 1))){}  // Wait for TXE (Transmit buffer empty)
	SPI1_DR = data;
	
	while (!(SPI1_SR & (1 << 0))){}  // Wait for RXNE (Receive buffer not empty)
	(void) SPI1_DR;                   // Dummy read to clear RXNE flag
	
	while (SPI1_SR & (1 << 7)){}     // Wait for BSY (Busy flag) clear
}


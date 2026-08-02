#include <SPI.h>
#include <GPIO.h>

void SPI1_Init_Master()
{
	GPIO_Config (MISO_Port, MISO_Pin, GPIO_Mode_Input_Floating);
	GPIO_Config (MOSI_Port, MOSI_Pin, GPIO_Mode_AF_PP);
	GPIO_Config (SCK_Port, SCK_Pin, GPIO_Mode_AF_PP);
	GPIO_Config (CS_Port, CS_Pin, GPIO_Mode_Output_PP);
	
	SPI1_CR1 = 0;
	SPI1_CR1 |= ((1 << 8) | (1 << 9));
	SPI1_CR1 |= ((1 << 2) | (1 << 6));
	
	GPIO_Write(CS_Port, CS_Pin, 1);
}


void SPI1_Send(uint8_t data)
{
	GPIO_Write(CS_Port, CS_Pin, 0);
	
	while (!(SPI1_CR1 & (1 << 1))){}
	SPI1_DR = data ;
		
	while (!(SPI1_CR1 & (1 << 0))){}
	(void) SPI1_DR;
		
//	uint32_t checkDataR = SPI1_DR ;
//	checkDataR--;
//	checkDataR++;	
	
	while (SPI1_SR & (1 << 7)){}
}


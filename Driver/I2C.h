#ifndef __I2C_H
#define	__I2C_H
#include <stdint.h>

#define	I2C_Addr_Base		0x40005400

#define SCL_Port		GPIOB	
#define	SCL_Pin			GPIO_PIN_6		
#define	SDA_Port		GPIOB	
#define	SDA_Pin			GPIO_PIN_7	


#define I2C_CR1			0x00
#define I2C_CR2			0x04
#define I2C_OAR1		0x08
#define I2C_OAR2		0x0C
#define I2C_DR			0x10
#define I2C_SR1			0x14
#define I2C_SR2			0x18
#define I2C_CCR			0x1C
#define I2C_TRISE		0x20


#define I2C1_CR1		(*((volatile uint32_t*) (I2C_CR1	+ I2C_Addr_Base)))
#define I2C1_CR2		(*((volatile uint32_t*) (I2C_CR2	+ I2C_Addr_Base)))
#define I2C1_OAR1		(*((volatile uint32_t*) (I2C_OAR1  	+ I2C_Addr_Base)))
#define I2C1_OAR2		(*((volatile uint32_t*) (I2C_OAR2  	+ I2C_Addr_Base)))
#define I2C1_DR			(*((volatile uint32_t*) (I2C_DR	  	+ I2C_Addr_Base)))
#define I2C1_SR1		(*((volatile uint32_t*) (I2C_SR1  	+ I2C_Addr_Base)))
#define I2C1_SR2		(*((volatile uint32_t*) (I2C_SR2  	+ I2C_Addr_Base)))
#define I2C1_CCR		(*((volatile uint32_t*) (I2C_CCR  	+ I2C_Addr_Base)))
#define I2C1_TRISE		(*((volatile uint32_t*) (I2C_TRISE	+ I2C_Addr_Base)))


void I2C_Init_Master();
void I2C_Start();
void I2C_Stop();
uint8_t I2C_Send_Address(uint8_t address, uint8_t rw);
uint8_t I2C_Send_Data(uint8_t data);
uint8_t I2C_Read_Data (uint8_t readData);


#endif
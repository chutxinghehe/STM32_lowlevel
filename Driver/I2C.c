#include <I2C.h>
#include <GPIO.h>

void I2C_Init_Master()
{
	GPIO_Config(SCL_Port, SCL_Pin, GPIO_Mode_AF_OD);
	GPIO_Config(SDA_Port, SDA_Pin, GPIO_Mode_AF_OD);

	I2C1_CR2 |= (0b001000);
	I2C1_CCR = 0x28;
	I2C1_TRISE = 9;
	I2C1_CR1 |= (1 << 0);
//	I2C1_CR1 |= (1 << 8); ????
	
}


void I2C_Start()
{
//	I2C1_CR1 &= ~(1 << 9);
	I2C1_CR1 |= (1 << 8);
	
	while (!(I2C1_SR1 & (1 << 0))){}
	// sb duoc set roi
}


void I2C_Stop()
{
	I2C1_CR1 |= (1 << 9);
}


uint8_t I2C_Send_Address(uint8_t address, uint8_t rw)
{
	// send address
	I2C1_DR = (address << 1) | (rw & 0x01);
	
	// read SR1 then read SR2 after ADDR is set
	while (!(I2C1_SR1 & (1 << 1)))
	{
		// error AF
		if ((I2C1_SR1) & (1 << 10))
		{
			I2C1_SR1 &= ~(1 << 10);
			I2C_Stop();
			return 1;
		}	
	}
	(void) I2C1_SR1;
	(void) I2C1_SR2;
	
		
	
	
	return 0;
}


uint8_t I2C_Send_Data(uint8_t data)
{
	//Data is written by 
	I2C1_DR = data;
	
	// if btf is set -> transfer succeed
	while (!(I2C1_SR1 & (1 << 2))){}
	
	// error AF
	if ((I2C1_SR1) & (1 << 10))
	{
		I2C1_SR1 &= ~(1 << 10);
		I2C_Stop();
		return 1;
	}
		
	return 0;
                                             }


uint8_t I2C_Read_Data (uint8_t readData)
{
	// if readData = 1 -> set ack 
	if (readData)
	{
		I2C1_CR1 |= (1 << 10);
	}
	else 
	{
		// set ack 
		I2C1_CR1 &= ~(1 << 10);
		I2C1_CR1 |= (1 << 9);
	}
	
	// wait til rxne = 1
	while (!(I2C1_SR1 & (1 << 6))){}
	
	return (uint8_t) I2C1_DR;
	
}
#include <I2C.h>
#include <GPIO.h>

void I2C_Init_Master()
{
	
	
	
	I2C1_CR2 |= (0b001000);
	I2C1_CCR = 0x28;
	I2C1_TRISE = 9;
	I2C1_CR1 |= (1 << 0)
	I2C1_CR1 |= (1 << 8);
	
}


void I2C_Start()
{
	
	(void) I2C1_SR1;
}


void I2C_Stop()
{

}


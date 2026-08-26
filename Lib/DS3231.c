#include "DS3231.h"

uint8_t dec_to_bcd(uint8_t dec)
{
	return (((dec / 10) << 4) | (dec % 10));
}


uint8_t bcd_to_dec(uint8_t bcd)
{
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


void set_time(uint8_t hour, uint8_t min, uint8_t sec)
{
	I2C_Start();
	I2C_Send_Address(DS3231_Address, 0);
	
	if (I2C_Send_Data(0x00) ||
		I2C_Send_Data(dec_to_bcd(sec))	||
		I2C_Send_Data(dec_to_bcd(min))	||
		I2C_Send_Data(dec_to_bcd(hour))	)
	{
		I2C_Stop();
		return;
	}
	
	I2C_Stop();
}


void get_time(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	I2C_Start();
	I2C_Send_Address(DS3231_Address, 0);
	I2C_Send_Data(0x00);
	
	I2C_Start();
	I2C_Send_Address(DS3231_Address, 1);
	
	*sec = bcd_to_dec(I2C_Read_Data(1));
	*min = bcd_to_dec(I2C_Read_Data(1));
	*hour = bcd_to_dec(I2C_Read_Data(0));
	
	I2C_Stop();
}
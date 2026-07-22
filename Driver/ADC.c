#include<ADC.h>
#include<TIME.h>

void ADC01_CH0_Init(void)
{
	ADC01_SMPR2 &= ~(uint32_t) 0x7 ;
	ADC01_SMPR2 = ADC01_SMPR2 | (uint32_t) 0x2;

	ADC01_SQR3 = 0;
	
	ADC01_CR2 |= (uint32_t) 0x02 ;
	
	ADC01_CR2 |= (uint32_t) 0x01 ;
	delay_ms(1);
	ADC01_CR2 |= (uint32_t) 0x01 ;
	
	ADC01_CR2 |= (uint32_t) (1 << 3);
	while (ADC01_CR2 & (uint32_t) (1 << 3));
	
	ADC01_CR2 |= (uint32_t) (1 << 2);
	while (ADC01_CR2 & (uint32_t) (1 << 2));
	
	ADC01_CR2 |= (uint32_t) (1 << 22);
}


uint16_t ADC01_CH0_Read(void)
{
	ADC01_CR2 |= (uint32_t) (1 << 22);
	
	while (!(ADC01_SR & (1 << 1)))
	{
	
	}
	
	return (uint16_t)(ADC01_DR & 0xffff) ;
}

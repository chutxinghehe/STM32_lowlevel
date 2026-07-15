#include <GPIO.h>

void GPIO_Config(volatile GPIO_Typedef* GPIOx, uint16_t pin, uint8_t mode)
{
	uint8_t pos = 0;
	uint32_t config = 0;
	
	for (pos = 0; pos < 16; pos++)
	{
		// clear 4 bit
		if (pin & (1 << pos))
		{
				if (pos < 8)
				{
					GPIOx->_CRL.REG &= ~(0xF << pos*4);
				}
				else if (pos >= 8)
				{
					GPIOx->_CRH.REG &= ~(0xF << ((pos-8)*4)); 
				}
			
				// pick mode
				switch (mode)
				{
						case (GPIO_Mode_Output_PP):
						{
							config = (0x03 << 0) | (0x00 << 2);			//0011
							break;
						}
			
						case (GPIO_Mode_Output_OD):
					{
							config = (0x03 << 0) | (0x01 << 2);			//0111
							break;
						}
			
						case (GPIO_Mode_AF_OD):
						{
							config = (0x03 << 0) | (0x03 << 2);
							break;
						}
			
						case (GPIO_Mode_AF_PP):
						{
							config = (0x03 << 0) | (0x02 << 2);
							break;
						}
				
						case (GPIO_Mode_Input_Analog):
						{
							config = (0x00 << 0) | (0x00 << 2);
							break;
						}
			
						case (GPIO_Mode_Input_Floating):
						{
							config = (0x00 << 0) | (0x01 << 2);
							break;
						}
			
						case (GPIO_Mode_Input_PU):
						{
							config = (0x02 << 2);
							GPIOx->_ODR.REG |= (1 << pos);
							break;
						}
			
						case (GPIO_Mode_Input_PD):
						{
							config = (0x02 << 2);
							GPIOx->_ODR.REG &= ~(1 << pos);
							break;
                        }
			}
		
			// gan gia tri
			if (pos < 8)
			{
				GPIOx->_CRL.REG |= (config << (pos * 4));
			}
			else
			{
				GPIOx->_CRH.REG |= (config << ((pos - 8) * 4));
			}
		}	
	}
}


void GPIO_Write(volatile GPIO_Typedef* GPIOx, uint16_t pin, uint8_t state)
{
    if (state)
    {
        GPIOx->_BSRR.REG = (pin);
    }
    else
    {
        GPIOx->_BRR.REG = pin;
    }    
}

uint8_t GPIO_Read(volatile GPIO_Typedef* GPIOx, uint16_t pin)
{
    return ((GPIOx->_IDR.REG & pin) ? 1 : 0);
}


#include <EXTI.h>
#include <TYPE.h>
#include <GPIO.h>

volatile uint32_t interrupt_count = 0;  // Biến test


void EXTI0_Init()
{
	AFIO->_EXTICR1.REG &= ~(uint32_t)(0xF << 0);	// clear 4 bit
	EXTI->_IMR.Bits.bit_0 = 1;						// clearer mask
	
	EXTI->_RTSR.Bits.bit_0 = 1;		//rising
	EXTI->_FTSR.Bits.bit_0 = 0;
	
	NVIC_ISR0 |= (1 << 6);
}


void EXTI0_IRQHandler(void)
{
	if (EXTI->_PR.Bits.bit_0)
	{
		interrupt_count++;  // Đếm số lần ngắt
		
		// Toggle LED PC13 nhanh để thấy rõ
		static uint8_t led_state = 0;
		led_state = !led_state;
		GPIO_Write(GPIOC, GPIO_PIN_13, led_state);
		
		EXTI->_PR.REG |= 1;  // Xóa cờ pending
	}
}


uint8_t get_pin_Number(uint16_t gpio_pin)
{
	for (int i = 0; i < 16; i ++)  // Sửa: 15 → 16 (để check cả pin 15)
	{
		if (gpio_pin & (1 << i))  // Sửa: &= → &
		{
			return i;
		}
	}
	return 0xff;
}


void EXTI_Init(uint16_t GPIO_PIN, GPIO_Typedef* Port, uint8_t type)
{
	uint8_t port_code;
	uint8_t pin;
	
	if (Port == GPIOA)
	{
		port_code = 0;
	}
	else if (Port == GPIOB)
	{
		port_code = 1;
	}
	else if (Port == GPIOC)
	{
		port_code = 2;
	}
	else
	{
		return;
	}
	
	pin = get_pin_Number(GPIO_PIN);		// pin la thu tu cua bit
	uint32_t shift = (pin % 4) * 4;
	
	if (pin < 4)
	{
		AFIO->_EXTICR1.REG &= ~(uint32_t)(0xf << shift);  // Sửa: Thêm ~ và dùng shift
		AFIO->_EXTICR1.REG |= (port_code << shift);
	}
	else if (pin >= 4 && pin < 8)  // Sửa: > 4 → >= 4
	{
		AFIO->_EXTICR2.REG &= ~(uint32_t)(0xf << shift);  // Sửa: Thêm ~ và dùng shift
		AFIO->_EXTICR2.REG |= (port_code << shift);
	}
	else if (pin >= 8 && pin < 12)  // Sửa: > 8 → >= 8
	{
		AFIO->_EXTICR3.REG &= ~(uint32_t)(0xf << shift);  // Sửa: Thêm ~ và dùng shift
		AFIO->_EXTICR3.REG |= (port_code << shift);
	}
	else 
	{
		AFIO->_EXTICR4.REG &= ~(uint32_t)(0xf << shift);  // Sửa: Thêm ~ và dùng shift
		AFIO->_EXTICR4.REG |= (port_code << shift);
	}
	
	
	EXTI->_IMR.REG |= (1 << pin) ;
	
	
	if (type == EXTI_RISING_MODE)
	{
		EXTI->_RTSR.REG |= (1 << pin);
		EXTI->_FTSR.REG &= ~(1 << pin);  // Sửa: |= ~ → &= ~
	}
	else if (type == EXTI_FALLING_MODE)
	{
		EXTI->_RTSR.REG &= ~(1 << pin);  // Sửa: |= ~ → &= ~
		EXTI->_FTSR.REG |= (1 << pin);
	}
	else
	{
		EXTI->_RTSR.REG |= (1 << pin);
		EXTI->_FTSR.REG |= (1 << pin);
	}
	
	if (pin <= 4)  // Sửa: < 4 → <= 4
	{
		NVIC_ISR0 |= (1 << (pin + 6));
	}
	else if (pin <= 9)
	{
		NVIC_ISR0 |= (1 << 23) ;
	}
	else if (pin <= 15)
	{
		NVIC_ISR1 |= (1 << (40-32));
	}
	
	
}





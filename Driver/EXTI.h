#ifndef __EXTI_h
#define __EXTI_h

#include <TYPE.h>
#include <AFIO.h>
#include <GPIO.h>

#define NVIC_ISR0		*((uint32_t*) 0xE000E100)
#define NVIC_ISR1		*((uint32_t*) 0xE000E104)

#define EXTI_RISING_MODE		0x00			
#define EXTI_FALLING_MODE		0x01
#define EXTI_BOTH_MODE			0x02


typedef struct {
    __32BITS _IMR;
    __32BITS _EMR;
    __32BITS _RTSR;
    __32BITS _FTSR;
    __32BITS _SWIER;
    __32BITS _PR;
} EXTI_Typedef;

#define EXTI    ((volatile EXTI_Typedef*) 0x40010400UL)

void EXTI0_Init();
void EXTI0_IRQHandler(void);

void EXTI_Init(uint16_t GPIO_PIN, GPIO_Typedef* Port, uint8_t type);
uint8_t get_pin_Number(uint16_t gpio_pin);

void EN_NVIC_UART1();

#endif
#ifndef	__RCC_H
#define	__RCC_H
#include	<stdint.h>

typedef struct {
	// Offset 0x00
	union {		
		uint32_t REG;
		struct {
			uint32_t HSION		: 1;
			uint32_t HSIRDY		: 1;
			uint32_t res1			: 1;
			uint32_t HSITRIM	: 5;
			uint32_t HSICAL		: 8;
			uint32_t HSEON		: 1;
			uint32_t HSERDY		: 1;
			uint32_t HSEBYP		: 1;
			uint32_t CSSON		: 1;
			uint32_t res2			: 4;
			uint32_t PLLON		: 1;
			uint32_t PLLRDY		: 1;
			uint32_t PLL2ON		: 1;
			uint32_t PLL2RDY	: 1;
			uint32_t PLL3ON		: 1;
			uint32_t PLL3RDY	: 1;
			uint32_t res3			: 2;
		}Bits;
	}CR;	
	
	//offset 0x04
	union {
		uint32_t REG;
		struct {
			uint32_t SW				: 2;
			uint32_t SWS			: 2;
			uint32_t HPRE			: 4;
			uint32_t PPRE1		: 3;
			uint32_t PPRE2		: 3;
			uint32_t ADC_PRE	: 2;
			uint32_t PLLSRC		: 1;
			uint32_t PLLXTPRE	: 1;
			uint32_t PLLMUL		: 4;
			uint32_t OTGFSPRE : 1;
			uint32_t res			: 1;
			uint32_t MCO			: 4;
			uint32_t res1			: 4;
		}BITS;
	}CFGR;
	
	//offset 0x08
	union {
		volatile uint32_t REG;
		struct{
			volatile uint32_t LSIRDYF		: 1;
			volatile uint32_t LSERDYF		: 1;
			volatile uint32_t HSIRDYF		: 1;
			volatile uint32_t HSERDYF		: 1;
			volatile uint32_t PLLRDYF		: 1;
			volatile uint32_t PLL2RDYF		: 1;
			volatile uint32_t PLL3RDYF		: 1;
			volatile uint32_t CSSF			: 1;
			volatile uint32_t LSIRDYIE		: 1;
			volatile uint32_t LSERDYIE		: 1;
			volatile uint32_t HSIRDYIE		: 1;
			volatile uint32_t HSERDYIE		: 1;
			volatile uint32_t PLLRDYIE		: 1;
			volatile uint32_t PLL2RDYIE		: 1;
			volatile uint32_t PLL3RDYIE		: 1;
			volatile uint32_t res			: 1;
			volatile uint32_t LSIRDYC		: 1;
			volatile uint32_t LSERDYC		: 1;
			volatile uint32_t HSIRDYC		: 1;
			volatile uint32_t HSERDYC		: 1;
			volatile uint32_t PLLRDYC		: 1;
			volatile uint32_t PLL2RDYC		: 1;
			volatile uint32_t PLL3RDYC		: 1;
			volatile uint32_t CSSC			: 1;
			volatile uint32_t res1			: 8;
		}BITS;
	}CIR;

	// Offset 0x0C
	union {
		volatile uint32_t REG;
		struct {
		
		}BITS;
	}APB2RSTR;
	
	
	// offset 0x10
	union {
		uint32_t REG;
		struct {
		
		}BITS;
	}APB1RSTR;
	
	//offset 0x14
	union {
		uint32_t REG;
		struct {
		
		}BITS;
	}AHBENR;
	
	// Offset 0x18
	union {
		volatile uint32_t REG;
		struct {
			volatile uint32_t AFIOEN			: 1;
			volatile uint32_t res1				: 1;
			volatile uint32_t IOPAEN			: 1;
			volatile uint32_t IOPBEN			: 1;
			volatile uint32_t IOPCEN			: 1;
			volatile uint32_t IOPDEN			: 1;
			volatile uint32_t IOPEEN			: 1;
			volatile uint32_t res2  			: 2;	
			volatile uint32_t ADC1EN			: 1;
			volatile uint32_t ADC2EN			: 1;
			volatile uint32_t TIM1EN			: 1;
			volatile uint32_t SPI1EN			: 1;
			volatile uint32_t res3				: 1;
			volatile uint32_t USART1EN			: 1;
			volatile uint32_t res4				: 17;
		}Bits;
	}APB2ENR;  
	
	//offset 0x1C
	union {
		volatile uint32_t REG;
		struct {

		}BITS;
	}APB1ENR;
}RCC_Typedef;


typedef union{
	uint32_t REG;
	struct{
		volatile uint32_t LATENCY : 3;
		volatile uint32_t HLFCYA  : 1;
		volatile uint32_t PRFTBE  : 1;
		volatile uint32_t PRFTBS  : 1;
		volatile uint32_t res			: 26;

	}BITS;
}FLASH_ACR;

#define ADDRESS_RCC					0x40021000UL
#define ADDRESS_FLASH_ACR		0x40022000UL

#define RCC						((volatile RCC_Typedef*)ADDRESS_RCC)
#define ACR						((volatile FLASH_ACR*)ADDRESS_FLASH_ACR)


void RCC_Enable_PortA();
void RCC_Enable_PortB();
void RCC_Enable_PortC();
void RCC_Enable_intPA0();

void RCC_Config_72Mhz();

void RCC_Config_UART();
void RCC_Enable_AFIO(void);
void RCC_Enable_ADC1();
void RCC_Enable_TIM2();
void RCC_Enable_UART1();
#endif

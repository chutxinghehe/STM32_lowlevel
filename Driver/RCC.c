#include <RCC.h>

void RCC_Config_72Mhz()
{
	// enable hse
	RCC->CR.Bits.HSEON = 1;
	while (!RCC->CR.Bits.HSEON){}
		
	ACR->BITS.LATENCY = 2;	
		
	RCC->CFGR.BITS.PLLSRC = 1;
	RCC->CFGR.BITS.PLLMUL = 7;
		
	RCC->CR.Bits.PLLON = 1;			// en pll
	while (!RCC->CR.Bits.PLLRDY){}
		
	//ahb
	RCC->CFGR.BITS.HPRE = 0;
		
	//apb1
	RCC->CFGR.BITS.PPRE1 = 4;			// /2
		
	//apb2
	RCC->CFGR.BITS.PPRE2 = 0;			// /1
		
	RCC->CFGR.BITS.SW = 2;
	while (RCC->CFGR.BITS.SWS != 2){}		// dung SW hay SWS ???
		
	
}


void RCC_Enable_PortA()
{
	RCC->APB2ENR.Bits.IOPAEN = 1;
}


void RCC_Enable_PortB()
{
	RCC->APB2ENR.Bits.IOPBEN = 1;
}


void RCC_Enable_PortC()
{
	RCC->APB2ENR.Bits.IOPCEN = 1; 
}

//void RCC_Enable_intPA0()
//{
//	RCC->APB2ENR.Bits.AFIOEN = 1;
//}

void RCC_Enable_AFIO(void){
	RCC->APB2ENR.Bits.AFIOEN = 1;
}


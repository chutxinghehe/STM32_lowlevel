#include <USB.h>
#include <EXTI.h>

void USB_Init()
{
	EN_NVIC_USB();
}


void USB_LP_CAN1_RX0_IRQHandler(void)
{
	
}




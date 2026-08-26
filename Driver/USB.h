#ifndef	__USB_H
#define	__USB_H

//======================= Typedef ========================
#include <stdint.h>

typedef struct
{
	union{
		
		uint32_t WORD;
		
		struct{
			uint32_t EA			: 4;
			uint32_t STAT_TX	: 2;
			uint32_t DTOG_TX	: 1;
			uint32_t CTR_TX     : 1;
			uint32_t EP_KIND    : 1;
			uint32_t EPTYPE     : 2;
			uint32_t SETUP      : 1;
			uint32_t STAT_RX    : 2;
			uint32_t DTOG_RX    : 1;
			uint32_t CTR_RX     : 1;
			uint32_t reserve	: 16;
		}Bits;
		
	}EPnRp[8];
	
	
	uint32_t res[8];	// 0x20 -> 0x3F
	
	
	union{
	
		uint32_t WORD;
		struct{
			uint32_t FRES		: 1;
			uint32_t PDWN		: 1;
			uint32_t LPMODE		: 1;
			uint32_t FSUSP		: 1;
			uint32_t RESUME		: 1;
			uint32_t res		: 3;
			uint32_t ESOFM		: 1;
			uint32_t SOFM		: 1;
			uint32_t RESETM		: 1;
			uint32_t SUSPM		: 1;
			uint32_t WKUPM		: 1;
			uint32_t ERRM		: 1;
			uint32_t PMAOVRM	: 1;
			uint32_t CTRM		: 1;
		}Bits;
	}CNTR;
	
	
	union{
	
		uint32_t WORD;
		struct{
			uint32_t EP_ID      : 4;
			uint32_t DIR        : 1;
			uint32_t            : 3;
			uint32_t ESOF       : 1;
			uint32_t SOF        : 1;
			uint32_t RESET      : 1;
			uint32_t SUSP       : 1;
			uint32_t WKUP       : 1;
			uint32_t ERR        : 1;
			uint32_t PMAOVR     : 1;
			uint32_t CTR        : 1;
		}Bits;
	}ISTR;
	
	
	union{
	
		uint32_t WORD;
		struct{
			uint32_t FN         : 11;
            uint32_t LSOF       : 2;
            uint32_t LCK        : 1;
            uint32_t RXDM       : 1;
            uint32_t RXDP       : 1;
		}Bits;
	}FNR;
	
	
	union{
	
		uint32_t WORD;
		struct{
			uint32_t ADD        : 7;
            uint32_t EF         : 1;
		}Bits;
	}DADDR;
	
	
	union{
	
		uint32_t WORD;
		struct{
			
		}Bits;
	}BTABLE;
	
}USB_Typedef;


//==================================================================
void USB_Init();
void USB_HP_CAN1_TX_IRQHandler();  // USB High Priority or CAN1 TX
void USB_LP_CAN1_RX0_IRQHandler(void); // USB Low  Priority or CAN1 RX0



//==================================================================
//							Variable
//===================================================================
#define USB_address		0x4000 5C00
#define USB				(*(volatile (USB_Typedef*) USB_address))




#endif
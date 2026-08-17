#include "ST7789.h"


/**
*	@brief	Khoi tao lcd
*	@ref	datasheet st7735 github adafruit
*/
const uint8_t u8InitCmdList[] = 
{
    // cmd    len   data...
    0xB1,  0x03, 0x01, 0x2C, 0x2D,                          // FRMCTR1 - frame rate normal mode
    0xB2,  0x03, 0x01, 0x2C, 0x2D,                          // FRMCTR2 - frame rate idle mode
    0xB3,  0x06, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D,        // FRMCTR3 - frame rate partial mode
    0xB4,  0x01, 0x07,                                      // INVCTR  - display inversion control
    0xC0,  0x03, 0xA2, 0x02, 0x84,                          // PWCTR1  - power control 1
    0xC1,  0x01, 0xC5,                                      // PWCTR2  - power control 2
    0xC2,  0x02, 0x0A, 0x00,                                // PWCTR3  - power control 3
    0xC3,  0x02, 0x8A, 0x2A,                                // PWCTR4  - power control 4
    0xC4,  0x02, 0x8A, 0xEE,                                // PWCTR5  - power control 5
    0xC5,  0x01, 0x0E,                                      // VMCTR1  - VCOM control
    0xE0,  0x10, 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,  // GMCTRP1 - gamma positive
                 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10,
    0xE1,  0x10, 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,  // GMCTRN1 - gamma negative
                 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10,
    LCD_CMD_END, LCD_CMD_END  // k?t th?c
};


void writeCMDTFT(uint8_t cmd)
{
	GPIO_Write(PORT_CS, PIN_CS, 0); // CS = 0
	GPIO_Write(PORT_A0, PIN_A0, 0); // A0 = 0 -> CMD
	SPI1_Send(cmd);
	GPIO_Write(PORT_CS, PIN_CS, 1); // CS = 1
}


void writeDataTFT(uint8_t data)
{
	GPIO_Write(PORT_CS, PIN_CS, 0);
	GPIO_Write(PORT_A0, PIN_A0, 1); // A0 = 1 -> DATA
	SPI1_Send(data);
	GPIO_Write(PORT_CS, PIN_CS, 1);
}


void sendCMDList(const uint8_t* cmdList)
{
	uint8_t index = 0;
	uint8_t cmd = 0;
	uint8_t num = 0;
	
	while(1)
	{
		cmd = *cmdList++;
		num = *cmdList++;
		if(cmd == LCD_CMD_END){
			break;
		}else{
			writeCMDTFT(cmd);
			for(index = 0; index < num ; index++){
				writeDataTFT(*cmdList++);
			}
		}
	}
}


/**
*	@brief	set vi tri cho pixel tu x1 den x2 ; va tu y1 den y2
*	@warning
*	- day la code danh cho man hinh 128x160
*	- moi lan gui lenh 0x2A se can 4 bytes
*	- 1 byte dau cho XS va 1 byte sau cho XE (X start - X end)
*	@note
*	- 0x2A: Collum Address Set
*	- 0x2B: Row Address Set
*	@ref	
*	- page 99/ st735datasheet
*	- page 101
*/
void setPos(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	writeCMDTFT(0x2A);
	writeDataTFT(0x00);
	writeDataTFT(x1);
	writeDataTFT(0x00);
	writeDataTFT(x2);
	
	writeCMDTFT(0x2B);
	writeDataTFT(0x00);
	writeDataTFT(y1);
	writeDataTFT(0x00);
	writeDataTFT(y2);
}


//RGB 16bit 565
void fullDisplay(uint16_t color)
{
	writeCMDTFT(0x2C);
	int i;
	for(i = 0 ; i < 128*160;i++)
	{
		writeDataTFT(color >> 8);
		writeDataTFT(color & 0xFF);	
	}
}


void drawPixel(uint8_t x, uint8_t y, uint16_t color)
{
	if(x >= 128 || y >= 160)
	{
		return ;
	}
	
	setPos(x,y,x+1,y+1);
	writeCMDTFT(0x2C);
	writeDataTFT(color >> 8);
	writeDataTFT(color & 0xFF);
}


void initTFT(void)
{
	GPIO_Config(PORT_A0, PIN_A0, GPIO_Mode_Output_PP);
	GPIO_Config(PORT_CS, PIN_CS, GPIO_Mode_Output_PP);
	GPIO_Config(PORT_RESET, PIN_RESET, GPIO_Mode_Output_PP);
	
	// HW RESET
	GPIO_Write(PORT_RESET, PIN_RESET, 0);
	delay_ms(20);
	GPIO_Write(PORT_RESET, PIN_RESET, 1);
	delay_ms(150);
	
	//SW RESET
	writeCMDTFT(0x01);
	delay_ms(150);
	
	// Sleep out
	writeCMDTFT(0x11);
	delay_ms(255);
	
	sendCMDList(u8InitCmdList);
	
	writeCMDTFT(0x36); // Memory Data Access Control - page 109 datasheet
	writeDataTFT(0x00); // Rotation, RGB/BGR order, mirror
	
	writeCMDTFT(0x3A); // Interface Pixel Format - color mode setting
	writeDataTFT(0x05);
	
	writeCMDTFT(0x20); // Display inversion off 
	
	setPos(0,0,128,160);
	
	// EN DISPLAY
	writeCMDTFT(0x29);
	delay_ms(100);

}


/**
*	@brief	viet 1 chu cai
*	@note
*	- x: khoang cach voi pixel dau tien theo truc x
*	- y: khoang cach voi pixel dau tien theo truc y
*	- font: chon kieu chu, vi du kieu 7x10
*	- color: mau chu
*	- bg: mau background chu (chi la background cho 1 o pixel chua chu)
*/
void drawChar(uint8_t x, uint8_t y, char ch, FontDef font, uint16_t color, uint16_t bg)
{
	uint8_t i,j;
	uint16_t pixelData;
	
	for( i = 0; i < font.height ;i++ )
	{
		pixelData = font.data[(ch - 32)*font.height + i];
		
		for(j = 0 ; j < font.width ;j++)
		{
			if( (pixelData << j) & 0x8000 )
			{
				drawPixel(x+j,y+i,color);
			}
			else
			{
				drawPixel(x+j,y+i,bg);
			}
		}
	}
}


/**
*	@brief	ham viet 1 chuoi chu viet
*	@note
*	- x: khoang cach voi pixel dau tien theo truc x
*	- y: khoang cach voi pixel dau tien theo truc y
*	- str: con tro tro den chuoi cac ky tu 
*	- font: fon chu; vi du 7x10
*/
void drawString(uint8_t x, uint8_t y, char *str, FontDef font, uint16_t color, uint16_t bg)
{
	while(*str != '\0')
	{
		drawChar(x,y,*str,font,color,bg);
		x+= font.width;
		str++;
	}
}

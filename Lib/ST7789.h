#ifndef _TFT_H
#define _TFT_H
#include <stdint.h>
#include "GPIO.h"
#include "SPI.h"
#include "TIME.h"
#include "Font.h"

// Ð?nh nghia các màu RGB565 (16-bit color)
#define COLOR_RED     0xF800   // red
#define COLOR_GREEN   0x07E0   // Xanh lá
#define COLOR_BLUE    0x001F   // Xanh duong
#define COLOR_YELLOW  0xFFE0   // Vàng
#define COLOR_CYAN    0x07FF   // Xanh lo
#define COLOR_MAGENTA 0xF81F   // Tím
#define COLOR_WHITE   0xFFFF   // Tr?ng
#define COLOR_BLACK   0x0000   // Ðen


#define LCD_CMD_END 0xFF

#define PORT_LED  GPIOB
#define PIN_LED   GPIO_PIN_3

#define PORT_RESET  GPIOB
#define PORT_CS     GPIOB
#define PORT_A0     GPIOB //DATA OR CMD

#define PIN_RESET   GPIO_PIN_10
#define PIN_CS      GPIO_PIN_0
#define PIN_A0      GPIO_PIN_1


extern const uint8_t u8InitCmdList[] ;


void writeCMDTFT(uint8_t cmd);
void writeDataTFT(uint8_t data);
void sendCMDList(const uint8_t* cmdList);
void setPos(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void fullDisplay(uint16_t color);
void drawPixel(uint8_t x, uint8_t y, uint16_t color);
void initTFT(void);
void drawChar(uint8_t x, uint8_t y, char ch, FontDef font, uint16_t color, uint16_t bg);
void drawString(uint8_t x, uint8_t y, char *str, FontDef font, uint16_t color, uint16_t bg);

#endif
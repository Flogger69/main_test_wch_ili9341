/*
 * ili9341.h
 *
 */
#include "main.h"
#include "fonts.h"
//#include "ili9341.h"


typedef enum {
	ROTATE_0,
	ROTATE_90,
	ROTATE_180,
	ROTATE_270
} LCD_Horizontal_t;

#define swap(a,b) {int16_t t=a;a=b;b=t;}
#define GUI_WIDTH 320
#define GUI_HEIGHT 240
void LCD_direction(LCD_Horizontal_t direction);


void ILI9341_Reset(void);
void ILI9341_SoftReset(void);

void LCD_WR_REG(uint8_t data);
void LCD_WR_DATA(uint8_t data);
void ILI9341_WriteData(uint8_t* buff, size_t buff_size);
void ILI9341_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
//void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size);
void RESET_L(void);
void RESET_H(void);
void CS_L(void);
void LED_H(void);
void DC_L(void);
void DC_H(void);
void ILI9341_Init(void);
void my_tft_init(void);
void ILI9341_SetWindow(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawBitmap(uint16_t w, uint16_t h, uint8_t *s);
void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ILI9341_FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9341_EndOfDrawBitmap(void);



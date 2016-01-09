/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef __DISPLAY_H__
	#define __DISPLAY_H__

	#include <project.h>

	/* Screen size */
	#define ILI9341_TFTWIDTH  320
	#define ILI9341_TFTHEIGHT 240

	/* Screen command and register addresses */
	#define ILI9341_NOP     0x00
	#define ILI9341_SWRESET 0x01
	#define ILI9341_RDDID   0x04
	#define ILI9341_RDDST   0x09

	#define ILI9341_SLPIN   0x10
	#define ILI9341_SLPOUT  0x11
	#define ILI9341_PTLON   0x12
	#define ILI9341_NORON   0x13

	#define ILI9341_RDMODE  0x0A
	#define ILI9341_RDMADCTL  0x0B
	#define ILI9341_RDPIXFMT  0x0C
	#define ILI9341_RDIMGFMT  0x0A
	#define ILI9341_RDSELFDIAG  0x0F

	#define ILI9341_INVOFF  0x20
	#define ILI9341_INVON   0x21
	#define ILI9341_GAMMASET 0x26
	#define ILI9341_DISPOFF 0x28
	#define ILI9341_DISPON  0x29

	#define ILI9341_CASET   0x2A
	#define ILI9341_PASET   0x2B
	#define ILI9341_RAMWR   0x2C
	#define ILI9341_RAMRD   0x2E

	#define ILI9341_PTLAR   0x30
	#define ILI9341_VSCRDEF 0x33
	#define ILI9341_MADCTL  0x36
	#define ILI9341_VSCRADD 0x37
	#define ILI9341_PIXFMT  0x3A

	#define ILI9341_FRMCTR1 0xB1
	#define ILI9341_FRMCTR2 0xB2
	#define ILI9341_FRMCTR3 0xB3
	#define ILI9341_INVCTR  0xB4
	#define ILI9341_DFUNCTR 0xB6

	#define ILI9341_PWCTR1  0xC0
	#define ILI9341_PWCTR2  0xC1
	#define ILI9341_PWCTR3  0xC2
	#define ILI9341_PWCTR4  0xC3
	#define ILI9341_PWCTR5  0xC4
	#define ILI9341_VMCTR1  0xC5
	#define ILI9341_VMCTR2  0xC7

	#define ILI9341_RDID1   0xDA
	#define ILI9341_RDID2   0xDB
	#define ILI9341_RDID3   0xDC
	#define ILI9341_RDID4   0xDD

	#define ILI9341_GMCTRP1 0xE0
	#define ILI9341_GMCTRN1 0xE1

	/* Color definitions */
	#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
	#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
	#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
	#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
	#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
	#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
	#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
	#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
	#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
	#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
	#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
	#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
	#define ILI9341_RED         0xF800      /* 255,   0,   0 */
	#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
	#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
	#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
	#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
	#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
	#define ILI9341_PINK        0xF81F
	#define ILI9341_GREY1		0x4208
	#define ILI9341_GREY2		0x8410
	#define ILI9341_GREY3		0xC618

	#define swap(a, b) { int16_t t = a; a = b; b = t; }

	#define CONSOLE_TL_X	10
	#define CONSOLE_TL_Y	10
	#define CONSOLE_WIDTH	150
	#define CONSOLE_HEIGHT	(ILI9341_TFTHEIGHT-18)

	enum {DISPLAY_ROT0 = 0, DISPLAY_ROT90 = 1, DISPLAY_ROT180 = 2, DISPLAY_ROT270 = 3};
	enum {DISPLAY_TLC = 0x01, DISPLAY_TRC = 0x02, DISPLAY_BRC = 0x04, DISPLAY_BLC = 0x08};
	uint16_t Display_Color565(uint8_t r, uint8_t g, uint8_t b);
	extern uint16_t cursor_s, cursor_y;

	void Display_Init(void);

	void Display_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	void Display_PushColor(uint16_t color);
	void Display_DrawPixel(int16_t x, int16_t y, uint16_t color);

	void Display_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
	void Display_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
	void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

	void Display_FillScreen(uint16_t color);

	void Display_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void Display_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

	void Display_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void Display_DrawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
	void Display_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
	void Display_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

	void Display_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
	void Display_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);

	void Display_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
	void Display_FillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

	void Display_SetTextCursor(int16_t x, int16_t y);
	void Display_SetTextBgColor(uint16_t c, uint16_t b);

	void Display_WriteString(const char *s, uint8_t size, int16_t x, int16_t y, uint16_t color, uint16_t bgcolor);

	#endif // __DISPLAY_H__

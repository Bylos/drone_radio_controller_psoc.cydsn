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

#include "display.h"
#include "glcdfont.c"
#include "stdio.h"

char cstring[64];
uint16_t console_x = 0, console_y = 0;
uint16_t cursor_x = 0, cursor_y = 0;
uint16_t textcolor = 0xFFFF, textbgcolor = 0xFFFF;

void readcommand(uint8_t c) {
	while(TS_SPI_SpiUartGetTxBufferSize());
	CyDelayUs(10);
	while(TS_SPI_SpiIsBusBusy());
	TS_DnC_DR &= ~TS_DnC_MASK;
	TS_SPI_SpiUartWriteTxData(c);
	TS_SPI_SpiUartWriteTxData(0x00);
	CyDelayUs(10);
	while(TS_SPI_SpiIsBusBusy());
}

uint8_t is_writing_data = 0;
void writecommand(uint8_t c)
{
	if (is_writing_data) {
		CyDelayCycles(1);
		TS_DnC_DR &= ~TS_DnC_MASK;
		is_writing_data = 0;
	}
	TS_SPI_SpiUartWriteTxData(c);
}

void writedata(uint8_t c)
{
	if(!is_writing_data) {
		CyDelayCycles(1);
		TS_DnC_DR |= TS_DnC_MASK;
		is_writing_data = 1;
	}
	TS_SPI_SpiUartWriteTxData(c);
}

uint16_t Display_Color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void Display_SetAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	writecommand(ILI9341_CASET);	// Column addr set
	writedata(x0 >> 8);
	writedata(x0 & 0xFF);			// XSTART 
	writedata(x1 >> 8);
	writedata(x1 & 0xFF);			// XEND
	writecommand(ILI9341_PASET);	// Row addr set
	writedata(y0>>8);
	writedata(y0);					// YSTART
	writedata(y1>>8);
	writedata(y1);					// YEND
	writecommand(ILI9341_RAMWR);	// write to RAM
}

void Display_PushColor(uint16_t color)
{
	uint8_t hi = color >> 8, lo = color;
	writedata(hi);
	writedata(lo);
}

void Display_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
	Display_SetAddrWindow(x,y,x+1,y+1);
	Display_PushColor(color);
}

void Display_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
	uint8_t hi = color >> 8, lo = color;
	Display_SetAddrWindow(x, y, x, y+h-1);
	while(h--)
	{
		writedata(hi);
		writedata(lo);
	}
}

void Display_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	uint8_t hi = color >> 8, lo = color;
	Display_SetAddrWindow(x, y, x+w-1, y);
	while(w--)
	{
		writedata(hi);
		writedata(lo);
	}
}

void Display_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t abs_y1y0 = (y1-y0)>0 ? y1-y0 : y0-y1;
	int16_t abs_x1x0 = (x1-x0)>0 ? x1-x0 : x0-x1;
	int16_t steep = abs_y1y0 > abs_x1x0;
	if (steep)
	{
		swap(x0, y0);
		swap(x1, y1);
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs_y1y0;
	int16_t err = dx / 2;
	int16_t ystep;
	if (y0 < y1)
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}
	for (; x0<=x1; x0++)
	{
		if (steep)
		{
			Display_DrawPixel(y0, x0, color);
		}
		else
		{
			Display_DrawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}

void Display_FillScreen(uint16_t color)
{
	Display_FillRect(0, 0, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, color);
}

// Draw a rectangle
void Display_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	Display_DrawFastHLine(x, y, w, color);
	Display_DrawFastHLine(x, y+h-1, w, color);
	Display_DrawFastVLine(x, y, h, color);
	Display_DrawFastVLine(x+w-1, y, h, color);
}

void Display_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	uint8_t hi = color >> 8, lo = color & 0xFF;
	Display_SetAddrWindow(x, y, x+w-1, y+h-1);
	for(y=h; y>0; y--)
	{
		for(x=w; x>0; x--)
		{
			writedata(hi);
			writedata(lo);
		}
	}
}

void Display_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;
	Display_DrawPixel(x0  , y0+r, color);
	Display_DrawPixel(x0  , y0-r, color);
	Display_DrawPixel(x0+r, y0  , color);
	Display_DrawPixel(x0-r, y0  , color);
	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		Display_DrawPixel(x0 + x, y0 + y, color);
		Display_DrawPixel(x0 - x, y0 + y, color);
		Display_DrawPixel(x0 + x, y0 - y, color);
		Display_DrawPixel(x0 - x, y0 - y, color);
		Display_DrawPixel(x0 + y, y0 + x, color);
		Display_DrawPixel(x0 - y, y0 + x, color);
		Display_DrawPixel(x0 + y, y0 - x, color);
		Display_DrawPixel(x0 - y, y0 - x, color);
	}
}

void Display_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	Display_DrawFastVLine(x0, y0-r, 2*r+1, color);
	Display_FillCircleHelper(x0, y0, r, 3, 0, color);
}

void Display_DrawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;
  while (x<y) {
	if (f >= 0) {
	  y--;
	  ddF_y += 2;
	  f     += ddF_y;
	}
	x++;
	ddF_x += 2;
	f     += ddF_x;
	if (cornername & 0x4) {
	  Display_DrawPixel(x0 + x, y0 + y, color);
	  Display_DrawPixel(x0 + y, y0 + x, color);
	} 
	if (cornername & 0x2) {
	  Display_DrawPixel(x0 + x, y0 - y, color);
	  Display_DrawPixel(x0 + y, y0 - x, color);
	}
	if (cornername & 0x8) {
	  Display_DrawPixel(x0 - y, y0 + x, color);
	  Display_DrawPixel(x0 - x, y0 + y, color);
	}
	if (cornername & 0x1) {
	  Display_DrawPixel(x0 - y, y0 - x, color);
	  Display_DrawPixel(x0 - x, y0 - y, color);
	}
  }
}

void Display_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;
	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & DISPLAY_TLC)
		{
			Display_DrawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			Display_DrawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & DISPLAY_TRC)
		{
			Display_DrawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			Display_DrawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}
			
// Draw a rounded rectangle
void Display_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
	// smarter version
	Display_DrawFastHLine(x+r  , y    , w-2*r, color); // Top
	Display_DrawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	Display_DrawFastVLine(x    , y+r  , h-2*r, color); // Left
	Display_DrawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	Display_DrawCircleHelper(x+r    , y+r    , r, 1, color);
	Display_DrawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	Display_DrawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	Display_DrawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void Display_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
	// smarter version
	Display_FillRect(x+r, y, w-2*r, h, color);
	// draw four corners
	Display_FillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	Display_FillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void Display_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	Display_DrawLine(x0, y0, x1, y1, color);
	Display_DrawLine(x1, y1, x2, y2, color);
	Display_DrawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void Display_FillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	int16_t a, b, y, last;
	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		Display_DrawFastHLine(a, y0, b-a+1, color);
		return;
	}
	int16_t
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1;
	int32_t
	sa   = 0,
	sb   = 0;
	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it
	for(y=y0; y<=last; y++) {
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
			sb += dx02;
		/* longhand:
		a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		Display_DrawFastHLine(a, y, b-a+1, color);
	}
	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		Display_DrawFastHLine(a, y, b-a+1, color);
	}
}

void Display_SetTextCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}

void Display_SetTextBgColor(uint16_t c, uint16_t b) {
  textcolor   = c;
  textbgcolor = b; 
}

void Display_DrawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
	int8_t i;
	for (i=0; i<6; i++ ) {
		uint8_t line;
		if (i == 5) line = 0x0;
		else line = font[(c*5)+i];
		int8_t j;
		for (j = 0; j<8; j++) {
			if (line & 0x1) {
				if (size == 1)  Display_DrawPixel(x+i, y+j, color);
				else {
					Display_FillRect(x+(i*size), y+(j*size), size, size, color);
				} 
			}
			else if (bg != color) {
				if (size == 1) Display_DrawPixel(x+i, y+j, bg);
				else {
					Display_FillRect(x+i*size, y+j*size, size, size, bg);
				}
			}
			line >>= 1;
		}
	}
}

void Display_WriteChar(uint8_t c, uint8_t textsize) {
	Display_DrawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
	cursor_x += textsize*6;
}

void Display_WriteString(const char *s, uint8_t size, int16_t x, int16_t y, uint16_t color, uint16_t bgcolor) {
	uint16_t i = 0;
	uint8_t *c = (uint8_t *)s;
	cursor_x = x;
	cursor_y = y;
	textcolor = color;
	textbgcolor = bgcolor;
	while(c[i] > 0) {
		Display_WriteChar(c[i], size);
		i++;
	}
}

void Display_Init(void) {
	//Reset screen
	CyDelay(200);
	writecommand(ILI9341_SWRESET);
	CyDelayUs(120);
	//Power control A
	writecommand  (0xCB);
	writedata(0x39);
	writedata(0x2C);
	writedata(0x00);
	writedata(0x34);
	writedata(0x02);
	//Power control A
	writecommand  (0xCF);
	writedata(0x00);
	writedata(0XC1);
	writedata(0X30);
	//Driver timing control A
	writecommand  (0xE8);
	writedata(0x85);
	writedata(0x00);
	writedata(0x78);
	//Driver timing control B
	writecommand  (0xEA);
	writedata(0x00);
	writedata(0x00);
	//Power on sequence control
	writecommand  (0xED);
	writedata(0x64);
	writedata(0x03);
	writedata(0X12);
	writedata(0X81);
	//Pump ratio control
	writecommand (0xF7);
	writedata(0x20);
	//Gamma Set
	writecommand  (ILI9341_GAMMASET);   //Gamma curve 3
	writedata(0x01);
	//Memory Access Control
	writecommand  (ILI9341_MADCTL);
	writedata(0xE8);
	//COLMOD: Pixel Format Set
	writecommand  (ILI9341_PIXFMT);
	writedata(0x05);
	//Frame Rate Control (In Normal Mode/Full Colors)
	writecommand  (ILI9341_FRMCTR1);
	writedata(0x00);
	writedata(0x1B);	// 10
	//Display Function Control
	writecommand  (ILI9341_DFUNCTR);
	writedata(0x0A);
	writedata(0x02);	// A2
	//Power Control 1
	writecommand  (ILI9341_PWCTR1);
	writedata(0x23);
	//Power Control 2
	writecommand  (ILI9341_PWCTR2);
	writedata(0x10);
	//VCOM Control 1
	writecommand  (ILI9341_VMCTR1);
	writedata(0x2B);
	writedata(0x2B);
	//Positive Gamma Correction
	writecommand  (ILI9341_GMCTRP1);
	writedata(0x0F);
	writedata(0x31);
	writedata(0x2B);
	writedata(0x0C);
	writedata(0x0E);
	writedata(0x08);
	writedata(0x4E);
	writedata(0xF1);
	writedata(0x37);
	writedata(0x07);
	writedata(0x10);
	writedata(0x03);
	writedata(0x0E);
	writedata(0x09);
	writedata(0x00);
	//Negative Gamma Correction
	writecommand  (ILI9341_GMCTRN1);
	writedata(0x00);
	writedata(0x0E);
	writedata(0x14);
	writedata(0x03);
	writedata(0x11);
	writedata(0x07);
	writedata(0x31);
	writedata(0xC1);
	writedata(0x48);
	writedata(0x08);
	writedata(0x0F);
	writedata(0x0C);
	writedata(0x31);
	writedata(0x36);
	writedata(0x0F);
	//Enable 3G
	writecommand  (0xF2);
	writedata(0x02);  //off
	//Start Screen
	writecommand(ILI9341_SLPOUT);
	CyDelay(120);
	writecommand(ILI9341_DISPON);
	writecommand(ILI9341_INVON);

	/* Clear screen and set up text */
	Display_FillScreen(ILI9341_BLACK);
}
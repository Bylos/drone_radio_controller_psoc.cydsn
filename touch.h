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

#ifndef __TOUCH_H__
	#define __TOUCH_H__
	
	#include <project.h>
	
	#define FT6206_ADDR					0x38
	#define FT6206_G_FT5201ID			0xA8
	#define FT6206_REG_NUMTOUCHES		0x02
	#define FT6206_NUM_X				0x33
	#define FT6206_NUM_Y				0x34
	#define FT6206_REG_MODE				0x00
	#define FT6206_REG_CALIBRATE		0x02
	#define FT6206_REG_WORKMODE			0x00
	#define FT6206_REG_FACTORYMODE		0x40
	#define FT6206_REG_THRESHHOLD		0x80
	#define FT6206_REG_POINTRATE		0x88
	#define FT6206_REG_FIRMVERS			0xA6
	#define FT6206_REG_CHIPID			0xA3
	#define FT6206_REG_VENDID 			0xA8
	// calibrated for Adafruit 2.8" ctp screen
	#define FT6206_DEFAULT_THRESSHOLD	128
	
	typedef struct {
		uint16_t x;
		uint16_t y;
	} point_t;

	uint8_t Touch_Begin(uint8_t thresh);  
	uint8_t Touch_IsTouched(void);
	point_t Touch_GetPoint(void);
	
	#endif // __TOUCH_H__

/* [] END OF FILE */

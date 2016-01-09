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

#ifndef __HARDWARE_H__
	#define __HARDWARE_H__
	
	#include <project.h>
	#include "joystick.h"
	#include "zigbee.h"
	#include "display.h"
	#include "crc.h"
	
	#define ADC_PERIOD_MS		50  // Actual Clock is 10kHz/250/2 = 20Hz
	#define DEBOUNCE_COUNT		5	// Number of ADC cycles to wait for debounce
	
	/* CORRECTED Hardware ADC Channel assignement */
	enum ADC_channel_t {
		ADC_JOY_LEFT_Y		= 0, 
		ADC_JOY_LEFT_X		= 1, 
		ADC_JOY_RIGHT_Y		= 2, 
		ADC_JOY_RIGHT_X		= 3,
		ADC_ZB_RSSI			= 4,
	};
	
	void Hardware_Init();
	uint8_t Hardware_GetAdcFlag(void);
	uint8_t Hardware_GetLeftClickFlag(void);
	uint8_t Hardware_GetRightClickFlag(void);
	void Hardware_ClearAllFlags(void);
	
	#endif /* __HARDWARE_H__ */

/* [] END OF FILE */

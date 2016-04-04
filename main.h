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

#ifndef __MAIN_H__
	#define __MAIN_H__

	#include <project.h>

	#include "crc.h"
	#include "display.h"
	#include "hardware.h"
	#include "joystick.h"
	#include "touch.h"
	#include "zigbee.h"

	#include "mode_seeking.h"
	#include "mode_standby.h"
	#include "mode_alexkidd.h"
    #include "mode_armed_generic.h"
	
	/* Controller & Quadcopter Modes */
	enum mode_t {
		MODE_BOOT 			= 254,
		MODE_SEEKING		= 255,
		MODE_STANDBY		= 0,
		MODE_ALEXKIDD 	    = 1,
		MODE_ACC_CAL		= 2,
		MODE_GYR_CAL		= 3,
		MODE_MAG_CAL		= 4,
		MODE_ALEXKIDD2	    = 5,
		MODE_ACRO			= 6,
		MODE_STABILIZED 	= 7
	};

	#define DRONE_MODE_NUM		8
    
	#endif // __MAIN_H__

/* [] END OF FILE */

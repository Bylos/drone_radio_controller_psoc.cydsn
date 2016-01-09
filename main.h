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
	
	/* Controller Modes */
	enum mode_t {
		MODE_BOOT 			= 0,
		MODE_SEEKING		= 1,
		MODE_STANDBY		= 2,
		MODE_ALEXKIDD		= 3,
	};

	/* Quadcopter Modes */
	enum drone_mode_t {
		DRONE_MODE_UNARMED	= 0,
		DRONE_MODE_ALEXKIDD = 1,
	};
	
	#endif // __MAIN_H__

/* [] END OF FILE */

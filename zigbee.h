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

#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__
	
	#include <project.h>
	#include "joystick.h"
	#include "crc.h"

	#define RX_TIMEOUT_MS		2000	// Time before timeout
	
	enum rx_frame_t {
		RX_FRAME_MODE		= 0,
	};
	
	#define RC_CHANNEL_MASK		0xF000
	#define RC_CHANNEL_SHIFT	12
	
	/* Convenient structure for RC data */
	typedef struct {
		signed short data :12;
		unsigned short channel  :4;
	} rc_t;

	/* Software RC Channel assignement */
	enum RC_channel_t {
		RC_JOY_LEFT_SEL     = 0, // would be emergency exit
		RC_JOY_RIGHT_Y      = 1, // would be throttle
		RC_JOY_RIGHT_X      = 2, // would be yaw
		RC_JOY_LEFT_Y       = 3, // would be pitch
		RC_JOY_LEFT_X       = 4, // would be roll
		RC_JOY_RIGHT_SEL    = 5, // would be arming
	};
	
	/* RC Commands */
	enum RC_command_t {
		RC_COMMAND_UNARM		= 0,
		RC_COMMAND_ALEXKIDD 	= 1,
	};
	
	void Zigbee_TimerAdd(uint16_t time_ms);
	uint8_t Zigbee_GetTimeoutFlag(void);

	uint8_t Zigbee_GetFrame(void);
	uint8_t Zigbee_GetDroneModeFlag(void);
	uint8_t Zigbee_GetDroneMode(void);
	
	void Zigbee_SendCommand(uint8_t command);
	void Zigbee_SendJoystick(joystick_t joystick);
	
	void Zigbee_SetRssiFlag(void);
	void Zigbee_SetRssi(uint16_t rssi);
	uint8_t Zigbee_GetRssiFlag(void);
    uint16_t Zigbee_GetRssi(void);
	
	void Zigbee_ClearAllFlags(void);

#endif // __ZIGBEE_H__

/* [] END OF FILE */

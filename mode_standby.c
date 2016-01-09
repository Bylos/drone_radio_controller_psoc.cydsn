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

#include "mode_standby.h"
#include "displayGUI_Standby.h"
#include "stdio.h"

void Mode_Standby_Init(void) {
	Hardware_ClearAllFlags();
	Joystick_ClearAllFlags();
	Zigbee_ClearAllFlags();
	DisplayGUI_Mode(1);
    DisplayGUI_BatteryLevel (86);
    DisplayGUI_SignalLevel (92);
    DisplayGUI_Standby_UpdateQuadFound();
}

uint8_t Mode_Standby_Run(void) {
	uint8_t next_mode = MODE_STANDBY;
	/* Check for drone mode to switch to AlexKidd */
	if (Zigbee_GetDroneModeFlag()) {
		switch (Zigbee_GetDroneMode()) {
		case DRONE_MODE_ALEXKIDD:
			next_mode = MODE_ALEXKIDD;
			break;
		default:
			break;
		}
	}
	/* Check for request to switch to AlexKidd */
	if (Hardware_GetRightClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_ALEXKIDD);
	}
	return next_mode;
}

/* [] END OF FILE */

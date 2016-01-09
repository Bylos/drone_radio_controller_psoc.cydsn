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

#include "mode_seeking.h"
#include "displayGUI_Standby.h"

void Mode_Seeking_Init(void) {
	Hardware_ClearAllFlags();
	Joystick_ClearAllFlags();
	Zigbee_ClearAllFlags();
	Display_FillScreen(ILI9341_BLACK);
	DisplayGUI_Mode(0);
    DisplayGUI_BatteryLevel (200);
    DisplayGUI_SignalLevel (200);
    DisplayGUI_Standby();
}

uint8_t Mode_Seeking_Run(void) {
	uint8_t next_mode = MODE_SEEKING;
	/* If drone is detected in different mode, resquest unarmed */
	if (Zigbee_GetDroneModeFlag()) {
		switch (Zigbee_GetDroneMode()) {
		case DRONE_MODE_UNARMED:
			next_mode = MODE_STANDBY;
			break;
		default:
			Zigbee_SendCommand(RC_COMMAND_UNARM);
			break;
		}
	}
	return next_mode;
}

/* [] END OF FILE */

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
	DisplayGUI_Mode(MODE_STANDBY);
    DisplayGUI_BatteryLevel (86);
    DisplayGUI_SignalLevel (92);
    DisplayGUI_Standby_UpdateQuadFound();
}

void Mode_Standby_Run(void) {
	/* Check for request to unarm drone (just in case of) */
	if (Hardware_GetLeftClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_UNARM);
	}
	/* Check for request to switch to AlexKidd */
	else if (Hardware_GetRightClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_ALEXKIDD);
	}
}

/* [] END OF FILE */

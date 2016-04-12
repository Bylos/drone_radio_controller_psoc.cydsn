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
    DisplayGUI_Standby();
	DisplayGUI_Mode(MODE_STANDBY);
    DisplayGUI_BatteryLevel (86);
    DisplayGUI_ControlMode();
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
    /* Check for tactile screen input */
    if (Touch_IsTouched()) {
        point_t point = Touch_GetPoint();
        
        if (point.x > 15 && point.x < 100) {
            if (point.y > 25 && point.y < 77) {
                Joystick_SetMode(MODE_1);
                DisplayGUI_ControlMode();
            }
            else if (point.y > 78 && point.y < 117) {
                Joystick_SetMode(MODE_2);
                DisplayGUI_ControlMode();
            }
        }
    }
}

/* [] END OF FILE */

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

#include "mode_alexkidd.h"
#include "displayGUI_AlexKidd.h"

void Mode_AlexKidd_Init(void) {
	Hardware_ClearAllFlags();
	Joystick_ClearAllFlags();
	Zigbee_ClearAllFlags();
	Display_FillScreen(ILI9341_BLACK);
    DisplayGUI_Mode(2);
    DisplayGUI_BatteryLevel (100);
    DisplayGUI_SignalLevel (37);
    DisplayGUI_AlexKidd();
}

static uint8_t highlight_status[4] = {0, 0, 0, 0};
uint8_t Mode_AlexKidd_Run(void) {
	uint8_t next_mode = MODE_ALEXKIDD;
	/* Check for new drone mode */
	if (Zigbee_GetDroneModeFlag()) {
		switch (Zigbee_GetDroneMode()) {
		case DRONE_MODE_UNARMED:
			next_mode = MODE_STANDBY;
			break;
		default:
			break;
		}
	}
	/* Check for joystick values */
	if (Joystick_GetValuesFlag()) {
		joystick_t joystick = Joystick_GetValues();
		
		int front_diff  = (joystick.left_y);
		int sides_diff  = (joystick.left_x);
		uint8_t highlight_status_new[4] = {
			(  front_diff - sides_diff)>204,	// front left motor
			(  front_diff + sides_diff)>204,	// front right motor
			(- front_diff + sides_diff)>204, // rear right motor
			(- front_diff - sides_diff)>204	// rear left motor
		};
		
		if ((highlight_status[0]^highlight_status_new[0]) |
			(highlight_status[1]^highlight_status_new[1]) |
			(highlight_status[2]^highlight_status_new[2]) |
			(highlight_status[3]^highlight_status_new[3]) ) {
			
			DisplayGUI_QuadMotorHighlight (90,115,highlight_status_new);
			memcpy(highlight_status, highlight_status_new,4);
			}
			
		Zigbee_SendJoystick(joystick);
	}
	/* Check for unarming drone */
	if (Hardware_GetLeftClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_UNARM);
	}
	return next_mode;
}

/* [] END OF FILE */

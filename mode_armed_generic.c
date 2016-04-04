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

#include "mode_armed_generic.h"
#include "displayGUI_Armed_Generic.h"

const char *ag[DRONE_MODE_NUM] = {
	"UNARMED",
	"ALEXKIDD",
	"ACCEL. CALIBRATION",
	"GYRO. CALIBRATION",
	"MAGN. CALIBRATION",
	"ALEX KIDD 2",
	"FLIGHT ACRO",
	"FLIGHT STABILIZED",
};

void Mode_Armed_Generic_Init(uint8_t chosen_mode) {
	Hardware_ClearAllFlags();
	Joystick_ClearAllFlags();
	Zigbee_ClearAllFlags();
	Display_FillScreen(ILI9341_BLACK);
    DisplayGUI_Mode(chosen_mode);
    DisplayGUI_BatteryLevel (100);
    DisplayGUI_SignalLevel (37);
    DisplayGUI_Armed_Generic();
	DisplayGUI_Armed_Generic_UpdateChosenMode(ag[chosen_mode]);
}

void Mode_Armed_Generic_Run(void) {
	/* Check for joystick values */
	if (Joystick_GetValuesFlag()) {
		joystick_t joystick = Joystick_GetValues();
		Zigbee_SendJoystick(joystick);
	}
	/* Check for unarming drone */
	if (Hardware_GetLeftClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_UNARM);
	}
}

/* [] END OF FILE */

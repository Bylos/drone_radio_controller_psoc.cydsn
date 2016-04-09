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

uint8_t chosen_mode = 3;

const char *ak[DRONE_MODE_NUM] = {
	"UNARMED",
	"ALEXKIDD",
	"ACCEL. CALIBRATION",
	"GYRO. CALIBRATION",
	"MAGN. CALIBRATION",
	"ALEX KIDD 2",
	"FLIGHT ACRO",
	"FLIGHT STABILIZED",
};

#define SELECT_DEBOUNCE_COUNT 5
uint8_t select_debouncer = 0;

void Mode_AlexKidd_Init(void) {
	Hardware_ClearAllFlags();
	Joystick_ClearAllFlags();
	Zigbee_ClearAllFlags();
	Display_FillScreen(ILI9341_BLACK);
    DisplayGUI_Mode(MODE_ALEXKIDD);
    DisplayGUI_BatteryLevel (100);
    //DisplayGUI_SignalLevel (37);
    DisplayGUI_AlexKidd();
	DisplayGUI_AlexKidd_UpdateChosenMode(ak[chosen_mode]);
}

static uint8_t highlight_status[4] = {0, 0, 0, 0};
void Mode_AlexKidd_Run(void) {
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
			
		if (!select_debouncer) {
			if (joystick.right_x > 2000) {
				chosen_mode ++;
				if (chosen_mode > DRONE_MODE_NUM-1) {
					chosen_mode = 2;
				}
				DisplayGUI_AlexKidd_UpdateChosenMode(ak[chosen_mode]);
				select_debouncer = SELECT_DEBOUNCE_COUNT;
			}
			else if (joystick.right_x < -2000) {
				chosen_mode --;
				if (chosen_mode < 2) {
					chosen_mode = DRONE_MODE_NUM-1;
				}
				DisplayGUI_AlexKidd_UpdateChosenMode(ak[chosen_mode]);
				select_debouncer = SELECT_DEBOUNCE_COUNT;
			}
		}
		else {
			select_debouncer --;
		}
		
		Zigbee_SendJoystick(joystick);
	}
	/* Check for unarming drone */
	if (Hardware_GetLeftClickFlag()) {
		Zigbee_SendCommand(RC_COMMAND_UNARM);
	}
	else if (Hardware_GetRightClickFlag()) {
		Zigbee_SendCommand(chosen_mode);
	}
}

/* [] END OF FILE */

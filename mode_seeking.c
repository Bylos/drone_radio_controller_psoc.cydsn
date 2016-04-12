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
    DisplayGUI_Seeking();
	DisplayGUI_Mode(MODE_SEEKING);
    DisplayGUI_BatteryLevel (200);
}

void Mode_Seeking_Run(void) {
}

/* [] END OF FILE */

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

#ifndef __DISPGUI_H__
#define __DISPGUI_H__

#include "display.h"

void DisplayGUI_Mode (uint8_t modeID);

void DisplayGUI_BatteryLevel (uint8_t battLevelPercent);

void DisplayGUI_SignalLevel (uint8_t signalLevelPercent);

void DisplayGUI_Quad (uint16_t x_pos, uint16_t y_pos);

void DisplayGUI_QuadMotorHighlight (uint16_t x_pos, uint16_t y_pos, uint8_t mon[4]);

void DisplayGUI_RemoteController (uint16_t x_pos, uint16_t y_pos, uint8_t scale, uint8_t activeDoFs[10]);

#endif // __DISPGUI_H__
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

#ifndef __DISPGUIAG_H__
#define __DISPGUIAG_H__

#include "displayGUI.h"

void DisplayGUI_Armed_Generic(void);

void DisplayGUI_Armed_Generic_UpdateChosenMode(const char* ModeName);

void DisplayGUI_Armed_Generic_UpdateBattery(uint8_t newBattLevelPercent);

void DisplayGUI_Armed_Generic_UpdateSignal(uint8_t newSignalLevelPercent);

#endif // __DISPGUIAG_H__

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

#ifndef __DISPGUIAK_H__
#define __DISPGUIAK_H__
    
#include "displayGUI.h"
    
void DisplayGUI_AlexKidd(void);

void DisplayGUI_AlexKidd_UpdateChosenMode(char* newModeName);

void DisplayGUI_AlexKidd_UpdateMotors(uint8_t m1on, uint8_t m2on, uint8_t m3on, uint8_t m4on);

void DisplayGUI_AlexKidd_UpdateBattery(uint8_t newBattLevelPercent);

void DisplayGUI_AlexKidd_UpdateSignal(uint8_t newSignalLevelPercent);
    
    
#endif // __DISPGUIAK_H__

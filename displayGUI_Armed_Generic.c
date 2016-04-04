#include "displayGUI_Armed_Generic.h"

void DisplayGUI_Armed_Generic(void) {

  DisplayGUI_Quad(90,115);
  
}

void DisplayGUI_Armed_Generic_UpdateChosenMode(const char* ModeName) {
    uint16_t i = 0;
    while(ModeName[i] > 0) i++;
    Display_FillRect(239-57+2, 168, 111, 9, ILI9341_WHITE);
    Display_WriteString(ModeName, 1, 239-i*6/2+1, 169, ILI9341_BLACK, ILI9341_WHITE);
}

void DisplayGUI_Armed_Generic_UpdateBattery(uint8_t newBattLevelPercent) {
  DisplayGUI_BatteryLevel(newBattLevelPercent);
}

void DisplayGUI_Armed_Generic_UpdateSignal(uint8_t newSignalLevelPercent) {
  DisplayGUI_SignalLevel(newSignalLevelPercent);
}

/* [] END OF FILE */

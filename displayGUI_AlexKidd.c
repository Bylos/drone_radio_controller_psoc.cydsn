#include "displayGUI_AlexKidd.h"

void DisplayGUI_AlexKidd(void) {

  DisplayGUI_Quad(90,115);
  
  uint8_t activeDoFs [10] = {1,1,1,1,0,0,0,0,0,0};
  DisplayGUI_RemoteController(239,80,1,activeDoFs);
  Display_WriteString("TEST MOTORS WITH", 1, 192, 45, ILI9341_WHITE, ILI9341_BLACK);
  Display_WriteString("LEFT JOYSTICK", 1, 201, 55, ILI9341_WHITE, ILI9341_BLACK);

  uint8_t activeDoFs2 [10] = {0,0,0,0,0,0,0,1,1,1};
  DisplayGUI_RemoteController(239,145,1,activeDoFs2);
  Display_WriteString("CHOOSE MODE WITH", 1, 193, 110, ILI9341_WHITE, ILI9341_BLACK);
  Display_WriteString("RIGHT JOYSTICK", 1, 199, 120, ILI9341_WHITE, ILI9341_BLACK);

  Display_FillRect(239-57+2, 168, 111, 9, ILI9341_WHITE);
  Display_WriteString("ACCEL. CALIBRATION", 1, 186, 169, ILI9341_BLACK, ILI9341_WHITE);
  Display_FillTriangle (239+58,169,239+58,175,239+58+5,172, ILI9341_GREY3);
  Display_FillTriangle (239-58,169,239-58,175,239-58-5,172, ILI9341_GREY3);

  Display_WriteString("RIGHT CLICK TO ENGAGE", 1, 178, 188, ILI9341_RED, ILI9341_BLACK);
  Display_WriteString("LEFT CLICK TO STANDBY", 1, 178, 198, ILI9341_BLUE, ILI9341_BLACK);
}

void DisplayGUI_AlexKidd_UpdateChosenMode(char* newModeName) {
    uint16_t i = 0;
    while(newModeName[i] > 0) i++;
    Display_FillRect(239-57+2, 168, 111, 9, ILI9341_WHITE);
    Display_WriteString(newModeName, 1, 239-i*6/2+1, 169, ILI9341_BLACK, ILI9341_WHITE);
}

void DisplayGUI_AlexKidd_UpdateBattery(uint8_t newBattLevelPercent) {
  DisplayGUI_BatteryLevel(newBattLevelPercent);
}

void DisplayGUI_AlexKidd_UpdateSignal(uint8_t newSignalLevelPercent) {
  DisplayGUI_SignalLevel(newSignalLevelPercent);
}

/* [] END OF FILE */

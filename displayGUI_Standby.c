#include "displayGUI_Standby.h"
#include "main.h"

void DisplayGUI_Seeking(void) {
  uint8_t activeDoFs [10] = {0,0,0,0,0,0,0,0,0,0};
  DisplayGUI_RemoteController(239,125,1,activeDoFs);
  Display_WriteString("QUADCOPTER", 1, 210, 65, ILI9341_WHITE, ILI9341_BLACK);
  Display_WriteString("NOT FOUND", 1, 213, 75, ILI9341_WHITE, ILI9341_BLACK);

  Display_WriteString("WAIT FOR QUAD DETECTION", 1, 171, 170, ILI9341_RED, ILI9341_BLACK);
}

void DisplayGUI_Standby(void) {
  DisplayGUI_Mode(MODE_STANDBY);
  Display_FillRect(0, 25, 320, 189, ILI9341_BLACK);

  uint8_t activeDoFs [10] = {0,0,0,0,0,0,0,0,0,1};
  DisplayGUI_RemoteController(239,100,1,activeDoFs);
  Display_WriteString("RIGHT CLICK TO ARM", 1, 186, 130, ILI9341_RED, ILI9341_BLACK);
}

void DisplayGUI_ControlMode(void) {
    switch (Joystick_GetMode()) {
        case MODE_1:
            Display_FillRoundRect(15, 40, 100, 25, 5, ILI9341_BLUE);
            Display_DrawRoundRect(15, 40, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 1", 2, 30, 46, ILI9341_WHITE, ILI9341_BLUE);
            Display_FillRoundRect(15, 80, 100, 25, 5, ILI9341_BLACK);
            Display_DrawRoundRect(15, 80, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 2", 2, 30, 86, ILI9341_WHITE, ILI9341_BLACK);
            break;
        case MODE_2:
            Display_FillRoundRect(15, 40, 100, 25, 5, ILI9341_BLACK);
            Display_DrawRoundRect(15, 40, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 1", 2, 30, 46, ILI9341_WHITE, ILI9341_BLACK);
            Display_FillRoundRect(15, 80, 100, 25, 5, ILI9341_BLUE);
            Display_DrawRoundRect(15, 80, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 2", 2, 30, 86, ILI9341_WHITE, ILI9341_BLUE);
            break;
        default: // default is MODE_1
            Display_FillRoundRect(15, 40, 100, 25, 5, ILI9341_BLUE);
            Display_DrawRoundRect(15, 40, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 1", 2, 30, 46, ILI9341_WHITE, ILI9341_BLUE);
            Display_FillRoundRect(15, 80, 100, 25, 5, ILI9341_BLACK);
            Display_DrawRoundRect(15, 80, 100, 25, 5, ILI9341_WHITE);
            Display_WriteString("MODE 2", 2, 30, 86, ILI9341_WHITE, ILI9341_BLACK);
            break;
    }
}
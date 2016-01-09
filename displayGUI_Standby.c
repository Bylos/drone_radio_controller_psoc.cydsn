#include "displayGUI_Standby.h"


void DisplayGUI_Standby(void) {

  uint8_t activeDoFs [10] = {0,0,0,0,0,0,0,0,0,0};
  DisplayGUI_RemoteController(239,125,1,activeDoFs);
  Display_WriteString("QUADCOPTER", 1, 210, 65, ILI9341_WHITE, ILI9341_BLACK);
  Display_WriteString("NOT FOUND", 1, 213, 75, ILI9341_WHITE, ILI9341_BLACK);

  Display_WriteString("WAIT FOR QUAD DETECTION", 1, 171, 170, ILI9341_RED, ILI9341_BLACK);
}

void DisplayGUI_Standby_UpdateQuadFound(void) {
  DisplayGUI_Mode(1);
  DisplayGUI_Quad(90,115);
  Display_FillRect(170, 50, 150, 160, ILI9341_BLACK);

  uint8_t activeDoFs [10] = {0,0,0,0,0,0,0,0,0,1};
  DisplayGUI_RemoteController(239,100,1,activeDoFs);
  Display_WriteString("RIGHT CLICK TO ARM", 1, 186, 130, ILI9341_RED, ILI9341_BLACK);
}

void DisplayGUI_Standby_UpdateQuadLost(void) {
  Display_FillRect(0, 30, 320, 180, ILI9341_BLACK);
  uint8_t activeDoFs [10] = {0,0,0,0,0,0,0,0,0,0};
  DisplayGUI_RemoteController(239,125,1,activeDoFs);
  Display_WriteString("QUADCOPTER", 1, 210, 65, ILI9341_WHITE, ILI9341_BLACK);
  Display_WriteString("NOT FOUND", 1, 213, 75, ILI9341_WHITE, ILI9341_BLACK);

  Display_WriteString("WAIT FOR QUAD DETECTION", 1, 171, 170, ILI9341_RED, ILI9341_BLACK);
}


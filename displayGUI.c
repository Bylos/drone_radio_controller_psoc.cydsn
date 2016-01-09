#include "displayGUI.h"
#include "stdio.h"

////////////////////////////////////////////////////////////////
//           Fonctions d'affichage du drone                   //
////////////////////////////////////////////////////////////////
void DisplayGUI_Mode (uint8_t modeID){
    if(modeID==0){
        Display_FillRect(0, 0, 320, 25,ILI9341_GREEN);
        Display_WriteString("MODE: SEEKING ...", 2, 50, 6, ILI9341_BLACK, ILI9341_GREEN);
	}
    if(modeID==1){
        Display_FillRect(0, 0, 320, 25,ILI9341_GREEN);
        Display_WriteString("MODE: STANDBY", 2, 50, 6, ILI9341_BLACK, ILI9341_GREEN);
	}
    if(modeID==2){
        Display_FillRect(0, 0, 320, 25,ILI9341_RED);
        Display_FillTriangle (14,3,5,22,23,22, ILI9341_BLACK);
        Display_FillTriangle (14,7,8,20,20,20, ILI9341_RED);
        Display_FillTriangle (13,11,15,11,14,16, ILI9341_BLACK);
        Display_FillCircle(14, 19, 2, ILI9341_BLACK);

        Display_FillTriangle (306,3,315,22,297,22, ILI9341_BLACK);
        Display_FillTriangle (306,7,312,20,300,20, ILI9341_RED);
        Display_FillTriangle (305,11,307,11,306,16, ILI9341_BLACK);
        Display_FillCircle(306, 19, 2, ILI9341_BLACK);

        Display_WriteString("MODE: TESTING MOTORS", 2, 41, 6, ILI9341_BLACK, ILI9341_RED);
	}
}




void DisplayGUI_BatteryLevel (uint8_t battLevelPercent){
    char buff[50];
    sprintf(buff,"BATTERY %3d%%",battLevelPercent);

    if (battLevelPercent<=20){
        Display_FillRect(0, 215, 159, 25, ILI9341_RED);
        Display_WriteString(buff, 2, 7, 220, ILI9341_BLACK, ILI9341_RED);
	} else if(battLevelPercent<=40){
        Display_FillRect(0, 215, 159, 25, ILI9341_ORANGE);
        Display_WriteString(buff, 2, 7, 220, ILI9341_BLACK, ILI9341_ORANGE);
	} else if(battLevelPercent<=60){
        Display_FillRect(0, 215, 159, 25, ILI9341_YELLOW);
        Display_WriteString(buff, 2, 7, 220, ILI9341_BLACK, ILI9341_YELLOW);
	} else if(battLevelPercent<=80){
        Display_FillRect(0, 215, 159, 25, ILI9341_GREENYELLOW);
        Display_WriteString(buff, 2, 7, 220, ILI9341_BLACK, ILI9341_GREENYELLOW);
	} else if(battLevelPercent<=100){
        Display_FillRect(0, 215, 159, 25, ILI9341_GREEN);
        Display_WriteString(buff, 2, 7, 220, ILI9341_BLACK, ILI9341_GREEN);
	} else{
        Display_FillRect(0, 215, 160, 25, ILI9341_WHITE);
        Display_FillRect(2, 217, 157, 21, ILI9341_BLACK);
        Display_WriteString("BATTERY ?", 2, 7, 220, ILI9341_WHITE, ILI9341_BLACK);
	}
}



void DisplayGUI_SignalLevel (uint8_t signalLevelPercent){
    char buffer[50];
    sprintf(buffer,"SIGNAL %3d%%",signalLevelPercent);

    if (signalLevelPercent<=20){
        Display_FillRect(161, 215, 159, 25, ILI9341_RED);
        Display_WriteString(buffer, 2, 175, 220, ILI9341_BLACK, ILI9341_RED);
	} else if(signalLevelPercent<=40){
        Display_FillRect(161, 215, 159, 25, ILI9341_ORANGE);
        Display_WriteString(buffer, 2, 175, 220, ILI9341_BLACK, ILI9341_ORANGE);
	} else if(signalLevelPercent<=60){
        Display_FillRect(161, 215, 159, 25, ILI9341_YELLOW);
        Display_WriteString(buffer, 2, 175, 220, ILI9341_BLACK, ILI9341_YELLOW);
	} else if(signalLevelPercent<=80){
        Display_FillRect(161, 215, 159, 25, ILI9341_GREENYELLOW);
        Display_WriteString(buffer, 2, 175, 220, ILI9341_BLACK, ILI9341_GREENYELLOW);
	} else if(signalLevelPercent<=100){
        Display_FillRect(161, 215, 159, 25, ILI9341_GREEN);
        Display_WriteString(buffer, 2, 175, 220, ILI9341_BLACK, ILI9341_GREEN);
	} else {
        Display_FillRect(160, 215, 160, 25, ILI9341_WHITE);
        Display_FillRect(161, 217, 157, 21, ILI9341_BLACK);
        Display_WriteString("SIGNAL ?", 2, 175, 220, ILI9341_WHITE, ILI9341_BLACK);
	}
}
    


void DisplayGUI_Quad (uint16_t x_pos, uint16_t y_pos){

    //arrow direction
    Display_FillRect(x_pos-2, y_pos-8-50, 5, 16, ILI9341_GREY3);
    Display_FillTriangle (x_pos, y_pos-8-60,  x_pos-5, y_pos-8-60+10,  x_pos+5, y_pos-8-60+10, ILI9341_GREY3)  ;

    //antenna
    Display_FillCircle(x_pos, y_pos+55, 22, ILI9341_GREY3);
    Display_FillCircle(x_pos, y_pos+55, 17, ILI9341_BLACK);
    Display_FillCircle(x_pos, y_pos+55, 14, ILI9341_GREY3);
    Display_FillCircle(x_pos, y_pos+55, 12, ILI9341_BLACK);
    Display_FillCircle(x_pos, y_pos+55, 9, ILI9341_GREY3);
    Display_FillCircle(x_pos, y_pos+55, 7, ILI9341_BLACK);
    Display_FillRect(x_pos-30, y_pos+55-30, 60, 30, ILI9341_BLACK);
    Display_FillTriangle (x_pos, y_pos+55,  x_pos+22, y_pos+55,  x_pos+22, y_pos+55+22, ILI9341_BLACK);
    Display_FillTriangle (x_pos, y_pos+55,  x_pos-22, y_pos+55,  x_pos-22, y_pos+55+22, ILI9341_BLACK);
    Display_FillRect(x_pos-2, y_pos-8+45, 5, 16, ILI9341_GREY3);

    //frame
    Display_FillTriangle (x_pos-40, y_pos-40, x_pos, y_pos-10,  x_pos, y_pos-20, ILI9341_GREY2);    //1, HG
    Display_FillTriangle (x_pos+40, y_pos-40, x_pos, y_pos-10,  x_pos, y_pos-20, ILI9341_GREY2);    //2, HD
    Display_FillTriangle (x_pos+40, y_pos+40, x_pos, y_pos+10,  x_pos, y_pos+20, ILI9341_GREY2);    //3, BD
    Display_FillTriangle (x_pos-40, y_pos+40, x_pos, y_pos+10,  x_pos, y_pos+20, ILI9341_GREY2);    //4, BG

    Display_FillRoundRect(x_pos-15, y_pos-37, 30, 74, 8, ILI9341_BLACK);
    Display_FillRoundRect(x_pos-13, y_pos-35, 26, 70, 6, ILI9341_GREY3);

    //helice HG
    Display_FillCircle(x_pos-40, y_pos-40, 22, ILI9341_BLACK);
    Display_FillCircle(x_pos-40, y_pos-40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos-40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40-14,y_pos-40-2,x_pos-40-14-3,y_pos-40+2,x_pos-40-14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40+14,y_pos-40+2,x_pos-40+14-3,y_pos-40-2,x_pos-40+14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("1", 1, x_pos-40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);

    //helice HD
    Display_FillCircle(x_pos+40, y_pos-40, 22, ILI9341_BLACK);
    Display_FillCircle(x_pos+40, y_pos-40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos+40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40+14,y_pos-40-2,x_pos+40+14-3,y_pos-40+2,x_pos+40+14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40-14,y_pos-40+2,x_pos+40-14-3,y_pos-40-2,x_pos+40-14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("2", 1, x_pos+40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);

    //helice BD
    Display_FillCircle(x_pos+40, y_pos+40, 22, ILI9341_BLACK);
    Display_FillCircle(x_pos+40, y_pos+40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos+40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40-14,y_pos+40-2,x_pos+40-14-3,y_pos+40+2,x_pos+40-14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40+14,y_pos+40+2,x_pos+40+14-3,y_pos+40-2,x_pos+40+14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("3", 1, x_pos+40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);

    //helice BG
    Display_FillCircle(x_pos-40, y_pos+40, 22, ILI9341_BLACK);
    Display_FillCircle(x_pos-40, y_pos+40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos-40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40+14,y_pos+40-2,x_pos-40+14-3,y_pos+40+2,x_pos-40+14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40-14,y_pos+40+2,x_pos-40-14-3,y_pos+40-2,x_pos-40-14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("4", 1, x_pos-40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);
}




void DisplayGUI_QuadMotorHighlight (uint16_t x_pos, uint16_t y_pos, uint8_t mon[4]){

  if(mon[0]){
    Display_FillCircle(x_pos-40, y_pos-40, 20, ILI9341_GREEN);
    Display_FillCircle(x_pos-40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40-14,y_pos-40-2,x_pos-40-14-3,y_pos-40+2,x_pos-40-14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40+14,y_pos-40+2,x_pos-40+14-3,y_pos-40-2,x_pos-40+14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("1", 1, x_pos-40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);
  } else {
    Display_FillCircle(x_pos-40, y_pos-40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos-40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40-14,y_pos-40-2,x_pos-40-14-3,y_pos-40+2,x_pos-40-14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40+14,y_pos-40+2,x_pos-40+14-3,y_pos-40-2,x_pos-40+14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("1", 1, x_pos-40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);
  }
  
  if(mon[1]){
    Display_FillCircle(x_pos+40, y_pos-40, 20, ILI9341_GREEN);
    Display_FillCircle(x_pos+40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40+14,y_pos-40-2,x_pos+40+14-3,y_pos-40+2,x_pos+40+14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40-14,y_pos-40+2,x_pos+40-14-3,y_pos-40-2,x_pos+40-14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("2", 1, x_pos+40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);
  } else {
    Display_FillCircle(x_pos+40, y_pos-40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos+40, y_pos-40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40+14,y_pos-40-2,x_pos+40+14-3,y_pos-40+2,x_pos+40+14+3,y_pos-40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40-14,y_pos-40+2,x_pos+40-14-3,y_pos-40-2,x_pos+40-14+3,y_pos-40-2, ILI9341_GREY1);
    Display_WriteString("2", 1, x_pos+40-2, y_pos-40-3, ILI9341_WHITE, ILI9341_BLACK);
  }
  
  if(mon[2]){
    Display_FillCircle(x_pos+40, y_pos+40, 20, ILI9341_GREEN);
    Display_FillCircle(x_pos+40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40-14,y_pos+40-2,x_pos+40-14-3,y_pos+40+2,x_pos+40-14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40+14,y_pos+40+2,x_pos+40+14-3,y_pos+40-2,x_pos+40+14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("3", 1, x_pos+40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);
  } else{
    Display_FillCircle(x_pos+40, y_pos+40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos+40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos+40-14,y_pos+40-2,x_pos+40-14-3,y_pos+40+2,x_pos+40-14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos+40+14,y_pos+40+2,x_pos+40+14-3,y_pos+40-2,x_pos+40+14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("3", 1, x_pos+40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);
  }
  
  if(mon[3]){
    Display_FillCircle(x_pos-40, y_pos+40, 20, ILI9341_GREEN);
    Display_FillCircle(x_pos-40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40+14,y_pos+40-2,x_pos-40+14-3,y_pos+40+2,x_pos-40+14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40-14,y_pos+40+2,x_pos-40-14-3,y_pos+40-2,x_pos-40-14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("4", 1, x_pos-40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);
  } else{
    Display_FillCircle(x_pos-40, y_pos+40, 20, ILI9341_GREY3);
    Display_FillCircle(x_pos-40, y_pos+40, 8, ILI9341_BLACK);
    Display_FillTriangle (x_pos-40+14,y_pos+40-2,x_pos-40+14-3,y_pos+40+2,x_pos-40+14+3,y_pos+40+2, ILI9341_GREY1);
    Display_FillTriangle (x_pos-40-14,y_pos+40+2,x_pos-40-14-3,y_pos+40-2,x_pos-40-14+3,y_pos+40-2, ILI9341_GREY1);
    Display_WriteString("4", 1, x_pos-40-2, y_pos+40-3, ILI9341_WHITE, ILI9341_BLACK);
  }
}
  
  


void DisplayGUI_RemoteController (uint16_t x_pos, uint16_t y_pos, uint8_t scale, uint8_t activeDoFs[10]){
    Display_FillRect(x_pos-scale*35, y_pos-scale*15, scale*70, scale*30, ILI9341_GREY3);
    Display_FillRect(x_pos-scale*8, y_pos-scale*7, scale*17, scale*14, ILI9341_BLACK);
    Display_FillRect(x_pos-scale*7, y_pos-scale*6, scale*15, scale*12, ILI9341_WHITE);
    
    Display_FillCircle(x_pos-scale*22, y_pos, scale*6, ILI9341_BLACK);
    Display_FillCircle(x_pos+scale*22, y_pos, scale*6, ILI9341_BLACK);

    //left joystick, top-bottom
    if(activeDoFs[0]){
        Display_FillRect(x_pos-scale*(22+1), y_pos-scale*(4+3), scale*2+1, scale*4, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*22, y_pos-scale*(4+3+5),  x_pos-scale*(22+3), y_pos-scale*(4+3)-1,  x_pos-scale*(22-3), y_pos-scale*(4+3)-1, ILI9341_RED);
	}
    if(activeDoFs[1]){
        Display_FillRect(x_pos-scale*(22+1), y_pos+scale*(3)+1, scale*2+1, scale*4, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*22, y_pos+scale*(4+3+5),  x_pos-scale*(22+3), y_pos+scale*(4+3)+1,  x_pos-scale*(22-3), y_pos+scale*(4+3)+1, ILI9341_RED);
	}

    //left joystick, left-right
    if(activeDoFs[2]){
        Display_FillRect(x_pos-scale*(22+4+3), y_pos-scale*(1), scale*4, scale*2+1, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*(22+4+3+5), y_pos,  x_pos-scale*(22+4+3)-1, y_pos-scale*(3),  x_pos-scale*(22+4+3)-1, y_pos-scale*(-3), ILI9341_RED);
	}
    if(activeDoFs[3]){
        Display_FillRect(x_pos-scale*(22-3)+1, y_pos-scale*(1), scale*4, scale*2+1, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*(22-4-3-5), y_pos,  x_pos-scale*(22-4-3)+1, y_pos-scale*(3),  x_pos-scale*(22-4-3)+1, y_pos-scale*(-3), ILI9341_RED);
	}

    //left joystick, click
    if(activeDoFs[4]){
        Display_FillCircle(x_pos-scale*22, y_pos, scale*3, ILI9341_RED);
	}
    
    //right joystick, top-bottom
    if(activeDoFs[5]){
        Display_FillRect(x_pos-scale*(-22+1), y_pos-scale*(4+3), scale*2+1, scale*4, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*-22, y_pos-scale*(4+3+5),  x_pos-scale*(-22+3), y_pos-scale*(4+3)-1,  x_pos-scale*(-22-3), y_pos-scale*(4+3)-1, ILI9341_RED);
	}
    if(activeDoFs[6]){
        Display_FillRect(x_pos-scale*(-22+1), y_pos+scale*(3)+1, scale*2+1, scale*4, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*-22, y_pos+scale*(4+3+5),  x_pos-scale*(-22+3), y_pos+scale*(4+3)+1,  x_pos-scale*(-22-3), y_pos+scale*(4+3)+1, ILI9341_RED);
	}

    //right joystick, left-right
    if(activeDoFs[7]){
        Display_FillRect(x_pos-scale*(-22+4+3), y_pos-scale*(1), scale*4, scale*2+1, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*(-22+4+3+5), y_pos,  x_pos-scale*(-22+4+3)-1, y_pos-scale*(3),  x_pos-scale*(-22+4+3)-1, y_pos-scale*(-3), ILI9341_RED);
	}
    if(activeDoFs[8]){
        Display_FillRect(x_pos-scale*(-22-3)+1, y_pos-scale*(1), scale*4, scale*2+1, ILI9341_RED);
        Display_FillTriangle (x_pos-scale*(-22-4-3-5), y_pos,  x_pos-scale*(-22-4-3)+1, y_pos-scale*(3),  x_pos-scale*(-22-4-3)+1, y_pos-scale*(-3), ILI9341_RED);
	}

    //right joystick, click
    if(activeDoFs[9]){
        Display_FillCircle(x_pos+scale*22, y_pos, scale*3, ILI9341_RED);
	}
}

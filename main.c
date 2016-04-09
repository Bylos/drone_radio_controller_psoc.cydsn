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

#include "main.h"

/*******************************************************************************
* Main Function
*******************************************************************************/
int main()
{
	/* State Machine Variables */
	uint8_t mode = MODE_BOOT;
	uint8_t next_mode = MODE_SEEKING;
	uint8_t rx_timeout;
	
	/* Enable Global Interrupts */
	CyGlobalIntEnable;
	
	/* Controller Initialization */
	Hardware_Init();
	
	/* Infinite Loop */
	for(;;) {
		
		/* Zigbee data polling ! */
		rx_timeout = Zigbee_GetFrame();
		if (rx_timeout) {
			next_mode = MODE_SEEKING;
		}
		
        /* Check for new drone mode */
        if (Zigbee_GetDroneModeFlag()) {
        	next_mode = Zigbee_GetDroneMode();
        }
    
		if (mode != next_mode) {
			switch (next_mode) {
			case MODE_SEEKING:
				Mode_Seeking_Init();
				break;
			case MODE_STANDBY:
				Mode_Standby_Init();
				break;
			case MODE_ALEXKIDD:
				Mode_AlexKidd_Init();
				break;
            case MODE_ACC_CAL:
            case MODE_GYR_CAL:
            case MODE_MAG_CAL:
            case MODE_ALEXKIDD2:
            case MODE_ACRO:
            case MODE_STABILIZED:
                Mode_Armed_Generic_Init(next_mode);
                break;
			default:
				break;
			}
			mode = next_mode;
		}
		
		switch(mode) {
		case MODE_SEEKING:
			Mode_Seeking_Run();
			break;
		case MODE_STANDBY:
			Mode_Standby_Run();
			break;
		case MODE_ALEXKIDD:
			Mode_AlexKidd_Run();
            break;
        case MODE_ACC_CAL:
        case MODE_GYR_CAL:
        case MODE_MAG_CAL:
        case MODE_ALEXKIDD2:
        case MODE_ACRO:
        case MODE_STABILIZED:
            Mode_Armed_Generic_Run();
            break;
		default:
			break;
		}
		
		// Update signal strength
		if (Zigbee_GetRssiFlag()) {
			DisplayGUI_SignalLevel(Zigbee_GetRssi()*10/408);
		}
	}
}

/* [] END OF FILE */

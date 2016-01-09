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
			default:
				break;
			}
			mode = next_mode;
		}
		
		switch(mode) {
		case MODE_SEEKING:
			next_mode = Mode_Seeking_Run();
			break;
		case MODE_STANDBY:
			next_mode = Mode_Standby_Run();
			break;
		case MODE_ALEXKIDD:
			next_mode = Mode_AlexKidd_Run();
		default:
			break;
		}
	}
}

/* [] END OF FILE */

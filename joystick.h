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

#ifndef __JOYSTICK_H__
	#define __JOYSTICK_H__
	    
	#include <project.h>

	typedef struct {
		int16 right_y;
		int16 right_x;
		int16 left_y;
		int16 left_x;
	} joystick_t;
	
	void Joystick_SetValuesFlag(void);
	uint8_t Joystick_GetValuesFlag(void);
	void Joystick_SetValues(joystick_t joystick);
	joystick_t Joystick_GetValues(void); 
	void Joystick_ClearAllFlags(void);

	#endif // __JOYSTICK_H__

/* [] END OF FILE */

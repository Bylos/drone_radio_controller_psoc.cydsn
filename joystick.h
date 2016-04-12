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
	    
    #define MODE_1          0x01
    #define MODE_2          0x02
    
	#include <project.h>

	typedef struct {
		int16 right_y;
		int16 right_x;
		int16 left_y;
		int16 left_x;
	} joystick_t;
	
    typedef struct {
        int16 throttle;
        int16 roll;
        int16 pitch;
        int16 yaw;
    } control_t;
    
    void Joystick_SetMode(uint8_t mode);
    uint8_t Joystick_GetMode(void);
	void Joystick_SetValuesFlag(void);
	uint8_t Joystick_GetValuesFlag(void);
	void Joystick_SetValues(joystick_t joystick);
	joystick_t Joystick_GetValues(void); 
	void Joystick_ClearAllFlags(void);

	#endif // __JOYSTICK_H__

/* [] END OF FILE */

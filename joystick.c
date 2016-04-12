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

#include "joystick.h"

static uint8_t _joystick_flag = 0;
static joystick_t _joystick = {0, 0, 0, 0};
static uint8_t _mode = MODE_1;

void Joystick_SetMode(uint8_t mode) {
    _mode = mode;
}

uint8_t Joystick_GetMode(void) {
    return _mode;
}

void Joystick_ClearAllFlags(void) {
	_joystick_flag = 0;
}

void Joystick_SetValuesFlag(void) {
	_joystick_flag = 1;
}

uint8_t Joystick_GetValuesFlag(void) {
	return _joystick_flag;
}

void Joystick_SetValues(joystick_t joystick) {
	_joystick = joystick;
}

joystick_t Joystick_GetValues(void) {
	_joystick_flag = 0;
	return _joystick;
}

/* [] END OF FILE */

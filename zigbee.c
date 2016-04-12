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

#include "zigbee.h"

static uint8_t buffer[64];

static uint16_t _rx_timer = 0;
static uint8_t _rx_timer_flag = 0;

static uint8_t _drone_mode_flag = 0;
static uint8_t _drone_mode = 0;

static uint16_t _rssi = 0;
static uint8_t _rssi_flag = 0;

void Zigbee_ClearAllFlags(void) {
	_rx_timer_flag = 0;
	_drone_mode_flag = 0;
	_rssi_flag = 0;
}

void Zigbee_TimerAdd(uint16_t time_ms) {
	_rx_timer += time_ms;
	if (_rx_timer >= RX_TIMEOUT_MS) {
		_rx_timer_flag = 1;
		_rx_timer = 0;
	}
}

uint8_t Zigbee_GetTimeoutFlag(void) {
	return _rx_timer_flag;
}

uint8_t Zigbee_GetDroneModeFlag(void) {
	return _drone_mode_flag;
}

uint8_t Zigbee_GetDroneMode(void) {
	_drone_mode_flag = 0;
	return _drone_mode;
}

uint8_t Zigbee_GetFrame(void) {
	uint8_t rx_data;
	uint8_t rx_length;
	uint8_t rx_crc;
	int i;
	
	// Check for a preamble
	if (UART_GetRxBufferSize() < 2) {
		return _rx_timer_flag;
	}
	rx_data = UART_GetByte();
	if (rx_data != 0xFF) {
		return _rx_timer_flag;
	}
	rx_data = UART_GetByte();
	if (rx_data != 0xFF) {
		return _rx_timer_flag;
	}
	
	// Wait for buffer length
	while (!UART_GetRxBufferSize());
	rx_length = UART_GetByte();
	
	// Read buffer
	for (i=0; i<rx_length; i++) {
		while (!UART_GetRxBufferSize());
		buffer[i] = UART_GetByte();
	}
	
	// Check crc
	while (!UART_GetRxBufferSize());
	rx_crc = UART_GetByte();
	if (rx_crc != CRC_Fast(buffer, rx_length)) {
		return _rx_timer_flag;
	}
	
	// Check frame type
	switch (buffer[0]) {
		case RX_FRAME_MODE:
			_drone_mode = buffer[1];
			_drone_mode_flag = 1;
			break;
		default:
			break;
	}
	
	// Reset timeout
	_rx_timer = 0;
	_rx_timer_flag = 0;
	return _rx_timer_flag;
}

#define PREAMBLE_SIZE	3
uint8_t preamble[PREAMBLE_SIZE] = {
		0xFF, 0xFF, //0xFF, 0xFF, 0xFF, 0xFF,
		0x00};

void Zigbee_SendCommand(uint8_t command) {
	uint8_t buffer[3] = {command, 0x00, 0x00};
	preamble[PREAMBLE_SIZE-1] = 0x02;
	buffer[2] = CRC_Fast(buffer, 2);
	UART_PutArray(preamble, PREAMBLE_SIZE);
	UART_PutArray(buffer, 3);
}

void Zigbee_SendJoystick(joystick_t joystick) {
	uint8_t frame[12] = {
		0xFF, 0xFF, 0x08,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00};
    control_t control = {0, 0, 0, 0};
    switch (Joystick_GetMode()) {
        case MODE_1:
            control.throttle = (joystick.right_y & ~(RC_CHANNEL_MASK)) | (RC_THROTTLE << RC_CHANNEL_SHIFT);
            control.yaw      = (joystick.left_x  & ~(RC_CHANNEL_MASK)) | (RC_YAW      << RC_CHANNEL_SHIFT);
            control.pitch    = (joystick.left_y  & ~(RC_CHANNEL_MASK)) | (RC_PITCH    << RC_CHANNEL_SHIFT);
            control.roll     = (joystick.right_x & ~(RC_CHANNEL_MASK)) | (RC_ROLL     << RC_CHANNEL_SHIFT);
        break;
        case MODE_2:
            control.throttle = (joystick.left_y  & ~(RC_CHANNEL_MASK)) | (RC_THROTTLE << RC_CHANNEL_SHIFT);
            control.yaw      = (joystick.left_x  & ~(RC_CHANNEL_MASK)) | (RC_YAW      << RC_CHANNEL_SHIFT);
            control.pitch    = (joystick.right_y & ~(RC_CHANNEL_MASK)) | (RC_PITCH    << RC_CHANNEL_SHIFT);
            control.roll     = (joystick.right_x & ~(RC_CHANNEL_MASK)) | (RC_ROLL     << RC_CHANNEL_SHIFT);            
        break;
        default: // default is MODE_1
            control.throttle = (joystick.right_y & ~(RC_CHANNEL_MASK)) | (RC_THROTTLE << RC_CHANNEL_SHIFT);
            control.yaw      = (joystick.left_x  & ~(RC_CHANNEL_MASK)) | (RC_YAW      << RC_CHANNEL_SHIFT);
            control.pitch    = (joystick.left_y  & ~(RC_CHANNEL_MASK)) | (RC_PITCH    << RC_CHANNEL_SHIFT);
            control.roll     = (joystick.right_x & ~(RC_CHANNEL_MASK)) | (RC_ROLL     << RC_CHANNEL_SHIFT);
        break;
    }
	memcpy(&frame[3], &control, 8);
	frame[11] = CRC_Fast(&frame[3], 8);
	UART_PutArray(frame, 12);
}

void Zigbee_SetRssiFlag(void) {
	_rssi_flag = 1;
}

uint8_t Zigbee_GetRssiFlag(void) {
	return _rssi_flag;
}

void Zigbee_SetRssi(uint16_t rssi) {
	_rssi = rssi;
}

uint16_t Zigbee_GetRssi(void) {
	_rssi_flag = 0;
	return _rssi;
}

/* [] END OF FILE */

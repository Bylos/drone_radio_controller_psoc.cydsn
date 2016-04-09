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

#include "hardware.h"

/*******************************************************************************
* Interrupts
*******************************************************************************/
static uint8_t _jl_sel_flag = 0;
static uint8_t _jl_debounce = 0;

static uint8_t _jr_sel_flag = 0;
static uint8_t _jr_debounce = 0;

static uint8_t _xbee_rssi_delay = 0;

static uint8_t _adc_flag = 0;

void Hardware_ClearAllFlags(void) {
	_jl_sel_flag = 0;
	_jr_sel_flag = 0;
	_adc_flag = 0;
}

CY_ISR(JL_SEL_Interrupt) {
	if (!_jl_debounce) {
		_jl_debounce = DEBOUNCE_COUNT;
		_jl_sel_flag = 1;
	}
}

uint8_t Hardware_GetLeftClickFlag(void) {
	if (_jl_sel_flag) {
		_jl_sel_flag = 0;
		return 1;
	}
	return 0;
}

CY_ISR(JR_SEL_Interrupt) {
	if (!_jr_debounce) {
		_jr_debounce = DEBOUNCE_COUNT;
		_jr_sel_flag = 1;
	}
}

uint8_t Hardware_GetRightClickFlag(void) {
	if (_jr_sel_flag) {
		_jr_sel_flag = 0;
		return 1;
	}
	return 0;
}

CY_ISR(ADC_Interrupt) {
	joystick_t joystick = {
		.left_y = ADC_SAR_Seq_GetResult16(ADC_JOY_LEFT_Y),
		.left_x = - ADC_SAR_Seq_GetResult16(ADC_JOY_LEFT_X),
		.right_y = ADC_SAR_Seq_GetResult16(ADC_JOY_RIGHT_Y),
		.right_x = - ADC_SAR_Seq_GetResult16(ADC_JOY_RIGHT_X)
	};
	Joystick_SetValues(joystick);
	Joystick_SetValuesFlag();
	
	if (!_xbee_rssi_delay) {
		_xbee_rssi_delay = XBEE_RSSI_DELAY;
		uint16_t rssi = (uint16_t)((int32_t)ADC_SAR_Seq_GetResult16(ADC_ZB_RSSI)+2048);
		Zigbee_SetRssi(rssi);
		Zigbee_SetRssiFlag();
	}
	else {
		_xbee_rssi_delay --;
	}
	
	Zigbee_TimerAdd(ADC_PERIOD_MS);
	
	if (_jr_debounce) {
		_jr_debounce --;
	}
	if (_jl_debounce) {
		_jl_debounce --;
	}
	
	_adc_flag = 1;
}

uint8_t Hardware_GetAdcFlag(void) {
	if (_adc_flag) {
		_adc_flag = 0;
		return 1;
	}
	return 0;
}

/*******************************************************************************
* Modules Initialization
*******************************************************************************/
void Hardware_Init() {
	/* Initialize User Modules */
	CRC_Init();
	ADC_SAR_Seq_Start();
	TS_SPI_Start();
	TS_I2C_Start();
	UART_Start();
	
	/* Screen Init Sequence */
	Display_Init();
	
	/* Clear Transmission Buffers */
	UART_ClearRxBuffer();
	UART_ClearTxBuffer();
	
	isr_ADC_ClearPending();
	isr_JL_SEL_ClearPending();
	isr_JR_SEL_ClearPending();
	
	isr_ADC_StartEx(ADC_Interrupt);
	isr_JL_SEL_StartEx(JL_SEL_Interrupt);
	isr_JR_SEL_StartEx(JR_SEL_Interrupt);
	
	/* Start Joystick Sampling */
	ADC_SAR_Seq_StartConvert();
}

/* [] END OF FILE */

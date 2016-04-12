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

#include "touch.h"

uint8_t touches;
uint16_t touchX[2], touchY[2], touchID[2];

uint8_t readRegister8(uint8_t reg) {
uint8_t x ;
	TS_I2C_I2CMasterClearStatus();
	TS_I2C_I2CMasterWriteBuf(FT6206_ADDR, &reg, 1, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_WR_CMPLT));
	TS_I2C_I2CMasterReadBuf(FT6206_ADDR, &x, 1, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_RD_CMPLT));
	return x;
}

void writeRegister8(uint8_t reg, uint8_t val) {
	TS_I2C_I2CMasterClearStatus();
	TS_I2C_I2CMasterWriteBuf(FT6206_ADDR, &reg, 1, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_WR_CMPLT));
	TS_I2C_I2CMasterWriteBuf(FT6206_ADDR, &val, 1, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_WR_CMPLT));
}

uint8_t Touch_Begin(uint8_t thresh) {
	writeRegister8(FT6206_REG_THRESHHOLD, thresh);
	if ((readRegister8(FT6206_REG_VENDID) != 17) || (readRegister8(FT6206_REG_CHIPID) != 6))
		return 0;
	return 1;
}

uint8_t Touch_IsTouched(void) {
	uint8_t n = readRegister8(FT6206_REG_NUMTOUCHES);
	if ((n == 1) || (n == 2)) return 1;
	return 0;
}


void readData(point_t* p) {
	uint8_t i2cdat[32], i;
	uint8_t val = 0;
	TS_I2C_I2CMasterClearStatus();
	TS_I2C_I2CMasterWriteBuf(FT6206_ADDR, &val, 1, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_WR_CMPLT));
	TS_I2C_I2CMasterReadBuf(FT6206_ADDR, i2cdat, 32, TS_I2C_I2C_MODE_COMPLETE_XFER);
	while (!(TS_I2C_I2CMasterStatus() & TS_I2C_I2C_MSTAT_RD_CMPLT));
	touches = i2cdat[0x02];
	if (touches > 2) {
		touches = 0;
		p->x = p->y = 0;
	}
	if (touches == 0) {
		p->x = p->y = 0;
		return;
	}
	for (i=0; i<2; i++) {
		touchX[i] = i2cdat[0x03 + i*6] & 0x0F;
		touchX[i] <<= 8;
		touchX[i] |= i2cdat[0x04 + i*6]; 
		touchY[i] = i2cdat[0x05 + i*6] & 0x0F;
		touchY[i] <<= 8;
		touchY[i] |= i2cdat[0x06 + i*6];
		touchID[i] = i2cdat[0x05 + i*6] >> 4;
	}
	p->x = touchY[0]; p->y = 240-touchX[0];
}

point_t Touch_GetPoint(void) {
	point_t point;
	readData(&point);
	return point;
}

/* [] END OF FILE */

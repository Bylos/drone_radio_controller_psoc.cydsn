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

#include "crc.h"

#define POLYNOMIAL 0xD8
#define TOPBIT (1 << 7)
uint8_t crcTable[256];

void CRC_Init(void) {
	uint8_t remainder;
	int dividend;
	for (dividend = 0; dividend < 256; ++dividend) {
		remainder = dividend;
		uint8_t bit;
		for (bit = 8; bit > 0; --bit) {		
			if (remainder & TOPBIT) {
				remainder = (remainder << 1) ^ POLYNOMIAL;
			} else {
				remainder = (remainder << 1);
			}
		}
		crcTable[dividend] = remainder;
	}
}   /* crcInit() */

uint8_t CRC_Fast(uint8_t const message[], int nBytes) {
	uint8_t data;
	uint8_t remainder = 0;
	int byte;
	for (byte = 0; byte < nBytes; ++byte) {
		data = message[byte] ^ remainder;
		remainder = crcTable[data] ^ (remainder << 8);
	}
	return (remainder);
}   /* crcFast() */

/* [] END OF FILE */

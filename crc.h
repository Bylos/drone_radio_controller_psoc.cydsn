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

#ifndef __CRC_H__
	#define __CRC_H__
	
	#include <project.h>
	
	void CRC_Init(void);
	uint8_t CRC_Fast(uint8_t const message[], int nBytes);
	
	#endif // __CRC_H__

/* [] END OF FILE */

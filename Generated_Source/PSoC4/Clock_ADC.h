/*******************************************************************************
* File Name: Clock_ADC.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_ADC_H)
#define CY_CLOCK_Clock_ADC_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock_ADC_StartEx(uint32 alignClkDiv);
#define Clock_ADC_Start() \
    Clock_ADC_StartEx(Clock_ADC__PA_DIV_ID)

#else

void Clock_ADC_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock_ADC_Stop(void);

void Clock_ADC_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_ADC_GetDividerRegister(void);
uint8  Clock_ADC_GetFractionalDividerRegister(void);

#define Clock_ADC_Enable()                         Clock_ADC_Start()
#define Clock_ADC_Disable()                        Clock_ADC_Stop()
#define Clock_ADC_SetDividerRegister(clkDivider, reset)  \
    Clock_ADC_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_ADC_SetDivider(clkDivider)           Clock_ADC_SetDividerRegister((clkDivider), 1u)
#define Clock_ADC_SetDividerValue(clkDivider)      Clock_ADC_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock_ADC_DIV_ID     Clock_ADC__DIV_ID

#define Clock_ADC_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock_ADC_CTRL_REG   (*(reg32 *)Clock_ADC__CTRL_REGISTER)
#define Clock_ADC_DIV_REG    (*(reg32 *)Clock_ADC__DIV_REGISTER)

#define Clock_ADC_CMD_DIV_SHIFT          (0u)
#define Clock_ADC_CMD_PA_DIV_SHIFT       (8u)
#define Clock_ADC_CMD_DISABLE_SHIFT      (30u)
#define Clock_ADC_CMD_ENABLE_SHIFT       (31u)

#define Clock_ADC_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock_ADC_CMD_DISABLE_SHIFT))
#define Clock_ADC_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock_ADC_CMD_ENABLE_SHIFT))

#define Clock_ADC_DIV_FRAC_MASK  (0x000000F8u)
#define Clock_ADC_DIV_FRAC_SHIFT (3u)
#define Clock_ADC_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock_ADC_DIV_INT_SHIFT  (8u)

#else 

#define Clock_ADC_DIV_REG        (*(reg32 *)Clock_ADC__REGISTER)
#define Clock_ADC_ENABLE_REG     Clock_ADC_DIV_REG
#define Clock_ADC_DIV_FRAC_MASK  Clock_ADC__FRAC_MASK
#define Clock_ADC_DIV_FRAC_SHIFT (16u)
#define Clock_ADC_DIV_INT_MASK   Clock_ADC__DIVIDER_MASK
#define Clock_ADC_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock_ADC_H) */

/* [] END OF FILE */

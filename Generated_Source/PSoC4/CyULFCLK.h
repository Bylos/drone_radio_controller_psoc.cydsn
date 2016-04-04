/*******************************************************************************
* File Name: CyULFCLK.h
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

#if !defined(CY_CLOCK_CyULFCLK_H)
#define CY_CLOCK_CyULFCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CyULFCLK_StartEx(uint32 alignClkDiv);
#define CyULFCLK_Start() \
    CyULFCLK_StartEx(CyULFCLK__PA_DIV_ID)

#else

void CyULFCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CyULFCLK_Stop(void);

void CyULFCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CyULFCLK_GetDividerRegister(void);
uint8  CyULFCLK_GetFractionalDividerRegister(void);

#define CyULFCLK_Enable()                         CyULFCLK_Start()
#define CyULFCLK_Disable()                        CyULFCLK_Stop()
#define CyULFCLK_SetDividerRegister(clkDivider, reset)  \
    CyULFCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define CyULFCLK_SetDivider(clkDivider)           CyULFCLK_SetDividerRegister((clkDivider), 1u)
#define CyULFCLK_SetDividerValue(clkDivider)      CyULFCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CyULFCLK_DIV_ID     CyULFCLK__DIV_ID

#define CyULFCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CyULFCLK_CTRL_REG   (*(reg32 *)CyULFCLK__CTRL_REGISTER)
#define CyULFCLK_DIV_REG    (*(reg32 *)CyULFCLK__DIV_REGISTER)

#define CyULFCLK_CMD_DIV_SHIFT          (0u)
#define CyULFCLK_CMD_PA_DIV_SHIFT       (8u)
#define CyULFCLK_CMD_DISABLE_SHIFT      (30u)
#define CyULFCLK_CMD_ENABLE_SHIFT       (31u)

#define CyULFCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CyULFCLK_CMD_DISABLE_SHIFT))
#define CyULFCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CyULFCLK_CMD_ENABLE_SHIFT))

#define CyULFCLK_DIV_FRAC_MASK  (0x000000F8u)
#define CyULFCLK_DIV_FRAC_SHIFT (3u)
#define CyULFCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define CyULFCLK_DIV_INT_SHIFT  (8u)

#else 

#define CyULFCLK_DIV_REG        (*(reg32 *)CyULFCLK__REGISTER)
#define CyULFCLK_ENABLE_REG     CyULFCLK_DIV_REG
#define CyULFCLK_DIV_FRAC_MASK  CyULFCLK__FRAC_MASK
#define CyULFCLK_DIV_FRAC_SHIFT (16u)
#define CyULFCLK_DIV_INT_MASK   CyULFCLK__DIVIDER_MASK
#define CyULFCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CyULFCLK_H) */

/* [] END OF FILE */

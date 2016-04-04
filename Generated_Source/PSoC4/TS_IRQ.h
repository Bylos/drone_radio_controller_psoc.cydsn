/*******************************************************************************
* File Name: TS_IRQ.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TS_IRQ_H) /* Pins TS_IRQ_H */
#define CY_PINS_TS_IRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TS_IRQ_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TS_IRQ_Write(uint8 value) ;
void    TS_IRQ_SetDriveMode(uint8 mode) ;
uint8   TS_IRQ_ReadDataReg(void) ;
uint8   TS_IRQ_Read(void) ;
uint8   TS_IRQ_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TS_IRQ_DRIVE_MODE_BITS        (3)
#define TS_IRQ_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TS_IRQ_DRIVE_MODE_BITS))

#define TS_IRQ_DM_ALG_HIZ         (0x00u)
#define TS_IRQ_DM_DIG_HIZ         (0x01u)
#define TS_IRQ_DM_RES_UP          (0x02u)
#define TS_IRQ_DM_RES_DWN         (0x03u)
#define TS_IRQ_DM_OD_LO           (0x04u)
#define TS_IRQ_DM_OD_HI           (0x05u)
#define TS_IRQ_DM_STRONG          (0x06u)
#define TS_IRQ_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TS_IRQ_MASK               TS_IRQ__MASK
#define TS_IRQ_SHIFT              TS_IRQ__SHIFT
#define TS_IRQ_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TS_IRQ_PS                     (* (reg32 *) TS_IRQ__PS)
/* Port Configuration */
#define TS_IRQ_PC                     (* (reg32 *) TS_IRQ__PC)
/* Data Register */
#define TS_IRQ_DR                     (* (reg32 *) TS_IRQ__DR)
/* Input Buffer Disable Override */
#define TS_IRQ_INP_DIS                (* (reg32 *) TS_IRQ__PC2)


#if defined(TS_IRQ__INTSTAT)  /* Interrupt Registers */

    #define TS_IRQ_INTSTAT                (* (reg32 *) TS_IRQ__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TS_IRQ_DRIVE_MODE_SHIFT       (0x00u)
#define TS_IRQ_DRIVE_MODE_MASK        (0x07u << TS_IRQ_DRIVE_MODE_SHIFT)


#endif /* End Pins TS_IRQ_H */


/* [] END OF FILE */

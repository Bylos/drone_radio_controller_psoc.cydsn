/*******************************************************************************
* File Name: MoM_Lo.h  
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

#if !defined(CY_PINS_MoM_Lo_H) /* Pins MoM_Lo_H */
#define CY_PINS_MoM_Lo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MoM_Lo_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    MoM_Lo_Write(uint8 value) ;
void    MoM_Lo_SetDriveMode(uint8 mode) ;
uint8   MoM_Lo_ReadDataReg(void) ;
uint8   MoM_Lo_Read(void) ;
uint8   MoM_Lo_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MoM_Lo_DRIVE_MODE_BITS        (3)
#define MoM_Lo_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MoM_Lo_DRIVE_MODE_BITS))

#define MoM_Lo_DM_ALG_HIZ         (0x00u)
#define MoM_Lo_DM_DIG_HIZ         (0x01u)
#define MoM_Lo_DM_RES_UP          (0x02u)
#define MoM_Lo_DM_RES_DWN         (0x03u)
#define MoM_Lo_DM_OD_LO           (0x04u)
#define MoM_Lo_DM_OD_HI           (0x05u)
#define MoM_Lo_DM_STRONG          (0x06u)
#define MoM_Lo_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define MoM_Lo_MASK               MoM_Lo__MASK
#define MoM_Lo_SHIFT              MoM_Lo__SHIFT
#define MoM_Lo_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MoM_Lo_PS                     (* (reg32 *) MoM_Lo__PS)
/* Port Configuration */
#define MoM_Lo_PC                     (* (reg32 *) MoM_Lo__PC)
/* Data Register */
#define MoM_Lo_DR                     (* (reg32 *) MoM_Lo__DR)
/* Input Buffer Disable Override */
#define MoM_Lo_INP_DIS                (* (reg32 *) MoM_Lo__PC2)


#if defined(MoM_Lo__INTSTAT)  /* Interrupt Registers */

    #define MoM_Lo_INTSTAT                (* (reg32 *) MoM_Lo__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define MoM_Lo_DRIVE_MODE_SHIFT       (0x00u)
#define MoM_Lo_DRIVE_MODE_MASK        (0x07u << MoM_Lo_DRIVE_MODE_SHIFT)


#endif /* End Pins MoM_Lo_H */


/* [] END OF FILE */

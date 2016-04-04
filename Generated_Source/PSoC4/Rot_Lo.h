/*******************************************************************************
* File Name: Rot_Lo.h  
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

#if !defined(CY_PINS_Rot_Lo_H) /* Pins Rot_Lo_H */
#define CY_PINS_Rot_Lo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot_Lo_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot_Lo_Write(uint8 value) ;
void    Rot_Lo_SetDriveMode(uint8 mode) ;
uint8   Rot_Lo_ReadDataReg(void) ;
uint8   Rot_Lo_Read(void) ;
uint8   Rot_Lo_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot_Lo_DRIVE_MODE_BITS        (3)
#define Rot_Lo_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot_Lo_DRIVE_MODE_BITS))

#define Rot_Lo_DM_ALG_HIZ         (0x00u)
#define Rot_Lo_DM_DIG_HIZ         (0x01u)
#define Rot_Lo_DM_RES_UP          (0x02u)
#define Rot_Lo_DM_RES_DWN         (0x03u)
#define Rot_Lo_DM_OD_LO           (0x04u)
#define Rot_Lo_DM_OD_HI           (0x05u)
#define Rot_Lo_DM_STRONG          (0x06u)
#define Rot_Lo_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot_Lo_MASK               Rot_Lo__MASK
#define Rot_Lo_SHIFT              Rot_Lo__SHIFT
#define Rot_Lo_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot_Lo_PS                     (* (reg32 *) Rot_Lo__PS)
/* Port Configuration */
#define Rot_Lo_PC                     (* (reg32 *) Rot_Lo__PC)
/* Data Register */
#define Rot_Lo_DR                     (* (reg32 *) Rot_Lo__DR)
/* Input Buffer Disable Override */
#define Rot_Lo_INP_DIS                (* (reg32 *) Rot_Lo__PC2)


#if defined(Rot_Lo__INTSTAT)  /* Interrupt Registers */

    #define Rot_Lo_INTSTAT                (* (reg32 *) Rot_Lo__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot_Lo_DRIVE_MODE_SHIFT       (0x00u)
#define Rot_Lo_DRIVE_MODE_MASK        (0x07u << Rot_Lo_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot_Lo_H */


/* [] END OF FILE */

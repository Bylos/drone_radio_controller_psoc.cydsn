/*******************************************************************************
* File Name: Rot_Hi.h  
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

#if !defined(CY_PINS_Rot_Hi_H) /* Pins Rot_Hi_H */
#define CY_PINS_Rot_Hi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Rot_Hi_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Rot_Hi_Write(uint8 value) ;
void    Rot_Hi_SetDriveMode(uint8 mode) ;
uint8   Rot_Hi_ReadDataReg(void) ;
uint8   Rot_Hi_Read(void) ;
uint8   Rot_Hi_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Rot_Hi_DRIVE_MODE_BITS        (3)
#define Rot_Hi_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Rot_Hi_DRIVE_MODE_BITS))

#define Rot_Hi_DM_ALG_HIZ         (0x00u)
#define Rot_Hi_DM_DIG_HIZ         (0x01u)
#define Rot_Hi_DM_RES_UP          (0x02u)
#define Rot_Hi_DM_RES_DWN         (0x03u)
#define Rot_Hi_DM_OD_LO           (0x04u)
#define Rot_Hi_DM_OD_HI           (0x05u)
#define Rot_Hi_DM_STRONG          (0x06u)
#define Rot_Hi_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Rot_Hi_MASK               Rot_Hi__MASK
#define Rot_Hi_SHIFT              Rot_Hi__SHIFT
#define Rot_Hi_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Rot_Hi_PS                     (* (reg32 *) Rot_Hi__PS)
/* Port Configuration */
#define Rot_Hi_PC                     (* (reg32 *) Rot_Hi__PC)
/* Data Register */
#define Rot_Hi_DR                     (* (reg32 *) Rot_Hi__DR)
/* Input Buffer Disable Override */
#define Rot_Hi_INP_DIS                (* (reg32 *) Rot_Hi__PC2)


#if defined(Rot_Hi__INTSTAT)  /* Interrupt Registers */

    #define Rot_Hi_INTSTAT                (* (reg32 *) Rot_Hi__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Rot_Hi_DRIVE_MODE_SHIFT       (0x00u)
#define Rot_Hi_DRIVE_MODE_MASK        (0x07u << Rot_Hi_DRIVE_MODE_SHIFT)


#endif /* End Pins Rot_Hi_H */


/* [] END OF FILE */

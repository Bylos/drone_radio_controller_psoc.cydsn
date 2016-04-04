/*******************************************************************************
* File Name: JR_Y.h  
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

#if !defined(CY_PINS_JR_Y_H) /* Pins JR_Y_H */
#define CY_PINS_JR_Y_H

#include "cytypes.h"
#include "cyfitter.h"
#include "JR_Y_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    JR_Y_Write(uint8 value) ;
void    JR_Y_SetDriveMode(uint8 mode) ;
uint8   JR_Y_ReadDataReg(void) ;
uint8   JR_Y_Read(void) ;
uint8   JR_Y_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define JR_Y_DRIVE_MODE_BITS        (3)
#define JR_Y_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - JR_Y_DRIVE_MODE_BITS))

#define JR_Y_DM_ALG_HIZ         (0x00u)
#define JR_Y_DM_DIG_HIZ         (0x01u)
#define JR_Y_DM_RES_UP          (0x02u)
#define JR_Y_DM_RES_DWN         (0x03u)
#define JR_Y_DM_OD_LO           (0x04u)
#define JR_Y_DM_OD_HI           (0x05u)
#define JR_Y_DM_STRONG          (0x06u)
#define JR_Y_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define JR_Y_MASK               JR_Y__MASK
#define JR_Y_SHIFT              JR_Y__SHIFT
#define JR_Y_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JR_Y_PS                     (* (reg32 *) JR_Y__PS)
/* Port Configuration */
#define JR_Y_PC                     (* (reg32 *) JR_Y__PC)
/* Data Register */
#define JR_Y_DR                     (* (reg32 *) JR_Y__DR)
/* Input Buffer Disable Override */
#define JR_Y_INP_DIS                (* (reg32 *) JR_Y__PC2)


#if defined(JR_Y__INTSTAT)  /* Interrupt Registers */

    #define JR_Y_INTSTAT                (* (reg32 *) JR_Y__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define JR_Y_DRIVE_MODE_SHIFT       (0x00u)
#define JR_Y_DRIVE_MODE_MASK        (0x07u << JR_Y_DRIVE_MODE_SHIFT)


#endif /* End Pins JR_Y_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: SW1_L.h  
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

#if !defined(CY_PINS_SW1_L_H) /* Pins SW1_L_H */
#define CY_PINS_SW1_L_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW1_L_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW1_L_Write(uint8 value) ;
void    SW1_L_SetDriveMode(uint8 mode) ;
uint8   SW1_L_ReadDataReg(void) ;
uint8   SW1_L_Read(void) ;
uint8   SW1_L_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW1_L_DRIVE_MODE_BITS        (3)
#define SW1_L_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW1_L_DRIVE_MODE_BITS))

#define SW1_L_DM_ALG_HIZ         (0x00u)
#define SW1_L_DM_DIG_HIZ         (0x01u)
#define SW1_L_DM_RES_UP          (0x02u)
#define SW1_L_DM_RES_DWN         (0x03u)
#define SW1_L_DM_OD_LO           (0x04u)
#define SW1_L_DM_OD_HI           (0x05u)
#define SW1_L_DM_STRONG          (0x06u)
#define SW1_L_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SW1_L_MASK               SW1_L__MASK
#define SW1_L_SHIFT              SW1_L__SHIFT
#define SW1_L_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW1_L_PS                     (* (reg32 *) SW1_L__PS)
/* Port Configuration */
#define SW1_L_PC                     (* (reg32 *) SW1_L__PC)
/* Data Register */
#define SW1_L_DR                     (* (reg32 *) SW1_L__DR)
/* Input Buffer Disable Override */
#define SW1_L_INP_DIS                (* (reg32 *) SW1_L__PC2)


#if defined(SW1_L__INTSTAT)  /* Interrupt Registers */

    #define SW1_L_INTSTAT                (* (reg32 *) SW1_L__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SW1_L_DRIVE_MODE_SHIFT       (0x00u)
#define SW1_L_DRIVE_MODE_MASK        (0x07u << SW1_L_DRIVE_MODE_SHIFT)


#endif /* End Pins SW1_L_H */


/* [] END OF FILE */

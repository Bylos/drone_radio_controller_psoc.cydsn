/*******************************************************************************
* File Name: SW1_R.h  
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

#if !defined(CY_PINS_SW1_R_H) /* Pins SW1_R_H */
#define CY_PINS_SW1_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW1_R_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW1_R_Write(uint8 value) ;
void    SW1_R_SetDriveMode(uint8 mode) ;
uint8   SW1_R_ReadDataReg(void) ;
uint8   SW1_R_Read(void) ;
uint8   SW1_R_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW1_R_DRIVE_MODE_BITS        (3)
#define SW1_R_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW1_R_DRIVE_MODE_BITS))

#define SW1_R_DM_ALG_HIZ         (0x00u)
#define SW1_R_DM_DIG_HIZ         (0x01u)
#define SW1_R_DM_RES_UP          (0x02u)
#define SW1_R_DM_RES_DWN         (0x03u)
#define SW1_R_DM_OD_LO           (0x04u)
#define SW1_R_DM_OD_HI           (0x05u)
#define SW1_R_DM_STRONG          (0x06u)
#define SW1_R_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SW1_R_MASK               SW1_R__MASK
#define SW1_R_SHIFT              SW1_R__SHIFT
#define SW1_R_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW1_R_PS                     (* (reg32 *) SW1_R__PS)
/* Port Configuration */
#define SW1_R_PC                     (* (reg32 *) SW1_R__PC)
/* Data Register */
#define SW1_R_DR                     (* (reg32 *) SW1_R__DR)
/* Input Buffer Disable Override */
#define SW1_R_INP_DIS                (* (reg32 *) SW1_R__PC2)


#if defined(SW1_R__INTSTAT)  /* Interrupt Registers */

    #define SW1_R_INTSTAT                (* (reg32 *) SW1_R__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SW1_R_DRIVE_MODE_SHIFT       (0x00u)
#define SW1_R_DRIVE_MODE_MASK        (0x07u << SW1_R_DRIVE_MODE_SHIFT)


#endif /* End Pins SW1_R_H */


/* [] END OF FILE */

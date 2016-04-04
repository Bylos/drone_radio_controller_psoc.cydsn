/*******************************************************************************
* File Name: LED_Blue.h  
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

#if !defined(CY_PINS_LED_Blue_H) /* Pins LED_Blue_H */
#define CY_PINS_LED_Blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_Blue_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Blue_Write(uint8 value) ;
void    LED_Blue_SetDriveMode(uint8 mode) ;
uint8   LED_Blue_ReadDataReg(void) ;
uint8   LED_Blue_Read(void) ;
uint8   LED_Blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_Blue_DRIVE_MODE_BITS        (3)
#define LED_Blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_Blue_DRIVE_MODE_BITS))

#define LED_Blue_DM_ALG_HIZ         (0x00u)
#define LED_Blue_DM_DIG_HIZ         (0x01u)
#define LED_Blue_DM_RES_UP          (0x02u)
#define LED_Blue_DM_RES_DWN         (0x03u)
#define LED_Blue_DM_OD_LO           (0x04u)
#define LED_Blue_DM_OD_HI           (0x05u)
#define LED_Blue_DM_STRONG          (0x06u)
#define LED_Blue_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_Blue_MASK               LED_Blue__MASK
#define LED_Blue_SHIFT              LED_Blue__SHIFT
#define LED_Blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_Blue_PS                     (* (reg32 *) LED_Blue__PS)
/* Port Configuration */
#define LED_Blue_PC                     (* (reg32 *) LED_Blue__PC)
/* Data Register */
#define LED_Blue_DR                     (* (reg32 *) LED_Blue__DR)
/* Input Buffer Disable Override */
#define LED_Blue_INP_DIS                (* (reg32 *) LED_Blue__PC2)


#if defined(LED_Blue__INTSTAT)  /* Interrupt Registers */

    #define LED_Blue_INTSTAT                (* (reg32 *) LED_Blue__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_Blue_DRIVE_MODE_SHIFT       (0x00u)
#define LED_Blue_DRIVE_MODE_MASK        (0x07u << LED_Blue_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_Blue_H */


/* [] END OF FILE */

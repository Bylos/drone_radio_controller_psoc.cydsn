/*******************************************************************************
* File Name: JR_SEL.h  
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

#if !defined(CY_PINS_JR_SEL_H) /* Pins JR_SEL_H */
#define CY_PINS_JR_SEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "JR_SEL_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    JR_SEL_Write(uint8 value) ;
void    JR_SEL_SetDriveMode(uint8 mode) ;
uint8   JR_SEL_ReadDataReg(void) ;
uint8   JR_SEL_Read(void) ;
uint8   JR_SEL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define JR_SEL_DRIVE_MODE_BITS        (3)
#define JR_SEL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - JR_SEL_DRIVE_MODE_BITS))

#define JR_SEL_DM_ALG_HIZ         (0x00u)
#define JR_SEL_DM_DIG_HIZ         (0x01u)
#define JR_SEL_DM_RES_UP          (0x02u)
#define JR_SEL_DM_RES_DWN         (0x03u)
#define JR_SEL_DM_OD_LO           (0x04u)
#define JR_SEL_DM_OD_HI           (0x05u)
#define JR_SEL_DM_STRONG          (0x06u)
#define JR_SEL_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define JR_SEL_MASK               JR_SEL__MASK
#define JR_SEL_SHIFT              JR_SEL__SHIFT
#define JR_SEL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JR_SEL_PS                     (* (reg32 *) JR_SEL__PS)
/* Port Configuration */
#define JR_SEL_PC                     (* (reg32 *) JR_SEL__PC)
/* Data Register */
#define JR_SEL_DR                     (* (reg32 *) JR_SEL__DR)
/* Input Buffer Disable Override */
#define JR_SEL_INP_DIS                (* (reg32 *) JR_SEL__PC2)


#if defined(JR_SEL__INTSTAT)  /* Interrupt Registers */

    #define JR_SEL_INTSTAT                (* (reg32 *) JR_SEL__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define JR_SEL_DRIVE_MODE_SHIFT       (0x00u)
#define JR_SEL_DRIVE_MODE_MASK        (0x07u << JR_SEL_DRIVE_MODE_SHIFT)


#endif /* End Pins JR_SEL_H */


/* [] END OF FILE */

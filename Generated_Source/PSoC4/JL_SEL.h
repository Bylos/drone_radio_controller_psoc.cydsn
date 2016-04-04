/*******************************************************************************
* File Name: JL_SEL.h  
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

#if !defined(CY_PINS_JL_SEL_H) /* Pins JL_SEL_H */
#define CY_PINS_JL_SEL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "JL_SEL_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    JL_SEL_Write(uint8 value) ;
void    JL_SEL_SetDriveMode(uint8 mode) ;
uint8   JL_SEL_ReadDataReg(void) ;
uint8   JL_SEL_Read(void) ;
uint8   JL_SEL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define JL_SEL_DRIVE_MODE_BITS        (3)
#define JL_SEL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - JL_SEL_DRIVE_MODE_BITS))

#define JL_SEL_DM_ALG_HIZ         (0x00u)
#define JL_SEL_DM_DIG_HIZ         (0x01u)
#define JL_SEL_DM_RES_UP          (0x02u)
#define JL_SEL_DM_RES_DWN         (0x03u)
#define JL_SEL_DM_OD_LO           (0x04u)
#define JL_SEL_DM_OD_HI           (0x05u)
#define JL_SEL_DM_STRONG          (0x06u)
#define JL_SEL_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define JL_SEL_MASK               JL_SEL__MASK
#define JL_SEL_SHIFT              JL_SEL__SHIFT
#define JL_SEL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JL_SEL_PS                     (* (reg32 *) JL_SEL__PS)
/* Port Configuration */
#define JL_SEL_PC                     (* (reg32 *) JL_SEL__PC)
/* Data Register */
#define JL_SEL_DR                     (* (reg32 *) JL_SEL__DR)
/* Input Buffer Disable Override */
#define JL_SEL_INP_DIS                (* (reg32 *) JL_SEL__PC2)


#if defined(JL_SEL__INTSTAT)  /* Interrupt Registers */

    #define JL_SEL_INTSTAT                (* (reg32 *) JL_SEL__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define JL_SEL_DRIVE_MODE_SHIFT       (0x00u)
#define JL_SEL_DRIVE_MODE_MASK        (0x07u << JL_SEL_DRIVE_MODE_SHIFT)


#endif /* End Pins JL_SEL_H */


/* [] END OF FILE */

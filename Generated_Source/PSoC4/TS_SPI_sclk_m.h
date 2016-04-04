/*******************************************************************************
* File Name: TS_SPI_sclk_m.h  
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

#if !defined(CY_PINS_TS_SPI_sclk_m_H) /* Pins TS_SPI_sclk_m_H */
#define CY_PINS_TS_SPI_sclk_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TS_SPI_sclk_m_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TS_SPI_sclk_m_Write(uint8 value) ;
void    TS_SPI_sclk_m_SetDriveMode(uint8 mode) ;
uint8   TS_SPI_sclk_m_ReadDataReg(void) ;
uint8   TS_SPI_sclk_m_Read(void) ;
uint8   TS_SPI_sclk_m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TS_SPI_sclk_m_DRIVE_MODE_BITS        (3)
#define TS_SPI_sclk_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TS_SPI_sclk_m_DRIVE_MODE_BITS))

#define TS_SPI_sclk_m_DM_ALG_HIZ         (0x00u)
#define TS_SPI_sclk_m_DM_DIG_HIZ         (0x01u)
#define TS_SPI_sclk_m_DM_RES_UP          (0x02u)
#define TS_SPI_sclk_m_DM_RES_DWN         (0x03u)
#define TS_SPI_sclk_m_DM_OD_LO           (0x04u)
#define TS_SPI_sclk_m_DM_OD_HI           (0x05u)
#define TS_SPI_sclk_m_DM_STRONG          (0x06u)
#define TS_SPI_sclk_m_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TS_SPI_sclk_m_MASK               TS_SPI_sclk_m__MASK
#define TS_SPI_sclk_m_SHIFT              TS_SPI_sclk_m__SHIFT
#define TS_SPI_sclk_m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TS_SPI_sclk_m_PS                     (* (reg32 *) TS_SPI_sclk_m__PS)
/* Port Configuration */
#define TS_SPI_sclk_m_PC                     (* (reg32 *) TS_SPI_sclk_m__PC)
/* Data Register */
#define TS_SPI_sclk_m_DR                     (* (reg32 *) TS_SPI_sclk_m__DR)
/* Input Buffer Disable Override */
#define TS_SPI_sclk_m_INP_DIS                (* (reg32 *) TS_SPI_sclk_m__PC2)


#if defined(TS_SPI_sclk_m__INTSTAT)  /* Interrupt Registers */

    #define TS_SPI_sclk_m_INTSTAT                (* (reg32 *) TS_SPI_sclk_m__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TS_SPI_sclk_m_DRIVE_MODE_SHIFT       (0x00u)
#define TS_SPI_sclk_m_DRIVE_MODE_MASK        (0x07u << TS_SPI_sclk_m_DRIVE_MODE_SHIFT)


#endif /* End Pins TS_SPI_sclk_m_H */


/* [] END OF FILE */

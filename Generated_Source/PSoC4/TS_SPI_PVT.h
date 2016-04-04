/*******************************************************************************
* File Name: .h
* Version 3.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_TS_SPI_H)
#define CY_SCB_PVT_TS_SPI_H

#include "TS_SPI.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define TS_SPI_SetI2CExtClkInterruptMode(interruptMask) TS_SPI_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define TS_SPI_ClearI2CExtClkInterruptSource(interruptMask) TS_SPI_CLEAR_INTR_I2C_EC(interruptMask)
#define TS_SPI_GetI2CExtClkInterruptSource()                (TS_SPI_INTR_I2C_EC_REG)
#define TS_SPI_GetI2CExtClkInterruptMode()                  (TS_SPI_INTR_I2C_EC_MASK_REG)
#define TS_SPI_GetI2CExtClkInterruptSourceMasked()          (TS_SPI_INTR_I2C_EC_MASKED_REG)

#if (!TS_SPI_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define TS_SPI_SetSpiExtClkInterruptMode(interruptMask) \
                                                                TS_SPI_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define TS_SPI_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                TS_SPI_CLEAR_INTR_SPI_EC(interruptMask)
    #define TS_SPI_GetExtSpiClkInterruptSource()                 (TS_SPI_INTR_SPI_EC_REG)
    #define TS_SPI_GetExtSpiClkInterruptMode()                   (TS_SPI_INTR_SPI_EC_MASK_REG)
    #define TS_SPI_GetExtSpiClkInterruptSourceMasked()           (TS_SPI_INTR_SPI_EC_MASKED_REG)
#endif /* (!TS_SPI_CY_SCBIP_V1) */

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void TS_SPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (TS_SPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER)
    extern cyisraddress TS_SPI_customIntrHandler;
#endif /* !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER) */
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */

extern TS_SPI_BACKUP_STRUCT TS_SPI_backup;

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 TS_SPI_scbMode;
    extern uint8 TS_SPI_scbEnableWake;
    extern uint8 TS_SPI_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 TS_SPI_mode;
    extern uint8 TS_SPI_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * TS_SPI_rxBuffer;
    extern uint8   TS_SPI_rxDataBits;
    extern uint32  TS_SPI_rxBufferSize;

    extern volatile uint8 * TS_SPI_txBuffer;
    extern uint8   TS_SPI_txDataBits;
    extern uint32  TS_SPI_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 TS_SPI_numberOfAddr;
    extern uint8 TS_SPI_subAddrSize;
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define TS_SPI_SCB_MODE_I2C_RUNTM_CFG     (TS_SPI_SCB_MODE_I2C      == TS_SPI_scbMode)
    #define TS_SPI_SCB_MODE_SPI_RUNTM_CFG     (TS_SPI_SCB_MODE_SPI      == TS_SPI_scbMode)
    #define TS_SPI_SCB_MODE_UART_RUNTM_CFG    (TS_SPI_SCB_MODE_UART     == TS_SPI_scbMode)
    #define TS_SPI_SCB_MODE_EZI2C_RUNTM_CFG   (TS_SPI_SCB_MODE_EZI2C    == TS_SPI_scbMode)
    #define TS_SPI_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (TS_SPI_SCB_MODE_UNCONFIG == TS_SPI_scbMode)

    /* Defines wakeup enable */
    #define TS_SPI_SCB_WAKE_ENABLE_CHECK       (0u != TS_SPI_scbEnableWake)
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!TS_SPI_CY_SCBIP_V1)
    #define TS_SPI_SCB_PINS_NUMBER    (7u)
#else
    #define TS_SPI_SCB_PINS_NUMBER    (2u)
#endif /* (!TS_SPI_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_TS_SPI_H) */


/* [] END OF FILE */

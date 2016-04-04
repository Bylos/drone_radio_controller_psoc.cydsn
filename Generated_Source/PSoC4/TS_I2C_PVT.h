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

#if !defined(CY_SCB_PVT_TS_I2C_H)
#define CY_SCB_PVT_TS_I2C_H

#include "TS_I2C.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define TS_I2C_SetI2CExtClkInterruptMode(interruptMask) TS_I2C_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define TS_I2C_ClearI2CExtClkInterruptSource(interruptMask) TS_I2C_CLEAR_INTR_I2C_EC(interruptMask)
#define TS_I2C_GetI2CExtClkInterruptSource()                (TS_I2C_INTR_I2C_EC_REG)
#define TS_I2C_GetI2CExtClkInterruptMode()                  (TS_I2C_INTR_I2C_EC_MASK_REG)
#define TS_I2C_GetI2CExtClkInterruptSourceMasked()          (TS_I2C_INTR_I2C_EC_MASKED_REG)

#if (!TS_I2C_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define TS_I2C_SetSpiExtClkInterruptMode(interruptMask) \
                                                                TS_I2C_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define TS_I2C_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                TS_I2C_CLEAR_INTR_SPI_EC(interruptMask)
    #define TS_I2C_GetExtSpiClkInterruptSource()                 (TS_I2C_INTR_SPI_EC_REG)
    #define TS_I2C_GetExtSpiClkInterruptMode()                   (TS_I2C_INTR_SPI_EC_MASK_REG)
    #define TS_I2C_GetExtSpiClkInterruptSourceMasked()           (TS_I2C_INTR_SPI_EC_MASKED_REG)
#endif /* (!TS_I2C_CY_SCBIP_V1) */

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void TS_I2C_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (TS_I2C_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_TS_I2C_CUSTOM_INTR_HANDLER)
    extern cyisraddress TS_I2C_customIntrHandler;
#endif /* !defined (CY_REMOVE_TS_I2C_CUSTOM_INTR_HANDLER) */
#endif /* (TS_I2C_SCB_IRQ_INTERNAL) */

extern TS_I2C_BACKUP_STRUCT TS_I2C_backup;

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 TS_I2C_scbMode;
    extern uint8 TS_I2C_scbEnableWake;
    extern uint8 TS_I2C_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 TS_I2C_mode;
    extern uint8 TS_I2C_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * TS_I2C_rxBuffer;
    extern uint8   TS_I2C_rxDataBits;
    extern uint32  TS_I2C_rxBufferSize;

    extern volatile uint8 * TS_I2C_txBuffer;
    extern uint8   TS_I2C_txDataBits;
    extern uint32  TS_I2C_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 TS_I2C_numberOfAddr;
    extern uint8 TS_I2C_subAddrSize;
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define TS_I2C_SCB_MODE_I2C_RUNTM_CFG     (TS_I2C_SCB_MODE_I2C      == TS_I2C_scbMode)
    #define TS_I2C_SCB_MODE_SPI_RUNTM_CFG     (TS_I2C_SCB_MODE_SPI      == TS_I2C_scbMode)
    #define TS_I2C_SCB_MODE_UART_RUNTM_CFG    (TS_I2C_SCB_MODE_UART     == TS_I2C_scbMode)
    #define TS_I2C_SCB_MODE_EZI2C_RUNTM_CFG   (TS_I2C_SCB_MODE_EZI2C    == TS_I2C_scbMode)
    #define TS_I2C_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (TS_I2C_SCB_MODE_UNCONFIG == TS_I2C_scbMode)

    /* Defines wakeup enable */
    #define TS_I2C_SCB_WAKE_ENABLE_CHECK       (0u != TS_I2C_scbEnableWake)
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!TS_I2C_CY_SCBIP_V1)
    #define TS_I2C_SCB_PINS_NUMBER    (7u)
#else
    #define TS_I2C_SCB_PINS_NUMBER    (2u)
#endif /* (!TS_I2C_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_TS_I2C_H) */


/* [] END OF FILE */

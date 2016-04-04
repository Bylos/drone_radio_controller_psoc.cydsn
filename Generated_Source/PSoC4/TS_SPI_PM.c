/*******************************************************************************
* File Name: TS_SPI_PM.c
* Version 3.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TS_SPI.h"
#include "TS_SPI_PVT.h"

#if(TS_SPI_SCB_MODE_I2C_INC)
    #include "TS_SPI_I2C_PVT.h"
#endif /* (TS_SPI_SCB_MODE_I2C_INC) */

#if(TS_SPI_SCB_MODE_EZI2C_INC)
    #include "TS_SPI_EZI2C_PVT.h"
#endif /* (TS_SPI_SCB_MODE_EZI2C_INC) */

#if(TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC)
    #include "TS_SPI_SPI_UART_PVT.h"
#endif /* (TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG || \
   (TS_SPI_SCB_MODE_I2C_CONST_CFG   && (!TS_SPI_I2C_WAKE_ENABLE_CONST))   || \
   (TS_SPI_SCB_MODE_EZI2C_CONST_CFG && (!TS_SPI_EZI2C_WAKE_ENABLE_CONST)) || \
   (TS_SPI_SCB_MODE_SPI_CONST_CFG   && (!TS_SPI_SPI_WAKE_ENABLE_CONST))   || \
   (TS_SPI_SCB_MODE_UART_CONST_CFG  && (!TS_SPI_UART_WAKE_ENABLE_CONST)))

    TS_SPI_BACKUP_STRUCT TS_SPI_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: TS_SPI_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_Sleep(void)
{
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(TS_SPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(TS_SPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            TS_SPI_I2CSaveConfig();
        }
        else if(TS_SPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            TS_SPI_EzI2CSaveConfig();
        }
    #if(!TS_SPI_CY_SCBIP_V1)
        else if(TS_SPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            TS_SPI_SpiSaveConfig();
        }
        else if(TS_SPI_SCB_MODE_UART_RUNTM_CFG)
        {
            TS_SPI_UartSaveConfig();
        }
    #endif /* (!TS_SPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        TS_SPI_backup.enableState = (uint8) TS_SPI_GET_CTRL_ENABLED;

        if(0u != TS_SPI_backup.enableState)
        {
            TS_SPI_Stop();
        }
    }

#else

    #if (TS_SPI_SCB_MODE_I2C_CONST_CFG && TS_SPI_I2C_WAKE_ENABLE_CONST)
        TS_SPI_I2CSaveConfig();

    #elif (TS_SPI_SCB_MODE_EZI2C_CONST_CFG && TS_SPI_EZI2C_WAKE_ENABLE_CONST)
        TS_SPI_EzI2CSaveConfig();

    #elif (TS_SPI_SCB_MODE_SPI_CONST_CFG && TS_SPI_SPI_WAKE_ENABLE_CONST)
        TS_SPI_SpiSaveConfig();

    #elif (TS_SPI_SCB_MODE_UART_CONST_CFG && TS_SPI_UART_WAKE_ENABLE_CONST)
        TS_SPI_UartSaveConfig();

    #else

        TS_SPI_backup.enableState = (uint8) TS_SPI_GET_CTRL_ENABLED;

        if(0u != TS_SPI_backup.enableState)
        {
            TS_SPI_Stop();
        }

    #endif /* defined (TS_SPI_SCB_MODE_I2C_CONST_CFG) && (TS_SPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_SPI_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_Wakeup(void)
{
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if(TS_SPI_SCB_WAKE_ENABLE_CHECK)
    {
        if(TS_SPI_SCB_MODE_I2C_RUNTM_CFG)
        {
            TS_SPI_I2CRestoreConfig();
        }
        else if(TS_SPI_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            TS_SPI_EzI2CRestoreConfig();
        }
    #if(!TS_SPI_CY_SCBIP_V1)
        else if(TS_SPI_SCB_MODE_SPI_RUNTM_CFG)
        {
            TS_SPI_SpiRestoreConfig();
        }
        else if(TS_SPI_SCB_MODE_UART_RUNTM_CFG)
        {
            TS_SPI_UartRestoreConfig();
        }
    #endif /* (!TS_SPI_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != TS_SPI_backup.enableState)
        {
            TS_SPI_Enable();
        }
    }

#else

    #if (TS_SPI_SCB_MODE_I2C_CONST_CFG  && TS_SPI_I2C_WAKE_ENABLE_CONST)
        TS_SPI_I2CRestoreConfig();

    #elif (TS_SPI_SCB_MODE_EZI2C_CONST_CFG && TS_SPI_EZI2C_WAKE_ENABLE_CONST)
        TS_SPI_EzI2CRestoreConfig();

    #elif (TS_SPI_SCB_MODE_SPI_CONST_CFG && TS_SPI_SPI_WAKE_ENABLE_CONST)
        TS_SPI_SpiRestoreConfig();

    #elif (TS_SPI_SCB_MODE_UART_CONST_CFG && TS_SPI_UART_WAKE_ENABLE_CONST)
        TS_SPI_UartRestoreConfig();

    #else

        if(0u != TS_SPI_backup.enableState)
        {
            TS_SPI_Enable();
        }

    #endif /* (TS_SPI_I2C_WAKE_ENABLE_CONST) */

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

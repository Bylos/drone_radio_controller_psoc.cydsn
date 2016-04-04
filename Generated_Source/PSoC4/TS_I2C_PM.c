/*******************************************************************************
* File Name: TS_I2C_PM.c
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

#include "TS_I2C.h"
#include "TS_I2C_PVT.h"

#if(TS_I2C_SCB_MODE_I2C_INC)
    #include "TS_I2C_I2C_PVT.h"
#endif /* (TS_I2C_SCB_MODE_I2C_INC) */

#if(TS_I2C_SCB_MODE_EZI2C_INC)
    #include "TS_I2C_EZI2C_PVT.h"
#endif /* (TS_I2C_SCB_MODE_EZI2C_INC) */

#if(TS_I2C_SCB_MODE_SPI_INC || TS_I2C_SCB_MODE_UART_INC)
    #include "TS_I2C_SPI_UART_PVT.h"
#endif /* (TS_I2C_SCB_MODE_SPI_INC || TS_I2C_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
   (TS_I2C_SCB_MODE_I2C_CONST_CFG   && (!TS_I2C_I2C_WAKE_ENABLE_CONST))   || \
   (TS_I2C_SCB_MODE_EZI2C_CONST_CFG && (!TS_I2C_EZI2C_WAKE_ENABLE_CONST)) || \
   (TS_I2C_SCB_MODE_SPI_CONST_CFG   && (!TS_I2C_SPI_WAKE_ENABLE_CONST))   || \
   (TS_I2C_SCB_MODE_UART_CONST_CFG  && (!TS_I2C_UART_WAKE_ENABLE_CONST)))

    TS_I2C_BACKUP_STRUCT TS_I2C_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: TS_I2C_Sleep
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
void TS_I2C_Sleep(void)
{
#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(TS_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(TS_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            TS_I2C_I2CSaveConfig();
        }
        else if(TS_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            TS_I2C_EzI2CSaveConfig();
        }
    #if(!TS_I2C_CY_SCBIP_V1)
        else if(TS_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            TS_I2C_SpiSaveConfig();
        }
        else if(TS_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            TS_I2C_UartSaveConfig();
        }
    #endif /* (!TS_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        TS_I2C_backup.enableState = (uint8) TS_I2C_GET_CTRL_ENABLED;

        if(0u != TS_I2C_backup.enableState)
        {
            TS_I2C_Stop();
        }
    }

#else

    #if (TS_I2C_SCB_MODE_I2C_CONST_CFG && TS_I2C_I2C_WAKE_ENABLE_CONST)
        TS_I2C_I2CSaveConfig();

    #elif (TS_I2C_SCB_MODE_EZI2C_CONST_CFG && TS_I2C_EZI2C_WAKE_ENABLE_CONST)
        TS_I2C_EzI2CSaveConfig();

    #elif (TS_I2C_SCB_MODE_SPI_CONST_CFG && TS_I2C_SPI_WAKE_ENABLE_CONST)
        TS_I2C_SpiSaveConfig();

    #elif (TS_I2C_SCB_MODE_UART_CONST_CFG && TS_I2C_UART_WAKE_ENABLE_CONST)
        TS_I2C_UartSaveConfig();

    #else

        TS_I2C_backup.enableState = (uint8) TS_I2C_GET_CTRL_ENABLED;

        if(0u != TS_I2C_backup.enableState)
        {
            TS_I2C_Stop();
        }

    #endif /* defined (TS_I2C_SCB_MODE_I2C_CONST_CFG) && (TS_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_I2C_Wakeup
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
void TS_I2C_Wakeup(void)
{
#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(TS_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(TS_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            TS_I2C_I2CRestoreConfig();
        }
        else if(TS_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            TS_I2C_EzI2CRestoreConfig();
        }
    #if(!TS_I2C_CY_SCBIP_V1)
        else if(TS_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            TS_I2C_SpiRestoreConfig();
        }
        else if(TS_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            TS_I2C_UartRestoreConfig();
        }
    #endif /* (!TS_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != TS_I2C_backup.enableState)
        {
            TS_I2C_Enable();
        }
    }

#else

    #if (TS_I2C_SCB_MODE_I2C_CONST_CFG  && TS_I2C_I2C_WAKE_ENABLE_CONST)
        TS_I2C_I2CRestoreConfig();

    #elif (TS_I2C_SCB_MODE_EZI2C_CONST_CFG && TS_I2C_EZI2C_WAKE_ENABLE_CONST)
        TS_I2C_EzI2CRestoreConfig();

    #elif (TS_I2C_SCB_MODE_SPI_CONST_CFG && TS_I2C_SPI_WAKE_ENABLE_CONST)
        TS_I2C_SpiRestoreConfig();

    #elif (TS_I2C_SCB_MODE_UART_CONST_CFG && TS_I2C_UART_WAKE_ENABLE_CONST)
        TS_I2C_UartRestoreConfig();

    #else

        if(0u != TS_I2C_backup.enableState)
        {
            TS_I2C_Enable();
        }

    #endif /* (TS_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */

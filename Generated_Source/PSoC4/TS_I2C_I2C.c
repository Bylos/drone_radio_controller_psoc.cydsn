/*******************************************************************************
* File Name: TS_I2C_I2C.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TS_I2C_PVT.h"
#include "TS_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 TS_I2C_state;  /* Current state of I2C FSM */

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const TS_I2C_I2C_INIT_STRUCT TS_I2C_configI2C =
    {
        TS_I2C_I2C_MODE,
        TS_I2C_I2C_OVS_FACTOR_LOW,
        TS_I2C_I2C_OVS_FACTOR_HIGH,
        TS_I2C_I2C_MEDIAN_FILTER_ENABLE,
        TS_I2C_I2C_SLAVE_ADDRESS,
        TS_I2C_I2C_SLAVE_ADDRESS_MASK,
        TS_I2C_I2C_ACCEPT_ADDRESS,
        TS_I2C_I2C_WAKE_ENABLE,
        TS_I2C_I2C_BYTE_MODE_ENABLE,
        TS_I2C_I2C_DATA_RATE,
        TS_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: TS_I2C_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_I2C_I2CInit(const TS_I2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            TS_I2C_SetPins(TS_I2C_SCB_MODE_I2C, TS_I2C_DUMMY_PARAM,
                                     TS_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            TS_I2C_scbMode       = (uint8) TS_I2C_SCB_MODE_I2C;
            TS_I2C_scbEnableWake = (uint8) config->enableWake;
            TS_I2C_scbEnableIntr = (uint8) TS_I2C_SCB_IRQ_INTERNAL;

            TS_I2C_mode          = (uint8) config->mode;
            TS_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (TS_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            TS_I2C_SET_I2C_CFG_SDA_FILT_TRIM(TS_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (TS_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((TS_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= TS_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (TS_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                TS_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = TS_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                TS_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = TS_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!TS_I2C_CY_SCBIP_V0)
            locEnableWake = (TS_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!TS_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            TS_I2C_CTRL_REG     = TS_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            TS_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            TS_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            TS_I2C_I2C_CTRL_REG = TS_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    TS_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    TS_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    TS_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            TS_I2C_RX_CTRL_REG      = TS_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                TS_I2C_I2C_RX_CTRL;
            TS_I2C_RX_FIFO_CTRL_REG = TS_I2C_CLEAR_REG;

            /* Set default address and mask */
            TS_I2C_RX_MATCH_REG    = ((TS_I2C_I2C_SLAVE) ?
                                                (TS_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 TS_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (TS_I2C_CLEAR_REG));


            /* Configure TX direction */
            TS_I2C_TX_CTRL_REG      = TS_I2C_I2C_TX_CTRL;
            TS_I2C_TX_FIFO_CTRL_REG = TS_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (TS_I2C_ISR_NUMBER);
            CyIntSetPriority(TS_I2C_ISR_NUMBER, TS_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(TS_I2C_ISR_NUMBER, &TS_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!TS_I2C_CY_SCBIP_V1)
            TS_I2C_INTR_SPI_EC_MASK_REG = TS_I2C_NO_INTR_SOURCES;
        #endif /* (!TS_I2C_CY_SCBIP_V1) */

            TS_I2C_INTR_I2C_EC_MASK_REG = TS_I2C_NO_INTR_SOURCES;
            TS_I2C_INTR_RX_MASK_REG     = TS_I2C_NO_INTR_SOURCES;
            TS_I2C_INTR_TX_MASK_REG     = TS_I2C_NO_INTR_SOURCES;

            TS_I2C_INTR_SLAVE_MASK_REG  = ((TS_I2C_I2C_SLAVE) ?
                            (TS_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             TS_I2C_I2C_INTR_SLAVE_MASK) : (TS_I2C_CLEAR_REG));

            TS_I2C_INTR_MASTER_MASK_REG = ((TS_I2C_I2C_MASTER) ?
                                                     (TS_I2C_I2C_INTR_MASTER_MASK) :
                                                     (TS_I2C_CLEAR_REG));

            /* Configure global variables */
            TS_I2C_state = TS_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            TS_I2C_slStatus        = 0u;
            TS_I2C_slRdBufIndex    = 0u;
            TS_I2C_slWrBufIndex    = 0u;
            TS_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            TS_I2C_mstrStatus     = 0u;
            TS_I2C_mstrRdBufIndex = 0u;
            TS_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: TS_I2C_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_I2C_I2CInit(void)
    {
    #if(TS_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        TS_I2C_SET_I2C_CFG_SDA_FILT_TRIM(TS_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (TS_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        TS_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        TS_I2C_CTRL_REG     = TS_I2C_I2C_DEFAULT_CTRL;
        TS_I2C_I2C_CTRL_REG = TS_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        TS_I2C_RX_CTRL_REG      = TS_I2C_I2C_DEFAULT_RX_CTRL;
        TS_I2C_RX_FIFO_CTRL_REG = TS_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        TS_I2C_RX_MATCH_REG     = TS_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        TS_I2C_TX_CTRL_REG      = TS_I2C_I2C_DEFAULT_TX_CTRL;
        TS_I2C_TX_FIFO_CTRL_REG = TS_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (TS_I2C_ISR_NUMBER);
        CyIntSetPriority(TS_I2C_ISR_NUMBER, TS_I2C_ISR_PRIORITY);
    #if(!TS_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(TS_I2C_ISR_NUMBER, &TS_I2C_I2C_ISR);
    #endif /* (TS_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!TS_I2C_CY_SCBIP_V1)
        TS_I2C_INTR_SPI_EC_MASK_REG = TS_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!TS_I2C_CY_SCBIP_V1) */

        TS_I2C_INTR_I2C_EC_MASK_REG = TS_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        TS_I2C_INTR_SLAVE_MASK_REG  = TS_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        TS_I2C_INTR_MASTER_MASK_REG = TS_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        TS_I2C_INTR_RX_MASK_REG     = TS_I2C_I2C_DEFAULT_INTR_RX_MASK;
        TS_I2C_INTR_TX_MASK_REG     = TS_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        TS_I2C_state = TS_I2C_I2C_FSM_IDLE;

    #if(TS_I2C_I2C_SLAVE)
        /* Internal slave variable */
        TS_I2C_slStatus        = 0u;
        TS_I2C_slRdBufIndex    = 0u;
        TS_I2C_slWrBufIndex    = 0u;
        TS_I2C_slOverFlowCount = 0u;
    #endif /* (TS_I2C_I2C_SLAVE) */

    #if(TS_I2C_I2C_MASTER)
    /* Internal master variable */
        TS_I2C_mstrStatus     = 0u;
        TS_I2C_mstrRdBufIndex = 0u;
        TS_I2C_mstrWrBufIndex = 0u;
    #endif /* (TS_I2C_I2C_MASTER) */
    }
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: TS_I2C_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_I2C_I2CStop(void)
{
    TS_I2C_state = TS_I2C_I2C_FSM_IDLE;
}


#if(TS_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: TS_I2C_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables TS_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_I2C_I2CSaveConfig(void)
    {
    #if (!TS_I2C_CY_SCBIP_V0)
        #if (TS_I2C_I2C_MULTI_MASTER_SLAVE_CONST && TS_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (TS_I2C_CTRL_REG & TS_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                TS_I2C_Stop();
                TS_I2C_CTRL_REG |= TS_I2C_CTRL_EC_AM_MODE;
                TS_I2C_Enable();
            }
        #endif /* (TS_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (TS_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            TS_I2C_SCBCLK_Stop();
        #endif /* (TS_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!TS_I2C_CY_SCBIP_V0) */

        TS_I2C_SetI2CExtClkInterruptMode(TS_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: TS_I2C_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables TS_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        TS_I2C_SetI2CExtClkInterruptMode(TS_I2C_NO_INTR_SOURCES);

    #if (!TS_I2C_CY_SCBIP_V0)
        #if (TS_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            TS_I2C_SCBCLK_Start();
        #endif /* (TS_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!TS_I2C_CY_SCBIP_V0) */
    }
#endif /* (TS_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */

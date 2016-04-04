/*******************************************************************************
* File Name: TS_SPI_SPI.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TS_SPI_PVT.h"
#include "TS_SPI_SPI_UART_PVT.h"

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const TS_SPI_SPI_INIT_STRUCT TS_SPI_configSpi =
    {
        TS_SPI_SPI_MODE,
        TS_SPI_SPI_SUB_MODE,
        TS_SPI_SPI_CLOCK_MODE,
        TS_SPI_SPI_OVS_FACTOR,
        TS_SPI_SPI_MEDIAN_FILTER_ENABLE,
        TS_SPI_SPI_LATE_MISO_SAMPLE_ENABLE,
        TS_SPI_SPI_WAKE_ENABLE,
        TS_SPI_SPI_RX_DATA_BITS_NUM,
        TS_SPI_SPI_TX_DATA_BITS_NUM,
        TS_SPI_SPI_BITS_ORDER,
        TS_SPI_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) TS_SPI_SCB_IRQ_INTERNAL,
        TS_SPI_SPI_INTR_RX_MASK,
        TS_SPI_SPI_RX_TRIGGER_LEVEL,
        TS_SPI_SPI_INTR_TX_MASK,
        TS_SPI_SPI_TX_TRIGGER_LEVEL,
        (uint8) TS_SPI_SPI_BYTE_MODE_ENABLE,
        (uint8) TS_SPI_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) TS_SPI_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: TS_SPI_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
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
    void TS_SPI_SpiInit(const TS_SPI_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            TS_SPI_SetPins(TS_SPI_SCB_MODE_SPI, config->mode, TS_SPI_DUMMY_PARAM);

            /* Store internal configuration */
            TS_SPI_scbMode       = (uint8) TS_SPI_SCB_MODE_SPI;
            TS_SPI_scbEnableWake = (uint8) config->enableWake;
            TS_SPI_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            TS_SPI_rxBuffer      =         config->rxBuffer;
            TS_SPI_rxDataBits    = (uint8) config->rxDataBits;
            TS_SPI_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            TS_SPI_txBuffer      =         config->txBuffer;
            TS_SPI_txDataBits    = (uint8) config->txDataBits;
            TS_SPI_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure SPI interface */
            TS_SPI_CTRL_REG     = TS_SPI_GET_CTRL_OVS(config->oversample)           |
                                            TS_SPI_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            TS_SPI_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            TS_SPI_CTRL_SPI;

            TS_SPI_SPI_CTRL_REG = TS_SPI_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            TS_SPI_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          TS_SPI_SPI_MODE_TI_PRECEDES_MASK) |
                                            TS_SPI_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            TS_SPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            TS_SPI_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            TS_SPI_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            TS_SPI_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            TS_SPI_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            TS_SPI_RX_CTRL_REG     =  TS_SPI_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                TS_SPI_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                TS_SPI_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                TS_SPI_SPI_RX_CTRL;

            TS_SPI_RX_FIFO_CTRL_REG = TS_SPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            TS_SPI_TX_CTRL_REG      = TS_SPI_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                TS_SPI_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                TS_SPI_SPI_TX_CTRL;

            TS_SPI_TX_FIFO_CTRL_REG = TS_SPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (TS_SPI_ISR_NUMBER);
            CyIntSetPriority(TS_SPI_ISR_NUMBER, TS_SPI_ISR_PRIORITY);
            (void) CyIntSetVector(TS_SPI_ISR_NUMBER, &TS_SPI_SPI_UART_ISR);

            /* Configure interrupt sources */
            TS_SPI_INTR_I2C_EC_MASK_REG = TS_SPI_NO_INTR_SOURCES;
            TS_SPI_INTR_SPI_EC_MASK_REG = TS_SPI_NO_INTR_SOURCES;
            TS_SPI_INTR_SLAVE_MASK_REG  = TS_SPI_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            TS_SPI_INTR_MASTER_MASK_REG = TS_SPI_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            TS_SPI_INTR_RX_MASK_REG     = TS_SPI_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            TS_SPI_INTR_TX_MASK_REG     = TS_SPI_GET_SPI_INTR_TX_MASK(config->txInterruptMask);

            /* Set active SS0 */
            TS_SPI_SpiSetActiveSlaveSelect(TS_SPI_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            TS_SPI_rxBufferHead     = 0u;
            TS_SPI_rxBufferTail     = 0u;
            TS_SPI_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            TS_SPI_txBufferHead = 0u;
            TS_SPI_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: TS_SPI_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiInit(void)
    {
        /* Configure SPI interface */
        TS_SPI_CTRL_REG     = TS_SPI_SPI_DEFAULT_CTRL;
        TS_SPI_SPI_CTRL_REG = TS_SPI_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        TS_SPI_RX_CTRL_REG      = TS_SPI_SPI_DEFAULT_RX_CTRL;
        TS_SPI_RX_FIFO_CTRL_REG = TS_SPI_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        TS_SPI_TX_CTRL_REG      = TS_SPI_SPI_DEFAULT_TX_CTRL;
        TS_SPI_TX_FIFO_CTRL_REG = TS_SPI_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(TS_SPI_SCB_IRQ_INTERNAL)
            CyIntDisable    (TS_SPI_ISR_NUMBER);
            CyIntSetPriority(TS_SPI_ISR_NUMBER, TS_SPI_ISR_PRIORITY);
            (void) CyIntSetVector(TS_SPI_ISR_NUMBER, &TS_SPI_SPI_UART_ISR);
    #endif /* (TS_SPI_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        TS_SPI_INTR_I2C_EC_MASK_REG = TS_SPI_SPI_DEFAULT_INTR_I2C_EC_MASK;
        TS_SPI_INTR_SPI_EC_MASK_REG = TS_SPI_SPI_DEFAULT_INTR_SPI_EC_MASK;
        TS_SPI_INTR_SLAVE_MASK_REG  = TS_SPI_SPI_DEFAULT_INTR_SLAVE_MASK;
        TS_SPI_INTR_MASTER_MASK_REG = TS_SPI_SPI_DEFAULT_INTR_MASTER_MASK;
        TS_SPI_INTR_RX_MASK_REG     = TS_SPI_SPI_DEFAULT_INTR_RX_MASK;
        TS_SPI_INTR_TX_MASK_REG     = TS_SPI_SPI_DEFAULT_INTR_TX_MASK;

        /* Set active SS0 for master */
    #if (TS_SPI_SPI_MASTER_CONST)
        TS_SPI_SpiSetActiveSlaveSelect(TS_SPI_SPI_SLAVE_SELECT0);
    #endif /* (TS_SPI_SPI_MASTER_CONST) */

    #if(TS_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        TS_SPI_rxBufferHead     = 0u;
        TS_SPI_rxBufferTail     = 0u;
        TS_SPI_rxBufferOverflow = 0u;
    #endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(TS_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        TS_SPI_txBufferHead = 0u;
        TS_SPI_txBufferTail = 0u;
    #endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: TS_SPI_SpiPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_SpiPostEnable(void)
{
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (TS_SPI_CHECK_SPI_MASTER)
    {
    #if (TS_SPI_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SCLK_HSIOM_REG, TS_SPI_SCLK_HSIOM_MASK,
                                       TS_SPI_SCLK_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
    #endif /* (TS_SPI_SCLK_PIN) */

    #if (TS_SPI_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS0_HSIOM_REG, TS_SPI_SS0_HSIOM_MASK,
                                       TS_SPI_SS0_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
    #endif /* (TS_SPI_SS0_PIN) */

    #if (TS_SPI_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS1_HSIOM_REG, TS_SPI_SS1_HSIOM_MASK,
                                       TS_SPI_SS1_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
    #endif /* (TS_SPI_SS1_PIN) */

    #if (TS_SPI_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS2_HSIOM_REG, TS_SPI_SS2_HSIOM_MASK,
                                       TS_SPI_SS2_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
    #endif /* (TS_SPI_SS2_PIN) */

    #if (TS_SPI_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS3_HSIOM_REG, TS_SPI_SS3_HSIOM_MASK,
                                       TS_SPI_SS3_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
    #endif /* (TS_SPI_SS3_PIN) */
    }

#else

#if (TS_SPI_SPI_MASTER_SCLK_PIN)
    /* Set SCB SPI to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SCLK_M_HSIOM_REG, TS_SPI_SCLK_M_HSIOM_MASK,
                                   TS_SPI_SCLK_M_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
#endif /* (TS_SPI_MISO_SDA_TX_PIN_PIN) */

#if (TS_SPI_SPI_MASTER_SS0_PIN)
    /* Set SCB SPI to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS0_M_HSIOM_REG, TS_SPI_SS0_M_HSIOM_MASK,
                                   TS_SPI_SS0_M_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS0_PIN) */

#if (TS_SPI_SPI_MASTER_SS1_PIN)
    /* Set SCB SPI to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS1_M_HSIOM_REG, TS_SPI_SS1_M_HSIOM_MASK,
                                   TS_SPI_SS1_M_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS1_PIN) */

#if (TS_SPI_SPI_MASTER_SS2_PIN)
    /* Set SCB SPI to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS2_M_HSIOM_REG, TS_SPI_SS2_M_HSIOM_MASK,
                                   TS_SPI_SS2_M_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS2_PIN) */

#if (TS_SPI_SPI_MASTER_SS3_PIN)
    /* Set SCB SPI to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS3_M_HSIOM_REG, TS_SPI_SS3_M_HSIOM_MASK,
                                   TS_SPI_SS3_M_HSIOM_POS, TS_SPI_HSIOM_SPI_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS3_PIN) */

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_SPI_SpiStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) to
*  keep them inactive after the block is disabled. The output pins are
*  controlled by the GPIO data register.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_SpiStop(void)
{
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    if (TS_SPI_CHECK_SPI_MASTER)
    {
    #if (TS_SPI_SCLK_PIN)
        /* Set output pin state after block is disabled */
        TS_SPI_spi_sclk_Write(TS_SPI_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SCLK_HSIOM_REG, TS_SPI_SCLK_HSIOM_MASK,
                                       TS_SPI_SCLK_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
    #endif /* (TS_SPI_MISO_SDA_TX_PIN_PIN) */

    #if (TS_SPI_SS0_PIN)
        /* Set output pin state after block is disabled */
        TS_SPI_spi_ss0_Write(TS_SPI_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS0_HSIOM_REG, TS_SPI_SS0_HSIOM_MASK,
                                       TS_SPI_SS0_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
    #endif /* (TS_SPI_SS0_PIN) */

    #if (TS_SPI_SS1_PIN)
        /* Set output pin state after block is disabled */
        TS_SPI_spi_ss1_Write(TS_SPI_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS1_HSIOM_REG, TS_SPI_SS1_HSIOM_MASK,
                                       TS_SPI_SS1_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
    #endif /* (TS_SPI_SS1_PIN) */

    #if (TS_SPI_SS2_PIN)
        /* Set output pin state after block is disabled */
        TS_SPI_spi_ss2_Write(TS_SPI_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS2_HSIOM_REG, TS_SPI_SS2_HSIOM_MASK,
                                       TS_SPI_SS2_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
    #endif /* (TS_SPI_SS2_PIN) */

    #if (TS_SPI_SS3_PIN)
        /* Set output pin state after block is disabled */
        TS_SPI_spi_ss3_Write(TS_SPI_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS3_HSIOM_REG, TS_SPI_SS3_HSIOM_MASK,
                                       TS_SPI_SS3_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
    #endif /* (TS_SPI_SS3_PIN) */
    }

#else

#if (TS_SPI_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    TS_SPI_sclk_m_Write(TS_SPI_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SCLK_M_HSIOM_REG, TS_SPI_SCLK_M_HSIOM_MASK,
                                   TS_SPI_SCLK_M_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
#endif /* (TS_SPI_MISO_SDA_TX_PIN_PIN) */

#if (TS_SPI_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    TS_SPI_ss0_m_Write(TS_SPI_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS0_M_HSIOM_REG, TS_SPI_SS0_M_HSIOM_MASK,
                                   TS_SPI_SS0_M_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS0_PIN) */

#if (TS_SPI_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    TS_SPI_ss1_m_Write(TS_SPI_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS1_M_HSIOM_REG, TS_SPI_SS1_M_HSIOM_MASK,
                                   TS_SPI_SS1_M_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS1_PIN) */

#if (TS_SPI_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    TS_SPI_ss2_m_Write(TS_SPI_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS2_M_HSIOM_REG, TS_SPI_SS2_M_HSIOM_MASK,
                                   TS_SPI_SS2_M_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS2_PIN) */

#if (TS_SPI_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    TS_SPI_ss3_m_Write(TS_SPI_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    TS_SPI_SET_HSIOM_SEL(TS_SPI_SS3_M_HSIOM_REG, TS_SPI_SS3_M_HSIOM_MASK,
                                   TS_SPI_SS3_M_HSIOM_POS, TS_SPI_HSIOM_GPIO_SEL);
#endif /* (TS_SPI_SPI_MASTER_SS3_PIN) */

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (TS_SPI_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: TS_SPI_SetActiveSlaveSelect
    ********************************************************************************
    *
    * Summary:
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set)
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    * Parameters:
    *  slaveSelect: slave select line which will be active while the following
    *               transfer.
    *   TS_SPI_SPI_SLAVE_SELECT0 - Slave select 0
    *   TS_SPI_SPI_SLAVE_SELECT1 - Slave select 1
    *   TS_SPI_SPI_SLAVE_SELECT2 - Slave select 2
    *   TS_SPI_SPI_SLAVE_SELECT3 - Slave select 3
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = TS_SPI_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~TS_SPI_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  TS_SPI_GET_SPI_CTRL_SS(slaveSelect);

        TS_SPI_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (TS_SPI_SPI_MASTER_CONST) */


#if !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: TS_SPI_SpiSetSlaveSelectPolarity
    ********************************************************************************
    *
    * Summary:
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  This function does not check that these conditions are met.
    *
    * Parameters:
    *  slaveSelect: slave select line to change active polarity.
    *   TS_SPI_SPI_SLAVE_SELECT0 - Slave select 0
    *   TS_SPI_SPI_SLAVE_SELECT1 - Slave select 1
    *   TS_SPI_SPI_SLAVE_SELECT2 - Slave select 2
    *   TS_SPI_SPI_SLAVE_SELECT3 - Slave select 3
    *
    *  polarity: active polarity of slave select line.
    *   TS_SPI_SPI_SS_ACTIVE_LOW  - Slave select is active low
    *   TS_SPI_SPI_SS_ACTIVE_HIGH - Slave select is active high
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = TS_SPI_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            TS_SPI_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            TS_SPI_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */


#if(TS_SPI_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: TS_SPI_SpiSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiSaveConfig(void)
    {
        TS_SPI_ClearSpiExtClkInterruptSource(TS_SPI_INTR_SPI_EC_WAKE_UP);
        TS_SPI_SetSpiExtClkInterruptMode(TS_SPI_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiRestoreConfig(void)
    {
        TS_SPI_SetSpiExtClkInterruptMode(TS_SPI_NO_INTR_SOURCES);
    }
#endif /* (TS_SPI_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */

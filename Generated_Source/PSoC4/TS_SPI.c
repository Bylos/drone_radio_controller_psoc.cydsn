/*******************************************************************************
* File Name: TS_SPI.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if (TS_SPI_SCB_MODE_I2C_INC)
    #include "TS_SPI_I2C_PVT.h"
#endif /* (TS_SPI_SCB_MODE_I2C_INC) */

#if (TS_SPI_SCB_MODE_EZI2C_INC)
    #include "TS_SPI_EZI2C_PVT.h"
#endif /* (TS_SPI_SCB_MODE_EZI2C_INC) */

#if (TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC)
    #include "TS_SPI_SPI_UART_PVT.h"
#endif /* (TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 TS_SPI_scbMode = TS_SPI_SCB_MODE_UNCONFIG;
    uint8 TS_SPI_scbEnableWake;
    uint8 TS_SPI_scbEnableIntr;

    /* I2C configuration variables */
    uint8 TS_SPI_mode;
    uint8 TS_SPI_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * TS_SPI_rxBuffer;
    uint8  TS_SPI_rxDataBits;
    uint32 TS_SPI_rxBufferSize;

    volatile uint8 * TS_SPI_txBuffer;
    uint8  TS_SPI_txDataBits;
    uint32 TS_SPI_txBufferSize;

    /* EZI2C configuration variables */
    uint8 TS_SPI_numberOfAddr;
    uint8 TS_SPI_subAddrSize;
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 TS_SPI_initVar = 0u;

#if (TS_SPI_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER)
    void (*TS_SPI_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER) */
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void TS_SPI_ScbEnableIntr(void);
static void TS_SPI_ScbModeStop(void);
static void TS_SPI_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: TS_SPI_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_Init(void)
{
#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (TS_SPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        TS_SPI_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (TS_SPI_SCB_MODE_I2C_CONST_CFG)
    TS_SPI_I2CInit();

#elif (TS_SPI_SCB_MODE_SPI_CONST_CFG)
    TS_SPI_SpiInit();

#elif (TS_SPI_SCB_MODE_UART_CONST_CFG)
    TS_SPI_UartInit();

#elif (TS_SPI_SCB_MODE_EZI2C_CONST_CFG)
    TS_SPI_EzI2CInit();

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_SPI_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_Enable(void)
{
#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!TS_SPI_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        TS_SPI_CTRL_REG |= TS_SPI_CTRL_ENABLED;

        TS_SPI_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        TS_SPI_ScbModePostEnable();
    }
#else
    TS_SPI_CTRL_REG |= TS_SPI_CTRL_ENABLED;

    TS_SPI_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    TS_SPI_ScbModePostEnable();
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_SPI_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TS_SPI_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void TS_SPI_Start(void)
{
    if (0u == TS_SPI_initVar)
    {
        TS_SPI_Init();
        TS_SPI_initVar = 1u; /* Component was initialized */
    }

    TS_SPI_Enable();
}


/*******************************************************************************
* Function Name: TS_SPI_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void TS_SPI_Stop(void)
{
#if (TS_SPI_SCB_IRQ_INTERNAL)
    TS_SPI_DisableInt();
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    TS_SPI_ScbModeStop();

    /* Disable SCB IP */
    TS_SPI_CTRL_REG &= (uint32) ~TS_SPI_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    TS_SPI_SetTxInterruptMode(TS_SPI_NO_INTR_SOURCES);

#if (TS_SPI_SCB_IRQ_INTERNAL)
    TS_SPI_ClearPendingInt();
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: TS_SPI_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = TS_SPI_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~TS_SPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (TS_SPI_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    TS_SPI_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: TS_SPI_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void TS_SPI_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = TS_SPI_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~TS_SPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (TS_SPI_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    TS_SPI_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (TS_SPI_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: TS_SPI_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER)
        TS_SPI_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_TS_SPI_CUSTOM_INTR_HANDLER) */
    }
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: TS_SPI_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void TS_SPI_ScbEnableIntr(void)
{
#if (TS_SPI_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != TS_SPI_scbEnableIntr)
        {
            TS_SPI_EnableInt();
        }

    #else
        TS_SPI_EnableInt();

    #endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (TS_SPI_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: TS_SPI_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void TS_SPI_ScbModePostEnable(void)
{
#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!TS_SPI_CY_SCBIP_V1)
    if (TS_SPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        TS_SPI_SpiPostEnable();
    }
    else if (TS_SPI_SCB_MODE_UART_RUNTM_CFG)
    {
        TS_SPI_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!TS_SPI_CY_SCBIP_V1) */

#elif (TS_SPI_SCB_MODE_SPI_CONST_CFG)
    TS_SPI_SpiPostEnable();

#elif (TS_SPI_SCB_MODE_UART_CONST_CFG)
    TS_SPI_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: TS_SPI_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void TS_SPI_ScbModeStop(void)
{
#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    if (TS_SPI_SCB_MODE_I2C_RUNTM_CFG)
    {
        TS_SPI_I2CStop();
    }
    else if (TS_SPI_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        TS_SPI_EzI2CStop();
    }
#if (!TS_SPI_CY_SCBIP_V1)
    else if (TS_SPI_SCB_MODE_SPI_RUNTM_CFG)
    {
        TS_SPI_SpiStop();
    }
    else if (TS_SPI_SCB_MODE_UART_RUNTM_CFG)
    {
        TS_SPI_UartStop();
    }
#endif /* (!TS_SPI_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (TS_SPI_SCB_MODE_I2C_CONST_CFG)
    TS_SPI_I2CStop();

#elif (TS_SPI_SCB_MODE_EZI2C_CONST_CFG)
    TS_SPI_EzI2CStop();

#elif (TS_SPI_SCB_MODE_SPI_CONST_CFG)
    TS_SPI_SpiStop();

#elif (TS_SPI_SCB_MODE_UART_CONST_CFG)
    TS_SPI_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: TS_SPI_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [TS_SPI_SCB_PINS_NUMBER];
        uint32 pinsDm   [TS_SPI_SCB_PINS_NUMBER];

    #if (!TS_SPI_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!TS_SPI_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < TS_SPI_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = TS_SPI_HSIOM_DEF_SEL;
            pinsDm[i]    = TS_SPI_PIN_DM_ALG_HIZ;
        }

        if ((TS_SPI_SCB_MODE_I2C   == mode) ||
           (TS_SPI_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_HSIOM_I2C_SEL;
            hsiomSel[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_HSIOM_I2C_SEL;

            pinsDm[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_PIN_DM_OD_LO;
            pinsDm[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_PIN_DM_OD_LO;
        }
    #if (!TS_SPI_CY_SCBIP_V1)
        else if (TS_SPI_SCB_MODE_SPI == mode)
        {
            hsiomSel[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
            hsiomSel[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
            hsiomSel[TS_SPI_SCLK_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;

            if (TS_SPI_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;
                pinsDm[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsDm[TS_SPI_SCLK_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;

            #if (TS_SPI_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[TS_SPI_SS0_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
                pinsDm  [TS_SPI_SS0_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;
            #endif /* (TS_SPI_SS0_PIN) */

            #if (TS_SPI_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= TS_SPI_TX_SDA_MISO_PIN_MASK;
            #endif /* (TS_SPI_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsDm[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;
                pinsDm[TS_SPI_SCLK_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;

            #if (TS_SPI_SS0_PIN)
                hsiomSel [TS_SPI_SS0_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
                pinsDm   [TS_SPI_SS0_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsInBuf |= TS_SPI_SS0_PIN_MASK;
            #endif /* (TS_SPI_SS0_PIN) */

            #if (TS_SPI_SS1_PIN)
                hsiomSel [TS_SPI_SS1_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
                pinsDm   [TS_SPI_SS1_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsInBuf |= TS_SPI_SS1_PIN_MASK;
            #endif /* (TS_SPI_SS1_PIN) */

            #if (TS_SPI_SS2_PIN)
                hsiomSel [TS_SPI_SS2_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
                pinsDm   [TS_SPI_SS2_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsInBuf |= TS_SPI_SS2_PIN_MASK;
            #endif /* (TS_SPI_SS2_PIN) */

            #if (TS_SPI_SS3_PIN)
                hsiomSel [TS_SPI_SS3_PIN_INDEX] = TS_SPI_HSIOM_SPI_SEL;
                pinsDm   [TS_SPI_SS3_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;
                pinsInBuf |= TS_SPI_SS3_PIN_MASK;
            #endif /* (TS_SPI_SS3_PIN) */

                /* Disable input buffers */
            #if (TS_SPI_RX_SCL_MOSI_PIN)
                pinsInBuf |= TS_SPI_RX_SCL_MOSI_PIN_MASK;
            #endif /* (TS_SPI_RX_SCL_MOSI_PIN) */

             #if (TS_SPI_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= TS_SPI_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (TS_SPI_RX_WAKE_SCL_MOSI_PIN) */

            #if (TS_SPI_SCLK_PIN)
                pinsInBuf |= TS_SPI_SCLK_PIN_MASK;
            #endif /* (TS_SPI_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (TS_SPI_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_HSIOM_UART_SEL;
                pinsDm  [TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (TS_SPI_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_HSIOM_UART_SEL;
                    pinsDm  [TS_SPI_RX_SCL_MOSI_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;
                }

                if (0u != (TS_SPI_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_HSIOM_UART_SEL;
                    pinsDm  [TS_SPI_TX_SDA_MISO_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;

                #if (TS_SPI_TX_SDA_MISO_PIN)
                     pinsInBuf |= TS_SPI_TX_SDA_MISO_PIN_MASK;
                #endif /* (TS_SPI_TX_SDA_MISO_PIN) */
                }

            #if !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
                if (TS_SPI_UART_MODE_STD == subMode)
                {
                    if (0u != (TS_SPI_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[TS_SPI_SCLK_PIN_INDEX] = TS_SPI_HSIOM_UART_SEL;
                        pinsDm  [TS_SPI_SCLK_PIN_INDEX] = TS_SPI_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (TS_SPI_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[TS_SPI_SS0_PIN_INDEX] = TS_SPI_HSIOM_UART_SEL;
                        pinsDm  [TS_SPI_SS0_PIN_INDEX] = TS_SPI_PIN_DM_STRONG;

                    #if (TS_SPI_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= TS_SPI_SS0_PIN_MASK;
                    #endif /* (TS_SPI_SS0_PIN) */
                    }
                }
            #endif /* !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */
            }
        }
    #endif /* (!TS_SPI_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (TS_SPI_RX_WAKE_SCL_MOSI_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       TS_SPI_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       TS_SPI_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[TS_SPI_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        TS_SPI_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[TS_SPI_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     TS_SPI_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & TS_SPI_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        TS_SPI_SET_INCFG_TYPE(TS_SPI_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        TS_SPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        TS_SPI_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        TS_SPI_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (TS_SPI_RX_WAKE_SCL_MOSI_PIN) */

    #if (TS_SPI_RX_SCL_MOSI_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_RX_SCL_MOSI_HSIOM_REG,
                                       TS_SPI_RX_SCL_MOSI_HSIOM_MASK,
                                       TS_SPI_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[TS_SPI_RX_SCL_MOSI_PIN_INDEX]);

        TS_SPI_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[TS_SPI_RX_SCL_MOSI_PIN_INDEX]);

    #if (!TS_SPI_CY_SCBIP_V1)
        TS_SPI_SET_INP_DIS(TS_SPI_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     TS_SPI_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & TS_SPI_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!TS_SPI_CY_SCBIP_V1) */
    #endif /* (TS_SPI_RX_SCL_MOSI_PIN) */

    #if (TS_SPI_TX_SDA_MISO_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_TX_SDA_MISO_HSIOM_REG,
                                       TS_SPI_TX_SDA_MISO_HSIOM_MASK,
                                       TS_SPI_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[TS_SPI_TX_SDA_MISO_PIN_INDEX]);

        TS_SPI_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[TS_SPI_TX_SDA_MISO_PIN_INDEX]);

    #if (!TS_SPI_CY_SCBIP_V1)
        TS_SPI_SET_INP_DIS(TS_SPI_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     TS_SPI_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & TS_SPI_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!TS_SPI_CY_SCBIP_V1) */
    #endif /* (TS_SPI_RX_SCL_MOSI_PIN) */

    #if (TS_SPI_SCLK_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SCLK_HSIOM_REG,
                                       TS_SPI_SCLK_HSIOM_MASK,
                                       TS_SPI_SCLK_HSIOM_POS,
                                       hsiomSel[TS_SPI_SCLK_PIN_INDEX]);

        TS_SPI_spi_sclk_SetDriveMode((uint8) pinsDm[TS_SPI_SCLK_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_spi_sclk_INP_DIS,
                                     TS_SPI_spi_sclk_MASK,
                                     (0u != (pinsInBuf & TS_SPI_SCLK_PIN_MASK)));
    #endif /* (TS_SPI_SCLK_PIN) */

    #if (TS_SPI_SS0_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS0_HSIOM_REG,
                                       TS_SPI_SS0_HSIOM_MASK,
                                       TS_SPI_SS0_HSIOM_POS,
                                       hsiomSel[TS_SPI_SS0_PIN_INDEX]);

        TS_SPI_spi_ss0_SetDriveMode((uint8) pinsDm[TS_SPI_SS0_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_spi_ss0_INP_DIS,
                                     TS_SPI_spi_ss0_MASK,
                                     (0u != (pinsInBuf & TS_SPI_SS0_PIN_MASK)));
    #endif /* (TS_SPI_SS0_PIN) */

    #if (TS_SPI_SS1_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS1_HSIOM_REG,
                                       TS_SPI_SS1_HSIOM_MASK,
                                       TS_SPI_SS1_HSIOM_POS,
                                       hsiomSel[TS_SPI_SS1_PIN_INDEX]);

        TS_SPI_spi_ss1_SetDriveMode((uint8) pinsDm[TS_SPI_SS1_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_spi_ss1_INP_DIS,
                                     TS_SPI_spi_ss1_MASK,
                                     (0u != (pinsInBuf & TS_SPI_SS1_PIN_MASK)));
    #endif /* (TS_SPI_SS1_PIN) */

    #if (TS_SPI_SS2_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS2_HSIOM_REG,
                                       TS_SPI_SS2_HSIOM_MASK,
                                       TS_SPI_SS2_HSIOM_POS,
                                       hsiomSel[TS_SPI_SS2_PIN_INDEX]);

        TS_SPI_spi_ss2_SetDriveMode((uint8) pinsDm[TS_SPI_SS2_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_spi_ss2_INP_DIS,
                                     TS_SPI_spi_ss2_MASK,
                                     (0u != (pinsInBuf & TS_SPI_SS2_PIN_MASK)));
    #endif /* (TS_SPI_SS2_PIN) */

    #if (TS_SPI_SS3_PIN)
        TS_SPI_SET_HSIOM_SEL(TS_SPI_SS3_HSIOM_REG,
                                       TS_SPI_SS3_HSIOM_MASK,
                                       TS_SPI_SS3_HSIOM_POS,
                                       hsiomSel[TS_SPI_SS3_PIN_INDEX]);

        TS_SPI_spi_ss3_SetDriveMode((uint8) pinsDm[TS_SPI_SS3_PIN_INDEX]);

        TS_SPI_SET_INP_DIS(TS_SPI_spi_ss3_INP_DIS,
                                     TS_SPI_spi_ss3_MASK,
                                     (0u != (pinsInBuf & TS_SPI_SS3_PIN_MASK)));
    #endif /* (TS_SPI_SS3_PIN) */
    }

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: TS_SPI_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (TS_SPI_CTRL_REG & TS_SPI_CTRL_EC_AM_MODE)) &&
            (0u == (TS_SPI_I2C_CTRL_REG & TS_SPI_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            TS_SPI_CTRL_REG &= ~TS_SPI_CTRL_EC_AM_MODE;
            TS_SPI_CTRL_REG |=  TS_SPI_CTRL_EC_AM_MODE;
        }

        TS_SPI_I2C_SLAVE_CMD_REG = TS_SPI_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */


/* [] END OF FILE */

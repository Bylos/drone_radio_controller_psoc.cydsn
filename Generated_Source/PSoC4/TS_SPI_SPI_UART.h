/*******************************************************************************
* File Name: TS_SPI_SPI_UART.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_TS_SPI_H)
#define CY_SCB_SPI_UART_TS_SPI_H

#include "TS_SPI.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define TS_SPI_SPI_MODE                   (1u)
#define TS_SPI_SPI_SUB_MODE               (0u)
#define TS_SPI_SPI_CLOCK_MODE             (0u)
#define TS_SPI_SPI_OVS_FACTOR             (6u)
#define TS_SPI_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define TS_SPI_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define TS_SPI_SPI_RX_DATA_BITS_NUM       (8u)
#define TS_SPI_SPI_TX_DATA_BITS_NUM       (8u)
#define TS_SPI_SPI_WAKE_ENABLE            (0u)
#define TS_SPI_SPI_BITS_ORDER             (1u)
#define TS_SPI_SPI_TRANSFER_SEPARATION    (1u)
#define TS_SPI_SPI_NUMBER_OF_SS_LINES     (1u)
#define TS_SPI_SPI_RX_BUFFER_SIZE         (8u)
#define TS_SPI_SPI_TX_BUFFER_SIZE         (8u)

#define TS_SPI_SPI_INTERRUPT_MODE         (0u)

#define TS_SPI_SPI_INTR_RX_MASK           (0u)
#define TS_SPI_SPI_INTR_TX_MASK           (0u)

#define TS_SPI_SPI_RX_TRIGGER_LEVEL       (7u)
#define TS_SPI_SPI_TX_TRIGGER_LEVEL       (0u)

#define TS_SPI_SPI_BYTE_MODE_ENABLE       (0u)
#define TS_SPI_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define TS_SPI_SPI_SS0_POLARITY           (0u)
#define TS_SPI_SPI_SS1_POLARITY           (0u)
#define TS_SPI_SPI_SS2_POLARITY           (0u)
#define TS_SPI_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define TS_SPI_UART_SUB_MODE              (0u)
#define TS_SPI_UART_DIRECTION             (3u)
#define TS_SPI_UART_DATA_BITS_NUM         (8u)
#define TS_SPI_UART_PARITY_TYPE           (2u)
#define TS_SPI_UART_STOP_BITS_NUM         (2u)
#define TS_SPI_UART_OVS_FACTOR            (12u)
#define TS_SPI_UART_IRDA_LOW_POWER        (0u)
#define TS_SPI_UART_MEDIAN_FILTER_ENABLE  (0u)
#define TS_SPI_UART_RETRY_ON_NACK         (0u)
#define TS_SPI_UART_IRDA_POLARITY         (0u)
#define TS_SPI_UART_DROP_ON_FRAME_ERR     (0u)
#define TS_SPI_UART_DROP_ON_PARITY_ERR    (0u)
#define TS_SPI_UART_WAKE_ENABLE           (0u)
#define TS_SPI_UART_RX_BUFFER_SIZE        (8u)
#define TS_SPI_UART_TX_BUFFER_SIZE        (8u)
#define TS_SPI_UART_MP_MODE_ENABLE        (0u)
#define TS_SPI_UART_MP_ACCEPT_ADDRESS     (0u)
#define TS_SPI_UART_MP_RX_ADDRESS         (2u)
#define TS_SPI_UART_MP_RX_ADDRESS_MASK    (255u)

#define TS_SPI_UART_INTERRUPT_MODE        (0u)

#define TS_SPI_UART_INTR_RX_MASK          (0u)
#define TS_SPI_UART_INTR_TX_MASK          (0u)

#define TS_SPI_UART_RX_TRIGGER_LEVEL      (7u)
#define TS_SPI_UART_TX_TRIGGER_LEVEL      (0u)

#define TS_SPI_UART_BYTE_MODE_ENABLE      (0u)
#define TS_SPI_UART_CTS_ENABLE            (0u)
#define TS_SPI_UART_CTS_POLARITY          (0u)
#define TS_SPI_UART_RTS_ENABLE            (0u)
#define TS_SPI_UART_RTS_POLARITY          (0u)
#define TS_SPI_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define TS_SPI_SPI_SLAVE  (0u)
#define TS_SPI_SPI_MASTER (1u)

/* UART direction enum */
#define TS_SPI_UART_RX    (1u)
#define TS_SPI_UART_TX    (2u)
#define TS_SPI_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define TS_SPI_SPI_SLAVE_CONST        (1u)
    #define TS_SPI_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define TS_SPI_RX_DIRECTION           (1u)
    #define TS_SPI_TX_DIRECTION           (1u)
    #define TS_SPI_UART_RX_DIRECTION      (1u)
    #define TS_SPI_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define TS_SPI_INTERNAL_RX_SW_BUFFER   (0u)
    #define TS_SPI_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define TS_SPI_INTERNAL_RX_BUFFER_SIZE    (TS_SPI_rxBufferSize + 1u)
    #define TS_SPI_RX_BUFFER_SIZE             (TS_SPI_rxBufferSize)
    #define TS_SPI_TX_BUFFER_SIZE             (TS_SPI_txBufferSize)

    /* Return true if buffer is provided */
    #define TS_SPI_CHECK_RX_SW_BUFFER (NULL != TS_SPI_rxBuffer)
    #define TS_SPI_CHECK_TX_SW_BUFFER (NULL != TS_SPI_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define TS_SPI_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define TS_SPI_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define TS_SPI_SPI_WAKE_ENABLE_CONST  (1u)
    #define TS_SPI_CHECK_SPI_WAKE_ENABLE  (0u != TS_SPI_scbEnableWake)
    #define TS_SPI_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
        #define TS_SPI_SPI_UART_FIFO_SIZE             (TS_SPI_FIFO_SIZE)
        #define TS_SPI_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define TS_SPI_SPI_UART_FIFO_SIZE (TS_SPI_GET_FIFO_SIZE(TS_SPI_CTRL_REG & \
                                                                                    TS_SPI_CTRL_BYTE_MODE))

        #define TS_SPI_CHECK_UART_RTS_CONTROL_FLOW \
                    ((TS_SPI_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != TS_SPI_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(TS_SPI_UART_FLOW_CTRL_REG)))
    #endif /* (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (TS_SPI_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define TS_SPI_SPI_RX_DIRECTION (1u)
        #define TS_SPI_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
            #define TS_SPI_SPI_UART_FIFO_SIZE    (TS_SPI_FIFO_SIZE)
        #else
            #define TS_SPI_SPI_UART_FIFO_SIZE \
                                           TS_SPI_GET_FIFO_SIZE(TS_SPI_SPI_BYTE_MODE_ENABLE)

        #endif /* (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define TS_SPI_INTERNAL_SPI_RX_SW_BUFFER  (TS_SPI_SPI_RX_BUFFER_SIZE > \
                                                                TS_SPI_SPI_UART_FIFO_SIZE)
        #define TS_SPI_INTERNAL_SPI_TX_SW_BUFFER  (TS_SPI_SPI_TX_BUFFER_SIZE > \
                                                                TS_SPI_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define TS_SPI_INTERNAL_RX_SW_BUFFER  (TS_SPI_INTERNAL_SPI_RX_SW_BUFFER)
        #define TS_SPI_INTERNAL_TX_SW_BUFFER  (TS_SPI_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define TS_SPI_INTERNAL_RX_BUFFER_SIZE    (TS_SPI_SPI_RX_BUFFER_SIZE + 1u)
        #define TS_SPI_RX_BUFFER_SIZE             (TS_SPI_SPI_RX_BUFFER_SIZE)
        #define TS_SPI_TX_BUFFER_SIZE             (TS_SPI_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define TS_SPI_SPI_WAKE_ENABLE_CONST  (0u != TS_SPI_SPI_WAKE_ENABLE)
        #define TS_SPI_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define TS_SPI_UART_RX_DIRECTION (0u != (TS_SPI_UART_DIRECTION & TS_SPI_UART_RX))
        #define TS_SPI_UART_TX_DIRECTION (0u != (TS_SPI_UART_DIRECTION & TS_SPI_UART_TX))

        /* Get FIFO size */
        #if (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
            #define TS_SPI_SPI_UART_FIFO_SIZE    (TS_SPI_FIFO_SIZE)
        #else
            #define TS_SPI_SPI_UART_FIFO_SIZE \
                                           TS_SPI_GET_FIFO_SIZE(TS_SPI_UART_BYTE_MODE_ENABLE)
        #endif /* (TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define TS_SPI_INTERNAL_UART_RX_SW_BUFFER  (TS_SPI_UART_RX_BUFFER_SIZE > \
                                                                TS_SPI_SPI_UART_FIFO_SIZE)
        #define TS_SPI_INTERNAL_UART_TX_SW_BUFFER  (TS_SPI_UART_TX_BUFFER_SIZE > \
                                                                    TS_SPI_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define TS_SPI_INTERNAL_RX_SW_BUFFER  (TS_SPI_INTERNAL_UART_RX_SW_BUFFER)
        #define TS_SPI_INTERNAL_TX_SW_BUFFER  (TS_SPI_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define TS_SPI_INTERNAL_RX_BUFFER_SIZE    (TS_SPI_UART_RX_BUFFER_SIZE + 1u)
        #define TS_SPI_RX_BUFFER_SIZE             (TS_SPI_UART_RX_BUFFER_SIZE)
        #define TS_SPI_TX_BUFFER_SIZE             (TS_SPI_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define TS_SPI_SPI_WAKE_ENABLE_CONST  (0u)
        #define TS_SPI_UART_WAKE_ENABLE_CONST (0u != TS_SPI_UART_WAKE_ENABLE)

    #endif /* (TS_SPI_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define TS_SPI_SPI_SLAVE_CONST    (TS_SPI_SPI_MODE == TS_SPI_SPI_SLAVE)
    #define TS_SPI_SPI_MASTER_CONST   (TS_SPI_SPI_MODE == TS_SPI_SPI_MASTER)

    /* Direction */
    #define TS_SPI_RX_DIRECTION ((TS_SPI_SCB_MODE_SPI_CONST_CFG) ? \
                                            (TS_SPI_SPI_RX_DIRECTION) : (TS_SPI_UART_RX_DIRECTION))

    #define TS_SPI_TX_DIRECTION ((TS_SPI_SCB_MODE_SPI_CONST_CFG) ? \
                                            (TS_SPI_SPI_TX_DIRECTION) : (TS_SPI_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define TS_SPI_CHECK_RX_SW_BUFFER (TS_SPI_INTERNAL_RX_SW_BUFFER)
    #define TS_SPI_CHECK_TX_SW_BUFFER (TS_SPI_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define TS_SPI_INTERNAL_RX_SW_BUFFER_CONST    (TS_SPI_INTERNAL_RX_SW_BUFFER)
    #define TS_SPI_INTERNAL_TX_SW_BUFFER_CONST    (TS_SPI_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define TS_SPI_CHECK_SPI_WAKE_ENABLE  (TS_SPI_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define TS_SPI_CHECK_UART_RTS_CONTROL_FLOW    (TS_SPI_SCB_MODE_UART_CONST_CFG && \
                                                             TS_SPI_UART_RTS_ENABLE)

#endif /* End (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* TS_SPI_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} TS_SPI_SPI_INIT_STRUCT;

/* TS_SPI_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} TS_SPI_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    void TS_SPI_SpiInit(const TS_SPI_SPI_INIT_STRUCT *config);
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(TS_SPI_SCB_MODE_SPI_INC)
    #define TS_SPI_SpiIsBusBusy() ((uint32) (0u != (TS_SPI_SPI_STATUS_REG & \
                                                              TS_SPI_SPI_STATUS_BUS_BUSY)))

    #if (TS_SPI_SPI_MASTER_CONST)
        void TS_SPI_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(TS_SPI_SPI_MASTER_CONST) */

    #if !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
        void TS_SPI_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */
#endif /* (TS_SPI_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    void TS_SPI_UartInit(const TS_SPI_UART_INIT_STRUCT *config);
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(TS_SPI_SCB_MODE_UART_INC)
    void TS_SPI_UartSetRxAddress(uint32 address);
    void TS_SPI_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(TS_SPI_UART_RX_DIRECTION)
        uint32 TS_SPI_UartGetChar(void);
        uint32 TS_SPI_UartGetByte(void);

        #if !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void TS_SPI_UartSetRtsPolarity(uint32 polarity);
            void TS_SPI_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */
    #endif /* (TS_SPI_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(TS_SPI_UART_TX_DIRECTION)
        #define TS_SPI_UartPutChar(ch)    TS_SPI_SpiUartWriteTxData((uint32)(ch))
        void TS_SPI_UartPutString(const char8 string[]);
        void TS_SPI_UartPutCRLF(uint32 txDataByte);

        #if !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void TS_SPI_UartEnableCts(void);
            void TS_SPI_UartDisableCts(void);
            void TS_SPI_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(TS_SPI_CY_SCBIP_V0 || TS_SPI_CY_SCBIP_V1) */
    #endif /* (TS_SPI_UART_TX_DIRECTION) */
#endif /* (TS_SPI_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(TS_SPI_RX_DIRECTION)
    uint32 TS_SPI_SpiUartReadRxData(void);
    uint32 TS_SPI_SpiUartGetRxBufferSize(void);
    void   TS_SPI_SpiUartClearRxBuffer(void);
#endif /* (TS_SPI_RX_DIRECTION) */

/* Common APIs TX direction */
#if(TS_SPI_TX_DIRECTION)
    void   TS_SPI_SpiUartWriteTxData(uint32 txData);
    void   TS_SPI_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 TS_SPI_SpiUartGetTxBufferSize(void);
    void   TS_SPI_SpiUartClearTxBuffer(void);
#endif /* (TS_SPI_TX_DIRECTION) */

CY_ISR_PROTO(TS_SPI_SPI_UART_ISR);

#if(TS_SPI_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(TS_SPI_UART_WAKEUP_ISR);
#endif /* (TS_SPI_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   TS_SPI_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 TS_SPI_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   TS_SPI_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 TS_SPI_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(TS_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        #define TS_SPI_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    TS_SPI_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define TS_SPI_GetWordFromRxBuffer(idx) TS_SPI_rxBufferInternal[(idx)]

    #endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(TS_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        #define TS_SPI_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        TS_SPI_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define TS_SPI_GetWordFromTxBuffer(idx) TS_SPI_txBufferInternal[(idx)]

    #endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (TS_SPI_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define TS_SPI_SPI_MODE_MOTOROLA      (0x00u)
#define TS_SPI_SPI_MODE_TI_COINCIDES  (0x01u)
#define TS_SPI_SPI_MODE_TI_PRECEDES   (0x11u)
#define TS_SPI_SPI_MODE_NATIONAL      (0x02u)
#define TS_SPI_SPI_MODE_MASK          (0x03u)
#define TS_SPI_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define TS_SPI_SPI_MODE_NS_MICROWIRE  (TS_SPI_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define TS_SPI_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define TS_SPI_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define TS_SPI_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define TS_SPI_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define TS_SPI_BITS_ORDER_LSB_FIRST   (0u)
#define TS_SPI_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define TS_SPI_SPI_TRANSFER_SEPARATED     (0u)
#define TS_SPI_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define TS_SPI_SPI_SLAVE_SELECT0    (TS_SPI_SCB__SS0_POSISTION)
#define TS_SPI_SPI_SLAVE_SELECT1    (TS_SPI_SCB__SS1_POSISTION)
#define TS_SPI_SPI_SLAVE_SELECT2    (TS_SPI_SCB__SS2_POSISTION)
#define TS_SPI_SPI_SLAVE_SELECT3    (TS_SPI_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define TS_SPI_SPI_SS_ACTIVE_LOW  (0u)
#define TS_SPI_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define TS_SPI_UART_MODE_STD          (0u)
#define TS_SPI_UART_MODE_SMARTCARD    (1u)
#define TS_SPI_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define TS_SPI_UART_RX    (1u)
#define TS_SPI_UART_TX    (2u)
#define TS_SPI_UART_TX_RX (3u)

/* UART parity enum */
#define TS_SPI_UART_PARITY_EVEN   (0u)
#define TS_SPI_UART_PARITY_ODD    (1u)
#define TS_SPI_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define TS_SPI_UART_STOP_BITS_1   (2u)
#define TS_SPI_UART_STOP_BITS_1_5 (3u)
#define TS_SPI_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define TS_SPI_UART_IRDA_LP_OVS16     (16u)
#define TS_SPI_UART_IRDA_LP_OVS32     (32u)
#define TS_SPI_UART_IRDA_LP_OVS48     (48u)
#define TS_SPI_UART_IRDA_LP_OVS96     (96u)
#define TS_SPI_UART_IRDA_LP_OVS192    (192u)
#define TS_SPI_UART_IRDA_LP_OVS768    (768u)
#define TS_SPI_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define TS_SPI_UART_MP_MARK       (0x100u)
#define TS_SPI_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define TS_SPI_UART_CTS_ACTIVE_LOW    (0u)
#define TS_SPI_UART_CTS_ACTIVE_HIGH   (1u)
#define TS_SPI_UART_RTS_ACTIVE_LOW    (0u)
#define TS_SPI_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define TS_SPI_INTR_RX_ERR        (TS_SPI_INTR_RX_OVERFLOW    | \
                                             TS_SPI_INTR_RX_UNDERFLOW   | \
                                             TS_SPI_INTR_RX_FRAME_ERROR | \
                                             TS_SPI_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for TS_SPI_UartGetByte() */
#define TS_SPI_UART_RX_OVERFLOW       (TS_SPI_INTR_RX_OVERFLOW << 8u)
#define TS_SPI_UART_RX_UNDERFLOW      (TS_SPI_INTR_RX_UNDERFLOW << 8u)
#define TS_SPI_UART_RX_FRAME_ERROR    (TS_SPI_INTR_RX_FRAME_ERROR << 8u)
#define TS_SPI_UART_RX_PARITY_ERROR   (TS_SPI_INTR_RX_PARITY_ERROR << 8u)
#define TS_SPI_UART_RX_ERROR_MASK     (TS_SPI_UART_RX_OVERFLOW    | \
                                                 TS_SPI_UART_RX_UNDERFLOW   | \
                                                 TS_SPI_UART_RX_FRAME_ERROR | \
                                                 TS_SPI_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const TS_SPI_SPI_INIT_STRUCT  TS_SPI_configSpi;
    extern const TS_SPI_UART_INIT_STRUCT TS_SPI_configUart;
#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define TS_SPI_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & TS_SPI_INTR_SLAVE_SPI_BUS_ERROR)
#define TS_SPI_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & TS_SPI_INTR_MASTER_SPI_DONE)
#define TS_SPI_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~TS_SPI_INTR_SLAVE_SPI_BUS_ERROR)

#define TS_SPI_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~TS_SPI_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define TS_SPI_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((TS_SPI_UART_IRDA_LP_OVS16   == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS16 : \
         ((TS_SPI_UART_IRDA_LP_OVS32   == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS32 : \
          ((TS_SPI_UART_IRDA_LP_OVS48   == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS48 : \
           ((TS_SPI_UART_IRDA_LP_OVS96   == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS96 : \
            ((TS_SPI_UART_IRDA_LP_OVS192  == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS192 : \
             ((TS_SPI_UART_IRDA_LP_OVS768  == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS768 : \
              ((TS_SPI_UART_IRDA_LP_OVS1536 == (oversample)) ? TS_SPI_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          TS_SPI_CTRL_OVS_IRDA_LP_OVS16)))))))

#define TS_SPI_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (TS_SPI_UART_RX & (direction))) ? \
                                                                     (TS_SPI_RX_CTRL_ENABLED) : (0u))

#define TS_SPI_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (TS_SPI_UART_TX & (direction))) ? \
                                                                     (TS_SPI_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define TS_SPI_CTRL_SPI      (TS_SPI_CTRL_MODE_SPI)
#define TS_SPI_SPI_RX_CTRL   (TS_SPI_RX_CTRL_ENABLED)
#define TS_SPI_SPI_TX_CTRL   (TS_SPI_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define TS_SPI_SPI_SS_POLARITY \
             (((uint32) TS_SPI_SPI_SS0_POLARITY << TS_SPI_SPI_SLAVE_SELECT0) | \
              ((uint32) TS_SPI_SPI_SS1_POLARITY << TS_SPI_SPI_SLAVE_SELECT1) | \
              ((uint32) TS_SPI_SPI_SS2_POLARITY << TS_SPI_SPI_SLAVE_SELECT2) | \
              ((uint32) TS_SPI_SPI_SS3_POLARITY << TS_SPI_SPI_SLAVE_SELECT3))

#if(TS_SPI_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define TS_SPI_SPI_DEFAULT_CTRL \
                    (TS_SPI_GET_CTRL_OVS(TS_SPI_SPI_OVS_FACTOR) | \
                     TS_SPI_GET_CTRL_BYTE_MODE (TS_SPI_SPI_BYTE_MODE_ENABLE) | \
                     TS_SPI_GET_CTRL_EC_AM_MODE(TS_SPI_SPI_WAKE_ENABLE)      | \
                     TS_SPI_CTRL_SPI)

    #define TS_SPI_SPI_DEFAULT_SPI_CTRL \
                    (TS_SPI_GET_SPI_CTRL_CONTINUOUS    (TS_SPI_SPI_TRANSFER_SEPARATION)       | \
                     TS_SPI_GET_SPI_CTRL_SELECT_PRECEDE(TS_SPI_SPI_SUB_MODE &                   \
                                                                  TS_SPI_SPI_MODE_TI_PRECEDES_MASK)     | \
                     TS_SPI_GET_SPI_CTRL_SCLK_MODE     (TS_SPI_SPI_CLOCK_MODE)                | \
                     TS_SPI_GET_SPI_CTRL_LATE_MISO_SAMPLE(TS_SPI_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     TS_SPI_GET_SPI_CTRL_SCLK_CONTINUOUS(TS_SPI_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     TS_SPI_GET_SPI_CTRL_SSEL_POLARITY (TS_SPI_SPI_SS_POLARITY)               | \
                     TS_SPI_GET_SPI_CTRL_SUB_MODE      (TS_SPI_SPI_SUB_MODE)                  | \
                     TS_SPI_GET_SPI_CTRL_MASTER_MODE   (TS_SPI_SPI_MODE))

    /* RX direction */
    #define TS_SPI_SPI_DEFAULT_RX_CTRL \
                    (TS_SPI_GET_RX_CTRL_DATA_WIDTH(TS_SPI_SPI_RX_DATA_BITS_NUM)     | \
                     TS_SPI_GET_RX_CTRL_BIT_ORDER (TS_SPI_SPI_BITS_ORDER)           | \
                     TS_SPI_GET_RX_CTRL_MEDIAN    (TS_SPI_SPI_MEDIAN_FILTER_ENABLE) | \
                     TS_SPI_SPI_RX_CTRL)

    #define TS_SPI_SPI_DEFAULT_RX_FIFO_CTRL \
                    TS_SPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(TS_SPI_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define TS_SPI_SPI_DEFAULT_TX_CTRL \
                    (TS_SPI_GET_TX_CTRL_DATA_WIDTH(TS_SPI_SPI_TX_DATA_BITS_NUM) | \
                     TS_SPI_GET_TX_CTRL_BIT_ORDER (TS_SPI_SPI_BITS_ORDER)       | \
                     TS_SPI_SPI_TX_CTRL)

    #define TS_SPI_SPI_DEFAULT_TX_FIFO_CTRL \
                    TS_SPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(TS_SPI_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define TS_SPI_SPI_DEFAULT_INTR_SPI_EC_MASK   (TS_SPI_NO_INTR_SOURCES)

    #define TS_SPI_SPI_DEFAULT_INTR_I2C_EC_MASK   (TS_SPI_NO_INTR_SOURCES)
    #define TS_SPI_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (TS_SPI_SPI_INTR_RX_MASK & TS_SPI_INTR_SLAVE_SPI_BUS_ERROR)

    #define TS_SPI_SPI_DEFAULT_INTR_MASTER_MASK \
                    (TS_SPI_SPI_INTR_TX_MASK & TS_SPI_INTR_MASTER_SPI_DONE)

    #define TS_SPI_SPI_DEFAULT_INTR_RX_MASK \
                    (TS_SPI_SPI_INTR_RX_MASK & (uint32) ~TS_SPI_INTR_SLAVE_SPI_BUS_ERROR)

    #define TS_SPI_SPI_DEFAULT_INTR_TX_MASK \
                    (TS_SPI_SPI_INTR_TX_MASK & (uint32) ~TS_SPI_INTR_MASTER_SPI_DONE)

#endif /* (TS_SPI_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define TS_SPI_CTRL_UART      (TS_SPI_CTRL_MODE_UART)
#define TS_SPI_UART_RX_CTRL   (TS_SPI_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define TS_SPI_UART_TX_CTRL   (TS_SPI_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(TS_SPI_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(TS_SPI_UART_MODE_IRDA == TS_SPI_UART_SUB_MODE)

        #define TS_SPI_DEFAULT_CTRL_OVS   ((0u != TS_SPI_UART_IRDA_LOW_POWER) ?              \
                                (TS_SPI_UART_GET_CTRL_OVS_IRDA_LP(TS_SPI_UART_OVS_FACTOR)) : \
                                (TS_SPI_CTRL_OVS_IRDA_OVS16))

    #else

        #define TS_SPI_DEFAULT_CTRL_OVS   TS_SPI_GET_CTRL_OVS(TS_SPI_UART_OVS_FACTOR)

    #endif /* (TS_SPI_UART_MODE_IRDA == TS_SPI_UART_SUB_MODE) */

    #define TS_SPI_UART_DEFAULT_CTRL \
                                (TS_SPI_GET_CTRL_BYTE_MODE  (TS_SPI_UART_BYTE_MODE_ENABLE)  | \
                                 TS_SPI_GET_CTRL_ADDR_ACCEPT(TS_SPI_UART_MP_ACCEPT_ADDRESS) | \
                                 TS_SPI_DEFAULT_CTRL_OVS                                              | \
                                 TS_SPI_CTRL_UART)

    #define TS_SPI_UART_DEFAULT_UART_CTRL \
                                    (TS_SPI_GET_UART_CTRL_MODE(TS_SPI_UART_SUB_MODE))

    /* RX direction */
    #define TS_SPI_UART_DEFAULT_RX_CTRL_PARITY \
                                ((TS_SPI_UART_PARITY_NONE != TS_SPI_UART_PARITY_TYPE) ?      \
                                  (TS_SPI_GET_UART_RX_CTRL_PARITY(TS_SPI_UART_PARITY_TYPE) | \
                                   TS_SPI_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define TS_SPI_UART_DEFAULT_UART_RX_CTRL \
                    (TS_SPI_GET_UART_RX_CTRL_MODE(TS_SPI_UART_STOP_BITS_NUM)                    | \
                     TS_SPI_GET_UART_RX_CTRL_POLARITY(TS_SPI_UART_IRDA_POLARITY)                | \
                     TS_SPI_GET_UART_RX_CTRL_MP_MODE(TS_SPI_UART_MP_MODE_ENABLE)                | \
                     TS_SPI_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(TS_SPI_UART_DROP_ON_PARITY_ERR) | \
                     TS_SPI_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(TS_SPI_UART_DROP_ON_FRAME_ERR)   | \
                     TS_SPI_UART_DEFAULT_RX_CTRL_PARITY)

    #define TS_SPI_UART_DEFAULT_RX_CTRL \
                                (TS_SPI_GET_RX_CTRL_DATA_WIDTH(TS_SPI_UART_DATA_BITS_NUM)        | \
                                 TS_SPI_GET_RX_CTRL_MEDIAN    (TS_SPI_UART_MEDIAN_FILTER_ENABLE) | \
                                 TS_SPI_GET_UART_RX_CTRL_ENABLED(TS_SPI_UART_DIRECTION))

    #define TS_SPI_UART_DEFAULT_RX_FIFO_CTRL \
                                TS_SPI_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(TS_SPI_UART_RX_TRIGGER_LEVEL)

    #define TS_SPI_UART_DEFAULT_RX_MATCH_REG  ((0u != TS_SPI_UART_MP_MODE_ENABLE) ?          \
                                (TS_SPI_GET_RX_MATCH_ADDR(TS_SPI_UART_MP_RX_ADDRESS) | \
                                 TS_SPI_GET_RX_MATCH_MASK(TS_SPI_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define TS_SPI_UART_DEFAULT_TX_CTRL_PARITY (TS_SPI_UART_DEFAULT_RX_CTRL_PARITY)

    #define TS_SPI_UART_DEFAULT_UART_TX_CTRL \
                                (TS_SPI_GET_UART_TX_CTRL_MODE(TS_SPI_UART_STOP_BITS_NUM)       | \
                                 TS_SPI_GET_UART_TX_CTRL_RETRY_NACK(TS_SPI_UART_RETRY_ON_NACK) | \
                                 TS_SPI_UART_DEFAULT_TX_CTRL_PARITY)

    #define TS_SPI_UART_DEFAULT_TX_CTRL \
                                (TS_SPI_GET_TX_CTRL_DATA_WIDTH(TS_SPI_UART_DATA_BITS_NUM) | \
                                 TS_SPI_GET_UART_TX_CTRL_ENABLED(TS_SPI_UART_DIRECTION))

    #define TS_SPI_UART_DEFAULT_TX_FIFO_CTRL \
                                TS_SPI_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(TS_SPI_UART_TX_TRIGGER_LEVEL)

    #define TS_SPI_UART_DEFAULT_FLOW_CTRL \
                        (TS_SPI_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(TS_SPI_UART_RTS_FIFO_LEVEL) | \
                         TS_SPI_GET_UART_FLOW_CTRL_RTS_POLARITY (TS_SPI_UART_RTS_POLARITY)   | \
                         TS_SPI_GET_UART_FLOW_CTRL_CTS_POLARITY (TS_SPI_UART_CTS_POLARITY)   | \
                         TS_SPI_GET_UART_FLOW_CTRL_CTS_ENABLE   (TS_SPI_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define TS_SPI_UART_DEFAULT_INTR_I2C_EC_MASK  (TS_SPI_NO_INTR_SOURCES)
    #define TS_SPI_UART_DEFAULT_INTR_SPI_EC_MASK  (TS_SPI_NO_INTR_SOURCES)
    #define TS_SPI_UART_DEFAULT_INTR_SLAVE_MASK   (TS_SPI_NO_INTR_SOURCES)
    #define TS_SPI_UART_DEFAULT_INTR_MASTER_MASK  (TS_SPI_NO_INTR_SOURCES)
    #define TS_SPI_UART_DEFAULT_INTR_RX_MASK      (TS_SPI_UART_INTR_RX_MASK)
    #define TS_SPI_UART_DEFAULT_INTR_TX_MASK      (TS_SPI_UART_INTR_TX_MASK)

#endif /* (TS_SPI_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define TS_SPI_SPIM_ACTIVE_SS0    (TS_SPI_SPI_SLAVE_SELECT0)
#define TS_SPI_SPIM_ACTIVE_SS1    (TS_SPI_SPI_SLAVE_SELECT1)
#define TS_SPI_SPIM_ACTIVE_SS2    (TS_SPI_SPI_SLAVE_SELECT2)
#define TS_SPI_SPIM_ACTIVE_SS3    (TS_SPI_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_TS_SPI_H */


/* [] END OF FILE */

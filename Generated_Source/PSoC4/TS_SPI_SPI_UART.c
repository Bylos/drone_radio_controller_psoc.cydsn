/*******************************************************************************
* File Name: TS_SPI_SPI_UART.c
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(TS_SPI_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 TS_SPI_rxBufferHead;
    volatile uint32 TS_SPI_rxBufferTail;
    volatile uint8  TS_SPI_rxBufferOverflow;
#endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

#if(TS_SPI_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 TS_SPI_txBufferHead;
    volatile uint32 TS_SPI_txBufferTail;
#endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

#if(TS_SPI_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 TS_SPI_rxBufferInternal[TS_SPI_INTERNAL_RX_BUFFER_SIZE];
#endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER) */

#if(TS_SPI_INTERNAL_TX_SW_BUFFER)
    volatile uint8 TS_SPI_txBufferInternal[TS_SPI_TX_BUFFER_SIZE];
#endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER) */


#if(TS_SPI_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into TS_SPI_SpiInit for description.
    *
    *******************************************************************************/
    uint32 TS_SPI_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (TS_SPI_CHECK_RX_SW_BUFFER)
        {
            if (TS_SPI_rxBufferHead != TS_SPI_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (TS_SPI_rxBufferTail + 1u);

                if (TS_SPI_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = TS_SPI_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                TS_SPI_rxBufferTail = locTail;

                #if (TS_SPI_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (TS_SPI_INTR_RX_MASK_REG & TS_SPI_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        TS_SPI_INTR_RX_MASK_REG |= TS_SPI_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = TS_SPI_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 TS_SPI_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (TS_SPI_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (TS_SPI_CHECK_RX_SW_BUFFER)
        {
            locHead = TS_SPI_rxBufferHead;

            if(locHead >= TS_SPI_rxBufferTail)
            {
                size = (locHead - TS_SPI_rxBufferTail);
            }
            else
            {
                size = (locHead + (TS_SPI_INTERNAL_RX_BUFFER_SIZE - TS_SPI_rxBufferTail));
            }
        }
        #else
        {
            size = TS_SPI_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiUartClearRxBuffer(void)
    {
        #if (TS_SPI_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            TS_SPI_DisableInt();

            /* Flush RX software buffer */
            TS_SPI_rxBufferHead = TS_SPI_rxBufferTail;
            TS_SPI_rxBufferOverflow = 0u;

            TS_SPI_CLEAR_RX_FIFO;
            TS_SPI_ClearRxInterruptSource(TS_SPI_INTR_RX_ALL);

            #if (TS_SPI_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                TS_SPI_INTR_RX_MASK_REG |= TS_SPI_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            TS_SPI_EnableInt();
        }
        #else
        {
            TS_SPI_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (TS_SPI_RX_DIRECTION) */


#if(TS_SPI_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiUartWriteTxData(uint32 txData)
    {
    #if (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (TS_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((TS_SPI_txBufferHead == TS_SPI_txBufferTail) &&
                (TS_SPI_SPI_UART_FIFO_SIZE != TS_SPI_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                TS_SPI_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (TS_SPI_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (TS_SPI_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == TS_SPI_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                TS_SPI_ClearTxInterruptSource(TS_SPI_INTR_TX_NOT_FULL);

                TS_SPI_PutWordInTxBuffer(locHead, txData);

                TS_SPI_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (TS_SPI_INTR_TX_MASK_REG & TS_SPI_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    TS_SPI_INTR_TX_MASK_REG |= (uint32) TS_SPI_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (TS_SPI_SPI_UART_FIFO_SIZE == TS_SPI_GET_TX_FIFO_ENTRIES)
            {
            }

            TS_SPI_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            TS_SPI_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 TS_SPI_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (TS_SPI_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (TS_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = TS_SPI_txBufferTail;

            if (TS_SPI_txBufferHead >= locTail)
            {
                size = (TS_SPI_txBufferHead - locTail);
            }
            else
            {
                size = (TS_SPI_txBufferHead + (TS_SPI_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = TS_SPI_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: TS_SPI_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_SpiUartClearTxBuffer(void)
    {
        #if (TS_SPI_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            TS_SPI_DisableInt();

            /* Flush TX software buffer */
            TS_SPI_txBufferHead = TS_SPI_txBufferTail;

            TS_SPI_INTR_TX_MASK_REG &= (uint32) ~TS_SPI_INTR_TX_NOT_FULL;
            TS_SPI_CLEAR_TX_FIFO;
            TS_SPI_ClearTxInterruptSource(TS_SPI_INTR_TX_ALL);

            /* Release lock */
            TS_SPI_EnableInt();
        }
        #else
        {
            TS_SPI_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (TS_SPI_TX_DIRECTION) */


/*******************************************************************************
* Function Name: TS_SPI_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 TS_SPI_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = TS_SPI_GetRxInterruptMode();

    TS_SPI_SetRxInterruptMode(TS_SPI_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: TS_SPI_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 TS_SPI_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = TS_SPI_GetTxInterruptMode();

    TS_SPI_SetTxInterruptMode(TS_SPI_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: TS_SPI_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (TS_SPI_ONE_BYTE_WIDTH == TS_SPI_rxDataBits)
        {
            TS_SPI_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            TS_SPI_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            TS_SPI_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: TS_SPI_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 TS_SPI_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (TS_SPI_ONE_BYTE_WIDTH == TS_SPI_rxDataBits)
        {
            value = TS_SPI_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) TS_SPI_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)TS_SPI_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: TS_SPI_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void TS_SPI_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (TS_SPI_ONE_BYTE_WIDTH == TS_SPI_txDataBits)
        {
            TS_SPI_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            TS_SPI_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            TS_SPI_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: TS_SPI_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 TS_SPI_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (TS_SPI_ONE_BYTE_WIDTH == TS_SPI_txDataBits)
        {
            value = (uint32) TS_SPI_txBuffer[idx];
        }
        else
        {
            value  = (uint32) TS_SPI_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) TS_SPI_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */

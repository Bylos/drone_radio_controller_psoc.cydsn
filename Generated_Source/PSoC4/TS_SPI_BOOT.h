/*******************************************************************************
* File Name: TS_SPI_BOOT.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_TS_SPI_H)
#define CY_SCB_BOOT_TS_SPI_H

#include "TS_SPI_PVT.h"

#if (TS_SPI_SCB_MODE_I2C_INC)
    #include "TS_SPI_I2C.h"
#endif /* (TS_SPI_SCB_MODE_I2C_INC) */

#if (TS_SPI_SCB_MODE_EZI2C_INC)
    #include "TS_SPI_EZI2C.h"
#endif /* (TS_SPI_SCB_MODE_EZI2C_INC) */

#if (TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC)
    #include "TS_SPI_SPI_UART.h"
#endif /* (TS_SPI_SCB_MODE_SPI_INC || TS_SPI_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define TS_SPI_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TS_SPI) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (TS_SPI_SCB_MODE_I2C_INC)
    #define TS_SPI_I2C_BTLDR_COMM_ENABLED     (TS_SPI_BTLDR_COMM_ENABLED && \
                                                            (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             TS_SPI_I2C_SLAVE_CONST))
#else
     #define TS_SPI_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (TS_SPI_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (TS_SPI_SCB_MODE_EZI2C_INC)
    #define TS_SPI_EZI2C_BTLDR_COMM_ENABLED   (TS_SPI_BTLDR_COMM_ENABLED && \
                                                         TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define TS_SPI_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (TS_SPI_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (TS_SPI_SCB_MODE_SPI_INC)
    #define TS_SPI_SPI_BTLDR_COMM_ENABLED     (TS_SPI_BTLDR_COMM_ENABLED && \
                                                            (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             TS_SPI_SPI_SLAVE_CONST))
#else
        #define TS_SPI_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (TS_SPI_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (TS_SPI_SCB_MODE_UART_INC)
       #define TS_SPI_UART_BTLDR_COMM_ENABLED    (TS_SPI_BTLDR_COMM_ENABLED && \
                                                            (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (TS_SPI_UART_RX_DIRECTION && \
                                                              TS_SPI_UART_TX_DIRECTION)))
#else
     #define TS_SPI_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (TS_SPI_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define TS_SPI_BTLDR_COMM_MODE_ENABLED    (TS_SPI_I2C_BTLDR_COMM_ENABLED   || \
                                                     TS_SPI_SPI_BTLDR_COMM_ENABLED   || \
                                                     TS_SPI_EZI2C_BTLDR_COMM_ENABLED || \
                                                     TS_SPI_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void TS_SPI_I2CCyBtldrCommStart(void);
    void TS_SPI_I2CCyBtldrCommStop (void);
    void TS_SPI_I2CCyBtldrCommReset(void);
    cystatus TS_SPI_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus TS_SPI_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (TS_SPI_SCB_MODE_I2C_CONST_CFG)
        #define TS_SPI_CyBtldrCommStart   TS_SPI_I2CCyBtldrCommStart
        #define TS_SPI_CyBtldrCommStop    TS_SPI_I2CCyBtldrCommStop
        #define TS_SPI_CyBtldrCommReset   TS_SPI_I2CCyBtldrCommReset
        #define TS_SPI_CyBtldrCommRead    TS_SPI_I2CCyBtldrCommRead
        #define TS_SPI_CyBtldrCommWrite   TS_SPI_I2CCyBtldrCommWrite
    #endif /* (TS_SPI_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void TS_SPI_EzI2CCyBtldrCommStart(void);
    void TS_SPI_EzI2CCyBtldrCommStop (void);
    void TS_SPI_EzI2CCyBtldrCommReset(void);
    cystatus TS_SPI_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus TS_SPI_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (TS_SPI_SCB_MODE_EZI2C_CONST_CFG)
        #define TS_SPI_CyBtldrCommStart   TS_SPI_EzI2CCyBtldrCommStart
        #define TS_SPI_CyBtldrCommStop    TS_SPI_EzI2CCyBtldrCommStop
        #define TS_SPI_CyBtldrCommReset   TS_SPI_EzI2CCyBtldrCommReset
        #define TS_SPI_CyBtldrCommRead    TS_SPI_EzI2CCyBtldrCommRead
        #define TS_SPI_CyBtldrCommWrite   TS_SPI_EzI2CCyBtldrCommWrite
    #endif /* (TS_SPI_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void TS_SPI_SpiCyBtldrCommStart(void);
    void TS_SPI_SpiCyBtldrCommStop (void);
    void TS_SPI_SpiCyBtldrCommReset(void);
    cystatus TS_SPI_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus TS_SPI_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (TS_SPI_SCB_MODE_SPI_CONST_CFG)
        #define TS_SPI_CyBtldrCommStart   TS_SPI_SpiCyBtldrCommStart
        #define TS_SPI_CyBtldrCommStop    TS_SPI_SpiCyBtldrCommStop
        #define TS_SPI_CyBtldrCommReset   TS_SPI_SpiCyBtldrCommReset
        #define TS_SPI_CyBtldrCommRead    TS_SPI_SpiCyBtldrCommRead
        #define TS_SPI_CyBtldrCommWrite   TS_SPI_SpiCyBtldrCommWrite
    #endif /* (TS_SPI_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void TS_SPI_UartCyBtldrCommStart(void);
    void TS_SPI_UartCyBtldrCommStop (void);
    void TS_SPI_UartCyBtldrCommReset(void);
    cystatus TS_SPI_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus TS_SPI_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (TS_SPI_SCB_MODE_UART_CONST_CFG)
        #define TS_SPI_CyBtldrCommStart   TS_SPI_UartCyBtldrCommStart
        #define TS_SPI_CyBtldrCommStop    TS_SPI_UartCyBtldrCommStop
        #define TS_SPI_CyBtldrCommReset   TS_SPI_UartCyBtldrCommReset
        #define TS_SPI_CyBtldrCommRead    TS_SPI_UartCyBtldrCommRead
        #define TS_SPI_CyBtldrCommWrite   TS_SPI_UartCyBtldrCommWrite
    #endif /* (TS_SPI_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_BTLDR_COMM_ENABLED)
    #if (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void TS_SPI_CyBtldrCommStart(void);
        void TS_SPI_CyBtldrCommStop (void);
        void TS_SPI_CyBtldrCommReset(void);
        cystatus TS_SPI_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus TS_SPI_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (TS_SPI_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TS_SPI)
        #define CyBtldrCommStart    TS_SPI_CyBtldrCommStart
        #define CyBtldrCommStop     TS_SPI_CyBtldrCommStop
        #define CyBtldrCommReset    TS_SPI_CyBtldrCommReset
        #define CyBtldrCommWrite    TS_SPI_CyBtldrCommWrite
        #define CyBtldrCommRead     TS_SPI_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_TS_SPI) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (TS_SPI_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define TS_SPI_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define TS_SPI_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define TS_SPI_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define TS_SPI_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef TS_SPI_SPI_BYTE_TO_BYTE
    #define TS_SPI_SPI_BYTE_TO_BYTE   (3u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef TS_SPI_UART_BYTE_TO_BYTE
    #define TS_SPI_UART_BYTE_TO_BYTE  (2500u)
#endif /* TS_SPI_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_TS_SPI_H) */


/* [] END OF FILE */

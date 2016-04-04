/*******************************************************************************
* File Name: TS_I2C_I2C.h
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  the I2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_TS_I2C_H)
#define CY_SCB_I2C_TS_I2C_H

#include "TS_I2C.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define TS_I2C_I2C_MODE                   (2u)
#define TS_I2C_I2C_OVS_FACTOR_LOW         (8u)
#define TS_I2C_I2C_OVS_FACTOR_HIGH        (8u)
#define TS_I2C_I2C_MEDIAN_FILTER_ENABLE   (1u)
#define TS_I2C_I2C_SLAVE_ADDRESS          (8u)
#define TS_I2C_I2C_SLAVE_ADDRESS_MASK     (254u)
#define TS_I2C_I2C_ACCEPT_ADDRESS         (0u)
#define TS_I2C_I2C_ACCEPT_GENERAL_CALL    (0u)
#define TS_I2C_I2C_WAKE_ENABLE            (0u)
#define TS_I2C_I2C_DATA_RATE              (100u)
#define TS_I2C_I2C_DATA_RATE_ACTUAL       (91u)
#define TS_I2C_I2C_CLOCK_FROM_TERM        (0u)
#define TS_I2C_I2C_EXTERN_INTR_HANDLER    (0u)
#define TS_I2C_I2C_BYTE_MODE_ENABLE       (0u)
#define TS_I2C_I2C_MANUAL_OVS_CONTROL     (0u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* I2C sub mode enum */
#define TS_I2C_I2C_MODE_SLAVE              (0x01u)
#define TS_I2C_I2C_MODE_MASTER             (0x02u)
#define TS_I2C_I2C_MODE_MULTI_MASTER       (0x06u)
#define TS_I2C_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define TS_I2C_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

#if (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Returns true if slave mode is enabled */
    #define TS_I2C_I2C_SLAVE  (0u != (TS_I2C_I2C_MODE_SLAVE & TS_I2C_mode))

    /* Returns true if master mode is enabled */
    #define TS_I2C_I2C_MASTER (0u != (TS_I2C_I2C_MODE_MASTER & TS_I2C_mode))

    /* Returns true if multi-master mode is enabled */
    #define TS_I2C_I2C_MULTI_MASTER \
                            (0u != (TS_I2C_I2C_MODE_MULTI_MASTER_MASK & TS_I2C_mode))

    /* Returns true if mode is multi-master-slave */
    #define TS_I2C_I2C_MULTI_MASTER_SLAVE \
                            (TS_I2C_I2C_MODE_MULTI_MASTER_SLAVE == TS_I2C_mode)

    /* Returns true if address accepts in RX FIFO */
    #define TS_I2C_CHECK_I2C_ACCEPT_ADDRESS   (0u != TS_I2C_acceptAddr)
    #define TS_I2C_CHECK_I2C_GENERAL_CALL \
                (0u != (TS_I2C_I2C_CTRL_REG & TS_I2C_I2C_CTRL_S_GENERAL_IGNORE))

    #define TS_I2C_I2C_WAKE_ENABLE_CONST              (1u)
    #define TS_I2C_I2C_SLAVE_CONST                    (1u)
    #define TS_I2C_I2C_MASTER_CONST                   (1u)
    #define TS_I2C_I2C_MULTI_MASTER_SLAVE_CONST       (1u)
    #define TS_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST     (1u)
    #define TS_I2C_CHECK_I2C_GENERAL_CALL_CONST       (1u)
    #define TS_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (1u)

    /* Returns FIFO size */
    #if (TS_I2C_CY_SCBIP_V0 || TS_I2C_CY_SCBIP_V1)
        #define TS_I2C_I2C_FIFO_SIZE      (TS_I2C_FIFO_SIZE)
    #else
        #define TS_I2C_I2C_FIFO_SIZE      (TS_I2C_GET_FIFO_SIZE(TS_I2C_CTRL_REG & \
                                                                                    TS_I2C_CTRL_BYTE_MODE))
    #endif /* (TS_I2C_CY_SCBIP_V0 || TS_I2C_CY_SCBIP_V1) */

#else

    /* Returns true if slave mode is enabled */
    #define TS_I2C_I2C_SLAVE   (0u != (TS_I2C_I2C_MODE_SLAVE & TS_I2C_I2C_MODE))

    /* Returns true if master mode is enabled */
    #define TS_I2C_I2C_MASTER  (0u != (TS_I2C_I2C_MODE_MASTER & TS_I2C_I2C_MODE))

    /* Returns true if multi-master mode is enabled */
    #define TS_I2C_I2C_MULTI_MASTER \
                                    (0u != (TS_I2C_I2C_MODE_MULTI_MASTER_MASK & TS_I2C_I2C_MODE))

    /* Returns true if mode is multi-master-slave */
    #define TS_I2C_I2C_MULTI_MASTER_SLAVE \
                                    (TS_I2C_I2C_MODE_MULTI_MASTER_SLAVE == TS_I2C_I2C_MODE)

    /* Returns true if address accepts in RX FIFO */
    #define TS_I2C_CHECK_I2C_ACCEPT_ADDRESS   (0u != TS_I2C_I2C_ACCEPT_ADDRESS)
    #define TS_I2C_CHECK_I2C_GENERAL_CALL     (0u != TS_I2C_I2C_ACCEPT_GENERAL_CALL)

    /* Returns true if wakeup on address match is enabled */
    #define TS_I2C_I2C_WAKE_ENABLE_CONST  (0u != TS_I2C_I2C_WAKE_ENABLE)

    #define TS_I2C_I2C_SLAVE_CONST    (TS_I2C_I2C_SLAVE)
    #define TS_I2C_I2C_MASTER_CONST   (TS_I2C_I2C_MASTER)
    #define TS_I2C_I2C_MULTI_MASTER_SLAVE_CONST   (TS_I2C_I2C_MULTI_MASTER_SLAVE)
    #define TS_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST (TS_I2C_CHECK_I2C_ACCEPT_ADDRESS)
    #define TS_I2C_CHECK_I2C_GENERAL_CALL_CONST   (TS_I2C_CHECK_I2C_GENERAL_CALL)
    #define TS_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (TS_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST || \
                                                                  TS_I2C_CHECK_I2C_GENERAL_CALL_CONST)

    /* I2C: TX or RX FIFO size */
    #if (TS_I2C_CY_SCBIP_V0 || TS_I2C_CY_SCBIP_V1)
        #define TS_I2C_I2C_FIFO_SIZE  (TS_I2C_FIFO_SIZE)
    #else
        #define TS_I2C_I2C_FIFO_SIZE  TS_I2C_GET_FIFO_SIZE(TS_I2C_I2C_BYTE_MODE_ENABLE)
    #endif /* (TS_I2C_CY_SCBIP_V0 || TS_I2C_CY_SCBIP_V1) */

    /* Adjust AF and DF filter settings. Ticket ID#176179 */
    #if ((TS_I2C_I2C_MODE_SLAVE == TS_I2C_I2C_MODE) ||     \
            ((TS_I2C_I2C_MODE_SLAVE != TS_I2C_I2C_MODE) && \
             (TS_I2C_I2C_DATA_RATE_ACTUAL <= TS_I2C_I2C_DATA_RATE_FS_MODE_MAX)))

        #define TS_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ       (0u)
        #define TS_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    do{;}while(0)
    #else
        #define TS_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ       (1u)
        #define TS_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    TS_I2C_I2C_CFG_ANALOG_FITER_DISABLE
    #endif

    /* Select oversampling factor low and high */
    #define TS_I2C_I2C_OVS_FACTOR_LOW_MIN     ((0u != TS_I2C_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (8u) : (9u))

    #define TS_I2C_I2C_OVS_FACTOR_HIGH_MIN    ((0u != TS_I2C_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (8u) : (9u))

#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#define TS_I2C_I2C_CUSTOM_ADDRESS_HANDLER (TS_I2C_CHECK_I2C_GENERAL_CALL || \
                                                     TS_I2C_CHECK_I2C_ACCEPT_ADDRESS)


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint32 mode;
    uint32 oversampleLow;
    uint32 oversampleHigh;
    uint32 enableMedianFilter;
    uint32 slaveAddr;
    uint32 slaveAddrMask;
    uint32 acceptAddr;
    uint32 enableWake;
    uint8  enableByteMode;
    uint16 dataRate;
    uint8  acceptGeneralAddr;
} TS_I2C_I2C_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Common functions */
#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    void TS_I2C_I2CInit(const TS_I2C_I2C_INIT_STRUCT *config);
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (TS_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    void TS_I2C_SetI2cAddressCustomInterruptHandler(uint32 (*func) (void));
#endif /* (TS_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/* I2C Master functions prototypes */
#if(TS_I2C_I2C_MASTER_CONST)
    /* Read and Clear status functions */
    uint32 TS_I2C_I2CMasterStatus(void);
    uint32 TS_I2C_I2CMasterClearStatus(void);

    /* Interrupt based operation functions */
    uint32 TS_I2C_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode);
    uint32 TS_I2C_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode);
    uint32 TS_I2C_I2CMasterGetReadBufSize(void);
    uint32 TS_I2C_I2CMasterGetWriteBufSize(void);
    void   TS_I2C_I2CMasterClearReadBuf(void);
    void   TS_I2C_I2CMasterClearWriteBuf(void);

    /* Manual operation functions */
    uint32 TS_I2C_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW);
    uint32 TS_I2C_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW);
    uint32 TS_I2C_I2CMasterSendStop(void);
    uint32 TS_I2C_I2CMasterWriteByte(uint32 theByte);
    uint32 TS_I2C_I2CMasterReadByte(uint32 ackNack);
#endif /* (TS_I2C_I2C_MASTER_CONST) */

/* I2C Slave functions prototypes */
#if(TS_I2C_I2C_SLAVE_CONST)
    /* Read and Clear status functions */
    uint32 TS_I2C_I2CSlaveStatus(void);
    uint32 TS_I2C_I2CSlaveClearReadStatus(void);
    uint32 TS_I2C_I2CSlaveClearWriteStatus(void);

    /* Set Slave address and mask */
    void   TS_I2C_I2CSlaveSetAddress(uint32 address);
    void   TS_I2C_I2CSlaveSetAddressMask(uint32 addressMask);

    /* Interrupt based operation functions */
    void   TS_I2C_I2CSlaveInitReadBuf(uint8 * rdBuf, uint32 bufSize);
    void   TS_I2C_I2CSlaveInitWriteBuf(uint8 * wrBuf, uint32 bufSize);
    uint32 TS_I2C_I2CSlaveGetReadBufSize(void);
    uint32 TS_I2C_I2CSlaveGetWriteBufSize(void);
    void   TS_I2C_I2CSlaveClearReadBuf(void);
    void   TS_I2C_I2CSlaveClearWriteBuf(void);
#endif /* (TS_I2C_I2C_SLAVE_CONST) */

CY_ISR_PROTO(TS_I2C_I2C_ISR);


/***************************************
*            API Constants
***************************************/

/* I2C sub mode enum */
#define TS_I2C_I2C_MODE_SLAVE              (0x01u)
#define TS_I2C_I2C_MODE_MASTER             (0x02u)
#define TS_I2C_I2C_MODE_MULTI_MASTER       (0x06u)
#define TS_I2C_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define TS_I2C_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

/* Master/Slave control constants */
#define TS_I2C_I2C_WRITE_XFER_MODE    (0u)    /* Write    */
#define TS_I2C_I2C_READ_XFER_MODE     (1u)    /* Read     */
#define TS_I2C_I2C_ACK_ADDR           (0u)    /* Send ACK to address */
#define TS_I2C_I2C_NAK_ADDR           (1u)    /* Send NAK to address */
#define TS_I2C_I2C_ACK_DATA           (0u)    /* Send ACK to data */
#define TS_I2C_I2C_NAK_DATA           (1u)    /* Send NAK to data */

/* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
#define TS_I2C_I2C_MODE_COMPLETE_XFER     (0x00u)    /* Full transfer with Start and Stop       */
#define TS_I2C_I2C_MODE_REPEAT_START      (0x01u)    /* Begin with a ReStart instead of a Start */
#define TS_I2C_I2C_MODE_NO_STOP           (0x02u)    /* Complete the transfer without a Stop    */

/* Master status */
#define TS_I2C_I2C_MSTAT_CLEAR            ((uint16) 0x00u)   /* Clear (init) status value */

#define TS_I2C_I2C_MSTAT_RD_CMPLT         ((uint16) 0x01u)   /* Read complete               */
#define TS_I2C_I2C_MSTAT_WR_CMPLT         ((uint16) 0x02u)   /* Write complete              */
#define TS_I2C_I2C_MSTAT_XFER_INP         ((uint16) 0x04u)   /* Master transfer in progress */
#define TS_I2C_I2C_MSTAT_XFER_HALT        ((uint16) 0x08u)   /* Transfer is halted          */

#define TS_I2C_I2C_MSTAT_ERR_MASK         ((uint16) 0x3F0u) /* Mask for all errors                          */
#define TS_I2C_I2C_MSTAT_ERR_SHORT_XFER   ((uint16) 0x10u)  /* Master NAKed before end of packet            */
#define TS_I2C_I2C_MSTAT_ERR_ADDR_NAK     ((uint16) 0x20u)  /* Slave did not ACK                            */
#define TS_I2C_I2C_MSTAT_ERR_ARB_LOST     ((uint16) 0x40u)  /* Master lost arbitration during communication */
#define TS_I2C_I2C_MSTAT_ERR_ABORT_XFER   ((uint16) 0x80u)  /* The Slave was addressed before the Start gen */
#define TS_I2C_I2C_MSTAT_ERR_BUS_ERROR    ((uint16) 0x100u) /* The misplaced Start or Stop was occurred     */
#define TS_I2C_I2C_MSTAT_ERR_XFER         ((uint16) 0x200u) /* Error during transfer                        */

/* Master API returns */
#define TS_I2C_I2C_MSTR_NO_ERROR          (0x00u)  /* Function complete without error                       */
#define TS_I2C_I2C_MSTR_ERR_ARB_LOST      (0x01u)  /* Master lost arbitration: INTR_MASTER_I2C_ARB_LOST     */
#define TS_I2C_I2C_MSTR_ERR_LB_NAK        (0x02u)  /* Last Byte Naked: INTR_MASTER_I2C_NACK                 */
#define TS_I2C_I2C_MSTR_NOT_READY         (0x04u)  /* Master on the bus or Slave operation is in progress   */
#define TS_I2C_I2C_MSTR_BUS_BUSY          (0x08u)  /* Bus is busy, process not started                      */
#define TS_I2C_I2C_MSTR_ERR_ABORT_START   (0x10u)  /* Slave was addressed before master begin Start gen     */
#define TS_I2C_I2C_MSTR_ERR_BUS_ERR       (0x100u) /* Bus error has: INTR_MASTER_I2C_BUS_ERROR              */

/* Slave Status Constants */
#define TS_I2C_I2C_SSTAT_RD_CMPLT         (0x01u)    /* Read transfer complete                        */
#define TS_I2C_I2C_SSTAT_RD_BUSY          (0x02u)    /* Read transfer in progress                     */
#define TS_I2C_I2C_SSTAT_RD_OVFL          (0x04u)    /* Read overflow: master reads above buffer size */
#define TS_I2C_I2C_SSTAT_RD_ERR           (0x08u)    /* Read was interrupted by misplaced Start/Stop  */
#define TS_I2C_I2C_SSTAT_RD_MASK          (0x0Fu)    /* Read Status Mask                              */
#define TS_I2C_I2C_SSTAT_RD_NO_ERR        (0x00u)    /* Read no Error                                 */

#define TS_I2C_I2C_SSTAT_WR_CMPLT         (0x10u)    /* Write transfer complete                         */
#define TS_I2C_I2C_SSTAT_WR_BUSY          (0x20u)    /* Write transfer in progress                      */
#define TS_I2C_I2C_SSTAT_WR_OVFL          (0x40u)    /* Write overflow: master writes above buffer size */
#define TS_I2C_I2C_SSTAT_WR_ERR           (0x80u)    /* Write was interrupted by misplaced Start/Stop   */
#define TS_I2C_I2C_SSTAT_WR_MASK          (0xF0u)    /* Write Status Mask                               */
#define TS_I2C_I2C_SSTAT_WR_NO_ERR        (0x00u)    /* Write no Error                                  */

#define TS_I2C_I2C_SSTAT_RD_CLEAR         (0x0Du)    /* Read Status clear: do not clear */
#define TS_I2C_I2C_SSTAT_WR_CLEAR         (0xD0u)    /* Write Status Clear */

/* Internal I2C component constants */
#define TS_I2C_I2C_READ_FLAG              (0x01u)     /* Read flag of the Address */
#define TS_I2C_I2C_SLAVE_OVFL_RETURN      (0xFFu)     /* Return by slave when overflow */

#define TS_I2C_I2C_RESET_ERROR            (0x01u)     /* Flag to re-enable SCB IP */


/***************************************
*     Vars with External Linkage
***************************************/

#if(TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const TS_I2C_I2C_INIT_STRUCT TS_I2C_configI2C;
#endif /* (TS_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

#define TS_I2C_I2C_FSM_EXIT_IDLE      (0x00u) /* Master and Slave are not active, need to exit to IDLE */

/* Slave mode FSM states */
#define TS_I2C_I2C_FSM_IDLE           (0x10u) /* Idle I2C state                */
#define TS_I2C_I2C_FSM_SLAVE          (0x10u) /* Slave mask for all its states */

#define TS_I2C_I2C_FSM_SL_WR          (0x11u) /* Slave write states */
#define TS_I2C_I2C_FSM_SL_RD          (0x12u) /* Slave read  states */

/* Master mode FSM states */
#define TS_I2C_I2C_FSM_MASTER         (0x20u) /* Master mask for all its states */
#define TS_I2C_I2C_FSM_MSTR_ADDR      (0x08u) /* Master address phase           */
#define TS_I2C_I2C_FSM_MSTR_DATA      (0x04u) /* Master data phase              */
#define TS_I2C_I2C_FSM_MSTR_RD        (0x01u) /* Master read phase              */

#define TS_I2C_I2C_FSM_MSTR_WR_ADDR   (0x28u) /* FSM master transmit address with write          */
#define TS_I2C_I2C_FSM_MSTR_RD_ADDR   (0x29u) /* FSM master transmit address with read           */
#define TS_I2C_I2C_FSM_MSTR_WR_DATA   (0x24u) /* FSM master writes data into the slave           */
#define TS_I2C_I2C_FSM_MSTR_RD_DATA   (0x25u) /* FSM master reads data from the slave            */
#define TS_I2C_I2C_FSM_MSTR_HALT      (0x60u) /* FSM master halt state: wait for Stop or ReStart */

/* Requests to complete any on-going transfer */
#define TS_I2C_I2C_CMPLT_ANY_TRANSFER     (0x01u)

/* Returns true if FSM is in any Master state */
#define TS_I2C_CHECK_I2C_FSM_MASTER   (0u != (TS_I2C_I2C_FSM_MASTER & TS_I2C_state))

/* Returns true if FSM is in any Slave state */
#define TS_I2C_CHECK_I2C_FSM_SLAVE    (0u != (TS_I2C_I2C_FSM_SLAVE  & TS_I2C_state))

/* Returns true if FSM is in Master send address state */
#define TS_I2C_CHECK_I2C_FSM_ADDR (0u != (TS_I2C_I2C_FSM_MSTR_ADDR & TS_I2C_state))

/* Returns true if FSM is in Master send or receive data state */
#define TS_I2C_CHECK_I2C_FSM_DATA (0u != (TS_I2C_I2C_FSM_MSTR_DATA  & TS_I2C_state))

/* Returns true if FSM is in any of read states: applied for Slave and Master */
#define TS_I2C_CHECK_I2C_FSM_RD   (0u != (TS_I2C_I2C_FSM_MSTR_RD  & TS_I2C_state))

/* Returns true if FSM is in IDLE state */
#define TS_I2C_CHECK_I2C_FSM_IDLE (TS_I2C_I2C_FSM_IDLE == TS_I2C_state)

/* Returns true if FSM is HALT state */
#define TS_I2C_CHECK_I2C_FSM_HALT (TS_I2C_I2C_FSM_MSTR_HALT == TS_I2C_state)

/* Set Master read or write completion depends on state */
#define TS_I2C_GET_I2C_MSTAT_CMPLT (TS_I2C_CHECK_I2C_FSM_RD ?           \
                                                    (TS_I2C_I2C_MSTAT_RD_CMPLT) : \
                                                    (TS_I2C_I2C_MSTAT_WR_CMPLT))


/***************************************
*       Macro Definitions
***************************************/

/* Returns TRUE if sourceMask is set in TS_I2C_I2C_MASTER_CMD_REG: used to check if Start was generated */
#define TS_I2C_CHECK_I2C_MASTER_CMD(sourceMask)   (0u != (TS_I2C_I2C_MASTER_CMD_REG & (sourceMask)))

/* Returns TRUE if TS_I2C_MODE_NO_STOP is set in TS_I2C_mstrControl: detects NoStop condition */
#define TS_I2C_CHECK_I2C_MODE_NO_STOP(mode)   (0u != (TS_I2C_I2C_MODE_NO_STOP & (mode)))

/* Returns TRUE if TS_I2C_MODE_REPEAT_START is set: used to detect when generate ReStart condition */
#define TS_I2C_CHECK_I2C_MODE_RESTART(mode)   (0u != (TS_I2C_I2C_MODE_REPEAT_START  & (mode)))

/* Returns TRUE if TS_I2C_state is in one of master states */
#define TS_I2C_CHECK_I2C_MASTER_ACTIVE    (TS_I2C_CHECK_I2C_FSM_MASTER)


/***************************************
*      Common Register Settings
***************************************/

#define TS_I2C_CTRL_I2C       (TS_I2C_CTRL_MODE_I2C)

#define TS_I2C_I2C_CTRL       (TS_I2C_I2C_CTRL_S_GENERAL_IGNORE)

#define TS_I2C_I2C_RX_CTRL    ((TS_I2C_FIFO_SIZE - 1u)  | \
                                         TS_I2C_RX_CTRL_MSB_FIRST | \
                                         TS_I2C_RX_CTRL_ENABLED)

#define TS_I2C_I2C_TX_CTRL    ((TS_I2C_FIFO_SIZE - 1u)  | \
                                         TS_I2C_TX_CTRL_MSB_FIRST | \
                                         TS_I2C_TX_CTRL_ENABLED)

#define TS_I2C_I2C_INTR_SLAVE_MASK    (TS_I2C_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                 TS_I2C_INTR_SLAVE_I2C_NACK       | \
                                                 TS_I2C_INTR_SLAVE_I2C_WRITE_STOP | \
                                                 TS_I2C_INTR_SLAVE_I2C_BUS_ERROR  | \
                                                 TS_I2C_INTR_SLAVE_I2C_ARB_LOST)

#define TS_I2C_I2C_INTR_MASTER_MASK   (TS_I2C_INTR_MASTER_I2C_ARB_LOST | \
                                                 TS_I2C_INTR_MASTER_I2C_NACK     | \
                                                 TS_I2C_INTR_MASTER_I2C_STOP     | \
                                                 TS_I2C_INTR_MASTER_I2C_BUS_ERROR)

/* Calculates tLOW in uS units */
#define TS_I2C_I2C_TLOW_TIME  ((1000u / TS_I2C_I2C_DATA_RATE) + \
                                            ((0u != (1000u % TS_I2C_I2C_DATA_RATE)) ? (1u) : (0u)))
/* tHIGH = tLOW */
#define TS_I2C_I2C_THIGH_TIME (TS_I2C_I2C_TLOW_TIME)

#define TS_I2C_I2C_SCL_LOW    (0u)
#define TS_I2C_I2C_SCL_HIGH   (1u)

#define TS_I2C_I2C_IGNORE_GENERAL_CALL    ((uint32) (0u == TS_I2C_I2C_ACCEPT_GENERAL_CALL))


/***************************************
*    Initialization Register Settings
***************************************/

#if(TS_I2C_SCB_MODE_I2C_CONST_CFG)

    #if (!TS_I2C_CY_SCBIP_V0)
        #define TS_I2C_I2C_WAKE_ENABLE_ADJ    (TS_I2C_I2C_MULTI_MASTER_SLAVE ? \
                                                            (0u) : (TS_I2C_I2C_WAKE_ENABLE))
    #else
        #define TS_I2C_I2C_WAKE_ENABLE_ADJ    (TS_I2C_I2C_WAKE_ENABLE)
    #endif /* (!TS_I2C_CY_SCBIP_V0) */

    #define TS_I2C_I2C_MODE_MASKED    (TS_I2C_I2C_MODE & \
                                                (TS_I2C_I2C_MODE_SLAVE | TS_I2C_I2C_MODE_MASTER))

    #define TS_I2C_I2C_DEFAULT_CTRL \
                                (TS_I2C_GET_CTRL_BYTE_MODE  (TS_I2C_I2C_BYTE_MODE_ENABLE) | \
                                 TS_I2C_GET_CTRL_ADDR_ACCEPT(TS_I2C_I2C_ACCEPT_ADDRESS)   | \
                                 TS_I2C_GET_CTRL_EC_AM_MODE (TS_I2C_I2C_WAKE_ENABLE_ADJ))

    #define TS_I2C_I2C_DEFAULT_I2C_CTRL \
                    (TS_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(TS_I2C_I2C_OVS_FACTOR_HIGH_MIN)   | \
                     TS_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (TS_I2C_I2C_OVS_FACTOR_LOW_MIN)    | \
                     TS_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE(TS_I2C_I2C_IGNORE_GENERAL_CALL) | \
                     TS_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (TS_I2C_I2C_MODE_MASKED))

    #define TS_I2C_I2C_DEFAULT_RX_MATCH ((TS_I2C_I2C_SLAVE) ? \
                                (TS_I2C_GET_I2C_8BIT_ADDRESS(TS_I2C_I2C_SLAVE_ADDRESS) | \
                                 TS_I2C_GET_RX_MATCH_MASK   (TS_I2C_I2C_SLAVE_ADDRESS_MASK)) : (0u))

    #define TS_I2C_I2C_DEFAULT_RX_CTRL \
                                (TS_I2C_GET_RX_CTRL_MEDIAN(TS_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ) | \
                                 TS_I2C_I2C_RX_CTRL)

    #define TS_I2C_I2C_DEFAULT_TX_CTRL  (TS_I2C_I2C_TX_CTRL)

    #define TS_I2C_I2C_DEFAULT_RX_FIFO_CTRL (0u)
    #define TS_I2C_I2C_DEFAULT_TX_FIFO_CTRL (0u)

    /* Interrupt sources */
    #define TS_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK   (TS_I2C_NO_INTR_SOURCES)
    #define TS_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK   (TS_I2C_NO_INTR_SOURCES)
    #define TS_I2C_I2C_DEFAULT_INTR_RX_MASK       (TS_I2C_NO_INTR_SOURCES)
    #define TS_I2C_I2C_DEFAULT_INTR_TX_MASK       (TS_I2C_NO_INTR_SOURCES)

    #define TS_I2C_I2C_DEFAULT_INTR_SLAVE_MASK    ((TS_I2C_I2C_SLAVE) ? \
                (TS_I2C_I2C_INTR_SLAVE_MASK | \
                 TS_I2C_GET_INTR_SLAVE_I2C_GENERAL(TS_I2C_I2C_ACCEPT_GENERAL_CALL)) : (0u))

    #define TS_I2C_I2C_DEFAULT_INTR_MASTER_MASK   ((TS_I2C_I2C_MASTER) ? \
                                                                (TS_I2C_I2C_INTR_MASTER_MASK) : (0u))

#endif /* (TS_I2C_SCB_MODE_I2C_CONST_CFG) */

#endif /* (CY_SCB_I2C_TS_I2C_H) */


/* [] END OF FILE */

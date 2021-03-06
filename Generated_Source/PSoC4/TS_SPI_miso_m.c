/*******************************************************************************
* File Name: TS_SPI_miso_m.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "TS_SPI_miso_m.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TS_SPI_miso_m_PC =   (TS_SPI_miso_m_PC & \
                                (uint32)(~(uint32)(TS_SPI_miso_m_DRIVE_MODE_IND_MASK << (TS_SPI_miso_m_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TS_SPI_miso_m_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TS_SPI_miso_m_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void TS_SPI_miso_m_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TS_SPI_miso_m_DR & (uint8)(~TS_SPI_miso_m_MASK));
    drVal = (drVal | ((uint8)(value << TS_SPI_miso_m_SHIFT) & TS_SPI_miso_m_MASK));
    TS_SPI_miso_m_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TS_SPI_miso_m_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TS_SPI_miso_m_DM_STRONG     Strong Drive 
*  TS_SPI_miso_m_DM_OD_HI      Open Drain, Drives High 
*  TS_SPI_miso_m_DM_OD_LO      Open Drain, Drives Low 
*  TS_SPI_miso_m_DM_RES_UP     Resistive Pull Up 
*  TS_SPI_miso_m_DM_RES_DWN    Resistive Pull Down 
*  TS_SPI_miso_m_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TS_SPI_miso_m_DM_DIG_HIZ    High Impedance Digital 
*  TS_SPI_miso_m_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TS_SPI_miso_m_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TS_SPI_miso_m__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TS_SPI_miso_m_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro TS_SPI_miso_m_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TS_SPI_miso_m_Read(void) 
{
    return (uint8)((TS_SPI_miso_m_PS & TS_SPI_miso_m_MASK) >> TS_SPI_miso_m_SHIFT);
}


/*******************************************************************************
* Function Name: TS_SPI_miso_m_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 TS_SPI_miso_m_ReadDataReg(void) 
{
    return (uint8)((TS_SPI_miso_m_DR & TS_SPI_miso_m_MASK) >> TS_SPI_miso_m_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TS_SPI_miso_m_INTSTAT) 

    /*******************************************************************************
    * Function Name: TS_SPI_miso_m_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 TS_SPI_miso_m_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TS_SPI_miso_m_INTSTAT & TS_SPI_miso_m_MASK);
		TS_SPI_miso_m_INTSTAT = maskedStatus;
        return maskedStatus >> TS_SPI_miso_m_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

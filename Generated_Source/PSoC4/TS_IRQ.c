/*******************************************************************************
* File Name: TS_IRQ.c  
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
#include "TS_IRQ.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        TS_IRQ_PC =   (TS_IRQ_PC & \
                                (uint32)(~(uint32)(TS_IRQ_DRIVE_MODE_IND_MASK << (TS_IRQ_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (TS_IRQ_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: TS_IRQ_Write
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
void TS_IRQ_Write(uint8 value) 
{
    uint8 drVal = (uint8)(TS_IRQ_DR & (uint8)(~TS_IRQ_MASK));
    drVal = (drVal | ((uint8)(value << TS_IRQ_SHIFT) & TS_IRQ_MASK));
    TS_IRQ_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: TS_IRQ_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TS_IRQ_DM_STRONG     Strong Drive 
*  TS_IRQ_DM_OD_HI      Open Drain, Drives High 
*  TS_IRQ_DM_OD_LO      Open Drain, Drives Low 
*  TS_IRQ_DM_RES_UP     Resistive Pull Up 
*  TS_IRQ_DM_RES_DWN    Resistive Pull Down 
*  TS_IRQ_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TS_IRQ_DM_DIG_HIZ    High Impedance Digital 
*  TS_IRQ_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TS_IRQ_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(TS_IRQ__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: TS_IRQ_Read
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
*  Macro TS_IRQ_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TS_IRQ_Read(void) 
{
    return (uint8)((TS_IRQ_PS & TS_IRQ_MASK) >> TS_IRQ_SHIFT);
}


/*******************************************************************************
* Function Name: TS_IRQ_ReadDataReg
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
uint8 TS_IRQ_ReadDataReg(void) 
{
    return (uint8)((TS_IRQ_DR & TS_IRQ_MASK) >> TS_IRQ_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TS_IRQ_INTSTAT) 

    /*******************************************************************************
    * Function Name: TS_IRQ_ClearInterrupt
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
    uint8 TS_IRQ_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(TS_IRQ_INTSTAT & TS_IRQ_MASK);
		TS_IRQ_INTSTAT = maskedStatus;
        return maskedStatus >> TS_IRQ_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

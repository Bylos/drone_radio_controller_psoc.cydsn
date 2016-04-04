/*******************************************************************************
* File Name: MoM_Hi.c  
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
#include "MoM_Hi.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        MoM_Hi_PC =   (MoM_Hi_PC & \
                                (uint32)(~(uint32)(MoM_Hi_DRIVE_MODE_IND_MASK << (MoM_Hi_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (MoM_Hi_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: MoM_Hi_Write
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
void MoM_Hi_Write(uint8 value) 
{
    uint8 drVal = (uint8)(MoM_Hi_DR & (uint8)(~MoM_Hi_MASK));
    drVal = (drVal | ((uint8)(value << MoM_Hi_SHIFT) & MoM_Hi_MASK));
    MoM_Hi_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: MoM_Hi_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  MoM_Hi_DM_STRONG     Strong Drive 
*  MoM_Hi_DM_OD_HI      Open Drain, Drives High 
*  MoM_Hi_DM_OD_LO      Open Drain, Drives Low 
*  MoM_Hi_DM_RES_UP     Resistive Pull Up 
*  MoM_Hi_DM_RES_DWN    Resistive Pull Down 
*  MoM_Hi_DM_RES_UPDWN  Resistive Pull Up/Down 
*  MoM_Hi_DM_DIG_HIZ    High Impedance Digital 
*  MoM_Hi_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void MoM_Hi_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(MoM_Hi__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: MoM_Hi_Read
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
*  Macro MoM_Hi_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 MoM_Hi_Read(void) 
{
    return (uint8)((MoM_Hi_PS & MoM_Hi_MASK) >> MoM_Hi_SHIFT);
}


/*******************************************************************************
* Function Name: MoM_Hi_ReadDataReg
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
uint8 MoM_Hi_ReadDataReg(void) 
{
    return (uint8)((MoM_Hi_DR & MoM_Hi_MASK) >> MoM_Hi_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(MoM_Hi_INTSTAT) 

    /*******************************************************************************
    * Function Name: MoM_Hi_ClearInterrupt
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
    uint8 MoM_Hi_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(MoM_Hi_INTSTAT & MoM_Hi_MASK);
		MoM_Hi_INTSTAT = maskedStatus;
        return maskedStatus >> MoM_Hi_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

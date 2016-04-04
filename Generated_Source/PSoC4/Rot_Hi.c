/*******************************************************************************
* File Name: Rot_Hi.c  
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
#include "Rot_Hi.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Rot_Hi_PC =   (Rot_Hi_PC & \
                                (uint32)(~(uint32)(Rot_Hi_DRIVE_MODE_IND_MASK << (Rot_Hi_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Rot_Hi_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Rot_Hi_Write
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
void Rot_Hi_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Rot_Hi_DR & (uint8)(~Rot_Hi_MASK));
    drVal = (drVal | ((uint8)(value << Rot_Hi_SHIFT) & Rot_Hi_MASK));
    Rot_Hi_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Rot_Hi_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Rot_Hi_DM_STRONG     Strong Drive 
*  Rot_Hi_DM_OD_HI      Open Drain, Drives High 
*  Rot_Hi_DM_OD_LO      Open Drain, Drives Low 
*  Rot_Hi_DM_RES_UP     Resistive Pull Up 
*  Rot_Hi_DM_RES_DWN    Resistive Pull Down 
*  Rot_Hi_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Rot_Hi_DM_DIG_HIZ    High Impedance Digital 
*  Rot_Hi_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Rot_Hi_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Rot_Hi__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Rot_Hi_Read
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
*  Macro Rot_Hi_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Rot_Hi_Read(void) 
{
    return (uint8)((Rot_Hi_PS & Rot_Hi_MASK) >> Rot_Hi_SHIFT);
}


/*******************************************************************************
* Function Name: Rot_Hi_ReadDataReg
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
uint8 Rot_Hi_ReadDataReg(void) 
{
    return (uint8)((Rot_Hi_DR & Rot_Hi_MASK) >> Rot_Hi_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Rot_Hi_INTSTAT) 

    /*******************************************************************************
    * Function Name: Rot_Hi_ClearInterrupt
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
    uint8 Rot_Hi_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Rot_Hi_INTSTAT & Rot_Hi_MASK);
		Rot_Hi_INTSTAT = maskedStatus;
        return maskedStatus >> Rot_Hi_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

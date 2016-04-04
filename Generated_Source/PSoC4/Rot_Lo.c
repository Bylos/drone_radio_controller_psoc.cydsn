/*******************************************************************************
* File Name: Rot_Lo.c  
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
#include "Rot_Lo.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Rot_Lo_PC =   (Rot_Lo_PC & \
                                (uint32)(~(uint32)(Rot_Lo_DRIVE_MODE_IND_MASK << (Rot_Lo_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Rot_Lo_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Rot_Lo_Write
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
void Rot_Lo_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Rot_Lo_DR & (uint8)(~Rot_Lo_MASK));
    drVal = (drVal | ((uint8)(value << Rot_Lo_SHIFT) & Rot_Lo_MASK));
    Rot_Lo_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Rot_Lo_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Rot_Lo_DM_STRONG     Strong Drive 
*  Rot_Lo_DM_OD_HI      Open Drain, Drives High 
*  Rot_Lo_DM_OD_LO      Open Drain, Drives Low 
*  Rot_Lo_DM_RES_UP     Resistive Pull Up 
*  Rot_Lo_DM_RES_DWN    Resistive Pull Down 
*  Rot_Lo_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Rot_Lo_DM_DIG_HIZ    High Impedance Digital 
*  Rot_Lo_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Rot_Lo_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Rot_Lo__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Rot_Lo_Read
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
*  Macro Rot_Lo_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Rot_Lo_Read(void) 
{
    return (uint8)((Rot_Lo_PS & Rot_Lo_MASK) >> Rot_Lo_SHIFT);
}


/*******************************************************************************
* Function Name: Rot_Lo_ReadDataReg
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
uint8 Rot_Lo_ReadDataReg(void) 
{
    return (uint8)((Rot_Lo_DR & Rot_Lo_MASK) >> Rot_Lo_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Rot_Lo_INTSTAT) 

    /*******************************************************************************
    * Function Name: Rot_Lo_ClearInterrupt
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
    uint8 Rot_Lo_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Rot_Lo_INTSTAT & Rot_Lo_MASK);
		Rot_Lo_INTSTAT = maskedStatus;
        return maskedStatus >> Rot_Lo_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

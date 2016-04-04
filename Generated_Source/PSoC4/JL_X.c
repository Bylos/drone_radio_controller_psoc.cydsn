/*******************************************************************************
* File Name: JL_X.c  
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
#include "JL_X.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        JL_X_PC =   (JL_X_PC & \
                                (uint32)(~(uint32)(JL_X_DRIVE_MODE_IND_MASK << (JL_X_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (JL_X_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: JL_X_Write
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
void JL_X_Write(uint8 value) 
{
    uint8 drVal = (uint8)(JL_X_DR & (uint8)(~JL_X_MASK));
    drVal = (drVal | ((uint8)(value << JL_X_SHIFT) & JL_X_MASK));
    JL_X_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: JL_X_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  JL_X_DM_STRONG     Strong Drive 
*  JL_X_DM_OD_HI      Open Drain, Drives High 
*  JL_X_DM_OD_LO      Open Drain, Drives Low 
*  JL_X_DM_RES_UP     Resistive Pull Up 
*  JL_X_DM_RES_DWN    Resistive Pull Down 
*  JL_X_DM_RES_UPDWN  Resistive Pull Up/Down 
*  JL_X_DM_DIG_HIZ    High Impedance Digital 
*  JL_X_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void JL_X_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(JL_X__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: JL_X_Read
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
*  Macro JL_X_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 JL_X_Read(void) 
{
    return (uint8)((JL_X_PS & JL_X_MASK) >> JL_X_SHIFT);
}


/*******************************************************************************
* Function Name: JL_X_ReadDataReg
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
uint8 JL_X_ReadDataReg(void) 
{
    return (uint8)((JL_X_DR & JL_X_MASK) >> JL_X_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(JL_X_INTSTAT) 

    /*******************************************************************************
    * Function Name: JL_X_ClearInterrupt
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
    uint8 JL_X_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(JL_X_INTSTAT & JL_X_MASK);
		JL_X_INTSTAT = maskedStatus;
        return maskedStatus >> JL_X_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

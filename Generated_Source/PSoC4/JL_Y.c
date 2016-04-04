/*******************************************************************************
* File Name: JL_Y.c  
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
#include "JL_Y.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        JL_Y_PC =   (JL_Y_PC & \
                                (uint32)(~(uint32)(JL_Y_DRIVE_MODE_IND_MASK << (JL_Y_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (JL_Y_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: JL_Y_Write
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
void JL_Y_Write(uint8 value) 
{
    uint8 drVal = (uint8)(JL_Y_DR & (uint8)(~JL_Y_MASK));
    drVal = (drVal | ((uint8)(value << JL_Y_SHIFT) & JL_Y_MASK));
    JL_Y_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: JL_Y_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  JL_Y_DM_STRONG     Strong Drive 
*  JL_Y_DM_OD_HI      Open Drain, Drives High 
*  JL_Y_DM_OD_LO      Open Drain, Drives Low 
*  JL_Y_DM_RES_UP     Resistive Pull Up 
*  JL_Y_DM_RES_DWN    Resistive Pull Down 
*  JL_Y_DM_RES_UPDWN  Resistive Pull Up/Down 
*  JL_Y_DM_DIG_HIZ    High Impedance Digital 
*  JL_Y_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void JL_Y_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(JL_Y__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: JL_Y_Read
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
*  Macro JL_Y_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 JL_Y_Read(void) 
{
    return (uint8)((JL_Y_PS & JL_Y_MASK) >> JL_Y_SHIFT);
}


/*******************************************************************************
* Function Name: JL_Y_ReadDataReg
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
uint8 JL_Y_ReadDataReg(void) 
{
    return (uint8)((JL_Y_DR & JL_Y_MASK) >> JL_Y_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(JL_Y_INTSTAT) 

    /*******************************************************************************
    * Function Name: JL_Y_ClearInterrupt
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
    uint8 JL_Y_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(JL_Y_INTSTAT & JL_Y_MASK);
		JL_Y_INTSTAT = maskedStatus;
        return maskedStatus >> JL_Y_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

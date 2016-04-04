/*******************************************************************************
* File Name: JL_SEL.c  
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
#include "JL_SEL.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        JL_SEL_PC =   (JL_SEL_PC & \
                                (uint32)(~(uint32)(JL_SEL_DRIVE_MODE_IND_MASK << (JL_SEL_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (JL_SEL_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: JL_SEL_Write
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
void JL_SEL_Write(uint8 value) 
{
    uint8 drVal = (uint8)(JL_SEL_DR & (uint8)(~JL_SEL_MASK));
    drVal = (drVal | ((uint8)(value << JL_SEL_SHIFT) & JL_SEL_MASK));
    JL_SEL_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: JL_SEL_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  JL_SEL_DM_STRONG     Strong Drive 
*  JL_SEL_DM_OD_HI      Open Drain, Drives High 
*  JL_SEL_DM_OD_LO      Open Drain, Drives Low 
*  JL_SEL_DM_RES_UP     Resistive Pull Up 
*  JL_SEL_DM_RES_DWN    Resistive Pull Down 
*  JL_SEL_DM_RES_UPDWN  Resistive Pull Up/Down 
*  JL_SEL_DM_DIG_HIZ    High Impedance Digital 
*  JL_SEL_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void JL_SEL_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(JL_SEL__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: JL_SEL_Read
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
*  Macro JL_SEL_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 JL_SEL_Read(void) 
{
    return (uint8)((JL_SEL_PS & JL_SEL_MASK) >> JL_SEL_SHIFT);
}


/*******************************************************************************
* Function Name: JL_SEL_ReadDataReg
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
uint8 JL_SEL_ReadDataReg(void) 
{
    return (uint8)((JL_SEL_DR & JL_SEL_MASK) >> JL_SEL_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(JL_SEL_INTSTAT) 

    /*******************************************************************************
    * Function Name: JL_SEL_ClearInterrupt
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
    uint8 JL_SEL_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(JL_SEL_INTSTAT & JL_SEL_MASK);
		JL_SEL_INTSTAT = maskedStatus;
        return maskedStatus >> JL_SEL_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

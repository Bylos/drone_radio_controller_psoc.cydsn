/*******************************************************************************
* File Name: SW2_L.c  
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
#include "SW2_L.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SW2_L_PC =   (SW2_L_PC & \
                                (uint32)(~(uint32)(SW2_L_DRIVE_MODE_IND_MASK << (SW2_L_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SW2_L_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SW2_L_Write
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
void SW2_L_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SW2_L_DR & (uint8)(~SW2_L_MASK));
    drVal = (drVal | ((uint8)(value << SW2_L_SHIFT) & SW2_L_MASK));
    SW2_L_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SW2_L_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SW2_L_DM_STRONG     Strong Drive 
*  SW2_L_DM_OD_HI      Open Drain, Drives High 
*  SW2_L_DM_OD_LO      Open Drain, Drives Low 
*  SW2_L_DM_RES_UP     Resistive Pull Up 
*  SW2_L_DM_RES_DWN    Resistive Pull Down 
*  SW2_L_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SW2_L_DM_DIG_HIZ    High Impedance Digital 
*  SW2_L_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SW2_L_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SW2_L__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SW2_L_Read
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
*  Macro SW2_L_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SW2_L_Read(void) 
{
    return (uint8)((SW2_L_PS & SW2_L_MASK) >> SW2_L_SHIFT);
}


/*******************************************************************************
* Function Name: SW2_L_ReadDataReg
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
uint8 SW2_L_ReadDataReg(void) 
{
    return (uint8)((SW2_L_DR & SW2_L_MASK) >> SW2_L_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SW2_L_INTSTAT) 

    /*******************************************************************************
    * Function Name: SW2_L_ClearInterrupt
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
    uint8 SW2_L_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SW2_L_INTSTAT & SW2_L_MASK);
		SW2_L_INTSTAT = maskedStatus;
        return maskedStatus >> SW2_L_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */

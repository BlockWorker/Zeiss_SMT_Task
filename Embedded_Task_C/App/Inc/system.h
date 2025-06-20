/*
 * system.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 * 	Contains the central initialisation and system management logic.
 */

#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_


#include "common.h"


typedef enum {
  REV_A = REV_A_VALUE,
  REV_B = REV_B_VALUE,
  REV_C = REV_C_VALUE
} HardwareRevision;


//the currently active hardware revision
extern HardwareRevision hardware_revision;


//Performs system initialisation, returns success
bool SYSTEM_Init();

//Performs main system loop processing
void SYSTEM_LoopUpdate();

//Handles ADC conversion-complete interrupts
void SYSTEM_HandleADCInterrupt();


#endif /* INC_SYSTEM_H_ */

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


//Performs system initialisation, returns success
bool SYSTEM_Init();

//Performs main system loop processing
void SYSTEM_LoopUpdate();

//Handles ADC conversion-complete interrupts
void SYSTEM_HandleADCInterrupt();


#endif /* INC_SYSTEM_H_ */

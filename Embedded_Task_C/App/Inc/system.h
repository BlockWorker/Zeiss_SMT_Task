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

//Handles a new temperature update interrupt
void SYSTEM_HandleTempUpdateInterrupt();


#endif /* INC_SYSTEM_H_ */

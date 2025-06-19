/*
 * display.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Implements the temperature display logic.
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_


#include "common.h"


typedef enum {
  DISP_OFF = 0,
  DISP_NORMAL = 1,
  DISP_WARNING = 2,
  DISP_CRITICAL = 3
} DISPLAY_State;


//Performs initialisation of the display, returns success
bool DISPLAY_Init();

//Updates the display based on the given temperature (in °C)
void DISPLAY_Update(float temperature);

//Returns the current display state
DISPLAY_State DISPLAY_GetState();


#endif /* INC_DISPLAY_H_ */

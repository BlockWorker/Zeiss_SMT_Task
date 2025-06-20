/*
 * display.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Implements the temperature display logic.
 */

#include "display.h"
#include "bsp.h"


//current display state - assume off by default
static DISPLAY_State display_state = DISP_OFF;


//Performs initialisation of the display, returns success
bool DISPLAY_Init() {
  //turn display off by default
  display_state = DISP_OFF;
  BSP_SetDisplay(display_state);

  return true;
}

//Updates the display based on the given temperature (in °C)
void DISPLAY_Update(float temperature) {
  if (temperature >= DISP_NORMAL_TEMP_MIN && temperature < DISP_NORMAL_TEMP_MAX) {
    //normal temperature range
    display_state = DISP_NORMAL;
  } else if (temperature >= DISP_WARNING_TEMP_MIN && temperature < DISP_WARNING_TEMP_MAX) {
    //warning temperature range
    display_state = DISP_WARNING;
  } else {
    //critical temperature range
    display_state = DISP_CRITICAL;
  }

  //update physical display accordingly
  BSP_SetDisplay(display_state);
}

//Returns the current display state
DISPLAY_State DISPLAY_GetState() {
  return display_state;
}

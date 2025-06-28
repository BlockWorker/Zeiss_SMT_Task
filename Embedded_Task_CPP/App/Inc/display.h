/*
 * display.h
 *
 *  Created on: Jun 20, 2025
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
} DisplayState;


class Display {
public:
  //Performs initialisation of the display, returns success
  bool Init();

  //Updates the display based on the given temperature (in °C)
  void Update(float temperature);

  //Returns the current display state
  DisplayState GetState() const;

  //initialise the display to be off at first
  Display() : display_state(DISP_OFF) {}

private:
  DisplayState display_state;
};


#endif /* INC_DISPLAY_H_ */

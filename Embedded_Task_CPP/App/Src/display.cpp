/*
 * display.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Implements the temperature display logic.
 */


#include "display.h"
#include "system_manager.h"


//Performs initialisation of the display, returns success
bool Display::Init() {
  BSP* bsp = SystemManager::instance.GetBSP();
  if (bsp == NULL) {
    return false;
  }

  //turn display off by default
  this->display_state = DISP_OFF;
  bsp->SetDisplay(this->display_state);

  return true;
}

//Updates the display based on the given temperature (in °C)
void Display::Update(float temperature) {
  if (temperature >= DISP_NORMAL_TEMP_MIN && temperature < DISP_NORMAL_TEMP_MAX) {
    //normal temperature range
    this->display_state = DISP_NORMAL;
  } else if (temperature >= DISP_WARNING_TEMP_MIN && temperature < DISP_WARNING_TEMP_MAX) {
    //warning temperature range
    this->display_state = DISP_WARNING;
  } else {
    //critical temperature range
    this->display_state = DISP_CRITICAL;
  }

  //update physical display accordingly
  BSP* bsp = SystemManager::instance.GetBSP();
  if (bsp != NULL) {
    bsp->SetDisplay(this->display_state);
  }
}

//Returns the current display state
DisplayState Display::GetState() const {
  return this->display_state;
}

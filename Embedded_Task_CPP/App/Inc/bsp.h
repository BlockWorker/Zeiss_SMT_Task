/*
 * bsp.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains the Board Support Package (hardware interface abstraction) and related types/definitions.
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_


#include "common.h"
#include "display.h"


class BSP {
public:
  //initialises and enables the temperature sensor ADC, returns success
  bool StartADC();
  //gets the latest temperature ADC measurement, in ADC counts
  uint32_t GetADCValue() const;

  //sets the physical display to the given state
  void SetDisplay(DisplayState state);

  //read `length` bytes starting at EEPROM address `address` into `buffer`, returns success
  bool ReadEEPROM(uint16_t address, uint8_t* buffer, uint8_t length);

  BSP() {}
};


#endif /* INC_BSP_H_ */

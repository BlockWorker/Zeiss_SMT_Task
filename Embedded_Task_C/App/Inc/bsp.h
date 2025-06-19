/*
 * bsp.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the Board Support Package (hardware interface abstraction) and related types/definitions.
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_


#include "common.h"
#include "display.h"


//maximum value of ADC counts (i.e., ADC count value of positive reference)
#define BSP_ADC_COUNT_MAX 4095


typedef enum {
  REV_A = 0,
  REV_B = 1,
  REV_C = 2
} BSP_HardwareRevision;


//the currently active hardware revision
extern BSP_HardwareRevision hardware_revision;


/******************************************
 *               TEMP/ADC                 *
 ******************************************/

//initialises and enables the temperature sensor ADC, returns success
bool BSP_StartADC();

//gets the latest temperature ADC measurement, in ADC counts
uint32_t BSP_GetADCValue();


/******************************************
 *                DISPLAY                 *
 ******************************************/

//sets the physical display to the given state
void BSP_SetDisplay(DISPLAY_State state);


/******************************************
 *                EEPROM                  *
 ******************************************/

//read `length` bytes starting at EEPROM address `address` into `buffer`, returns success
bool BSP_ReadEEPROM(uint16_t address, uint8_t* buffer, uint8_t length);


#endif /* INC_BSP_H_ */

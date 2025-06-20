/*
 * config.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */

#include "config.h"
#include "bsp.h"


//memory address of the hardware revision
#define CONFIG_REVISION_ADDRESS 0
//length of the hardware revision, in bytes
#define CONFIG_REVISION_SIZE 1

//memory address of the serial number
#define CONFIG_SERIAL_ADDRESS 1
//length of the serial number, in bytes
#define CONFIG_SERIAL_LENGTH 8


//serial number, initially empty
static char config_serial_number[CONFIG_SERIAL_LENGTH + 1] = "";


//Reads the configuration from ROM, returns success
bool CONFIG_Load() {
  //read revision from EEPROM
  uint8_t revision;
  if (!BSP_ReadEEPROM(CONFIG_REVISION_ADDRESS, &revision, CONFIG_REVISION_SIZE)) {
    return false;
  }

  //check for revision validity
  if (revision == REV_A || revision == REV_B || revision == REV_C) {
    //valid: update hardware revision, continue
    hardware_revision = (BSP_HardwareRevision)revision;
  } else {
    //invalid: return failure
    return false;
  }

  //read serial number from EEPROM, ensuring zero-termination
  if (!BSP_ReadEEPROM(CONFIG_SERIAL_ADDRESS, (uint8_t*)config_serial_number, CONFIG_SERIAL_LENGTH)) {
    //read failed: reset serial number to empty, return failure
    config_serial_number[0] = 0;
    return false;
  } else {
    //read successful: ensure null-termination of serial number
    config_serial_number[CONFIG_SERIAL_LENGTH] = 0;
  }

  return true;
}

//Returns the serial number string specified in the configuration
const char* CONFIG_GetSerialNumber() {
  return config_serial_number;
}

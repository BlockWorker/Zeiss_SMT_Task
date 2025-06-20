/*
 * hardware_config.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */

#include "hardware_config.h"
#include "bsp.h"
#include "system.h"


//serial number, initially empty
static char config_serial_number[CONFIG_SERIAL_LENGTH + 1] = "";


//Reads the configuration from ROM, returns success
bool CONFIG_Load() {
  //read revision from EEPROM
  uint8_t revision;
  if (!BSP_ReadEEPROM(CONFIG_REVISION_ADDRESS, &revision, CONFIG_REVISION_LENGTH)) {
    return false;
  }

  //check for revision validity
  if (revision == REV_A_VALUE || revision == REV_B_VALUE || revision == REV_C_VALUE) {
    //valid: update hardware revision, continue
    hardware_revision = (HardwareRevision)revision;
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

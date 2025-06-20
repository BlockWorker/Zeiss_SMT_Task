/*
 * hardware_config.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */


#include "hardware_config.h"
#include "system_manager.h"


//Reads the configuration from ROM, returns success
bool HardwareConfig::Load() {
  BSP* bsp = SystemManager::instance.GetBSP();
  if (bsp == NULL) {
    return false;
  }

  //read revision from EEPROM
  uint8_t revision;
  if (!bsp->ReadEEPROM(CONFIG_REVISION_ADDRESS, &revision, CONFIG_REVISION_LENGTH)) {
    return false;
  }

  //check for revision validity
  if (revision == REV_A_VALUE || revision == REV_B_VALUE || revision == REV_C_VALUE) {
    //valid: update hardware revision, continue
    SystemManager::instance.SetHardwareRevision((HardwareRevision)revision);
  } else {
    //invalid: return failure
    return false;
  }

  //read serial number from EEPROM
  this->serial_number.resize(CONFIG_SERIAL_LENGTH);
  if (!bsp->ReadEEPROM(CONFIG_SERIAL_ADDRESS, (uint8_t*)this->serial_number.data(), CONFIG_SERIAL_LENGTH)) {
    //read failed: reset serial number to empty, return failure
    this->serial_number.clear();
    return false;
  }

  return true;
}

//Returns the serial number string specified in the configuration
const std::string& HardwareConfig::GetSerialNumber() const {
  return this->serial_number;
}

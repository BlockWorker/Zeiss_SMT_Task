/*
 * hardware_config.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */

#ifndef INC_HARDWARE_CONFIG_H_
#define INC_HARDWARE_CONFIG_H_


#include "common.h"
#include <string>


class HardwareConfig {
public:
  //Reads the configuration from ROM, returns success
  bool Load();

  //Returns the serial number string specified in the configuration
  const std::string& GetSerialNumber() const;

  HardwareConfig() {}

private:
  std::string serial_number;
};


#endif /* INC_HARDWARE_CONFIG_H_ */

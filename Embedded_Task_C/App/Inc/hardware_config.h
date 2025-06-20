/*
 * hardware_config.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */

#ifndef INC_HARDWARE_CONFIG_H_
#define INC_HARDWARE_CONFIG_H_


#include "common.h"


//Reads the configuration from ROM, returns success
bool CONFIG_Load();

//Returns the serial number string specified in the configuration
const char* CONFIG_GetSerialNumber();


#endif /* INC_HARDWARE_CONFIG_H_ */

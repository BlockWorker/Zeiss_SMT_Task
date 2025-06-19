/*
 * config.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the hardware configuration settings.
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_


#include "common.h"


//Reads the configuration from ROM, returns success
bool CONFIG_Read();

//Returns the serial number string specified in the configuration
char* CONFIG_GetSerialNumber();


#endif /* INC_CONFIG_H_ */

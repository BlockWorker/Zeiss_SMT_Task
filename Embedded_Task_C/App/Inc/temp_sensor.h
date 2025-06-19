/*
 * temp_sensor.h
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Handles the temperature sensor interaction.
 */

#ifndef INC_TEMP_SENSOR_H_
#define INC_TEMP_SENSOR_H_


#include "common.h"


//Performs initialisation of the temperature sensor, returns success
bool TEMP_Init();

//Handles a new temperature update interrupt
void TEMP_UpdateInterrupt();

//Returns the last measured temperature, in °C
float TEMP_GetLast();


#endif /* INC_TEMP_SENSOR_H_ */

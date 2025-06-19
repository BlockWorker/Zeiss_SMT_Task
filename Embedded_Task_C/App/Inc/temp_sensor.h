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

//Processes a new temperature value in ADC counts, converting it to °C
float TEMP_HandleUpdate(uint32_t adc_counts);

//Returns the last measured temperature, in °C
float TEMP_GetLast();


#endif /* INC_TEMP_SENSOR_H_ */

/*
 * temp_sensor.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Handles the temperature sensor interaction.
 */


#include "temp_sensor.h"
#include "system_manager.h"
#include <cmath>


//Performs initialisation of the temperature sensor, returns success
bool TempSensor::Init() {
  BSP* bsp = SystemManager::instance.GetBSP();
  if (bsp == NULL) {
    return false;
  }

  //reset "last" measurement to default
  this->temp_last = TEMP_DEFAULT_VALUE;

  //initialise and start the ADC
  return bsp->StartADC();
}

//Returns the last measured temperature, in °C
float TempSensor::GetLast() const {
  return this->temp_last;
}


//Processes a new temperature value in ADC counts, converting it to °C, for hardware revision A
float TempSensor_RevA::HandleUpdate(uint32_t adc_counts) {
  //apply simple conversion factor
  this->temp_last = (float)adc_counts * TEMP_REV_A_FACTOR;

  return this->temp_last;
}


//Processes a new temperature value in ADC counts, converting it to °C, for hardware revision B
float TempSensor_RevB::HandleUpdate(uint32_t adc_counts) {
  //apply simple conversion factor
  this->temp_last = (float)adc_counts * TEMP_REV_B_FACTOR;

  return this->temp_last;
}


//Processes a new temperature value in ADC counts, converting it to °C, for hardware revision C
float TempSensor_RevC::HandleUpdate(uint32_t adc_counts) {
  //NTC thermistor with pull-up resistor: calculate temperature using Steinhart-Hart approximation

  //calculate measured voltage, as a ratio of the reference/supply voltage
  float voltage_ratio = (float)adc_counts / (float)ADC_COUNT_MAX;

  //calculate resistance of the thermistor in its voltage divider
  float therm_resistance = TEMP_REV_C_PULLUP / (1.0f / voltage_ratio - 1.0f);
  //convert to "normalised" resistance, relative to nominal thermistor resistance
  float therm_res_ratio = therm_resistance / TEMP_REV_C_THERM_NOMINAL;

  //calculate natural logarithm of normalised resistance
  float therm_res_ratio_ln = logf(therm_res_ratio);

  //calculate approximate temperature in Kelvin, using Steinhart-Hart approximation
  float temp_K = 1.0f / (TEMP_REV_C_COEFF_A + therm_res_ratio_ln * (TEMP_REV_C_COEFF_B + therm_res_ratio_ln * (TEMP_REV_C_COEFF_C + therm_res_ratio_ln * TEMP_REV_C_COEFF_D)));

  //convert temperature to °C
  this->temp_last = temp_K - 273.15f;

  return this->temp_last;
}

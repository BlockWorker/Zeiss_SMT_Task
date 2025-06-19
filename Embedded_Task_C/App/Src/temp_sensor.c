/*
 * temp_sensor.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 */

#include "temp_sensor.h"
#include "bsp.h"
#include <math.h>


//temperature conversion factors (°C per count) for hardware revisions A and B
#define TEMP_REV_A_FACTOR 1.0f
#define TEMP_REV_B_FACTOR 0.1f

//temperature conversion parameters for hardware revision C (NTC thermistor with pull-up resistor)
//pull-up resistor value in ohms
#define TEMP_REV_C_PULLUP 200000.0f
//nominal (25°C) thermistor resistance in ohms
#define TEMP_REV_C_THERM_NOMINAL 220000.0f
//Steinhart-Hart coefficients of the NTC thermistor
#define TEMP_REV_C_COEFF_A 3.354016E-03f
#define TEMP_REV_C_COEFF_B 2.367720E-04f
#define TEMP_REV_C_COEFF_C 3.585140E-06f
#define TEMP_REV_C_COEFF_D 1.255349E-07f


//last temperature measurement in °C, assume 25°C initially
static float temp_last = 25.0f;


//Performs initialisation of the temperature sensor, returns success
bool TEMP_Init() {
  //reset "last" measurement to default of 25°C
  temp_last = 25.0f;

  //initialise and start the ADC
  return BSP_StartADC();
}


//calculates NTC thermistor temperature approximation (in °C) for Rev. C
static float TEMP_CalculateNTCApproximationRevC(uint32_t adc_counts) {
  //calculate measured voltage, as a ratio of the reference/supply voltage
  float voltage_ratio = (float)adc_counts / (float)BSP_ADC_COUNT_MAX;

  //calculate resistance of the thermistor in its voltage divider
  float therm_resistance = TEMP_REV_C_PULLUP / (1.0f / voltage_ratio - 1.0f);
  //convert to "normalised" resistance, relative to nominal thermistor resistance
  float therm_res_ratio = therm_resistance / TEMP_REV_C_THERM_NOMINAL;

  //calculate natural logarithm of normalised resistance
  float therm_res_ratio_ln = logf(therm_res_ratio);

  //calculate approximate temperature in Kelvin, using Steinhart-Hart approximation
  float temp_K = 1.0f / (TEMP_REV_C_COEFF_A + therm_res_ratio_ln * (TEMP_REV_C_COEFF_B + therm_res_ratio_ln * (TEMP_REV_C_COEFF_C + therm_res_ratio_ln * TEMP_REV_C_COEFF_D)));

  //convert temperature to °C and return
  return temp_K - 273.15f;
}

//Processes a new temperature value in ADC counts, converting it to °C
float TEMP_HandleUpdate(uint32_t adc_counts) {
  //different handling depending on the active hardware revision
  switch (hardware_revision) {
    case REV_A:
      //revision A: simple conversion factor
      temp_last = (float)adc_counts * TEMP_REV_A_FACTOR;
      break;
    case REV_B:
      //revision B: simple conversion factor
      temp_last = (float)adc_counts * TEMP_REV_B_FACTOR;
      break;
    case REV_C:
      //revision C: NTC thermistor with pull-up resistor; calculate temperature using Steinhart-Hart approximation
      temp_last = TEMP_CalculateNTCApproximationRevC(adc_counts);
      break;
    default:
      //invalid hardware revision - should never happen, treat as 0°C (critical)
      temp_last = 0.0f;
      break;
  }

  return temp_last;
}

//Returns the last measured temperature, in °C
float TEMP_GetLast() {
  return temp_last;
}

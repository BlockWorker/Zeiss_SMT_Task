/*
 * system.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the central initialisation and system management logic.
 */

#include "system.h"
#include "bsp.h"
#include "config.h"
#include "display.h"
#include "temp_sensor.h"


//Performs system initialisation, returns success
bool SYSTEM_Init() {
  //start by reading the configuration from EEPROM
  if (!CONFIG_Read()) {
    printf("* Configuration read failed!\n");
    return false;
  }

  //print system information
  printf("Starting temperature monitor Rev. %s\n", (hardware_revision == REV_A) ? "A" : ((hardware_revision == REV_B) ? "B" : "C"));
  printf("Serial number: %s\n", CONFIG_GetSerialNumber());

  //initialise display
  if (!DISPLAY_Init()) {
    printf("* Display init failed!\n");
    return false;
  }

  //initialise temperature sensor, starting value acquisition
  if (!TEMP_Init()) {
    printf("* Temperature sensor init failed!\n");
    return false;
  }

  return true;
}

//Handles a new temperature update interrupt
void SYSTEM_HandleTempUpdateInterrupt() {
  //get the raw ADC value from the temperature sensor
  uint32_t adc_counts = BSP_GetADCValue();

  //convert the ADC value to the actual temperature in °C
  float temp_C = TEMP_HandleUpdate(adc_counts);

  //update the display according to the temperature
  DISPLAY_Update(temp_C);

  //print every 10000th temperature value to the console
  static uint32_t update_counter = 0;
  if (++update_counter >= 10000) {
    update_counter = 0;
    printf("Temperature: %.2f C\n", temp_C);
  }
}

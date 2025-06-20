/*
 * temp_sensor.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Handles the temperature sensor interaction.
 */

#ifndef INC_TEMP_SENSOR_H_
#define INC_TEMP_SENSOR_H_


#include "common.h"


//abstract temperature sensor logic, for any hardware revision
class TempSensor {
public:
  //Performs initialisation of the temperature sensor, returns success
  bool Init();

  //Processes a new temperature value in ADC counts, converting it to °C
  virtual float HandleUpdate(uint32_t adc_counts) = 0;

  //Returns the last measured temperature, in °C
  float GetLast() const;

  //initialise the "last" temperature to default value at first
  TempSensor() : temp_last(TEMP_DEFAULT_VALUE) {}

  virtual ~TempSensor() {}

protected:
  float temp_last;
};


//temperature sensor logic for specific hardware revisions
class TempSensor_RevA : public TempSensor {
public:
  float HandleUpdate(uint32_t adc_counts) override;
};

class TempSensor_RevB : public TempSensor {
public:
  float HandleUpdate(uint32_t adc_counts) override;
};

class TempSensor_RevC : public TempSensor {
public:
  float HandleUpdate(uint32_t adc_counts) override;
};


#endif /* INC_TEMP_SENSOR_H_ */

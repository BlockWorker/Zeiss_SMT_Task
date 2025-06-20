/*
 * system_manager.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains the central initialisation and system management logic.
 */

#ifndef INC_SYSTEM_MANAGER_H_
#define INC_SYSTEM_MANAGER_H_


#include "common.h"
#include "bsp.h"
#include "hardware_config.h"
#include "display.h"
#include "temp_sensor.h"


typedef enum {
  REV_A = REV_A_VALUE,
  REV_B = REV_B_VALUE,
  REV_C = REV_C_VALUE
} HardwareRevision;


class SystemManager {
public:
  //The central system manager instance (singleton semantics)
  static SystemManager instance;

  //Performs system initialisation, returns success
  bool Init();

  //Performs main system loop processing
  void LoopUpdate();

  //Handles ADC conversion-complete interrupts
  void HandleADCInterrupt();

  //Getters for various system components
  BSP* GetBSP();
  HardwareConfig* GetHardwareConfig();
  Display* GetDisplay();
  TempSensor* GetTempSensor();

  //sets the currently active hardware revision
  void SetHardwareRevision(HardwareRevision rev);
  //returns the currently active hardware revision
  HardwareRevision GetHardwareRevision() const;

  //enforce singleton semantics (no copying)
  SystemManager(SystemManager&) = delete;
  void operator=(const SystemManager&) = delete;

private:
  //private constructor/destructor due to singleton semantics
  SystemManager();
  ~SystemManager();

  //system component pointers
  BSP* bsp;
  HardwareConfig* hardware_config;
  Display* display;
  TempSensor* temp_sensor;

  //the currently active hardware revision
  HardwareRevision hardware_revision;

  //flag whether a new ADC measurement is available to be read
  volatile bool adc_update_available;
};


#endif /* INC_SYSTEM_MANAGER_H_ */

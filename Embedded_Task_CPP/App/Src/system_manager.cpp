/*
 * system_manager.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains the central initialisation and system management logic.
 */


#include "system_manager.h"


//The central system manager instance (singleton semantics)
SystemManager SystemManager::instance;


//Performs system initialisation, returns success
bool SystemManager::Init() {
  this->adc_update_available = false;

  //create BSP, hardware config, and display components
  this->bsp = new BSP;
  this->hardware_config = new HardwareConfig;
  this->display = new Display;

  if (this->bsp == NULL || this->hardware_config == NULL || this->display == NULL) {
    printf("* Component creation failed!\n");
    return false;
  }

  //start by reading the configuration from EEPROM
  if (!this->hardware_config->Load()) {
    printf("* Configuration read failed!\n");
    return false;
  }

  //create temperature sensor component, according to the hardware revision
  switch (this->hardware_revision) {
    case REV_A:
      this->temp_sensor = new TempSensor_RevA;
      break;
    case REV_B:
      this->temp_sensor = new TempSensor_RevB;
      break;
    case REV_C:
      this->temp_sensor = new TempSensor_RevC;
      break;
    default:
      //invalid revision, should never happen
      printf("* Invalid hardware revision detected!\n");
      return false;
  }

  if (this->temp_sensor == NULL) {
    printf("* Temperature sensor component creation failed!\n");
    return false;
  }

  //print system information
  printf("Starting temperature monitor, C++ version, Rev. %s\n", (this->hardware_revision == REV_A) ? "A" : ((this->hardware_revision == REV_B) ? "B" : "C"));
  printf("Serial number: %s\n", this->hardware_config->GetSerialNumber().c_str());

  //initialise display
  if (!this->display->Init()) {
    printf("* Display init failed!\n");
    return false;
  }

  //initialise temperature sensor, starting value acquisition
  if (!this->temp_sensor->Init()) {
    printf("* Temperature sensor init failed!\n");
    return false;
  }

  return true;
}

//Performs main system loop processing
void SystemManager::LoopUpdate() {
  //perform temperature updates whenever there is a new ADC measurement available
  if (this->adc_update_available) {
    this->adc_update_available = false;

    //make sure we are fully initialised, abort update otherwise
    if (this->bsp == NULL || this->temp_sensor == NULL || this->display == NULL) {
      return;
    }

    //get the raw ADC value from the temperature sensor
    uint32_t adc_counts = this->bsp->GetADCValue();

    //convert the ADC value to the actual temperature in °C
    float temp_C = this->temp_sensor->HandleUpdate(adc_counts);

    //update the display according to the temperature
    this->display->Update(temp_C);

    //print every 10000th temperature value to the console
    static uint32_t update_counter = 0;
    if (++update_counter >= 10000) {
      update_counter = 0;
      printf("Temperature: %.2f C\n", temp_C);
    }
  }
}


//Handles ADC conversion-complete interrupts
void SystemManager::HandleADCInterrupt() {
  //set update available flag
  this->adc_update_available = true;
}


//Getters for various system components
BSP* SystemManager::GetBSP() {
  return this->bsp;
}

HardwareConfig* SystemManager::GetHardwareConfig() {
  return this->hardware_config;
}

Display* SystemManager::GetDisplay() {
  return this->display;
}

TempSensor* SystemManager::GetTempSensor() {
  return this->temp_sensor;
}


//sets the currently active hardware revision
void SystemManager::SetHardwareRevision(HardwareRevision rev) {
  this->hardware_revision = rev;
}

//returns the currently active hardware revision
HardwareRevision SystemManager::GetHardwareRevision() const {
  return this->hardware_revision;
}


SystemManager::SystemManager() {
  this->adc_update_available = false;

  //initialise the hardware revision to a default of A, to be overwritten when config is loaded
  this->hardware_revision = REV_A;

  //initialise system component pointers to null, until Init function is called
  this->bsp = NULL;
  this->hardware_config = NULL;
  this->display = NULL;
  this->temp_sensor = NULL;
}

SystemManager::~SystemManager() {
  //clean up system components
  delete this->bsp;
  delete this->hardware_config;
  delete this->display;
  delete this->temp_sensor;
}

/*
 * hardware.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Alex
 *
 *  Contains the Board Support Package (hardware interface abstraction) and related types/definitions.
 */

#include "bsp.h"
#include "main.h"
#include "system.h"


/******************************************
 *               TEMP/ADC                 *
 ******************************************/

//initialises and enables the temperature sensor ADC, returns success
bool BSP_StartADC() {
  //start the ADC itself, in interrupt mode
  if (HAL_ADC_Start_IT(&hadc1) != HAL_OK) {
    return false;
  }

  //start the sample trigger timer
  return HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) == HAL_OK;
}

//gets the latest temperature ADC measurement, in ADC counts
uint32_t BSP_GetADCValue() {
  return HAL_ADC_GetValue(&hadc1);
}

//interrupt handler for ADC "conversion complete"
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
  if (hadc == &hadc1) {
    //notify the system of the update
    SYSTEM_HandleADCInterrupt();
  }
}


/******************************************
 *                DISPLAY                 *
 ******************************************/

//sets the physical display to the given state
void BSP_SetDisplay(DISPLAY_State state) {
  //update green LED
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, (state == DISP_NORMAL) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  //update yellow LED
  HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, (state == DISP_WARNING) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  //update red LED
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, (state == DISP_CRITICAL) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}


/******************************************
 *                EEPROM                  *
 ******************************************/

//read `length` bytes starting at EEPROM address `address` into `buffer`, returns success
bool BSP_ReadEEPROM(uint16_t address, uint8_t* buffer, uint8_t length) {
  //check parameter validity
  if (address > BSP_EEPROM_MAX_MEM_ADDR || length > BSP_EEPROM_MAX_READ_BYTES) {
    printf("* Attempted EEPROM read with invalid address or too many bytes\n");
    return false;
  }

  //perform I2C memory read
  return HAL_I2C_Mem_Read(&hi2c2, (uint16_t)BSP_EEPROM_I2C_ADDR << 1, address, I2C_MEMADD_SIZE_16BIT, buffer, length, BSP_EEPROM_READ_TIMEOUT_MS) == HAL_OK;
}

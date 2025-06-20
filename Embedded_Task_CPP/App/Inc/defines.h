/*
 * defines.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 *
 *  Contains definitions for implementation-specific constants.
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_


//maximum value of ADC counts (i.e., ADC count value of positive reference)
#define ADC_COUNT_MAX   4095

//numeric values of hardware revisions
#define REV_A_VALUE     0
#define REV_B_VALUE     1
#define REV_C_VALUE     2



/**************************************
 *  BSP implementation configuration  *
 **************************************/

//I2C address of the EEPROM chip
#define BSP_EEPROM_I2C_ADDR         0x57

//maximum memory address of the EEPROM chip
#define BSP_EEPROM_MAX_MEM_ADDR     0xFFF

//maximum bytes supported per EEPROM read
#define BSP_EEPROM_MAX_READ_BYTES   32

//EEPROM read timeout in milliseconds
#define BSP_EEPROM_READ_TIMEOUT_MS  10



/******************************************
 *  Display implementation configuration  *
 ******************************************/

//temperature limits for "normal" and "warning" regions, everything else is considered "critical"
#define DISP_NORMAL_TEMP_MIN    5.0f
#define DISP_NORMAL_TEMP_MAX    85.0f
#define DISP_WARNING_TEMP_MIN   85.0f
#define DISP_WARNING_TEMP_MAX   105.0f



/**************************************************
 *  Hardware config implementation configuration  *
 **************************************************/

//memory address of the hardware revision
#define CONFIG_REVISION_ADDRESS   0

//length of the hardware revision, in bytes
#define CONFIG_REVISION_LENGTH    1

//memory address of the serial number
#define CONFIG_SERIAL_ADDRESS     1

//length of the serial number, in bytes
#define CONFIG_SERIAL_LENGTH      8



/**********************************************
 *  Temp sensor implementation configuration  *
 **********************************************/

//default temperature after reset
#define TEMP_DEFAULT_VALUE  25.0f


//temperature conversion factors (°C per count) for hardware revisions A and B
#define TEMP_REV_A_FACTOR   1.0f
#define TEMP_REV_B_FACTOR   0.1f


//temperature conversion parameters for hardware revision C (NTC thermistor with pull-up resistor)

//pull-up resistor value in ohms
#define TEMP_REV_C_PULLUP         200000.0f

//nominal (25°C) thermistor resistance in ohms
#define TEMP_REV_C_THERM_NOMINAL  220000.0f

//Steinhart-Hart coefficients of the NTC thermistor
#define TEMP_REV_C_COEFF_A        3.354016E-03f
#define TEMP_REV_C_COEFF_B        2.367720E-04f
#define TEMP_REV_C_COEFF_C        3.585140E-06f
#define TEMP_REV_C_COEFF_D        1.255349E-07f


#endif /* INC_DEFINES_H_ */

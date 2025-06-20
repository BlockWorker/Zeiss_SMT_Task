/*
 * cpp_main.cpp
 *
 *  Created on: Jun 20, 2025
 *      Author: Alex
 */


#include "cpp_main.h"
#include "system_manager.h"


//main function in C++ mode
int cpp_main() {
  //initialisation section
  if (!SystemManager::instance.Init()) {
    //initialisation failed: wait a little to allow debug printouts to finish, then halt
    printf("*** System initialisation failed!\n");
    HAL_Delay(100);
    Error_Handler();
  }

  //infinite loop
  while (1) {
    //perform system loop updates
    SystemManager::instance.LoopUpdate();
  }
}


#ifndef _MAIN_H_
#define _MAIN_H_

/*File name: main.h;
* Author: Daniil;
* Compiler: armclang;
* Language: C11;
* Hardware used in testing: STM32 NUCLEO-F401RE.
* Warnings: -
* Description: -
* Last update: 01.05.2023.
*/


#include <stm32f4xx.h>
//#include "stm32f4xx_it.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"


#define LED_APin GPIO_PIN_5


int main(void);

#endif //#ifndef _MAIN_H_

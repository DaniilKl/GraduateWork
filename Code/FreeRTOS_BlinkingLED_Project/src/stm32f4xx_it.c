/*File name: stm32f4xx_it.c;
* Author: Daniil;
* Compiler: armclang;
* Language: C;
* Hardware used in testing: STM32 NUCLEO-F401RE.
* Warnings: -
* Description: -
* Last update: 01.05.2023.
*/


#include "stm32f4xx_it.h"
	
//System events handlers:
void NMI_Handler(void){

}

void HardFault_Handler(void){

}

void MemManage_Handler(void){

}

void BusFault_Handler(void){

}

void UsageFault_Handler(void){

}

void SVC_Handler(void){

}

void DebugMon_Handler(void){

}

void PendSV_Handler(void){

}

void SysTick_Handler(void){
	HAL_IncTick();
}
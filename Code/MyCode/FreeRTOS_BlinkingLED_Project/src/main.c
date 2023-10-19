/*File name: Mmain.c;
* Author: Daniil;
* Compiler: armclang;
* Language: C11;
* Hardware used in testing: STM32 NUCLEO-F401RE.
* Warnings: -
* Description: -
* Last update: 01.05.2023.
*/

#include "main.h"

//main.c definitions:
	//Tasks stacks lengths definitions:
	#define TASK_STACK_LENGHT_WORDS 1000

//Hardware initializations function:
static inline void SysInit(void){
	HAL_Init();
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	
	GPIO_InitStructure.Pin = LED_APin;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}
//Error handler impleemnted for debugging purposes:
static void ErrorHandler(void){
	while(1){}
}


void LED_ON_Task(void *pvParameters);
void LED_OFF_Task(void *pvParameters);


int main(void){ //The main function will blink the LED with 5 Hz frequency.
	SysInit();//System initialization.
	
	if (xTaskCreate(LED_ON_Task, "LED_ON_Task", TASK_STACK_LENGHT_WORDS, NULL, 0, NULL) == pdFAIL) //If memory allocation to this task fails go to ErrorHandler
		ErrorHandler(); 
	if (xTaskCreate(LED_OFF_Task, "LED_OFF_Task", TASK_STACK_LENGHT_WORDS, NULL, 0, NULL) ==pdFAIL) //If memory allocation to this task fails go to ErrorHandler
		ErrorHandler();
	
	vTaskStartScheduler(); //Starting scheduler.
	//Infinite loop:
	while (1){
		
	
	}
}

void LED_ON_Task (void *pvParameters){
	
	//Infinite loop:
	while (1){
		HAL_GPIO_WritePin(GPIOA, LED_APin, GPIO_PIN_SET);
		vTaskDelay(pdMS_TO_TICKS( 500 ));
	}
	
	vTaskDelete(NULL); 
}

void LED_OFF_Task (void *pvParameters){
	
	//Infinite loop:
	while (1){
		HAL_GPIO_WritePin(GPIOA, LED_APin, GPIO_PIN_RESET);
		vTaskDelay(pdMS_TO_TICKS( 600 ));
	}
	
	vTaskDelete(NULL); 
}




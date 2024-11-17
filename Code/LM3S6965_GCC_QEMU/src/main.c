#include <stdint.h>

/* FreeRTOS includes: */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

#define TASK_STACK_LENGHT_WORDS 1000

void WRITE_Task(void *pvParameters);
void ERASE_Task(void *pvParameters);

volatile int global_var = 0;

int main(void){
	xTaskCreate(WRITE_Task, "WRITE_Task", TASK_STACK_LENGHT_WORDS, NULL, 1, NULL);
	xTaskCreate(ERASE_Task, "ERASE_Task", TASK_STACK_LENGHT_WORDS, NULL, 0, NULL);
	vTaskStartScheduler();

	while (1){

	}
}

void WRITE_Task (void *pvParameters){

	while (1){
		global_var = 1;
		vTaskDelay(pdMS_TO_TICKS( 500 ));
	}
	vTaskDelete(NULL);
}

void ERASE_Task (void *pvParameters){
	
	while (1){
		global_var = 0;
		vTaskDelay(pdMS_TO_TICKS( 1000 ));
	}
	vTaskDelete(NULL); 
}

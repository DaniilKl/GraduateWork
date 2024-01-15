//#include <stm32f4xx.h>
//#include "stm32f4xx_it.h"

#include <stdint.h>

// AHB1 definitions:
#define PERIPHERAL_BASE (0x40000000U)
#define AHB1_BASE (PERIPHERAL_BASE + 0x20000U)
#define AHB1_RCC_BASE (AHB1_BASE + 0x3800U)
#define AHB1_GPIOA_BASE (AHB1_BASE + 0x0U)

#define RCC_AHB1ENR ((volatile uint32_t*)(AHB1_RCC_BASE + 0x30U))

#define GPIOA_MODER ((volatile uint32_t*)(AHB1_GPIOA_BASE + 0x0U))
#define GPIO_MODER5 (0xaU)
#define GPIOA_ODR ((volatile uint32_t*)(AHB1_GPIOA_BASE + 0x14U))

#define LED_PIN (0x5U)

/* FreeRTOS includes: */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

#define TASK_STACK_LENGHT_WORDS 1000

void LED_ON_Task(void *pvParameters);
void LED_OFF_Task(void *pvParameters);

int main(void){
	*RCC_AHB1ENR |= (uint32_t)0x1;
	
	uint32_t dummy;
	dummy = *(RCC_AHB1ENR);
	dummy = *(RCC_AHB1ENR);
  
	*GPIOA_MODER |= (1 << GPIO_MODER5);

	xTaskCreate(LED_ON_Task, "LED_ON_Task", TASK_STACK_LENGHT_WORDS, NULL, 0, NULL);
	xTaskCreate(LED_OFF_Task, "LED_OFF_Task", TASK_STACK_LENGHT_WORDS, NULL, 0, NULL);
	vTaskStartScheduler();

	while (1){
		
	}
}

void LED_ON_Task (void *pvParameters){

	while (1){
		*GPIOA_ODR |= (1 << LED_PIN);
		vTaskDelay(pdMS_TO_TICKS( 500 ));
	}
	vTaskDelete(NULL);
}

void LED_OFF_Task (void *pvParameters){
	
	while (1){
		*GPIOA_ODR &= ~(1 << LED_PIN);
		vTaskDelay(pdMS_TO_TICKS( 600 ));
	}
	vTaskDelete(NULL); 
}

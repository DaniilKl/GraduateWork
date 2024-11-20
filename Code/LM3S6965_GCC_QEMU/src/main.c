#include <stdint.h>

/* FreeRTOS includes: */
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

/*
 * Task control block.  A task control block (TCB) is allocated for each task,
 * and stores task state information, including a pointer to the task's context
 * (the task's run time environment, including register values)
 */
typedef struct tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t * pxTopOfStack; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

    #if ( portUSING_MPU_WRAPPERS == 1 )
        xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
    #endif

    ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
    UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
    StackType_t * pxStack;                      /*< Points to the start of the stack. */
    TickType_t xTaskStarted;                    /* The tick value when task started execution. */
    TickType_t xTaskExecutionTime;              /* Number of ticks needed for task to be executed. NOTE: for task load simulation only. */
    TickType_t xTaskCurrentExecutionTime;       /* Set to xTaskExecutionTime and decreased every SysTick. NOTE: for task load simulation only. */
    TickType_t xTaskExecutionDeadline;          /* Deadline for a task. */
    char pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

    #if ( ( portSTACK_GROWTH > 0 ) || ( configRECORD_STACK_HIGH_ADDRESS == 1 ) )
        StackType_t * pxEndOfStack; /*< Points to the highest valid address for the stack. */
    #endif

    #if ( portCRITICAL_NESTING_IN_TCB == 1 )
        UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
    #endif

    #if ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
        UBaseType_t uxTaskNumber; /*< Stores a number specifically for use by third party trace code. */
    #endif

    #if ( configUSE_MUTEXES == 1 )
        UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
        UBaseType_t uxMutexesHeld;
    #endif

    #if ( configUSE_APPLICATION_TASK_TAG == 1 )
        TaskHookFunction_t pxTaskTag;
    #endif

    #if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS > 0 )
        void * pvThreadLocalStoragePointers[ configNUM_THREAD_LOCAL_STORAGE_POINTERS ];
    #endif

    #if ( configGENERATE_RUN_TIME_STATS == 1 )
        configRUN_TIME_COUNTER_TYPE ulRunTimeCounter; /*< Stores the amount of time the task has spent in the Running state. */
    #endif

    #if ( ( configUSE_NEWLIB_REENTRANT == 1 ) || ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 ) )
        configTLS_BLOCK_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
    #endif

    #if ( configUSE_TASK_NOTIFICATIONS == 1 )
        volatile uint32_t ulNotifiedValue[ configTASK_NOTIFICATION_ARRAY_ENTRIES ];
        volatile uint8_t ucNotifyState[ configTASK_NOTIFICATION_ARRAY_ENTRIES ];
    #endif

    /* See the comments in FreeRTOS.h with the definition of
     * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
    #if ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
        uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
    #endif

    #if ( INCLUDE_xTaskAbortDelay == 1 )
        uint8_t ucDelayAborted;
    #endif

    #if ( configUSE_POSIX_ERRNO == 1 )
        int iTaskErrno;
    #endif
} tskTCB;

/* The old tskTCB name is maintained above then typedefed to the new TCB_t name
 * below to enable the use of older kernel aware debuggers. */
typedef tskTCB TCB_t;

extern TCB_t * volatile pxCurrentTCB;

#define TASK_STACK_LENGHT_WORDS 1000

void FIRST_Task(void *pvParameters);
void SECOND_Task(void *pvParameters);
void THIRD_Task(void *pvParameters);
void FOURTH_Task(void *pvParameters);

void task_start_work(uint64_t *counter){
	*counter++;
}
void task_end_work(uint64_t *counter){
	*counter++;
}

volatile int global_var = 0;

int main(void){
	xTaskCreate(FIRST_Task, "FIRST_Task", TASK_STACK_LENGHT_WORDS, NULL, 2, 2, 4, NULL);
	xTaskCreate(SECOND_Task, "SECOND_Task", TASK_STACK_LENGHT_WORDS, NULL, 5, 1, 4, NULL);
	xTaskCreate(THIRD_Task, "THIRD_Task", TASK_STACK_LENGHT_WORDS, NULL, 3, 3, 4, NULL);
	xTaskCreate(FOURTH_Task, "FOURTH_Task", TASK_STACK_LENGHT_WORDS, NULL, 1, 1, 4, NULL);

	vTaskStartScheduler();

	while (1){

	};
}

void FIRST_Task (void *pvParameters){
	static uint64_t task1_work_started_counter = 0;
	static uint64_t task1_work_completed_counter = 0;

	while (1){
		task_start_work(&task1_work_started_counter);

		pxCurrentTCB->xTaskCurrentExecutionTime = pxCurrentTCB->xTaskExecutionTime;
		do{
		}while( pxCurrentTCB->xTaskCurrentExecutionTime != 0 );

		task_end_work(&task1_work_completed_counter);
		vTaskDelay(4);
	}
	vTaskDelete(NULL);
}

void SECOND_Task (void *pvParameters){
	static uint64_t task1_work_started_counter = 0;
	static uint64_t task1_work_completed_counter = 0;

	while (1){
		task_start_work(&task1_work_started_counter);

		pxCurrentTCB->xTaskCurrentExecutionTime = pxCurrentTCB->xTaskExecutionTime;
		do{
		}while( pxCurrentTCB->xTaskCurrentExecutionTime != 0 );

		task_end_work(&task1_work_completed_counter);
		vTaskDelay(7);
	}
	vTaskDelete(NULL);
}

void THIRD_Task (void *pvParameters){
	static uint64_t task1_work_started_counter = 0;
	static uint64_t task1_work_completed_counter = 0;

	while (1){
		task_start_work(&task1_work_started_counter);

		pxCurrentTCB->xTaskCurrentExecutionTime = pxCurrentTCB->xTaskExecutionTime;
		do{
		}while( pxCurrentTCB->xTaskCurrentExecutionTime != 0 );

		task_end_work(&task1_work_completed_counter);
		vTaskDelay(6);
	}
	vTaskDelete(NULL);
}

void FOURTH_Task (void *pvParameters){
	static uint64_t task1_work_started_counter = 0;
	static uint64_t task1_work_completed_counter = 0;

	while (1){
		task_start_work(&task1_work_started_counter);

		pxCurrentTCB->xTaskCurrentExecutionTime = pxCurrentTCB->xTaskExecutionTime;
		do{
		}while( pxCurrentTCB->xTaskCurrentExecutionTime != 0 );

		task_end_work(&task1_work_completed_counter);
		vTaskDelay(8);
	}
	vTaskDelete(NULL);
}

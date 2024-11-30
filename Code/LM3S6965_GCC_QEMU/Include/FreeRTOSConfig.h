
/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#include <stdint.h>

//config* definitions
#define configAPPLICATION_ALLOCATED_HEAP 								0
//#define	configASSERT 																		0
#define	configCHECK_FOR_STACK_OVERFLOW 									0
#define	configENABLE_BACKWARD_COMPATIBILITY 						0
#define	configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
//#define	configMAX_SYSCALL_INTERRUPT_PRIORITY 
//#define	configKERNEL_INTERRUPT_PRIORITY 
//#define	configMAX_CO_ROUTINE_PRIORITIES
//#define	configNUM_THREAD_LOCAL_STORAGE_POINTERS
//#define	configTIMER_QUEUE_LENGTH
//#define	configTIMER_TASK_PRIORITY
//#define configTIMER_TASK_STACK_DEPTH
#define configCPU_CLOCK_HZ															( 50000000 )
#define configTICK_RATE_HZ															( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES														( 26UL )
#define configMINIMAL_STACK_SIZE												( ( unsigned short ) 20 )
#define configTOTAL_HEAP_SIZE														( ( size_t ) ( 63800 ) )
#define configMAX_TASK_NAME_LEN													( 10 )
#define configIDLE_SHOULD_YIELD													0
#define configQUEUE_REGISTRY_SIZE												8
#define configGENERATE_RUN_TIME_STATS										0
#define configSUPPORT_DYNAMIC_ALLOCATION 							  1
#define configSUPPORT_STATIC_ALLOCATION 			  				0
//configUSE* definitions:
	#define configUSE_TRACE_FACILITY											0
	#define configUSE_16_BIT_TICKS												0
	#define configUSE_MUTEXES															0
	#define configUSE_RECURSIVE_MUTEXES										0
	#define configUSE_APPLICATION_TASK_TAG								0
	#define configUSE_COUNTING_SEMAPHORES									0
	#define configUSE_PORT_OPTIMISED_TASK_SELECTION				0
	#define configUSE_PREEMPTION													1
	#define configUSE_ALTERNATIVE_API 										0
	#define configUSE_CO_ROUTINES 												0
	#define configUSE_NEWLIB_REENTRANT 										0
	#define configUSE_QUEUE_SETS 													0
	#define configUSE_STATS_FORMATTING_FUNCTIONS 					0
	#define configUSE_TASK_NOTIFICATIONS 									0
	#define configUSE_TICKLESS_IDLE                       0
	#define configUSE_TIMERS				                      0
	#define configUSE_TIME_SLICING                        0
	//config_*_HOOK definitions:
	#define configUSE_IDLE_HOOK														0
	#define configUSE_TICK_HOOK														0
	#define configUSE_DAEMON_TASK_STARTUP_HOOK 						0
	#define configUSE_MALLOC_FAILED_HOOK 									0
//configTIMER* definitions:
//#define configTIMER_TASK_PRIORITY		( 2 )
//#define configTIMER_QUEUE_LENGTH		5
//#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_xEventGroupSetBitsFromISR 0
#define INCLUDE_xSemaphoreGetMutexHolder 0 
#define INCLUDE_xTimerPendFunctionCall 0
#define INCLUDE_eTaskGetState 0
#define INCLUDE_xTaskResumeFromISR 0
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetSchedulerState 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_xTaskGetHandle 0
#define INCLUDE_xTaskGetCurrentTaskHandle 0
#define INCLUDE_xTaskAbortDelay 0
#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_uxTaskPriorityGet		0
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			0
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				0

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		8        /* 63 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0x3f

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler


/*******************************************************************************
 * Custom definitions.
 ******************************************************************************/
//#define USE_FREERTOS_CLASSIC_SCHEDULER

//#define USE_FCFS_SCHEDULER

//#define USE_RR_SCHEDULER
/* Time slice for Round Robin scheduler in ticks, must be a power of 2:*/
//#define RR_TIME_SLICE 4

//#define USE_SRTN_SCHEDULER

//#define USE_SJF_SCHEDULER

//#define USE_DM_SCHEDULER

//#define USE_RM_SCHEDULER

#if defined(USE_DM_SCHEDULER) || defined(USE_RM_SCHEDULER)
	#define USE_FREERTOS_CLASSIC_SCHEDULER
	#define configUSE_PREEMPTION 1
	#define configUSE_TIME_SLICING 0
#endif

//#define USE_EDF_SCHEDULER

//#define USE_PREEMPTIVE_EDF_SCHEDULER

#ifdef USE_PREEMPTIVE_EDF_SCHEDULER
	#define USE_EDF_SCHEDULER
#endif

//#define USE_LLF_SCHEDULER

#define USE_PREEMPTIVE_LLF_SCHEDULER

#ifdef USE_PREEMPTIVE_LLF_SCHEDULER
	#define USE_LLF_SCHEDULER
#endif

#endif /* FREERTOS_CONFIG_H */


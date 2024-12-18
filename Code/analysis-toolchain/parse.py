#!/usr/bin/env python3

import sys
import re
from collections import defaultdict
import json


def extract_task_from_line(line, task_pattern):
    for word in line.split():
        print(f"For word: {word}")

        if word.endswith(task_pattern):
            return word
        elif word == task_pattern:
            return word
        else:
            continue

    return None


def key_exists_first_level(dictionary, key):
    return key if key in dictionary else None


def process_trace_log(lines, systick_end_parse):
    SysTickCount = 0
    ContextSwitches = 0

    CurrentTask = None

    TasksInf = {}

    xTaskDelayUntil = 0
    vTaskSwitchContext = 0
    PendSV_Handler = 0
    SysTick_Handler = 0
    xTaskIncrementTick = 0
    prvAddCurrentTaskToDelayedList = 0
    xTaskResumeAll = 0

    for line in lines:
        NextTask = None 
        print("===============")
        print("For line:")
        print (line)

        # Some of system calls should be tracked between tasks execution:
        if "xTaskDelayUntil" in line:
            xTaskDelayUntil += 1
            continue
        elif "vTaskSwitchContext" in line:
            vTaskSwitchContext += 1
            continue
        elif "PendSV_Handler" in line:
            PendSV_Handler += 1
            continue
        elif "SysTick_Handler" in line:
            SysTick_Handler += 1
            continue
        elif "xTaskIncrementTick" in line:
            xTaskIncrementTick += 1
            continue
        elif "prvAddCurrentTaskToDelayedList" in line:
            prvAddCurrentTaskToDelayedList += 1
            continue
        elif "xTaskResumeAll" in line:
            xTaskResumeAll += 1
            continue

        NextTask = extract_task_from_line(line, "_Task")
        # Maybe the idle task is executing:
        if NextTask == None:
            NextTask = extract_task_from_line(line, "prvIdleTask")
            # If not idle task, that it is probably some other communicate that
            # is not tracked here:
            if NextTask == None:
                continue
        
        print(f"NextTask: {NextTask}")
        print(f"CurrentTask: {CurrentTask}")
        print(f"CurrentTask inf.:")
        if CurrentTask != None:
            print(TasksInf[CurrentTask])

        # If this is the first appearance of the task, the task should be added
        # to the list:
        if key_exists_first_level(TasksInf, NextTask) == None:
            TasksInf[NextTask] = {}
            print("TaskInf after adding new task 1:")
            print(TasksInf)
            TasksInf[NextTask]["TaskName"] = NextTask 
            print("TaskInf after adding new task 2:")
            print(TasksInf)
            TasksInf[NextTask]["TaskStart"] = []
            print("TaskInf after adding new task 3:")
            print(TasksInf)
            TasksInf[NextTask]["TaskEnd"] = []
            print("TaskInf after adding new task 3:")
            print(TasksInf)
            TasksInf[NextTask]["TaskPreemptedTimes"] = 0
            print("TaskInf after adding new task 3:")
            print(TasksInf)

        # Check for SysTick:
        if SysTick_Handler != 0 and xTaskIncrementTick != 0:
            SysTickCount += 1

            if systick_end_parse != 0 and SysTickCount >= systick_end_parse:
                break

        if CurrentTask == None: # First task to execute since system started
            print(f"First task to execute: {NextTask}")
            TasksInf[NextTask]["TaskStart"].append(SysTickCount)
            CurrentTask = NextTask
        elif NextTask == CurrentTask: # Task continues execution
            # If a task just continues execution, this means there were no
            # context switch, therefore only one event could have interrupted
            # the task execution: SysTick, which is being detected earlier.
            # Task might as well end executing just before starting again:
            if xTaskDelayUntil != 0 and xTaskResumeAll !=0 and vTaskSwitchContext != 0 and PendSV_Handler != 0:
                print(f"Task continues execution: {NextTask}")
                ContextSwitches += 1
                TasksInf[CurrentTask]["TaskEnd"].append(SysTickCount)
                print(f"Task {CurrentTask} end logged: {TasksInf[CurrentTask]['TaskEnd']} ")

                TasksInf[NextTask]["TaskStart"].append(SysTickCount)
                print(f"Task {NextTask} start logged: {TasksInf[NextTask]['TaskStart']} ")
        elif NextTask != CurrentTask: # Context switch between tasks
            # The context switch between task may appear in two cases:
            # 1. Task is being preempted by another task;
            # 2. Task ends execution.
            # 
            # In case the task ended execution there might be two cases:
            # 1. Following task was a preempted task and it continues execution;
            # 2. Following task is a periodic task wich was not preempted but
            # starts execution again:
            #
            # Task has been preempted by another task:
            if PendSV_Handler != 0 and vTaskSwitchContext != 0 and xTaskDelayUntil == 1:
                print(f"Task {CurrentTask} has been preempted by {NextTask}")
                ContextSwitches += 1
                TasksInf[CurrentTask]["TaskPreemptedTimes"] += 1
                print(f"Task {CurrentTask} preemption logged: {TasksInf[CurrentTask]['TaskPreemptedTimes']}")
                TasksInf[NextTask]["TaskStart"].append(SysTickCount)
                print(f"Task {NextTask} start logged: {TasksInf[NextTask]['TaskStart']} ")
                CurrentTask = NextTask
            elif PendSV_Handler != 0 and vTaskSwitchContext != 0 and xTaskDelayUntil == 0 and xTaskIncrementTick != 0:
                print(f"Task {CurrentTask} has been preempted by {NextTask}")
                ContextSwitches += 1
                TasksInf[CurrentTask]["TaskPreemptedTimes"] += 1
                print(f"Task {CurrentTask} preemption logged: {TasksInf[CurrentTask]['TaskPreemptedTimes']}")
                CurrentTask = NextTask
            # Task ends execution and the following task is a periodic task that
            # starts execution again:
            elif PendSV_Handler != 0 and vTaskSwitchContext != 0 and xTaskDelayUntil != 0  and xTaskResumeAll != 0 and len(TasksInf[NextTask]['TaskStart']) == len(TasksInf[NextTask]['TaskEnd']):
                print(f"Task {CurrentTask} ends execution, following {NextTask}")
                ContextSwitches += 1
                TasksInf[CurrentTask]["TaskEnd"].append(SysTickCount)
                print(f"Task {CurrentTask} end logged: {TasksInf[CurrentTask]['TaskEnd']} ")

                TasksInf[NextTask]["TaskStart"].append(SysTickCount)
                print(f"Task {NextTask} start logged: {TasksInf[NextTask]['TaskStart']} ")
                CurrentTask = NextTask 
            # Task ends execution and the following task is a preempted task
            # that continues execution:
            elif PendSV_Handler != 0 and vTaskSwitchContext != 0 and xTaskDelayUntil != 0 and prvAddCurrentTaskToDelayedList != 0:
                ContextSwitches += 1
                print(f"Task {CurrentTask} ends execution, following preempted {NextTask}")
                TasksInf[CurrentTask]["TaskEnd"].append(SysTickCount)
                print(f"Task {CurrentTask} end logged: {TasksInf[CurrentTask]['TaskEnd']} ")

                CurrentTask = NextTask
        print("NextTask inf.:")
        print(TasksInf[CurrentTask])

        xTaskDelayUntil = 0
        vTaskSwitchContext = 0
        PendSV_Handler = 0
        SysTick_Handler = 0
        xTaskIncrementTick = 0
        prvAddCurrentTaskToDelayedList = 0
        xTaskResumeAll = 0

    return TasksInf, SysTickCount, ContextSwitches


def main():
    if len(sys.argv) != 4:
        print("Usage: ./parse.py <systick_end_parse> <path_to_trace_file> <path_to_output_file>")
        sys.exit(1)

    systick_end_parse = int(sys.argv[1])
    trace_log_path = sys.argv[2]
    output_file_path = sys.argv[3]
    
    with open(trace_log_path, 'r') as file:
        lines = file.readlines()

    # Process the trace log
    TasksInf, SysTickCount, ContextSwitches = process_trace_log(lines, systick_end_parse)

    TasksInf["SysTickCount"] = SysTickCount
    TasksInf["ContextSwitches"] = ContextSwitches

    print(TasksInf)

    with open(output_file_path, 'w') as json_file:
        json.dump(TasksInf, json_file, indent=4)


if __name__ == "__main__":
    main()


#!/usr/bin/env python3

import sys
import re
from collections import defaultdict
import math
import json


def SortOutTasksByPriority(TasksMetadata):
    TasksSortedByPriority = sorted(
        TasksMetadata.items(),  # Get all key-value pairs from the dictionary
        key=lambda item: item[1]['TaskPriority'],  # Sort by 'TaskPriority' value
        reverse=True  # Highest priority first
    )

    print("SortOutTasksByPriority: tasks sorted by priority:")
    print(TasksSortedByPriority)

    return TasksSortedByPriority


def GetHigherPriorityTasks(TasksSortedByPriority, Percentage):
    TaskCount = len(TasksSortedByPriority)
    print(f"GetHigherPriorityTasks: task count: {TaskCount}")
    Tasks = list(TasksSortedByPriority)
    print("GetHigherPriorityTasks: tasks sorted by priority:")
    print(Tasks)
    HighestPriorityTasks = []
    
    HighLevelPriorityTasksAmount = TaskCount * (Percentage / 100)
    HighLevelPriorityTasksAmount = math.ceil(HighLevelPriorityTasksAmount)
    print(f"GetHigherPriorityTasks: high-level priority tasks amount: {HighLevelPriorityTasksAmount}")

    for i in range(0, HighLevelPriorityTasksAmount):
        HighestPriorityTasks.append(Tasks[i][1]['TaskName'])

    print(f"GetHigherPriorityTasks: highest priority tasks: {HighestPriorityTasks}")

    return HighestPriorityTasks


def ComputeMetMissDeadline(TasksMetadata, TasksParsedInf, HighestPriorityPercentage):
    MetDeadline = {}
    MissDeadline = {}
    MissDeadlineHighestPriority = {}
    TasksSortedByPriority = SortOutTasksByPriority(TasksMetadata)
    HighestPriorityTasksList = GetHigherPriorityTasks(TasksSortedByPriority, HighestPriorityPercentage)

    for task, inf in TasksParsedInf.items():
        MetDeadline[task] = 0
        MissDeadline[task] = 0

        for i in range(0, len(inf["TaskEnd"])):
            AbsoluteDeadline = i * TasksMetadata[task]["TaskPeriod"] + TasksMetadata[task]["TaskDeadline"]

            if inf["TaskEnd"][i] <= AbsoluteDeadline:
                MetDeadline[task] += 1
            elif inf["TaskEnd"][i] > AbsoluteDeadline:
                MissDeadline[task] += 1

    for i in range(0, len(HighestPriorityTasksList)):
        MissDeadlineHighestPriority[HighestPriorityTasksList[i]]=MissDeadline[HighestPriorityTasksList[i]]

    return MetDeadline, MissDeadline, MissDeadlineHighestPriority

def ComputeLoadFactor(TasksMetadata):
    Tasks = list(TasksMetadata)
    TasksCount = len(Tasks)
    LoadFactor = 0

    for i in range(0, TasksCount):
        LoadFactor += TasksMetadata[Tasks[i]]["TaskExecutionTime"]/TasksMetadata[Tasks[i]]["TaskPeriod"]

    return LoadFactor


def ComputeTaskMeanExecutionTime(TasksMetadata):
    Tasks = list(TasksMetadata)
    TasksCount = len(Tasks)
    TaskMeanExecutionTime = 0
    TasksExecutionTime = 0

    for i in range(0, TasksCount):
        TasksExecutionTime += TasksMetadata[Tasks[i]]["TaskExecutionTime"]

    TaskMeanExecutionTime = TasksExecutionTime / TasksCount

    return TaskMeanExecutionTime


def main():
    if len(sys.argv) != 5:
        print("Usage: ./analyze.py <path_to_tasks_metadata_file> <high_priority_tasks_percentage> <path_to_parsed_trace_data_file> <path_to_output_file>")
        sys.exit(1)

    TasksMetadataFile = sys.argv[1]
    HighPriorityTasksPercentage = int(sys.argv[2])
    ParsedTraceDataFile = sys.argv[3]
    OutputFilePath = sys.argv[4]

    with open(TasksMetadataFile, 'r') as json_file:
        TasksMetadata = json.load(json_file)
    with open(ParsedTraceDataFile, 'r') as json_file:
        ParsingResults = json.load(json_file)

    SysTickCount = ParsingResults["SysTickCount"]
    ContextSwitchCount = ParsingResults["ContextSwitches"]

    # Extract all tasks information from ParsingResults:
    TasksParsedInf = {
        key: value
        for key, value in ParsingResults.items()
        if key.endswith("_Task")  # Check if the key ends with "_Task"
    }

    TasksAnalysysData = {}
    TasksAnalysysData['MetDeadline'] = {}
    TasksAnalysysData['MissDeadline'] = {}
    TasksAnalysysData['MetDeadline'], TasksAnalysysData['MissDeadline'], TasksAnalysysData['MissDeadlineHighPriorityTasks'] = ComputeMetMissDeadline(TasksMetadata, TasksParsedInf, HighPriorityTasksPercentage)
    TasksAnalysysData['LoadFactor'] = ComputeLoadFactor(TasksMetadata)
    TasksAnalysysData['MeanTaskExecutionTime'] = ComputeTaskMeanExecutionTime(TasksMetadata)

    with open(OutputFilePath, 'w') as json_file:
        json.dump(TasksAnalysysData, json_file, indent=4)


if __name__ == "__main__":
    main()


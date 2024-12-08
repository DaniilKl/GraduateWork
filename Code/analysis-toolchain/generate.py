#!/usr/bin/env python3

import numpy as np
import random
import sys
import json

def GenerateTasksMetadata(GenerationMetadata):
    TasksMetadata = {}
    UsedPriorities = set()  # Set to track used priorities

    for i in range(1, GenerationMetadata['TaskAmount'] + 1):
        TaskName = f"v{i}_Task"

        while True:
            TaskExecutionTime = int(np.random.normal(GenerationMetadata['StdMeanExec'][1], GenerationMetadata['StdMeanExec'][0]))
            if TaskExecutionTime >= GenerationMetadata['LowUpExec'][0] and TaskExecutionTime <= GenerationMetadata['LowUpExec'][1]:
                break

        while True:
            TaskPeriod = int(np.random.normal(GenerationMetadata['StdMeanPeriod'][1], GenerationMetadata['StdMeanPeriod'][0]))
            if TaskPeriod > (GenerationMetadata['LowUpPeriod'][0] * TaskExecutionTime) and TaskPeriod <= (GenerationMetadata['LowUpPeriod'][1] * TaskExecutionTime):
                break

        while True:
            TaskDeadline = int(np.random.normal(GenerationMetadata['StdMeanDeadline'][1], GenerationMetadata['StdMeanDeadline'][0]))
            if TaskDeadline >= (GenerationMetadata['LowUpDeadline'][0] * TaskExecutionTime) and TaskDeadline <= (GenerationMetadata['LowUpDeadline'][1] * TaskPeriod):
                break

        if GenerationMetadata['PriorityOverlapping'] == 0:
            while True:
                TaskPriority = int(np.random.normal(GenerationMetadata['StdMeanPriority'][1], GenerationMetadata['StdMeanPriority'][0]))
                if TaskPriority not in UsedPriorities and (TaskPriority >= GenerationMetadata['LowUpPriority'][0] and TaskPriority <= GenerationMetadata['LowUpPriority'][1]):
                    UsedPriorities.add(TaskPriority)
                    break
        else:
            while True:
                TaskPriority = int(np.random.normal(GenerationMetadata['StdMeanPriority'][1], GenerationMetadata['StdMeanPriority'][0]))
                if TaskPriority >= GenerationMetadata['LowUpPriority'][0] and TaskPriority <= GenerationMetadata['LowUpPriority'][1]:
                    break

        # Add task to the dictionary
        TasksMetadata[TaskName] = {
            "TaskName": TaskName,
            "TaskPriority": TaskPriority,
            "TaskExecutionTime": TaskExecutionTime,
            "TaskDeadline": TaskDeadline,
            "TaskPeriod": TaskPeriod
        }

    return TasksMetadata


def ComputeLoadFactor(TasksMetadata):
    Tasks = list(TasksMetadata)
    TasksCount = len(Tasks)
    LoadFactor = 0

    for i in range(0, TasksCount):
        LoadFactor += TasksMetadata[Tasks[i]]["TaskExecutionTime"]/TasksMetadata[Tasks[i]]["TaskDeadline"]

    return LoadFactor


def main():
    if len(sys.argv) != 3:
        print("Usage: ./generate.py <path_to_generation_metadata> <path_to_output_file>")
        print("<generate_for>: either LoadFactor or ExecutionTime")
        print("Example of generation metadata format:")
        print("{")
        print('    "TaskAmount": 24,')
        print('    "PriorityOverlapping": 1,')
        print('    "StdMeanPeriod": [1,2],')
        print('    "LowUpPeriod": [1,2],')
        print('    "StdMeanDeadline": [1,2],')
        print('    "LowUpDeadline": [1,2],')
        print('    "StdMeanExec": [1,2],')
        print('    "LowUpExec": [1,2],')
        print('    "StdMeanPriority": [1,2],')
        print('    "LowUpPriority": [1,2]')
        print("}")
        sys.exit(1)

    GenerationMetadataFile = sys.argv[1]
    OutputFilePath = sys.argv[2]


    with open(GenerationMetadataFile, 'r') as json_file:
        GenerationMetadata = json.load(json_file)

    TasksMetadata = GenerateTasksMetadata(GenerationMetadata)
    LoadFactor=ComputeLoadFactor(TasksMetadata)

    print(TasksMetadata)
    print(LoadFactor)

    with open(OutputFilePath, 'w') as json_file:
        json.dump(TasksMetadata, json_file, indent=4)


if __name__ == "__main__":
    main()


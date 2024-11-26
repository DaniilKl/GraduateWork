#!/usr/bin/env python3

import numpy as np
import random
import sys
import json

def GenerateTasksMetadata(NumTasks, AlphaBetaPeriod, AlphaBetaDeadline, StdMeanExec, StdMeanPriority):
    TasksMetadata = {}
    UsedPriorities = set()  # Set to track used priorities

    for i in range(1, NumTasks + 1):
        TaskName = f"v{i}_Task"

        # Generate TaskExecutionTime using Normal distribution and clip to [10, 1000]
        TaskExecutionTime = int(np.clip(np.random.normal(StdMeanExec[1], StdMeanExec[0]), 1, 20))

        # Generate TaskPeriod using Beta distribution scaled to [2 * TaskExecutionTime + 1, 300]
        BetaSamplePeriod = np.random.beta(AlphaBetaPeriod[0], AlphaBetaPeriod[1])
        TaskPeriod = int((TaskExecutionTime + 1) + BetaSamplePeriod * (300 - (TaskExecutionTime + 1)))

        # Generate TaskDeadline using Beta distribution scaled to [TaskExecutionTime, TaskPeriod]
        BetaSampleDeadline = np.random.beta(AlphaBetaDeadline[0], AlphaBetaDeadline[1])
        TaskDeadline = int(TaskExecutionTime + BetaSampleDeadline * (TaskPeriod - TaskExecutionTime))

        # Generate TaskPriority using Normal distribution and clip to [1, 25], ensuring it's unique
        while True:
            TaskPriority = int(np.clip(np.random.normal(StdMeanPriority[1], StdMeanPriority[0]), 1, 25))
            if TaskPriority not in UsedPriorities:
                UsedPriorities.add(TaskPriority)
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
        LoadFactor += TasksMetadata[Tasks[i]]["TaskExecutionTime"]/TasksMetadata[Tasks[i]]["TaskPeriod"]

    return LoadFactor


def main():
    if len(sys.argv) != 3:
        print("Usage: ./generate.py <number_of_tasks> <path_to_output_file>")
        sys.exit(1)

    NumberOfTasks = int(sys.argv[1])
    OutputFilePath = sys.argv[2]
    AlphaBetaPeriod = [3.5, 3]
    AlphaBetaDeadline = [3.5, 3]
    StdMeanExec = [10, 6]
    StdMeanPriority = [128,50]

    TasksMetadata = GenerateTasksMetadata(NumberOfTasks, AlphaBetaPeriod, AlphaBetaDeadline, StdMeanExec, StdMeanPriority)
    LoadFactor = ComputeLoadFactor(TasksMetadata)

    print(TasksMetadata)
    print(LoadFactor)

    with open(OutputFilePath, 'w') as json_file:
        json.dump(TasksMetadata, json_file, indent=4)


if __name__ == "__main__":
    main()


#!/usr/bin/env python3

import sys
import re
import json

def PrepareTasksStrings(TasksMetadata):
    Tasks = list(TasksMetadata)
    TasksCount = len(Tasks)

    TasksDeclarationStrings = "\n"
    TasksCreationStrings = "\n"
    TasksDefinitionStrings = "\n"

    for i in range(0, TasksCount):
        TasksDeclarationStrings += f"void {TasksMetadata[Tasks[i]]['TaskName']}(void *pvParameters);" + "\n"

        TasksCreationStrings += "        #ifdef USE_FREERTOS_CLASSIC_SCHEDULER\n"
        TasksCreationStrings += f"        xTaskCreate({TasksMetadata[Tasks[i]]['TaskName']}, \"{TasksMetadata[Tasks[i]]['TaskName']}\", TASK_STACK_LENGHT_WORDS, NULL, {TasksMetadata[Tasks[i]]['TaskPriority']}, {TasksMetadata[Tasks[i]]['TaskExecutionTime']}, {TasksMetadata[Tasks[i]]['TaskDeadline']}, NULL);" + "\n"
        TasksCreationStrings += "        #else\n"
        TasksCreationStrings += f"        xTaskCreate({TasksMetadata[Tasks[i]]['TaskName']}, \"{TasksMetadata[Tasks[i]]['TaskName']}\", TASK_STACK_LENGHT_WORDS, NULL, {TasksMetadata[Tasks[i]]['TaskExecutionTime']}, {TasksMetadata[Tasks[i]]['TaskDeadline']}, NULL);" + "\n"
        TasksCreationStrings += "        #endif\n"

        TasksDefinitionStrings += f"void {TasksMetadata[Tasks[i]]['TaskName']} (void *pvParameters)" + "{\n"
        TasksDefinitionStrings += "        TickType_t xLastWakeTime = 0;\n\n"
        TasksDefinitionStrings += "        while (1){\n"
        TasksDefinitionStrings += "                pxCurrentTCB->xTaskCurrentExecutionTime = pxCurrentTCB->xTaskExecutionTime;\n"
        TasksDefinitionStrings += "                do{\n"
        TasksDefinitionStrings += "                }while( pxCurrentTCB->xTaskCurrentExecutionTime != 0 );\n\n"
        TasksDefinitionStrings += f"                vTaskDelayUntil(&xLastWakeTime, {TasksMetadata[Tasks[i]]['TaskPeriod']});" + "\n"
        TasksDefinitionStrings += "        }\n\n"
        TasksDefinitionStrings += "        vTaskDelete(NULL);\n"
        TasksDefinitionStrings += "}\n\n"

    return TasksDeclarationStrings, TasksCreationStrings, TasksDefinitionStrings
    

def InsertTaskStrings(InputCFile, OutputCFile, TasksDeclarationStrings, TasksCreationStrings, TasksDefinitionStrings):
    with open(InputCFile, 'r') as file:
        CFileContent = file.read()

    def InsertNewLines(CFileContent, StartComment, StringToInsert):
        Pattern = re.escape(StartComment)
        NewContent = re.sub(Pattern, lambda m: m.group(0) + StringToInsert, CFileContent, flags=re.DOTALL)
        return NewContent

    CFileContent = InsertNewLines(CFileContent, "// Tasks declarations START", TasksDeclarationStrings)
    CFileContent = InsertNewLines(CFileContent, "// Tasks creation START", TasksCreationStrings)
    CFileContent = InsertNewLines(CFileContent, "// Tasks definition START", TasksDefinitionStrings)

    with open(OutputCFile, 'w') as file:
        file.write(CFileContent)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python script.py <input_c_file> <tasks_metadata_file> <output_c_file_path>")
        sys.exit(1)

    InputCFile = sys.argv[1]
    TasksMetadataFile = sys.argv[2]
    OutputCFile = sys.argv[3]

    with open(TasksMetadataFile, 'r') as json_file:
        TasksMetadata = json.load(json_file)

    TasksDeclarationStrings, TasksCreationStrings, TasksDefinitionStrings = PrepareTasksStrings(TasksMetadata)

    InsertTaskStrings(InputCFile, OutputCFile, TasksDeclarationStrings, TasksCreationStrings, TasksDefinitionStrings)


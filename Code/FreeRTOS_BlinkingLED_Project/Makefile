CC = ~/Toolchains/arm-none-eabi-13.2.Rel1/bin/arm-none-eabi-gcc-13.2.1

# Common variables:
BIN = FreeRTOSblinki.elf
SRC_DIR = $(abspath ./src)
BUILD_DIR = $(abspath ./build)

# Includes:
#CMSIS paths:
#CMSIS_SRC += $(abspath ../CMSIS*/Device/ARM/ARMCM4/Source/*.c)
#CMSIS_INC += $(abspath ../CMSIS*/Device/ARM/ARMCM4/Include/) \
#		 $(abspath ../CMSIS/CMSIS/Core/Include/)

#stm32f4xx-hal-driver paths:
#HAL_SRC += $(absapth ../stm32f4xx-hal-driver/Src/*.c)
#HAL_INC += $(abspath ../stm32f4xx-hal-driver/Inc/)

# FreeRTOS dirs paths:
FREERTOS_SRC_DIR := $(abspath ../FreeRTOSv202212.01/FreeRTOS/Source)
FREERTOS_PORTABLE_SRC_DIR := $(abspath \
			     ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F)
FREERTOS_MEM_SRC_DIR := $(abspath \
			../FreeRTOSv202212.01/FreeRTOS/Source/portable/MemMang)
FREERTOS_INC_DIR := -I$(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/include/)
FREERTOS_PORTABLE_INC_DIR := -I$(abspath \
			     ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F)

# FreeRTOS files paths:
FREERTOS_INC := $(FREERTOS_INC_DIR) \
		$(FREERTOS_PORTABLE_INC_DIR)
FREERTOS_SRC_FILES := tasks.c list.c heap_1.c port.c

# Local files paths
LOCAL_INC := -I$(abspath ./Include)
LOCAL_SRC_FILES := startup.c main.c

# Global files paths
INC := $(FREERTOS_INC) $(LOCAL_INC)
SRC_FILES := $(FREERTOS_SRC_FILES) $(LOCAL_SRC_FILES)

# Search path
VPATH = src:$(FREERTOS_SRC_DIR) \
	$(FREERTOS_PORTABLE_SRC_DIR) \
	$(FREERTOS_MEM_SRC_DIR) \
	$(wildcard $(abspath ./src))

# Object files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)


# Flags:
DEFINES := -DHEAP1

TARGETFLAGS := -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16

LINKERFLAGS := $(TARGETFLAGS) -T $(abspath ./linker_script.ld) \
	       -Wl,-Map=$(BUILD_DIR)/project.map,--cref -save-temps -lc \
	       -nostartfiles -static

DEBUGFLAGS := -ggdb -Og

# For more warnings add -Wall and -Wextra
CFLAGS := $(TARGETFLAGS) -Wno-error=implicit-function-declaration \
	  $(DEBUGFLAGS) $(INC) $(DEFINES)


OBJFILES := $(SRC:%.c=$(BUILDDIR)/%.o)


# Rules:
$(BUILD_DIR)/$(BIN): $(OBJ_FILES)
	$(CC) $(LINKERFLAGS) $+ -o $(@)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DIR):
	$(shell [ -d ./build ] || mkdir build)

.PHONY: clean

clean:
	rm -rf ./build

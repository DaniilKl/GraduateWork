CC = ~/Toolchains/arm-none-eabi-13.2.Rel1/bin/arm-none-eabi-gcc-13.2.1

# Common variables:
BIN = FreeRTOS_QEMU.elf
SRC_DIR = $(abspath ./src)
BUILD_DIR = $(abspath ./build)

# FreeRTOS dirs paths:
FREERTOS_SRC_DIR := $(abspath ../FreeRTOS/FreeRTOS/Source)
FREERTOS_PORTABLE_SRC_DIR := $(abspath \
			     ../FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM3)
FREERTOS_MEM_SRC_DIR := $(abspath \
			../FreeRTOS/FreeRTOS/Source/portable/MemMang)
FREERTOS_INC_DIR := -I$(abspath ../FreeRTOS/FreeRTOS/Source/include/)
FREERTOS_PORTABLE_INC_DIR := -I$(abspath \
			     ../FreeRTOS/FreeRTOS/Source/portable/GCC/ARM_CM3)

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

TARGETFLAGS := -mthumb -mcpu=cortex-m3

LINKERFLAGS := $(TARGETFLAGS) -T $(abspath ./linker_script.ld) \
	       -Wl,-Map=$(BUILD_DIR)/project.map,--cref -save-temps -lc \
	       -nostartfiles -static

DEBUGFLAGS := -ggdb -Og

# For more warnings add -Wall and -Wextra
CFLAGS := $(TARGETFLAGS) -Wno-error=implicit-function-declaration \
	  $(DEBUGFLAGS) $(INC) $(DEFINES) -O0


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

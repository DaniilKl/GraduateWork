CC = ~/Repos/arm-gnu-toolchain-12.3.rel1/bin/arm-none-linux-gnueabihf-gcc

#Common variables:
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

#FreeRTOS dirs paths:
FREERTOS_SRC_DIR := $(abspath ../FreeRTOSv202212.01/FreeRTOS/Source)
FREERTOS_PORTABLE_SRC_DIR := $(abspath \
			     ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F)
FREERTOS_MEM_SRC_DIR := $(abspath \
			../FreeRTOSv202212.01/FreeRTOS/Source/portable/MemMang)
FREERTOS_INC_DIR := -I$(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/include/)
FREERTOS_PORTABLE_INC_DIR := -I$(abspath \
			     ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F)

#FreeRTOS files paths:
FREERTOS_SRC := $(wildcard $(FREERTOS_SRC_DIR)/*.c) \
		$(wildcard $(FREERTOS_PORTABLE_SRC_DIR)/*.c) \
		$(wildcard $(FREERTOS_MEM_SRC_DIR)/*.c)
FREERTOS_INC := $(FREERTOS_INC_DIR) \
		$(FREERTOS_PORTABLE_INC_DIR)
FREERTOS_SRC_FILES := $(notdir $(FREERTOS_SRC))

# Local files paths
LOCAL_SRC := $(wildcard $(abspath ./src)/*.c)
LOCAL_INC := -I$(abspath ./Include)
LOCAL_SRC_FILES := $(notdir $(LOCAL_SRC))

# Global files paths
SRC := $(FREERTOS_SRC) $(LOCAL_SRC)
INC := $(FREERTOS_INC) $(LOCAL_INC)
SRC_FILES := $(FREERTOS_SRC_FILES) $(LOCAL_SRC_FILES)


# Flags:
DEFINES := -DHEAP1
LINKERFLAGS := -Xlinker \
	       -T $(abspath ./linker_script.ld) \
	       -Wl,-Map=$(BUILD_DIR)/project.map,--cref -save-temps -lc

TARGETFLAGS := -mcpu=cortex-m4 -mthumb
DEBUGFLAGS := -ggdb -Og

CPPFLAGS := $(DEFINES)
CFLAGS := $(TARGETFLAGS) -nostartfiles -Wno-error=implicit-function-declaration \
	  -Wno-builtin-declaration-mismatch -Werror \
	  -Wall -Wextra $(DEBUGFLAGS) $(INC)


OBJFILES := $(SRC:%.c=$(BUILDDIR)/%.o)


# Rules:
$(BUILD_DIR)/$(BIN): $(OBJ_FILES)
	$(CC) -ffunction-sections -fdata-sections $(CFLAGS) $(LINKERFLAGS) $+ -o $(@)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

INCLUDES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.d)
-include $(INCLUDES)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

$(BUILD_DIR):
	$(shell [ -d ./build ] || mkdir build)

.PHONY: clean

clean:
	rm -rf ./build

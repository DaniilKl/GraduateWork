CC = ~/Repos/arm-gnu-toolchain-12.3.rel1/bin/arm-none-linux-gnueabihf-gcc

#Common variables:
BIN = FreeRTOSblinki.elf
BUILDDIR = build

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
FREERTOS_INC_DIR := $(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/include)
FREERTOS_PORTABLE_INC_DIR := $(abspath \
			     ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F)

#FreeRTOS files paths:
FREERTOS_SRC := $(wildcard $(FREERTOS_SRC_DIR)/*.c) \
		$(wildcard $(FREERTOS_PORTABLE_SRC_DIR)/*.c) \
		$(wildcard $(FREERTOS_MEM_SRC_DIR)/*.c)
FREERTOS_INC := $(wildcard $(FREERTOS_INC_DIR)/*.h) \
		$(wildcard $(FREERTOS_PORTABLE_INC_DIR)/*.h)

#SRC += init/startup.c  syscall.c
SRC_DIR := $(FREERTOS_SRC_DIR) \
	   $(FREERTOS_PORTABLE_SRC_DIR) \
	   $(FREERTOS_MEM_SRC_DIR) \
	   $(abspath ./src)
INC_DIR := $(FREERTOS_INC_DIR) \
	   $(FREERTOS_PORTABLE_INC_DIR) \
	   $(abspath ./Include)

SRC += $(FREERTOS_SRC) $(wildcard $(abspath ./src/)/*.c)
INC += $(FREERTOS_INC) $(wildcard $(abspath ./Include/)/*.h)


# Flags:
DEFINES := -DHEAP1
LINKERFLAGS := -Xlinker \
	       -T $(abspath ./linker_script.ld) \
	       -Wl,-Map=$(BUILDDIR)/project.map,--cref -save-temps -lc

TARGETFLAGS := -mcpu=cortex-m4 -mthumb
OUTPUTFLAGS := -o $(BIN)
DEBUGFLAGS := -ggdb -Og

CPPFLAGS := $(DEFINES)
CFLAGS := $(TARGETFLAGS) -nostartfiles -Wno-error=implicit-function-declaration \
	  -Wno-builtin-declaration-mismatch -Werror \
	  -Wall -Wextra $(DEBUGFLAGS)


OBJFILES := $(SRC:%.c=$(BUILDDIR)/%.o)


# Rules:
$(BUILDDIR)/$(BIN): $(OBJ_FILES)
	$(CC) -ffunction-sections -fdata-sections $(CFLAGS) $(LINKERFLAGS) $+ -o $(@)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;

INCLUDES := $(SOURCE_FILES:%.c=$(BUILDDIR)/%.d)
-include $(INCLUDES)

${BUILDDIR}/%.o : %.c Makefile build_dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

build_dir:
	$(shell [ -d ./build ] || mkdir build)



.PHONY clean
clean:
	rm -rf ./build

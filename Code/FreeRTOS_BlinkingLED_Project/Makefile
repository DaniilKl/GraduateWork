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

#FreeRTOS paths:
FREERTOS_SRC += $(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/) \
		$(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F/) \
		$(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/portable/MemMang/)
FREERTOS_INC += $(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/include/) \
		$(abspath ../FreeRTOSv202212.01/FreeRTOS/Source/portable/GCC/ARM_CM4F/) \

#SRC += init/startup.c  syscall.c
SRC += $(FREERTOS_SRC) $(abspath ./src/) 

INC += $(FREERTOS_INC) $(abspath ./Include/)


# Flags:
DEFINES := -DHEAP1
LINKERFLAGS := -T ./linker_script.ld -W1, -Map=$(BUILDDIR)/project.map,--cref -save-temp
TARGETFLAGS := -mcpu=cortex-m4 -mthumb
OUTPUTFLAGS := -o blink.elf

FLAGS = $(LINKERFLAGS) $(TARGETFLAGS) $(OUTPUTFLAGS) -ggdb \
	-Wno-error=implicit-function-declaration \
	-Wno-builtin-declaration-mismatch -Werror -Wall -Wextra -nostartfiles \
	-fstrict-aliasing -Wstrict-aliasing -Wno-error=address-of-packed-member

# Rules:

build:
	$(CC) -ffunction-sections -fdata-sections main.c $(SRC) $(FLAGS)
	[ -d temps ] || mkdir temps
	mv *.i *.s *.o *.map ./temps

.PHONY clean
clean:
	rm -rf temps/

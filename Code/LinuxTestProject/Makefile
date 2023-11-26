CC = ~/Repos/arm-gnu-toolchain-12.3.rel1/bin/arm-none-linux-gnueabihf-gcc
LINKERFLAGS= -T $(LINKFILES)
TARGETFLAGS = -mcpu=cortex-m4 -mthumb
OUTPUTFLAGS = -o blink.elf
FLAGS = $(LINKERFLAGS) $(TARGETFLAGS) $(OUTPUTFLAGS) -ggdb -nostdlib -Wl,-Map=project.map,--cref -save-temps

LINKFILES = linker_script.ld

build:
	$(CC) main.c startup.c $(FLAGS)
	[ -d temps ] || mkdir temps
	mv *.i *.s *.o *.map ./temps

clean:
	rm -rf temps/

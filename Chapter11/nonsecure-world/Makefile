CROSS_COMPILE:=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)gcc
OBJS:=startup.o main.o timer.o led.o system.o

LSCRIPT:=target.ld

OBJCOPY:=$(CROSS_COMPILE)objcopy

secfail:CFLAGS+=-DTEST_GPIO_SECURE_FAIL



CFLAGS:=-mcpu=cortex-m3 -mthumb -g -ggdb -Wall -Wno-main -Wstack-usage=200 -ffreestanding -Wno-unused -nostdlib
CFLAGS+=-I$(PWD)/../secure-world
LDFLAGS:=-T $(LSCRIPT) -Wl,-gc-sections -Wl,-Map=image.map -nostdlib

#all: image.bin

image.bin: image.elf
	$(OBJCOPY) -O binary $^ $@


secfail:image.bin

image.elf: $(OBJS) $(LSCRIPT)
	$(LD) $(LDFLAGS) $(OBJS) $(PWD)/../secure-world/led_cmse.o -o $@
	
startup.o: startup.c

main.o: main.c

clean:
	rm -f image.bin image.elf *.o image.map tags

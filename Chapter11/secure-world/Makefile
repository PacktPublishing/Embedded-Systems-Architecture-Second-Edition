CROSS_COMPILE:=arm-none-eabi-
CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)ld
OBJCOPY:=$(CROSS_COMPILE)objcopy

CFLAGS:=-mcpu=cortex-m33 -mthumb -g -ggdb -Wall -Wno-main -fstack-check -mcmse
LDFLAGS:=-gc-sections -nostdlib --cmse-implib --out-implib=led_cmse.o

all: bootloader.bin

bootloader.bin: bootloader.elf
	$(OBJCOPY) -O binary  $< $@

bootloader.elf: startup_bl.o utils.o system.o led.o main.o nsc_led.o
	$(LD) $(LDFLAGS) $^ -o $@ -Map=bootloader.map -T bootloader.ld


clean:
	rm -f *.bin *.elf *.o *.map

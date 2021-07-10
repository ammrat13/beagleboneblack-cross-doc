MLO_OFILES := \
	src/start.o src/main.o \
	src/pwr/cm.o src/io/gpio.o
INCLUDE := -Iinclude/

TARGET ?= arm-linux-uclibcgnueabi
AS := $(TARGET)-as
CC := $(TARGET)-gcc
LD := $(TARGET)-gcc
OBJCOPY := $(TARGET)-objcopy

ASFLAGS := \
	-v -mcpu=cortex-a8
CFLAGS := \
	-v -Os -mcpu=cortex-a8 -Wall -Werror \
	-ffreestanding -nostdlib \
	-ffunction-sections -fdata-sections
LDFLAGS := \
	-v -mcpu=cortex-a8 \
	-ffreestanding -nostdlib \
	-Tutil/lnkscript -Wl,--orphan-handling=error,-gc-sections
OBJCOPYFLAGS := \
	-O binary


.PHONY : all clean
.SECONDARY :

all : MLO

clean :
	find . -name "*.o" -exec rm -vf {} \;
	find . -name "*.elf" -exec rm -vf {} \;
	find . -name "*.hex" -exec rm -vf {} \;
	rm -vf MLO


MLO : mlo.hex
	python util/img_hdr.py $^ $@

mlo.elf : $(MLO_OFILES)
	$(LD) $(LDFLAGS) -o $@ $^


%.o : %.s
	$(AS) $(ASFLAGS) -c -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

%.hex : %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $^ $@

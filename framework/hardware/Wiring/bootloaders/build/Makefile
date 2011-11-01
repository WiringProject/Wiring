## $Id: Makefile 1153 2011-06-07 00:51:12Z bhagman $
###############################################################################
#
# Wiring Bootloader Makefile
#
# Copyright (C) 2010-2011 Brett Hagman <bhagman@wiring.org.co>
#
# http://wiring.org.co/
# http://roguerobotics.com/
#
###############################################################################

PROJECT = WiringBoot

include *.mk

TARGET = WiringBoot

# SOURCEFOLDER = ..
VPATH = ..

#ifdef BOOT_PROTOCOL
#SOURCES = stk500v2.c serial.c WiringBoot.c
#else ifeq ($(strip $(BOOT_PROTOCOL)),STK500V1)
#SOURCES = stk500v1.c serial.c WiringBoot.c
#else ifeq ($(strip $(BOOT_PROTOCOL)),STK500V2)
#SOURCES = stk500v2.c serial.c WiringBoot.c
#else
#SOURCES = $(BOOT_PROTOCOL_SOURCE) serial.c WiringBoot.c
#endif

SOURCES = stk500v2.c serial.c WiringBoot.c

MYCFLAGS += -DHW_DEFS_H=\"boards/$(HW_DEFS_H)\"
MYCFLAGS += -DBOOTLOADER_ADDRESS=0x$(BOOTLOADER_ADDRESS)
#MYCFLAGS += -DBOOT_$(BOOT_PROTOCOL)
MYCFLAGS += $(EXTRACFLAGS)

MYLDFLAGS += -Wl,-section-start=.text=0x$(BOOTLOADER_ADDRESS)
MYLDFLAGS += -nostartfiles


LINKONLYOBJECTS =

###############################################
## No need to change anything below (hopefully)

CC = avr-gcc
CPP = avr-g++

## Objects that must be built in order to link

OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99
CFLAGS += -DF_CPU=$(F_CPU)UL
CFLAGS += $(MYCFLAGS)
CFLAGS += -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += $(MYLDFLAGS)


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings

## Common

COMPILE.c   = $(CC)  $(INCLUDES) $(CFLAGS)   -c
COMPILE.cxx = $(CPP) $(INCLUDES) $(CFLAGS)   -c
COMPILE.asm = $(CC)  $(INCLUDES) $(ASMFLAGS) -c
LINK.c      = $(CC)  $(CFLAGS) $(LDFLAGS)
LINK.cxx    = $(CPP) $(CFLAGS) $(LDFLAGS)

## Build
all: $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).lss size

## Compile

%.o: %.c
	$(COMPILE.c) $< -o $@

%.o: %.C
	$(COMPILE.cxx) $< -o $@

%.o: %.cc
	$(COMPILE.cxx) $< -o $@

%.o: %.cpp
	$(COMPILE.cxx) $< -o $@

%.o: %.CPP
	$(COMPILE.cxx) $< -o $@

%.o: %.c++
	$(COMPILE.cxx) $< -o $@

%.o: %.cp
	$(COMPILE.cxx) $< -o $@

%.o: %.cxx
	$(COMPILE.cxx) $< -o $@

%.o: %.asm
	$(COMPILE.asm) $< -o $@

%.o: %.S
	$(COMPILE.asm) $< -o $@


## Link
$(TARGET).elf: $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET).elf

%.hex: $(TARGET).elf
	@echo
	@echo "Creating Flash HEX file:"
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS) $< $@

%.eep: $(TARGET).elf
	@echo
	@echo "Creating EEPROM HEX file:"
	avr-objcopy -O ihex $(HEX_EEPROM_FLAGS) $< $@ || exit 0

%.lss: $(TARGET).elf
	@echo
	@echo "Generating listing file:"
	avr-objdump -h -S $< > $@

size: $(TARGET).elf
	@echo
	@avr-size -C --mcu=$(MCU) $(TARGET).elf

## Clean target
.PHONY: clean size
clean:
	-rm -f *.o $(TARGET).elf dep/* $(TARGET).eep $(TARGET).lss $(TARGET).map
	-rm -f *.hex


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

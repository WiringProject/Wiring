#*******************************************************************************
# Wiring Core Makefile
#*******************************************************************************

#--- AVR Toolchain Variables
CPP	= avr-g++
CC	= avr-gcc
AS	= avr-gcc
AR	= avr-ar
RM	= rm -f
RN	= mv
CP  = cp
BIN	= avr-objcopy
ELFCOF = objtool
INCDIR = .

#--- default mcu type
MCU = atmega128
#MCU = atmega1281
#MCU = atmega2561

#--- default c++ flags
CPPFLAGS = -g -mmcu=$(MCU) -Wall -w -Os -I. -fno-exceptions -ffunction-sections -fdata-sections -ffreestanding 

#--- default compiler flags -ahlmsn
CPFLAGS	= -g -mmcu=$(MCU) -Wall -w -Os -ffunction-sections -fdata-sections -ffreestanding -std=gnu99 -I.

#--- default assembler flags 
ASFLAGS = -mmcu=$(MCU) -Wa,-mmcu=$(MCU),-gstabs

#--- default linker flags
LDFLAGS = -Os -Wl,--gc-sections,-u,-Map=$(<:.o=.map),--cref -mmcu=$(MCU) -lm

#--- default ar flags
ARFLAGS = rcs

#--- output format can be srec (Motorola), ihex (Intel HEX)
ROMFORMAT = srec
EEPROMFORMAT = ihex

#*******************************************************************************
# Compilation Rules
#*******************************************************************************

#--- compile: create assembler and/or object files from C++ source
%o : %cpp 
	$(CPP) -c $(CPPFLAGS) -I$(INCDIR) $< -o $@

#--- compile: create assembler and/or object files from C source
#.c.o:
%o : %c 
	$(CC) -c $(CPFLAGS) -I$(INCDIR) $< -o $@

%s : %c
	$(CC) -s $(CPFLAGS) -I$(INCDIR) $< -o $@

#--- assemble: create object file from assembler source
%o : %S
	$(AS) -x assembler-with-cpp $(ASFLAGS) -I$(INCDIR) -c $< -o $@

%: %.c
	@echo "Error: target $@ not defined in Makefile"
	@exit 1

#--- link: create elf output file from object files
%elf:	%o
	$(CC) $^ $(LIB) $(LDFLAGS) -o $@

#--- create AVR Studio cof file from elf output file and map file
%cof: %elf
	$(ELFCOF) loadelf $^ mapfile $(<:.elf=.map) writecof $@

#--- create flash and eeprom bin file (ihex, srec) from elf output file
%rom: %elf
	$(BIN) -O $(ROMFORMAT) -R .eeprom $< $@

%eep: %elf
	$(BIN) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O $(EEPROMFORMAT) $< $(@:.elf=.eep)


#*******************************************************************************
# Project Build Rules
#*******************************************************************************

#--- if all other steps compile ok then echo "Errors: none".
DONE = @echo Errors: none

#--- declare the primary target
all:	Wiring Core 

#--- build binary, for AVRStudio: Wiring.cof

Wiring:	Wiring.rom
	$(DONE)

Core:		core.a
	$(DONE)

#--- specify linking list
Wiring.elf:	main.o Wiring.o WTimer.o WPulse.o WInterrupts.o Print.o WMath.o WString.o WMemory.o Tone.o WShift.o program.cpp

OBJ = Wiring.o main.o WTimer.o WPulse.o WInterrupts.o Print.o WMath.o WString.o WMemory.o Tone.o WShift.o
core.a:		$(OBJ) 
	@for i in $(OBJ); do echo $(AR) rcs core.a $$i; $(AR) rcs core.a $$i; done

#--- specify dependencies
program.o:	program.cpp WProgram.h WConstants.h 
main.o:		main.cpp
Wiring.o:	Wiring.c WConstants.h
WTimer.o:	WTimer.c WConstants.h
WInterrupts.o:	WInterrupts.c WConstants.h
WMath.o:	WMath.cpp
WMemory.o:	WMemory.cpp
WString.o:	WString.cpp WString.h
WPulse.o:	WPulse.cpp WConstants.h 
Print.o:	Print.cpp Print.h
Tone.o:		Tone.cpp
WShift.o:	WShift.cpp WProgram.h

#--- clean build directory
clean:
	$(RM) *.rom *.eep *.cof
	$(RM) *.o 
	$(RM) *.elf 
	$(RM) *.lst 
	$(RM) *.ma
	$(RM) *.a

#*******************************************************************************
# AVR Programmer Rules
#*******************************************************************************

UISP = uisp
UISPPORT = /dev/tty.usbserial-3B1

program: Wiring.rom
	$(UISP) -dprog=stk500 -v=2 -dserial=$(UISPPORT) -dpart=$(MCU) if=Wiring.rom --upload


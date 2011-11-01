## $Id: AtmelBare.mk 1219 2011-06-30 05:35:59Z bhagman $
#####################################################
#
# Bare Atmel microcontrollers.
# ATmega
# ATmega164P(A), '324P(A), '644P(A), '1284(P),
# ATmega88(P)A, '168(P)(A), and '328(P).
#
# Written by Brett Hagman <bhagman@wiring.org.co>
# 2010, 2011
#
# http://wiring.org.co/
#
# TODO: define '88, '164, and '324
#####################################################

## ATmega168-16MHz (old version)
atmel-168old-16MHz: HARDWARE = ATmega168old_16MHz
atmel-168old-16MHz: MCU = atmega168
atmel-168old-16MHz: BOOTLOADER_ADDRESS = 3800
atmel-168old-16MHz: F_CPU = 16000000
atmel-168old-16MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-168old-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-115200
atmel-168old-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega168xx-8MHz (old version)
atmel-168old-8MHz: HARDWARE = ATmega168old_8MHz
atmel-168old-8MHz: MCU = atmega168
atmel-168old-8MHz: BOOTLOADER_ADDRESS = 3800
atmel-168old-8MHz: F_CPU = 8000000
atmel-168old-8MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-168old-8MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-57600
atmel-168old-8MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega168xx-16MHz
atmel-168-16MHz: HARDWARE = ATmega168_16MHz
atmel-168-16MHz: MCU = atmega168p
atmel-168-16MHz: BOOTLOADER_ADDRESS = 3800
atmel-168-16MHz: F_CPU = 16000000
atmel-168-16MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-168-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-115200
atmel-168-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega168xx-8MHz
atmel-168-8MHz: HARDWARE = ATmega168_8MHz
atmel-168-8MHz: MCU = atmega168p
atmel-168-8MHz: BOOTLOADER_ADDRESS = 3800
atmel-168-8MHz: F_CPU = 8000000
atmel-168-8MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-168-8MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-57600
atmel-168-8MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega328xx-16MHz
atmel-328-16MHz: HARDWARE = ATmega328_16MHz
atmel-328-16MHz: MCU = atmega328p
atmel-328-16MHz: BOOTLOADER_ADDRESS = 7800
atmel-328-16MHz: F_CPU = 16000000
atmel-328-16MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-328-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-115200
atmel-328-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega328xx-8MHz
atmel-328-8MHz: HARDWARE = ATmega328_8MHz
atmel-328-8MHz: MCU = atmega328p
atmel-328-8MHz: BOOTLOADER_ADDRESS = 7800
atmel-328-8MHz: F_CPU = 8000000
atmel-328-8MHz: HW_DEFS_H = defs-atmel-mxx8.h
atmel-328-8MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-57600
atmel-328-8MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega644xx-16MHz
atmel-644-16MHz: HARDWARE = ATmega644_16MHz
atmel-644-16MHz: MCU = atmega644p
atmel-644-16MHz: BOOTLOADER_ADDRESS = F800
atmel-644-16MHz: F_CPU = 16000000
atmel-644-16MHz: HW_DEFS_H = defs-atmel-mxx4.h
atmel-644-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-115200
atmel-644-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega644xx-8MHz
atmel-644-8MHz: HARDWARE = ATmega644_8MHz
atmel-644-8MHz: MCU = atmega644p
atmel-644-8MHz: BOOTLOADER_ADDRESS = F800
atmel-644-8MHz: F_CPU = 8000000
atmel-644-8MHz: HW_DEFS_H = defs-atmel-mxx4.h
atmel-644-8MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-57600
atmel-644-8MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega1284x-16MHz
atmel-1284-16MHz: HARDWARE = ATmega1284_16MHz
atmel-1284-16MHz: MCU = atmega1284p
atmel-1284-16MHz: BOOTLOADER_ADDRESS = 1F800
atmel-1284-16MHz: F_CPU = 16000000
atmel-1284-16MHz: HW_DEFS_H = defs-atmel-mxx4.h
atmel-1284-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-115200
atmel-1284-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## ATmega1284x-8MHz
atmel-1284-8MHz: HARDWARE = ATmega1284_8MHz
atmel-1284-8MHz: MCU = atmega1284p
atmel-1284-8MHz: BOOTLOADER_ADDRESS = 1F800
atmel-1284-8MHz: F_CPU = 8000000
atmel-1284-8MHz: HW_DEFS_H = defs-atmel-mxx4.h
atmel-1284-8MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-57600
atmel-1284-8MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

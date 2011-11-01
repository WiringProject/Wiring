## $Id: Arduino.mk 1153 2011-06-07 00:51:12Z bhagman $
#####################################################
#
# Arduino Boards
#

arduino-328p-16MHz: HARDWARE = arduino-328p-16MHz
arduino-328p-16MHz: MCU = atmega328p
arduino-328p-16MHz: BOOTLOADER_ADDRESS = 7800
arduino-328p-16MHz: F_CPU = 16000000
arduino-328p-16MHz: HW_DEFS_H = defs-arduino-328p.h
arduino-328p-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#arduino-328p-16MHz: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
arduino-328p-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex


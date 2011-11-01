## $Id: Wiring.mk 1153 2011-06-07 00:51:12Z bhagman $
#####################################################
#
# Wiring boards
#
# Written by Brett Hagman <bhagman@wiring.org.co>
# 2010, 2011
#
# http://wiring.org.co/
#
#####################################################

## Wiring S
wiring-s: HARDWARE = WiringS
wiring-s: MCU = atmega644p
wiring-s: BOOTLOADER_ADDRESS = F800
wiring-s: F_CPU = 16000000
wiring-s: HW_DEFS_H = defs-wiring-s.h
#wiring-s: BOOT_PROTOCOL = STK500V2
wiring-s: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#wiring-s: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
wiring-s: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## Wiring V1 Mega
wiring-v1-mega: HARDWARE = Wiring-V1-Mega
wiring-v1-mega: MCU = atmega128
wiring-v1-mega: BOOTLOADER_ADDRESS = 1F800
wiring-v1-mega: F_CPU = 16000000
wiring-v1-mega: HW_DEFS_H = defs-wiring-v1-mega.h
#wiring-v1-mega: BOOT_PROTOCOL = STK500V2
wiring-v1-mega: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#wiring-s: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
wiring-v1-mega: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## Wiring V1.1 1281
wiring-v11-1281: HARDWARE = Wiring-V1.1-1281
wiring-v11-1281: MCU = atmega1281
wiring-v11-1281: BOOTLOADER_ADDRESS = 1F800
wiring-v11-1281: F_CPU = 16000000
wiring-v11-1281: HW_DEFS_H = defs-wiring-v11-1281.h
#wiring-v11-1281: BOOT_PROTOCOL = STK500V2
wiring-v11-1281: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#wiring-s: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
wiring-v11-1281: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## Wiring V1.1 2561
wiring-v11-2561: HARDWARE = Wiring-V1.1-2561
wiring-v11-2561: MCU = atmega2561
wiring-v11-2561: BOOTLOADER_ADDRESS = 3F800
wiring-v11-2561: F_CPU = 16000000
wiring-v11-2561: HW_DEFS_H = defs-wiring-v11-2561.h
#wiring-v11-2561: BOOT_PROTOCOL = STK500V2
wiring-v11-2561: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#wiring-s: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
wiring-v11-2561: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

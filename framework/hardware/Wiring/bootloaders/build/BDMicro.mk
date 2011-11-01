## $Id: BDMicro.mk 1241 2011-09-14 03:36:07Z bhagman $
#########################
# BDMicro Mavric boards
#
# http://www.bdmicro.com/


## Mavric-IIB-14.7456MHz
mavric-iib: HARDWARE = Mavric-IIB_14745600Hz
mavric-iib: MCU = atmega128
mavric-iib: BOOTLOADER_ADDRESS = 1F800
mavric-iib: F_CPU = 14745600
mavric-iib: HW_DEFS_H = defs-bdmicro-mavric-iib.h
mavric-iib: BOOT_PROTOCOL = STK500V2
mavric-iib: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=115200
mavric-iib: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

## Mavric-IIB-16MHz
mavric-iib-16MHz: HARDWARE = Mavric-IIB_16MHz
mavric-iib-16MHz: MCU = atmega128
mavric-iib-16MHz: BOOTLOADER_ADDRESS = 1F800
mavric-iib-16MHz: F_CPU = 16000000
mavric-iib-16MHz: HW_DEFS_H = defs-bdmicro-mavric-iib.h
mavric-iib-16MHz: BOOT_PROTOCOL = STK500V2
mavric-iib-16MHz: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=115200
mavric-iib-16MHz: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

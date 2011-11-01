## $Id: RogueRobotics.mk 1153 2011-06-07 00:51:12Z bhagman $
#####################################################
#
# Rogue Robotics boards
#
# http://www.roguerobotics.com/products/electronics/ledhead
# http://www.roguerobotics.com/products/electronics/redi
#
# Written by Brett Hagman <bhagman@roguerobotics.com>
# 2010, 2011
#
# http://wiring.org.co/
# http://roguerobotics.com/
#
#####################################################

# Rogue Robotics LEDHead
ledhead: HARDWARE = LEDHead
ledhead: MCU = atmega644p
ledhead: BOOTLOADER_ADDRESS = F800
ledhead: F_CPU = 16000000
ledhead: HW_DEFS_H = defs-rogue-ledhead.h
#ledhead: BOOT_PROTOCOL = STK500V2
ledhead: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#ledhead: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
ledhead: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

# Rogue Robotics rEDI
redi: HARDWARE = rEDI
redi: MCU = atmega644p
redi: BOOTLOADER_ADDRESS = F800
redi: F_CPU = 16000000
redi: HW_DEFS_H = defs-rogue-redi.h
#redi: BOOT_PROTOCOL = STK500V2
redi: EXTRACFLAGS = -DBOOT_USART=0 -DBOOT_BAUD_RATE=-117647
#redi: EXTRACFLAGS += -DSERIAL_TIMEOUT=2
redi: all
	mv $(PROJECT).hex $(PROJECT)_$(HARDWARE).hex

/* $Id: WiringBoot.h 1153 2011-06-07 00:51:12Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | Wiring Serial Bootloader for
|| | Atmel megaAVR controllers
|| | using STK500V2 protocol.
|| #
||
|| @notes
|| | Only DEBUG_USART can be configured for SOFT_USART (for now).
|| #
||
|| @license Please see License.txt for license information.
||
*/

#ifndef WIRING_BOOT
#define WIRING_BOOT

#include <stdint.h>
#include <ctype.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/boot.h>
#include <util/delay.h>
#include "bhexppgm.h"
#include "avrportreg.h"
#include "serial.h"


/*************************************************************************/
// Constants
/*************************************************************************/
// Load Configuration for specific hardware
// HW_DEFS_H is the header filename (passed by the compiler command line)
// containing macros for hardware definitions

#ifdef HW_DEFS_H
 #include HW_DEFS_H
#else
 // need to define HW_DEFS_H as "defs-[boardname].h" in Makefile
 #error "Missing required hardware definition file (HW_DEFS_H)"
#endif

// Time-out values
// The getch() routine takes about 20 cycles per loop
// For now, let's calculate for a 2 second time-out

#ifndef SERIAL_TIMEOUT
#define SERIAL_TIMEOUT 2
#endif

#define MAX_TIME_COUNT ((F_CPU * SERIAL_TIMEOUT) / 20)
#define MAX_ERROR_COUNT 5


/*************************************************************************/
// Now, check and set defaults
/*************************************************************************/

#ifndef F_CPU
 #define F_CPU 16000000UL
 #warning "F_CPU not set - default to 16MHz"
#endif

#ifndef BOOT_BAUD_RATE
 #define BOOT_BAUD_RATE 115200
 #warning "BOOT_BAUD_RATE not set - default to 115200 bps"
#endif


/*************************************************************************/
// Configuration
/*************************************************************************/

// LED routines can be customized in HW_DEFS_H header

// On-board LED is used to indicate that the bootloader started.
// If NUM_LED_FLASHES == 0, no need to define LED

#if (NUM_LED_FLASHES > 0)

 #if defined (LED_PORT) && defined (LED_PIN)
  // Basic LED initialization (if omitted)
  #ifndef LEDInitialize
   #define LEDInitialize()    *(PORT_TO_DDR(LED_PORT)) |= (1 << LED_PIN)
  #endif
  #ifndef LEDOn
   #define LEDOn()            LED_PORT |= (1 << LED_PIN)
  #endif
  #ifndef LEDOff
   #define LEDOff()           LED_PORT &= ~(1 << LED_PIN)
  #endif
 #else
  #define LEDInitialize()
  #define LEDOn()
  #define LEDOff()
 #endif

 // LED flash time (in ms)
 #ifndef LED_FLASH_TIME
  #define LED_FLASH_TIME 100
  #warning "LED_FLASH_TIME not set - default to 100ms"
 #endif
#else
 #define LEDInitialize()
 #define LEDOn()
 #define LEDOff()
#endif

// Can define separate LED control for RX and TX
#ifndef LEDRXOn
 #define LEDRXInitialize()
 #define LEDRXOn()
 #define LEDRXOff()
#endif

#ifndef LEDTXOn
 #define LEDTXInitialize()
 #define LEDTXOn()
 #define LEDTXOff()
#endif


/*************************************************************************/
// Configure serial connections
/*************************************************************************/

#ifdef BOOT_USART
 #if BOOT_USART == 0
  #ifdef UBRRL
   #define boot_serial_init()           USARTInit()
   #define boot_serial_putch(c)         USARTSendByte(c)
   #define boot_serial_getch()          USARTGetByte()
   #define boot_serial_available()      USARTHasData()
   #define boot_serial_setBitrate(br)   USARTSetBitrate(br)
  #else
   #define boot_serial_init()           USART0Init()
   #define boot_serial_putch(c)         USART0SendByte(c)
   #define boot_serial_getch()          USART0GetByte()
   #define boot_serial_available()      USART0HasData()
   #define boot_serial_setBitrate(br)   USART0SetBitrate(br)
  #endif
 #elif BOOT_USART == 1
  #define boot_serial_init()            USART1Init()
  #define boot_serial_putch(c)          USART1SendByte(c)
  #define boot_serial_getch()           USART1GetByte()
  #define boot_serial_available()       USART1HasData()
  #define boot_serial_setBitrate(br)    USART1SetBitrate(br)
 #elif BOOT_USART == 2
  #define boot_serial_init()            USART2Init()
  #define boot_serial_putch(c)          USART2SendByte(c)
  #define boot_serial_getch()           USART2GetByte()
  #define boot_serial_available()       USART2HasData()
  #define boot_serial_setBitrate(br)    USART2SetBitrate(br)
 #elif BOOT_USART == 3
  #define boot_serial_init()            USART3Init()
  #define boot_serial_putch(c)          USART3SendByte(c)
  #define boot_serial_getch()           USART3GetByte()
  #define boot_serial_available()       USART3HasData()
  #define boot_serial_setBitrate(br)    USART3SetBitrate(br)
 #endif
#else
 #error "BOOT_USART not set"
#endif

#ifdef DEBUG
 #if DEBUG_USART == SOFT_PORT
   #define debug_serial_putch(c)        softSerialSendByte(c)
   #define debug_serial_init()          softSerialInit()
   #define debug_serial_getch()         softSerialGetByte()
   #define debug_serial_available()     softSerialHasData()
   #define debug_serial_setBitrate(br)  softSerialSetBitrate(br)
 #elif DEBUG_USART == 0
  #ifdef UBRRL
   #define debug_serial_putch(c)        USARTSendByte(c)
   #define debug_serial_init()          USARTInit()
   #define debug_serial_getch()         USARTGetByte()
   #define debug_serial_available()     USARTHasData()
   #define debug_serial_setBitrate(br)  USARTSetBitrate(br)
  #else
   #define debug_serial_putch(c)        USART0SendByte(c)
   #define debug_serial_init()          USART0Init()
   #define debug_serial_getch()         USART0GetByte()
   #define debug_serial_available()     USART0HasData()
   #define debug_serial_setBitrate(br)  USART0SetBitrate(br)
  #endif
 #elif DEBUG_USART == 1
  #define debug_serial_putch(c)         USART1SendByte(c)
  #define debug_serial_init()           USART1Init()
  #define debug_serial_getch()          USART1GetByte()
  #define debug_serial_available()      USART1HasData()
  #define debug_serial_setBitrate(br)   USART1SetBitrate(br)
 #elif DEBUG_USART == 2
  #define debug_serial_putch(c)         USART2SendByte(c)
  #define debug_serial_init()           USART2Init()
  #define debug_serial_getch()          USART2GetByte()
  #define debug_serial_available()      USART2HasData()
  #define debug_serial_setBitrate(br)   USART2SetBitrate(br)
 #elif DEBUG_USART == 3
  #define debug_serial_putch(c)         USART3SendByte(c)
  #define debug_serial_init()           USART3Init()
  #define debug_serial_getch()          USART3GetByte()
  #define debug_serial_available()      USART3HasData()
  #define debug_serial_setBitrate(br)   USART3SetBitrate(br)
 #else
  #error "DEBUG_USART not set"
 #endif
#else
 #define debug_serial_putch(c)
 #define debug_serial_init()
 #define debug_serial_getch()
 #define debug_serial_available()
 #define debug_serial_setBitrate(br)
#endif


/*************************************************************************/
// Prototypes
/*************************************************************************/

uint8_t boot_serial_getchTimeout(void);
void boot_serial_putstr_P(uint_flashptr_t str);
void boot_serial_getNch(uint8_t count);


#endif
// WIRING_BOOT

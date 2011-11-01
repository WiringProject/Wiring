/* $Id: defs-bdmicro-mavric-iib.h 1178 2011-06-11 06:02:07Z bhagman $
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | STK500v2 bootloader hardware definition file for
|| | BDMicro Mavric-IIB.
|| |
|| | http://www.bdmicro.com/mavric-iib/
|| #
||
|| @license Please see License.txt for license information.
||
*/

// BOOT_BAUD_RATE = Bitrate for bootloader
// -ve values tell the usart initialization to use U2X
// We use these values to force rounding
// @ 16MHz, best match for 115200 = -117647
// @ 16MHz, best match for 57600 = -57142
//#define BOOT_BAUD_RATE -57142

// BOOT_USART = USART to use on MCU (0 = first/only, 1 = second, 2 = third...)
//#define BOOT_USART 0


//////////////////////////////////////////////////
// SDBoot parameters
//////////////////////////////////////////////////

// SDBOOT = Check RogueSD module for new sketch and program
// Values: NO_SDBOOT          (No SDBOOT code generated)
//         SDBOOT_ON_POWER_UP (SDBOOT code starts on power-up)
//         SDBOOT_ALWAYS      (SDBOOT code starts on external reset, or power-up)
//         SDBOOT_PIN_CHECK   (A defined pin must be held low before SDBOOT code begins)
//         SDBOOT_PIN_HOLD    (After new code has been programmed, app will not start until pin is released)
//         SDBOOT_RENAME      (After new code has been programmed, file is renamed)
//
// If SDBOOT != NO_SDBOOT, any combination of these values can be used, but there must be
// one of SDBOOT_ON_POWER_UP or SDBOOT_ALWAYS

// e.g. SDBOOT starts on power-up reset ONLY, and the file is renamed after programming.
#define SDBOOT (SDBOOT_ON_POWER_UP + SDBOOT_RENAME)

// ROGUESD_USART = USART connected to RogueSD module (can be the same as BOOT_USART)
#define ROGUESD_USART 0

// SDBoot pin control (if SDBOOT_PIN_CHECK enabled)
// SCK/D13 = PORTB7

//#define HW_SDBOOT_CHECK_PORT    PORTB
//#define HW_SDBOOT_CHECK_PIN     PORTB7


//////////////////////////////////////////////////
// Debug parameters
//////////////////////////////////////////////////

// DEBUG = If defined, enable debugging output
// (may be best to define in makefile)
//#define DEBUG

// DEBUG_USART = USART to use for debugging purposes
// Can be any hardware USART, or SOFT_PORT - a software serial output
// (Soft serial parameters defined in makefile - see ledhead.mk)
//#define DEBUG_USART SOFT_PORT


//////////////////////////////////////////////////
// LED parameters
//////////////////////////////////////////////////

// D15 = PORTB0
#define LED_PORT          PORTB
#define LED_PIN           PINB0

// Number of times to flash LED on boot (one time)
// LED_FLASH_TIME is in milliseconds
#define NUM_LED_FLASHES 0
#define LED_FLASH_TIME  50


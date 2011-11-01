/* $Id: Wiring.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Wiring core prototype definitions.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WIRING_H
#define WIRING_H

// Set our Core Platform
#define WIRING_CORE_ATMEL_AVR_8_BIT

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************
 * C Includes
 *************************************************************/

#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "WConstants.h"
#include "Binary.h"


/*************************************************************
 * Timer Constants
 *************************************************************/

// Internal timer constants, for board definitions etc.

#define NOT_A_TIMER 0

#define TIMER0  1
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER1C 5
#define TIMER2  6
#define TIMER2A 6
#define TIMER2B 7
#define TIMER3A 8
#define TIMER3B 9
#define TIMER3C 10
#define TIMER4A 11
#define TIMER4B 12
#define TIMER4C 13
#define TIMER5A 14
#define TIMER5B 15
#define TIMER5C 16

/*
 * Power management constants
 */

#define POWER_ADC 0
#define POWER_SPI 1
#define POWER_WIRE 2
#define POWER_TIMER0 3
#define POWER_TIMER1 4
#define POWER_TIMER2 5
#define POWER_TIMER3 6
#define POWER_TIMER4 7
#define POWER_TIMER5 8
#define POWER_SERIAL0 9
#define POWER_SERIAL1 10
#define POWER_SERIAL2 11
#define POWER_SERIAL3 12
#define POWER_USB 13
#define POWER_ALL 14

#include "WPower.h"

/*
 * Sleep management constants
 */

#define SLEEP_IDLE 0
#define SLEEP_ADC 1
#define SLEEP_POWER_DOWN 2
#define SLEEP_POWER_SAVE 3
#define SLEEP_STANDBY 4
#define SLEEP_EXTENDED_STANDBY 5

#include "WSleep.h"

/*************************************************************
 * Board specific definitions
 *************************************************************/

#define NOT_A_REG  NULL
#define NOT_A_PORT 0xFF

#include "BoardDefs.h"

/*************************************************************
 * C Core API Functions
 *
 * Delay and Timing
 *************************************************************/

#include "WDelay.h"

/*************************************************************
 * Digital
 *************************************************************/

#include "WDigital.h"

#define digitalWrite(PIN, VALUE) pinWrite(PIN, VALUE)
#define digitalRead(PIN) pinRead(PIN)

static inline void pullup(uint8_t PIN) { pinWrite(PIN, HIGH); }
static inline void noPullup(uint8_t PIN) { pinWrite(PIN, LOW); }

/*************************************************************
 * Analog
 *************************************************************/

#include "WAnalog.h"

/*************************************************************
 * Interrupts
 *************************************************************/

#define interrupts()   sei()
#define noInterrupts() cli()

#include "WInterrupts.h"


#ifdef __cplusplus
}
#endif



/*************************************************************
 * C++ Core API Functions
 *************************************************************/

#ifdef __cplusplus
#include "WVector.h"
#include "WString.h"
#include "WCharacter.h"
//#include "WMemory.h"
#include "WShift.h"
#include "WMath.h"
#include "WHardwareSerial.h"
#include "WConstantTypes.h"

/*************************************************************
 * Timers
 *************************************************************/

#include "WHardwareTimer.h"

/*************************************************************
 * Pulse
 *************************************************************/

#include "WPulse.h"

/*************************************************************
 * String
 *************************************************************/
/*
int splitString( const String &, int ,  Vector<int> & );
int splitString( const String &, int,  Vector<long> & );
*/

/*************************************************************
 * Tone
 *************************************************************/

#include "WTone.h"

/*************************************************************
 * PWM
 *************************************************************/

#include "WPWM.h"


// C++ Protection
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release(__guard *);
extern "C" void __cxa_guard_abort(__guard *);
extern "C" void __cxa_pure_virtual(void);


// main program prototypes
void setup(void);
void loop(void);
// OS_main added to avr-gcc 4.4, WinAVR 4.3
// OS_main eliminates register save on main() entry
int main(void) __attribute__ ((noreturn,OS_main));

#endif // __cplusplus

#endif
// WIRING_H

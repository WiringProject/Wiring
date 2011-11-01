/* $Id: WDelay.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Delay and timing control.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WDELAY_H
#define WDELAY_H

// Prototypes

void Wiring_Delay_Timer0_overflow(void);
void delay(unsigned long);
#define delayMilliseconds(ms) delay(ms)

// ***DOC*** because we are using __builtin_avr_delay_cycles(n), n should be a constant,
// otherwise there will be run-time division overhead.
/*
#if __HAS_DELAY_CYCLES && defined(__OPTIMIZE__)
extern void __builtin_avr_delay_cycles(unsigned long);
#define delayMicroseconds(us) __builtin_avr_delay_cycles(microsecondsToClockCycles(us))
#define delayCycles(cycles) __builtin_avr_delay_cycles(cycles)
#else
void delayMicroseconds(unsigned long);
#endif
*/

void delayMicroseconds(uint16_t);
unsigned long millis(void);
unsigned long micros(void);


#endif
// WDELAY_H

/* $Id: WPulse.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Pulse input/output control methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WPULSE_H
#define WPULSE_H

#include <inttypes.h>

// Prototypes

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
/*
// Pulse input
unsigned long pulseIn(uint8_t, uint8_t);
unsigned long pulseIn(uint8_t, uint8_t, unsigned long);
// Pulse output
void pulseOut(uint8_t, uint16_t, uint16_t);
void pulseOut(uint8_t, uint16_t);
uint16_t pulseRunning(uint8_t);
void pulseStop(uint8_t);
*/

#endif
// WPULSE_H

/* $Id: WDigital.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Digital pin/port control for
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
|| 
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WDIGITAL_H
#define WDIGITAL_H

#include <Wiring.h>

// Pin functions
void _pinMode(uint8_t, uint8_t);
uint8_t _pinRead(uint8_t);
void _pinWrite(uint8_t, uint8_t);

// Port functions
void _portMode(uint8_t, uint8_t);
uint8_t _portRead(uint8_t);
void _portWrite(uint8_t, uint8_t);

static inline void pinMode(uint8_t, uint8_t) __attribute__((always_inline, unused));
static inline void pinMode(uint8_t PIN, uint8_t MODE)
{
  if (__builtin_constant_p(PIN) && __builtin_constant_p(MODE))
  {
    if (MODE)
      *(portModeRegister(digitalPinToPort(PIN))) |= digitalPinToBitMask(PIN);
    else
      *(portModeRegister(digitalPinToPort(PIN))) &= ~digitalPinToBitMask(PIN);  
  }
  else
    _pinMode(PIN, MODE);
}


static inline uint8_t pinRead(uint8_t) __attribute__((always_inline, unused));
static inline uint8_t pinRead(uint8_t PIN)
{
  if (__builtin_constant_p(PIN))
    return (*(portInputRegister(digitalPinToPort(PIN))) & digitalPinToBitMask(PIN)) ? HIGH : LOW;
  else
    return _pinRead(PIN);
}


// BH: We don't need to turn off interrupts for the
// single instruction expansion macro. (i.e. this static inline
// will be optimized to a single instruction if constants are used)
static inline void pinWrite(uint8_t, uint8_t) __attribute__((always_inline, unused));
static inline void pinWrite(uint8_t PIN, uint8_t VALUE)
{
  if (__builtin_constant_p(PIN) && __builtin_constant_p(VALUE))
  {
    if (VALUE)
    {
//      uint8_t oldSREG = SREG;
//      cli();
      *(digitalPinToPortReg(PIN)) |= digitalPinToBitMask(PIN);
//      SREG = oldSREG;
    }
    else
    {
//      uint8_t oldSREG = SREG;
//      cli();
      *(digitalPinToPortReg(PIN)) &= ~digitalPinToBitMask(PIN);  
//      SREG = oldSREG;
    }
  }
  else
    _pinWrite(PIN, VALUE);
}

static inline void portMode(uint8_t, uint8_t) __attribute__((always_inline, unused));
static inline void portMode(uint8_t PORT, uint8_t MODE)
{
  if (__builtin_constant_p(PORT) && __builtin_constant_p(MODE))
    if (MODE == OUTPUT)
      *(portModeRegister(PORT)) = 0xff;
    else
      *(portModeRegister(PORT)) = 0;
  else
    _portMode(PORT, MODE);
}

static inline uint8_t portRead(uint8_t) __attribute__((always_inline, unused));
static inline uint8_t portRead(uint8_t PORT)
{
  if (__builtin_constant_p(PORT))
    return *(portInputRegister(PORT));
  else
    return _portRead(PORT);
}

static inline void portWrite(uint8_t, uint8_t) __attribute__((always_inline, unused));
static inline void portWrite(uint8_t PORT, uint8_t VALUE)
{
  if (__builtin_constant_p(PORT) && __builtin_constant_p(VALUE))
    *(portOutputRegister(PORT)) = VALUE;
  else
    _portWrite(PORT, VALUE);
}

#endif
// WDIGITAL_H

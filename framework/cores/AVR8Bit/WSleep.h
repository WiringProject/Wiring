/* $Id: WSleep.h 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Sleep power management utility functions for
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WSLEEP_H
#define WSLEEP_H

#include <Wiring.h>


/* 
 * Sleep power management
 */


static inline void enableSleep() __attribute__((always_inline, unused));
static inline void enableSleep()
{
#if defined sleep_enable
  sleep_enable();
#endif
}

#define noSleep() disableSleep()
static inline void disableSleep() __attribute__((always_inline, unused));
static inline void disableSleep()
{
#if defined sleep_disable
  sleep_disable();
#endif
}

static inline void sleepMode(uint8_t P) __attribute__((always_inline, unused));
static inline void sleepMode(uint8_t P)
{
#if defined set_sleep_mode
  switch (P)
  {
    case SLEEP_IDLE:
#if defined SLEEP_MODE_IDLE
      set_sleep_mode(SLEEP_MODE_IDLE);
#endif
      break;
    case SLEEP_ADC:
#if defined SLEEP_MODE_ADC
      set_sleep_mode(SLEEP_MODE_ADC);
#endif
      break;
    case SLEEP_POWER_DOWN:
#if defined SLEEP_MODE_PWR_DOWN
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
#endif
      break;
    case SLEEP_POWER_SAVE:
#if defined SLEEP_MODE_PWR_SAVE
      set_sleep_mode(SLEEP_MODE_PWR_SAVE);
#endif
      break;
    case SLEEP_STANDBY:
#if defined SLEEP_MODE_STANDBY
      set_sleep_mode(SLEEP_MODE_STANDBY);
#endif
      break;
    case SLEEP_EXTENDED_STANDBY:
#if defined SLEEP_MODE_EXT_STANDBY
      set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
#endif
      break;
    default:
      break;
  }
#endif
}

static inline void startSleep() __attribute__((always_inline, unused));
static inline void startSleep()
{
#if defined sleep_cpu
  sleep_cpu();
#endif
}

static inline void sleep() __attribute__((always_inline, unused));
static inline void sleep()
{
#if defined sleep_mode
  sleep_mode();
#endif
}

#endif
// WSLEEP_H

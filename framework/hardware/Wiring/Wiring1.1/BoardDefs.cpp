/* $Id: BoardDefs.cpp 1232 2011-09-01 05:55:38Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Wiring Mega 128/1281/2561
|| |   Wiring 1.1 (ATmega1281/2561)
|| |   (Atmel AVR 8 bit microcontroller core)
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>

void boardInit(void)
{
  // Initializes main clock used for delay functions, and PWM (fast PWM only)
  Timer0.setMode(0b0011);  // fast PWM
  Timer0.attachInterrupt(INTERRUPT_OVERFLOW, Wiring_Delay_Timer0_overflow);
  Timer0.setClockSource(CLOCK_PRESCALE_64);

  // All other clocks are initialized for PWM use (phase-correct PWM)
  Timer1.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer1.setClockSource(CLOCK_PRESCALE_64);

  Timer2.setMode(0b0001);  // phase-correct PWM
  Timer2.setClockSource(CLOCK_PRESCALE_64);

  Timer3.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer3.setClockSource(CLOCK_PRESCALE_64);

#if NUM_16BIT_TIMERS > 2
  Timer4.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer4.setClockSource(CLOCK_PRESCALE_64);

  Timer5.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer5.setClockSource(CLOCK_PRESCALE_64);
#endif
  // Start interrupts
  sei();
}


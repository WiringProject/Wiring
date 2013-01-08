/* $Id: BoardDefs.cpp 1179 2011-06-11 06:02:39Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Arduino Duemilanove, Uno, and all
|| |   ATmega168(P)A/328(P) Arduino compatible boards.
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

  // Start interrupts
  sei();
}

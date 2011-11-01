/* $Id: BoardDefs.cpp 1138 2011-05-30 21:33:00Z bhagman $

  BoardDefs.h - Board Specific Definitions
  Part of the Wiring Project - http://wiring.org.co/

  Copyright (C) 2004-2011 Hernando Barragan
  Copyright (C) 2010-2011 Brett Hagman

  Please see License.txt for license information.
*/

/**************************************************************************
  Wiring Project - Hardware Specific Definitions

  Definitions for:
    BDMicro Mavric IIB
  (Atmel AVR 8 bit microcontroller core)

  Copyright (C) 2011 Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

**************************************************************************/

#include "WProgram.h"

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

  // Start interrupts
  sei();
}

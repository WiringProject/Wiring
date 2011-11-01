/* $Id: WInterrupts.c 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Hardware interrupt control methods for
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @notes
|| | The ATmega32(A) only has two mode settings for INT2
|| | (Rising and Falling edges)
|| |
|| | TODO: The interface is still pretty weak.  The interrupt
|| |  function table needs better index control.  Could we use
|| |  an enum eventually?
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <Wiring.h>
//#include "WInterrupts.h"

static volatile voidFuncPtr intFunc[NUM_EXTERNAL_INTERRUPTS];
static volatile voidFuncPtr spiIntFunc;
// static volatile voidFuncPtr twiIntFunc;

/*
modes can be 

LOW     - A low level on INTn
CHANGE  - Any edge of INTn
FALLING - The falling edge of INTn
RISING  - The rising edge of INTn
*/

void interruptMode(uint8_t interruptNum, uint8_t mode)
{
  if (interruptNum < NUM_EXTERNAL_INTERRUPTS)
  {
    switch (interruptNum)
    {
      case 0:
        EIMSK &= ~(1 << INT0);
        EICRA = (EICRA & ~(0b11 << ISC00)) | (mode << ISC00);
        EIMSK |= (1 << INT0);
        break;
#if NUM_EXTERNAL_INTERRUPTS > 1
      case 1:
        EIMSK &= ~(1 << INT1);
        EICRA = (EICRA & ~(0b11 << ISC10)) | (mode << ISC10);
        EIMSK |= (1 << INT1);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 2
      case 2:
        EIMSK &= ~(1 << INT2);
#if defined(ISC2)
        // ATmega16/32(A):
        // ISC2 = 0 == Falling edge ((FALLING = 2) & 1 = 0)
        // ISC2 = 1 == Rising edge  ((RISING  = 3) & 1 = 1)
        EICRA = (EICRA & ~(1 << ISC2) | ((mode & 1) << ISC2);
#else
        EICRA = (EICRA & ~(0b11 << ISC20)) | (mode << ISC20);
#endif
        EIMSK |= (1 << INT2);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 3
      case 3:
        EIMSK &= ~(1 << INT3);
        EICRA = (EICRA & ~(0b11 << ISC30)) | (mode << ISC30);
        EIMSK |= (1 << INT3);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 4
      case 4:
        EIMSK &= ~(1 << INT4);
        EICRB = (EICRB & ~(0b11 << ISC40)) | (mode << ISC40);
        EIMSK |= (1 << INT4);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 5
      case 5:
        EIMSK &= ~(1 << INT5);
        EICRB = (EICRB & ~(0b11 << ISC50)) | (mode << ISC50);
        EIMSK |= (1 << INT5);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 6
      case 6:
        EIMSK &= ~(1 << INT6);
        EICRB = (EICRB & ~(0b11 << ISC60)) | (mode << ISC60);
        EIMSK |= (1 << INT6);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 7
      case 7:
        EIMSK &= ~(1 << INT7);
        EICRB = (EICRB & ~(0b11 << ISC70)) | (mode << ISC70);
        EIMSK |= (1 << INT7);
        break;
#endif
    }
  }
}


void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), uint8_t mode)
{
  if (interruptNum < NUM_EXTERNAL_INTERRUPTS)
  {
    intFunc[interruptNum] = userFunc;
    interruptMode(interruptNum, mode);
  }
}


void detachInterrupt(uint8_t interruptNum)
{
  if (interruptNum < NUM_EXTERNAL_INTERRUPTS)
  {
    switch (interruptNum)
    {
      case 0:
        EIMSK &= ~(1 << INT0);
        break;
#if NUM_EXTERNAL_INTERRUPTS > 1
      case 1:
        EIMSK &= ~(1 << INT1);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 2
      case 2:
        EIMSK &= ~(1 << INT2);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 3
      case 3:
        EIMSK &= ~(1 << INT3);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 4
      case 4:
        EIMSK &= ~(1 << INT4);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 5
      case 5:
        EIMSK &= ~(1 << INT5);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 6
      case 6:
        EIMSK &= ~(1 << INT6);
        break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 7
      case 7:
        EIMSK &= ~(1 << INT7);
        break;
#endif
    }

    intFunc[interruptNum] = NULL;
  }
}


void attachInterruptSPI(void (*userFunc)(void))
{
  spiIntFunc = userFunc;
}

void detachInterruptSPI(void)
{
  spiIntFunc = NULL;
}

/*
void attachInterruptTwi(void (*userFunc)(void) ) {
  twiIntFunc = userFunc;
}
*/

ISR(INT0_vect)
{
  if (intFunc[0])
    intFunc[0]();
}

#if NUM_EXTERNAL_INTERRUPTS > 1
ISR(INT1_vect)
{
  if (intFunc[1])
    intFunc[1]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 2
ISR(INT2_vect)
{
  if (intFunc[2])
    intFunc[2]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 3
ISR(INT3_vect)
{
  if (intFunc[3])
    intFunc[3]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 4
ISR(INT4_vect)
{
  if (intFunc[4])
    intFunc[4]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 5
ISR(INT5_vect)
{
  if (intFunc[5])
    intFunc[5]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 6
ISR(INT6_vect)
{
  if (intFunc[6])
    intFunc[6]();
}
#endif

#if NUM_EXTERNAL_INTERRUPTS > 7
ISR(INT7_vect)
{
  if (intFunc[7])
    intFunc[7]();
}
#endif

#if defined(SPI_STC_vect)
ISR(SPI_STC_vect)
{
  if (spiIntFunc)
    spiIntFunc();
}
#endif

/*
ISR(SIG_2WIRE_SERIAL) {
  if(twiIntFunc)
    twiIntFunc();
}
*/


/* $Id: WPWM.cpp 1161 2011-06-08 02:44:34Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | PWM output methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>

// only include if HardwareTimer has been included
#ifdef WHARDWARETIMER_H
void pwmWrite(uint8_t pin, uint16_t val, uint8_t outputMode)
{
  // If 0, turn off PWM (some OCRn registers, in fast PWM mode, will still generate spikes when its OCR is set to zero).
  if (val == 0)
  {
    outputMode = 0; // turn off PWM
    digitalWrite(pin, LOW);
  }

  switch (digitalPinToTimer(pin))
  {
    case TIMER0A:
      Timer0.setOutputMode(CHANNEL_A, outputMode);
      Timer0.setOCR(CHANNEL_A, val);
      break;
    case TIMER0B:
      Timer0.setOutputMode(CHANNEL_B, outputMode);
      Timer0.setOCR(CHANNEL_B, val);
      break;
    case TIMER1A:
      Timer1.setOutputMode(CHANNEL_A, outputMode);
      Timer1.setOCR(CHANNEL_A, val);
      break;
    case TIMER1B:
      Timer1.setOutputMode(CHANNEL_B, outputMode);
      Timer1.setOCR(CHANNEL_B, val);
      break;
    case TIMER1C:
      Timer1.setOutputMode(CHANNEL_C, outputMode);
      Timer1.setOCR(CHANNEL_C, val);
      break;
#if (NUM_8BIT_TIMERS > 1)
    case TIMER2A:
      Timer2.setOutputMode(CHANNEL_A, outputMode);
      Timer2.setOCR(CHANNEL_A, val);
      break;
    case TIMER2B:
      Timer2.setOutputMode(CHANNEL_B, outputMode);
      Timer2.setOCR(CHANNEL_B, val);
      break;
#endif
#if (NUM_16BIT_TIMERS > 1)
    case TIMER3A:
      Timer3.setOutputMode(CHANNEL_A, outputMode);
      Timer3.setOCR(CHANNEL_A, val);
      break;
    case TIMER3B:
      Timer3.setOutputMode(CHANNEL_B, outputMode);
      Timer3.setOCR(CHANNEL_B, val);
      break;
    case TIMER3C:
      Timer3.setOutputMode(CHANNEL_C, outputMode);
      Timer3.setOCR(CHANNEL_C, val);
      break;
#if NUM_16BIT_TIMERS > 2
    case TIMER4A:
      Timer4.setOutputMode(CHANNEL_A, outputMode);
      Timer4.setOCR(CHANNEL_A, val);
      break;
    case TIMER4B:
      Timer4.setOutputMode(CHANNEL_B, outputMode);
      Timer4.setOCR(CHANNEL_B, val);
      break;
    case TIMER4C:
      Timer4.setOutputMode(CHANNEL_C, outputMode);
      Timer4.setOCR(CHANNEL_C, val);
      break;
    case TIMER5A:
      Timer5.setOutputMode(CHANNEL_A, outputMode);
      Timer5.setOCR(CHANNEL_A, val);
      break;
    case TIMER5B:
      Timer5.setOutputMode(CHANNEL_B, outputMode);
      Timer5.setOCR(CHANNEL_B, val);
      break;
    case TIMER5C:
      Timer5.setOutputMode(CHANNEL_C, outputMode);
      Timer5.setOCR(CHANNEL_C, val);
      break;
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
    case NOT_A_TIMER:
    default:
      if (val < 128)
      {
        digitalWrite(pin, LOW);
      }
      else
      {
        digitalWrite(pin, HIGH);
      }
  }
}

void setPWMResolution(uint8_t pin, uint8_t bitResolution)
{
  uint8_t mode = 0b0001;

  if (bitResolution == 9)
    mode = 0b0010;
  else if (bitResolution == 10)
    mode = 0b0011;

  // We can only set the resolution to 9 or 10 bits on 16 bit timers
  switch (digitalPinToTimer(pin))
  {
    case TIMER1A:
    case TIMER1B:
    case TIMER1C:
      Timer1.setMode(mode);
      Timer1.setOCR(CHANNEL_A, 0);
      Timer1.setOCR(CHANNEL_B, 0);
      Timer1.setOCR(CHANNEL_C, 0);
      break;
#if (NUM_16BIT_TIMERS > 1)
    case TIMER3A:
    case TIMER3B:
    case TIMER3C:
      Timer3.setMode(mode);
      Timer3.setOCR(CHANNEL_A, 0);
      Timer3.setOCR(CHANNEL_B, 0);
      Timer3.setOCR(CHANNEL_C, 0);
      break;
#if NUM_16BIT_TIMERS > 2
    case TIMER4A:
    case TIMER4B:
    case TIMER4C:
      Timer4.setMode(mode);
      Timer4.setOCR(CHANNEL_A, 0);
      Timer4.setOCR(CHANNEL_B, 0);
      Timer4.setOCR(CHANNEL_C, 0);
      break;
    case TIMER5A:
    case TIMER5B:
    case TIMER5C:
      Timer5.setMode(mode);
      Timer5.setOCR(CHANNEL_A, 0);
      Timer5.setOCR(CHANNEL_B, 0);
      Timer5.setOCR(CHANNEL_C, 0);
      break;
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
  }
}


void setPWMPrescale(uint8_t pin, uint8_t prescalar)
{
  switch (digitalPinToTimer(pin))
  {
    case TIMER0A:
    case TIMER0B:
      Timer0.setClockSource(prescalar);
      break;
    case TIMER1A:
    case TIMER1B:
    case TIMER1C:
      Timer1.setClockSource(prescalar);
      break;
#if (NUM_8BIT_TIMERS > 1)
    case TIMER2A:
    case TIMER2B:
      Timer2.setClockSource(prescalar);
      break;
#endif
#if (NUM_16BIT_TIMERS > 1)
    case TIMER3A:
    case TIMER3B:
    case TIMER3C:
      Timer3.setClockSource(prescalar);
      break;
#if NUM_16BIT_TIMERS > 2
    case TIMER4A:
    case TIMER4B:
    case TIMER4C:
      Timer4.setClockSource(prescalar);
      break;
    case TIMER5A:
    case TIMER5B:
    case TIMER5C:
      Timer5.setClockSource(prescalar);
      break;
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
  }
}

#endif


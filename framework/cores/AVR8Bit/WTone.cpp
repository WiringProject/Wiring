/* $Id: WTone.cpp 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Tone generator methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| #
|| 
|| @license Please see cores/Common/License.txt.
||
*/

#include <avr/pgmspace.h>
#include <Wiring.h>

// Internal notes:
//
// setTonePolyphony(uint8_t) - sets the max number of tones to play
//  - max is limited by the number of timers on the board
//
// tone(pin, frequency) - plays a tone on pin at frequency Hz.
//  - if a previous tone command is playing, and a new pin is specified,
//    and tonePolyphony has been set to > 1, and there are available timers,
//    a simultaneous tone will be played on the new pin.
//
// toggle_count notes:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)

// Avoid using Timer0 because it is used for millis() etc.

uint8_t tonePolyphony = 1;

volatile int32_t timer1_toggle_count;
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;
void ToneTimer1Service();

#if (NUM_8BIT_TIMERS == 2)
volatile int32_t timer2_toggle_count;
volatile uint8_t *timer2_pin_port;
volatile uint8_t timer2_pin_mask;
void ToneTimer2Service();
#endif

#if (NUM_16BIT_TIMERS > 1)
volatile int32_t timer3_toggle_count;
volatile uint8_t *timer3_pin_port;
volatile uint8_t timer3_pin_mask;
void ToneTimer3Service();
#endif

#if (NUM_16BIT_TIMERS > 2)
volatile int32_t timer4_toggle_count;
volatile uint8_t *timer4_pin_port;
volatile uint8_t timer4_pin_mask;
void ToneTimer4Service();

volatile int32_t timer5_toggle_count;
volatile uint8_t *timer5_pin_port;
volatile uint8_t timer5_pin_mask;
void ToneTimer5Service();
#endif




#if (NUM_16BIT_TIMERS > 2)
#define TONE_PINS 5

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 3, 4, 5, 2, 1 };
static uint8_t tone_pins[TONE_PINS] = { 255, 255, 255, 255, 255 };

#elif (NUM_16BIT_TIMERS > 1)
#define TONE_PINS 3

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 3, 2, 1 };
static uint8_t tone_pins[TONE_PINS] = { 255, 255, 255 };

#elif (NUM_8BIT_TIMERS > 1)
#define TONE_PINS 2

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2, 1 };
static uint8_t tone_pins[TONE_PINS] = { 255, 255 };

#else
#define TONE_PINS 1

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 1 };
static uint8_t tone_pins[TONE_PINS] = { 255 };

#endif



void setTonePolyphony(uint8_t polyphony)
{
  if (polyphony > 0)
    if (polyphony <= TONE_PINS)
      tonePolyphony = polyphony;
    else
      tonePolyphony = TONE_PINS;
}

uint8_t getTonePolyphony(void)
{
  return tonePolyphony;
}


int8_t tonePrepareTimer(uint8_t _pin)
{
  int8_t _timer = -1;

  // if we're already using the pin, the timer should be configured.  
  for (uint8_t i = 0; i < tonePolyphony; i++)
    if (tone_pins[i] == _pin)
      return pgm_read_byte(tone_pin_to_timer_PGM + i);
  
  // search for an unused timer.
  for (uint8_t i = 0; i < tonePolyphony; i++)
    if (tone_pins[i] == 255)
    {
      tone_pins[i] = _pin;
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      break;
    }
  
  if (_timer != -1)
  {
    // Set timer specific stuff
    // All timers in CTC mode
    // 8 bit timers will require changing prescalar values,
    // whereas 16 bit timers are set to either ck/1 or ck/64 prescalar
    switch (_timer)
    {
      case 1:
        // 16 bit timer
        Timer1.setMode(0b0100);  // CTC mode
        Timer1.stop();

        timer1_pin_port = digitalPinToPortReg(_pin);
        timer1_pin_mask = digitalPinToBitMask(_pin);
        break;
#if (NUM_8BIT_TIMERS > 1)
      case 2:
        // 8 bit timer
        Timer2.setMode(0b0010);  // CTC mode
        Timer2.stop();

        timer2_pin_port = digitalPinToPortReg(_pin);
        timer2_pin_mask = digitalPinToBitMask(_pin);
        break;
#endif
#if (NUM_16BIT_TIMERS > 1)
      case 3:
        // 16 bit timer
        Timer3.setMode(0b0100);  // CTC mode
        Timer3.stop();

        timer3_pin_port = digitalPinToPortReg(_pin);
        timer3_pin_mask = digitalPinToBitMask(_pin);
        break;
#endif
#if (NUM_16BIT_TIMERS > 2)
      case 4:
        // 16 bit timer
        Timer4.setMode(0b0100);  // CTC mode
        Timer4.stop();

        timer4_pin_port = digitalPinToPortReg(_pin);
        timer4_pin_mask = digitalPinToBitMask(_pin);
        break;
      case 5:
        // 16 bit timer
        Timer5.setMode(0b0100);  // CTC mode
        Timer5.stop();

        timer5_pin_port = digitalPinToPortReg(_pin);
        timer5_pin_mask = digitalPinToBitMask(_pin);
        break;
#endif
      default:
        break;
    }
  }

  return _timer;
}



// frequency (in hertz) and duration (in milliseconds).

void tone(uint8_t _pin, unsigned int frequency, long duration)
{
  uint8_t prescalar = CLOCK_NO_PRESCALE;
  long toggle_count = 0;
  uint32_t ocr = 0;
  int8_t _timer;

  if (frequency == 0)
  {
    noTone(_pin);
    return;
  }

  _timer = tonePrepareTimer(_pin);

  // Set the pinMode as OUTPUT
  pinMode(_pin, OUTPUT);

  if (frequency > 0 && _timer >= 1)
  {
    // if we are using an 8 bit timer, scan through prescalars to find the best fit
#if (NUM_8BIT_TIMERS > 1)
    if (_timer == 2)
    {
      ocr = F_CPU / frequency / 2 - 1;
      prescalar = CLOCK_NO_PRESCALE;
      if (ocr > 255)
      {
        ocr = F_CPU / frequency / 2 / 8 - 1;
        prescalar = CLOCK_PRESCALE_8;

// ATmega64 and ATmega128 only have ck/32 on Timer 0 (which we don't use)
#if !defined (__AVR_ATmega128__) && !defined (__AVR_ATmega64__)
        if (ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 32 - 1;
          prescalar = CLOCK_PRESCALE_32;
        }
#endif

        if (ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 64 - 1;
          prescalar = CLOCK_PRESCALE_64;

// ATmega64 and ATmega128 don't have ck/128 on Timer 2
#if !defined (__AVR_ATmega128__) && !defined (__AVR_ATmega64__)
          if (ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 128 - 1;
            prescalar = CLOCK_PRESCALE_128;
          }
#endif

          if (ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 256 - 1;
            prescalar = CLOCK_PRESCALE_256;

            if (ocr > 255)
            {
              // can't do any better than /1024
              ocr = F_CPU / frequency / 2 / 1024 - 1;
              prescalar = CLOCK_PRESCALE_1024;
            }
          }
        }
      }

      Timer2.setClockSource(prescalar);
    }
    else
#endif // NUM_8BIT_TIMERS > 1
    {
      // two choices for the 16 bit timers: ck/1 or ck/64
      ocr = F_CPU / frequency / 2 - 1;
      prescalar = CLOCK_NO_PRESCALE;
      if (ocr > 0xffff)
      {
        ocr = F_CPU / frequency / 2 / 64 - 1;
        prescalar = CLOCK_PRESCALE_64;
      }

      if (_timer == 1)
        Timer1.setClockSource(prescalar);
#if (NUM_16BIT_TIMERS > 1)
      else if (_timer == 3)
        Timer3.setClockSource(prescalar);
#if (NUM_16BIT_TIMERS > 2)
      else if (_timer == 4)
        Timer4.setClockSource(prescalar);
      else if (_timer == 5)
        Timer5.setClockSource(prescalar);
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
    }

    // Calculate the toggle count
    if (duration > 0)
      toggle_count = 2 * frequency * duration / 1000;
    else
      toggle_count = -1;

    // Set the OCR for the given timer,
    // set the toggle count,
    // then turn on the interrupts
    switch (_timer)
    {
      case 1:
        Timer1.setOCR(CHANNEL_A, ocr);
        timer1_toggle_count = toggle_count;
        Timer1.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, ToneTimer1Service);
        break;
#if (NUM_8BIT_TIMERS > 1)
      case 2:
        Timer2.setOCR(CHANNEL_A, ocr);
        timer2_toggle_count = toggle_count;
        Timer2.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, ToneTimer2Service);
        break;
#endif
#if (NUM_16BIT_TIMERS > 1)
      case 3:
        Timer3.setOCR(CHANNEL_A, ocr);
        timer3_toggle_count = toggle_count;
        Timer3.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, ToneTimer3Service);
        break;
#if (NUM_16BIT_TIMERS > 2)
      case 4:
        Timer4.setOCR(CHANNEL_A, ocr);
        timer4_toggle_count = toggle_count;
        Timer4.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, ToneTimer4Service);
        break;
      case 5:
        Timer5.setOCR(CHANNEL_A, ocr);
        timer5_toggle_count = toggle_count;
        Timer5.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, ToneTimer5Service);
        break;
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
    }
  }
}


void noTone(uint8_t _pin)
{
  int8_t _timer = -1;
  
  for (int i = 0; i < TONE_PINS; i++)
    if (tone_pins[i] == _pin)
    {
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      tone_pins[i] = 255;
    }
  
  switch (_timer)
  {
    case 1:
      Timer1.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
      break;
#if (NUM_8BIT_TIMERS > 1)
    case 2:
      Timer2.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
      break;
#endif
#if (NUM_16BIT_TIMERS > 1)
    case 3:
      Timer3.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
      break;
#if (NUM_16BIT_TIMERS > 2)
    case 4:
      Timer4.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
      break;
    case 5:
      Timer5.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
      break;
#endif // NUM_16BIT_TIMERS > 2
#endif // NUM_16BIT_TIMERS > 1
    default:
      break;
  }

  digitalWrite(_pin, LOW);              // keep pin low after forced stop
}


void ToneTimer1Service()
{
  if (timer1_toggle_count != 0)
  {
    // toggle the pin
    *timer1_pin_port ^= timer1_pin_mask;

    if (timer1_toggle_count > 0)
      timer1_toggle_count--;
  }
  else
  {
    Timer1.disableInterrupt(INTERRUPT_COMPARE_MATCH_A);
    *timer1_pin_port &= ~timer1_pin_mask;  // keep pin low after stop
  }
}


#if (NUM_8BIT_TIMERS > 1)
void ToneTimer2Service()
{
  if (timer2_toggle_count != 0)
  {
    // toggle the pin
    *timer2_pin_port ^= timer2_pin_mask;

    if (timer2_toggle_count > 0)
      timer2_toggle_count--;
  }
  else
  {
    Timer2.disableInterrupt(INTERRUPT_COMPARE_MATCH_A);
    *timer2_pin_port &= ~timer2_pin_mask;  // keep pin low after stop
  }
}
#endif


#if (NUM_16BIT_TIMERS > 1)
void ToneTimer3Service()
{
  if (timer3_toggle_count != 0)
  {
    // toggle the pin
    *timer3_pin_port ^= timer3_pin_mask;

    if (timer3_toggle_count > 0)
      timer3_toggle_count--;
  }
  else
  {
    Timer3.disableInterrupt(INTERRUPT_COMPARE_MATCH_A);
    *timer3_pin_port &= ~timer3_pin_mask;  // keep pin low after stop
  }
}

#if (NUM_16BIT_TIMERS > 2)
void ToneTimer4Service()
{
  if (timer4_toggle_count != 0)
  {
    // toggle the pin
    *timer4_pin_port ^= timer4_pin_mask;

    if (timer4_toggle_count > 0)
      timer4_toggle_count--;
  }
  else
  {
    Timer4.disableInterrupt(INTERRUPT_COMPARE_MATCH_A);
    *timer4_pin_port &= ~timer4_pin_mask;  // keep pin low after stop
  }
}

void ToneTimer5Service()
{
  if (timer5_toggle_count != 0)
  {
    // toggle the pin
    *timer5_pin_port ^= timer5_pin_mask;

    if (timer5_toggle_count > 0)
      timer5_toggle_count--;
  }
  else
  {
    Timer5.disableInterrupt(INTERRUPT_COMPARE_MATCH_A);
    *timer5_pin_port &= ~timer5_pin_mask;  // keep pin low after stop
  }
}
#endif  // (NUM_16BIT_TIMERS > 2)
#endif  // (NUM_16BIT_TIMERS > 1)


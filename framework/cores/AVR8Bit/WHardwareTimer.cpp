/* $Id: WHardwareTimer.cpp 1240 2011-09-14 03:32:39Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Hardware Timer class for Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @notes
|| |
|| | AVR 8 bit microcontrollers that have 4 16 bit timers are:
|| | ATmega640
|| | ATmega1280
|| | ATmega2560
|| | ATmega1281
|| | ATmega2560
|| |
|| | AVR 8 bit microcontrollers that have 2 16 bit timers are:
|| | ATmega64(A)
|| | ATmega128(A)
|| | ATmega16U4
|| | ATmega32U4
|| |
|| | Anomalies:
|| |   ATmega32(A)/ATmega64(A)/ATmega128(A)
|| |     * use TIMSK (and ETISMK) for controlling interrupt masks
|| |       (i.e. global mask register, vs. individual mask registers per
|| |       timer, e.g. TIMSK0).
|| |   ATmega64(A)/ATmega128(A)
|| |     * Timer 2 does not have ck/32 clock prescalar
|| |     * All timers have same set of prescalars
|| |   ATmega325/3250
|| |     * will more than likely fail because of the TCCR2A acting
|| |       like a single TCCR2 register (i.e. it has no TCCR2B register)
|| |
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "WHardwareTimer.h"


// Compare Output Mode bits
// For 16 bit timers
#define COMnA1 7
#define COMnA0 6
#define COMnB1 5
#define COMnB0 4
#define COMnC1 3
#define COMnC0 2
// For 8 bit timers with only single OCR
#define COMn1 5
#define COMn0 4

// Common to all except ATmega32/64/128 (and very few others)
#define TOIEn  0
#define OCIEnA 1
#define OCIEnB 2
#define OCIEnC 3
#define ICIEn  5


#if defined (TIMER0_COMP_vect)
// only a single COMP vector
ISR(TIMER0_COMP_vect)
{
  if (Timer0.compareMatchAFunction != NULL)
    Timer0.compareMatchAFunction();
}
#else
ISR(TIMER0_COMPA_vect)
{
  if (Timer0.compareMatchAFunction != NULL)
    Timer0.compareMatchAFunction();
}
ISR(TIMER0_COMPB_vect)
{
  if (Timer0.compareMatchBFunction != NULL)
    Timer0.compareMatchBFunction();
}
#endif
ISR(TIMER0_OVF_vect)
{
  if (Timer0.overflowFunction != NULL)
    Timer0.overflowFunction();
}

#if (NUM_8BIT_TIMERS == 2)
#if defined (TIMER2_COMP_vect)
// only a single COMP vector
ISR(TIMER2_COMP_vect)
{
  if (Timer2.compareMatchAFunction != NULL)
    Timer2.compareMatchAFunction();
}
#else
ISR(TIMER2_COMPA_vect)
{
  if (Timer2.compareMatchAFunction != NULL)
    Timer2.compareMatchAFunction();
}
ISR(TIMER2_COMPB_vect)
{
  if (Timer2.compareMatchBFunction != NULL)
    Timer2.compareMatchBFunction();
}
#endif
ISR(TIMER2_OVF_vect)
{
  if (Timer2.overflowFunction != NULL)
    Timer2.overflowFunction();
}
#endif

ISR(TIMER1_COMPA_vect)
{
  if (Timer1.compareMatchAFunction != NULL)
    Timer1.compareMatchAFunction();
}
ISR(TIMER1_COMPB_vect)
{
  if (Timer1.compareMatchBFunction != NULL)
    Timer1.compareMatchBFunction();
}
// Most controllers don't have a third compare match on Timer 1
#if defined (TIMER1_COMPC_vect)
ISR(TIMER1_COMPC_vect)
{
  if (Timer1.compareMatchCFunction != NULL)
    Timer1.compareMatchCFunction();
}
#endif
ISR(TIMER1_OVF_vect)
{
  if (Timer1.overflowFunction != NULL)
    Timer1.overflowFunction();
}
ISR(TIMER1_CAPT_vect)
{
  if (Timer1.captureEventFunction != NULL)
    Timer1.captureEventFunction();
}

#if (NUM_16BIT_TIMERS > 1)
ISR(TIMER3_COMPA_vect)
{
  if (Timer3.compareMatchAFunction != NULL)
    Timer3.compareMatchAFunction();
}
ISR(TIMER3_COMPB_vect)
{
  if (Timer3.compareMatchBFunction != NULL)
    Timer3.compareMatchBFunction();
}
ISR(TIMER3_COMPC_vect)
{
  if (Timer3.compareMatchCFunction != NULL)
    Timer3.compareMatchCFunction();
}
ISR(TIMER3_OVF_vect)
{
  if (Timer3.overflowFunction != NULL)
    Timer3.overflowFunction();
}
ISR(TIMER3_CAPT_vect)
{
  if (Timer3.captureEventFunction != NULL)
    Timer3.captureEventFunction();
}
#endif

#if (NUM_16BIT_TIMERS > 2)
ISR(TIMER4_COMPA_vect)
{
  if (Timer4.compareMatchAFunction != NULL)
    Timer4.compareMatchAFunction();
}
ISR(TIMER4_COMPB_vect)
{
  if (Timer4.compareMatchBFunction != NULL)
    Timer4.compareMatchBFunction();
}
ISR(TIMER4_COMPC_vect)
{
  if (Timer4.compareMatchCFunction != NULL)
    Timer4.compareMatchCFunction();
}
ISR(TIMER4_OVF_vect)
{
  if (Timer4.overflowFunction != NULL)
    Timer4.overflowFunction();
}
ISR(TIMER4_CAPT_vect)
{
  if (Timer4.captureEventFunction != NULL)
    Timer4.captureEventFunction();
}

ISR(TIMER5_COMPA_vect)
{
  if (Timer5.compareMatchAFunction != NULL)
    Timer5.compareMatchAFunction();
}
ISR(TIMER5_COMPB_vect)
{
  if (Timer5.compareMatchBFunction != NULL)
    Timer5.compareMatchBFunction();
}
ISR(TIMER5_COMPC_vect)
{
  if (Timer5.compareMatchCFunction != NULL)
    Timer5.compareMatchCFunction();
}
ISR(TIMER5_OVF_vect)
{
  if (Timer5.overflowFunction != NULL)
    Timer5.overflowFunction();
}
ISR(TIMER5_CAPT_vect)
{
  if (Timer5.captureEventFunction != NULL)
    Timer5.captureEventFunction();
}
#endif

// Constructor

HardwareTimer::HardwareTimer(uint8_t timerNumber)
{
  _timerNumber = timerNumber;

  switch (timerNumber)
  {
    case 0:
#if defined (TIMSK)
      _tcntnh = NULL;
      _tcntnl = &TCNT0;
      _timskn = &TIMSK;
      _tccrna = &TCCR0;
      _tccrnb = &TCCR0;

      _ocrnah = NULL;
      _ocrnal = &OCR0;
      _ocrnbh = NULL;
      _ocrnbl = NULL;
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 1;
#else
      _tcntnh = NULL;
      _tcntnl = &TCNT0;
      _timskn = &TIMSK0;
      _tccrna = &TCCR0A;
      _tccrnb = &TCCR0B;

      _ocrnah = NULL;
      _ocrnal = &OCR0A;
      _ocrnbh = NULL;
      _ocrnbl = &OCR0B;
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 2;
#endif
      break;

    case 1:
#if defined (TIMSK)
      _timskn = &TIMSK;
#else
      _timskn = &TIMSK1;
#endif

      _tcntnh = &TCNT1H;
      _tcntnl = &TCNT1L;
      _tccrna = &TCCR1A;
      _tccrnb = &TCCR1B;

      _ocrnah = &OCR1AH;
      _ocrnal = &OCR1AL;
      _ocrnbh = &OCR1BH;
      _ocrnbl = &OCR1BL;
#if defined (OCR1CH)
      _ocrnch = &OCR1CH;
      _ocrncl = &OCR1CL;
      _channelCount = 3;
#else
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 2;
#endif
      break;

#if (NUM_8BIT_TIMERS > 1)
    case 2:
#if defined (TIMSK)
      _tcntnh = NULL;
      _tcntnl = &TCNT2;
      _timskn = &TIMSK;
      _tccrna = &TCCR2;
      _tccrnb = &TCCR2;

      _ocrnah = NULL;
      _ocrnal = &OCR2;
      _ocrnbh = NULL;
      _ocrnbl = NULL;
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 1;
#else
      _tcntnh = NULL;
      _tcntnl = &TCNT2;
      _timskn = &TIMSK2;
      _tccrna = &TCCR2A;
      _tccrnb = &TCCR2B;

      _ocrnah = NULL;
      _ocrnal = &OCR2A;
      _ocrnbh = NULL;
      _ocrnbl = &OCR2B;
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 2;
#endif
      break;
#endif

#if (NUM_16BIT_TIMERS > 1)
    case 3:
#if defined (TIMSK)
      _timskn = &ETIMSK;
#else
      _timskn = &TIMSK3;
#endif

      _tcntnh = &TCNT3H;
      _tcntnl = &TCNT3L;
      _tccrna = &TCCR3A;
      _tccrnb = &TCCR3B;

      _ocrnah = &OCR3AH;
      _ocrnal = &OCR3AL;
      _ocrnbh = &OCR3BH;
      _ocrnbl = &OCR3BL;
#if defined (OCR1CH)  // if the controller has 3 channels on Timer 1, the same will apply to Timer 3
      _ocrnch = &OCR3CH;
      _ocrncl = &OCR3CL;
      _channelCount = 3;
#else
      _ocrnch = NULL;
      _ocrncl = NULL;
      _channelCount = 2;
#endif
      break;

#if (NUM_16BIT_TIMERS > 2)
    case 4:
      _timskn = &TIMSK4;

      _tcntnh = &TCNT4H;
      _tcntnl = &TCNT4L;
      _tccrna = &TCCR4A;
      _tccrnb = &TCCR4B;

      _ocrnah = &OCR4AH;
      _ocrnal = &OCR4AL;
      _ocrnbh = &OCR4BH;
      _ocrnbl = &OCR4BL;
      _ocrnch = &OCR4CH;
      _ocrncl = &OCR4CL;
      _channelCount = 3;
      break;

    case 5:
      _timskn = &TIMSK5;

      _tcntnh = &TCNT5H;
      _tcntnl = &TCNT5L;
      _tccrna = &TCCR5A;
      _tccrnb = &TCCR5B;

      _ocrnah = &OCR5AH;
      _ocrnal = &OCR5AL;
      _ocrnbh = &OCR5BH;
      _ocrnbl = &OCR5BL;
      _ocrnch = &OCR5CH;
      _ocrncl = &OCR5CL;
      _channelCount = 3;
      break;
#endif

#endif

  }

  setClockSource(CLOCK_STOP);
  if (_tcntnh != NULL)  // 16 bit timers
    *_tcntnh = 0;
  *_tcntnl = 0;

  overflowFunction = NULL;
  compareMatchAFunction = NULL;
  compareMatchBFunction = NULL;
  compareMatchCFunction = NULL;
  captureEventFunction = NULL;
}


void HardwareTimer::setClockSource(uint8_t clockSource)
{
  uint8_t bits = 0;

  // Select our clock source based on timer type and clockSource.
  // Timer 2 is the only RTC clock on the majority of Atmel AVR 8 bit controllers.
  // Timer 2 has a different set of clock prescalars, except for ATmega64/128, where
  // Timer 0 has the different set of clock prescalars - yuck.

#if defined (__AVR_ATmega128__) || defined (__AVR_ATmega64__)
  if (_timerNumber == 0)
#else
  if (_timerNumber == 2)
#endif
    switch (clockSource)
    {
      case CLOCK_NO_PRESCALE:
        bits = 0b001;
        break;
      case CLOCK_PRESCALE_8:
        bits = 0b010;
        break;
      case CLOCK_PRESCALE_32:
        bits = 0b011;
        break;
      case CLOCK_PRESCALE_64:
        bits = 0b100;
        break;
      case CLOCK_PRESCALE_128:
        bits = 0b101;
        break;
      case CLOCK_PRESCALE_256:
        bits = 0b110;
        break;
      case CLOCK_PRESCALE_1024:
        bits = 0b111;
        break;

      //case CLOCK_STOP:
      //case CLOCK_EXTERNAL_FALLING:
      //case CLOCK_EXTERNAL_RISING:
      default:
        bits = 0;
        break;
    }
  else
    // all the rest use same prescale divisors
    switch (clockSource)
    {
      case CLOCK_NO_PRESCALE:
        bits = 0b001;
        break;
      case CLOCK_PRESCALE_8:
        bits = 0b010;
        break;
      case CLOCK_PRESCALE_64:
        bits = 0b011;
        break;
      case CLOCK_PRESCALE_256:
        bits = 0b100;
        break;
      case CLOCK_PRESCALE_1024:
        bits = 0b101;
        break;
      case CLOCK_EXTERNAL_FALLING:
        bits = 0b110;
        break;
      case CLOCK_EXTERNAL_RISING:
        bits = 0b111;
        break;

      //case CLOCK_STOP:
      //case CLOCK_PRESCALE_32:
      //case CLOCK_PRESCALE_128:
      default:
        bits = 0;
        break;
    }

  *_tccrnb = (*_tccrnb & 0b11111000) | bits;
}


void HardwareTimer::setInterrupt(uint8_t interrupt, uint8_t value)
{
  int8_t flagBit = -1;
  uint8_t bitValue = 0;

  if (value)
    bitValue = 1;

#if defined (TIMSK)
  // ATmega32/64/128(A) support
  // check register to figure out which bit in the TIMSK/ETIMSK to set
  // OK to be explicit (i.e. ETIMSK = ...)

  volatile uint8_t *timskReg = &TIMSK;

  switch (interrupt)
  {
    case INTERRUPT_OVERFLOW:
      if (_timerNumber == 0)
        flagBit = TOIE0;
      else if (_timerNumber == 1)
        flagBit = TOIE1;
      else if (_timerNumber == 2)
        flagBit = TOIE2;
#if defined (ETIMSK)
      else if (_timerNumber == 3)
      {
        flagBit = TOIE3;
        timskReg = &ETIMSK;
      }
#endif
      break;
    case INTERRUPT_COMPARE_MATCH_A:
      if (_timerNumber == 0)
        flagBit = OCIE0;
      else if (_timerNumber == 1)
        flagBit = OCIE1A;
      else if (_timerNumber == 2)
        flagBit = OCIE2;
#if defined (ETIMSK)
      else if (_timerNumber == 3)
      {
        flagBit = OCIE3A;
        timskReg = &ETIMSK;
      }
#endif
      break;
    case INTERRUPT_COMPARE_MATCH_B:
      if (_timerNumber == 1)
        flagBit = OCIE1B;
#if defined (ETIMSK)
      else if (_timerNumber == 3)
      {
        flagBit = OCIE3B;
        timskReg = &ETIMSK;
      }
#endif
      break;
    case INTERRUPT_COMPARE_MATCH_C:
#if defined (ETIMSK)
      timskReg = &ETIMSK;
      if (_timerNumber == 1)
        flagBit = OCIE1C;
      else if (_timerNumber == 3)
        flagBit = OCIE3C;
#endif
      break;
    case INTERRUPT_CAPTURE_EVENT:
      if (_timerNumber == 1)
        flagBit = TICIE1;
#if defined (ETIMSK)
      else if (_timerNumber == 3)
      {
        flagBit = TICIE3;
        timskReg = &ETIMSK;
      }
#endif
      break;
  }

  // Only set if the flagBit has been set
  if (flagBit >= 0)
    *timskReg = (*timskReg & ~(1 << flagBit)) | (bitValue << flagBit);

#else  // Everybody else
  switch (interrupt)
  {
    case INTERRUPT_OVERFLOW:
      flagBit = TOIEn;
      break;
    case INTERRUPT_COMPARE_MATCH_A:
      flagBit = OCIEnA;
      break;
    case INTERRUPT_COMPARE_MATCH_B:
      flagBit = OCIEnB;
      break;
    case INTERRUPT_COMPARE_MATCH_C:
      flagBit = OCIEnC;
      break;
    case INTERRUPT_CAPTURE_EVENT:
      flagBit = ICIEn;
      break;
  }

  // Only set if the flagBit has been set
  if (flagBit >= 0)
    *_timskn = (*_timskn & ~(1 << flagBit)) | (bitValue << flagBit);

#endif  // defined (TIMSK)
}


// Attach an interrupt function, and set the appropriate interrupt flag
void HardwareTimer::attachInterrupt(uint8_t interrupt, void (*userFunc)(void), uint8_t enable)
{
  switch (interrupt)
  {
    case INTERRUPT_OVERFLOW:
      overflowFunction = userFunc;
      break;
    case INTERRUPT_COMPARE_MATCH_A:
      compareMatchAFunction = userFunc;
      break;
    case INTERRUPT_COMPARE_MATCH_B:
      compareMatchBFunction = userFunc;
      break;
    case INTERRUPT_COMPARE_MATCH_C:
      compareMatchCFunction = userFunc;
      break;
    case INTERRUPT_CAPTURE_EVENT:
      captureEventFunction = userFunc;
      break;
  }

  if (userFunc == NULL)
    setInterrupt(interrupt, 0);
  else if (enable)
    setInterrupt(interrupt, 1);
}

/*
uint16_t HardwareTimer::getPrescaler()
{
  return (pgm_read_word(timerPrescaleFactor+(*_tccrnb & TIMER_PRESCALE_MASK)));
}
*/

void HardwareTimer::setMode(uint8_t mode)
{
  // WGMn3 and WGMn2 are in positions 4 and 3, respectively, in TCCRnB
  // WGMn1 and WGNn0 are in positions 1 and 0, respectively, in TCCRnA

  // For devices with global TIMSK, 8 bit timers have:
  // WGMn0 in position 6 of TCCRn register
  // WGMn1 in position 3 of TCCRn register

#if defined (TIMSK)
  if (_timerNumber == 0 || _timerNumber == 2)
  {
    // only a single control register on these devices (TCCRn)
    *_tccrna = (*_tccrna & 0b10110111)
                 | ((mode & 0b00000001) << 6)
                 | ((mode & 0b00000010) << 2);
  }
  else
  {
    // everything else conforms (the two control registers for the WGM)
#endif
  *_tccrna = (*_tccrna & 0b11111100) | (mode & 0b00000011);
  *_tccrnb = (*_tccrnb & 0b11100111) | ((mode & 0b00001100) << 1);
#if defined (TIMSK)
  }
#endif
}

/* =====BH===== - This will only apply to 16 bit timers
void HardwareTimer::setPWMMode(uint8_t bitResolution)
{
  // configures timern for use with PWM output
  // on pins OCnA, OCnB, and OCnC

  if (bitResolution == 9)
    setMode(0b0010);
  else if (bitResolution == 10)
    setMode(0b0011);
  else
    setMode(0b0001);

  *_ocrnah = 0;
  *_ocrnal = 0;
  *_ocrnbh = 0;
  *_ocrnbl = 0;
  *_ocrnch = 0;
  *_ocrncl = 0;
}
*/

/*
void HardwareTimer::setPWMOff()
{
  // setMode(0b0000);  // not necessary
  setOutputMode(PWMChannelA, 0);
  setOutputMode(PWMChannelB, 0);
  setOutputMode(PWMChannelC, 0);
}
*/

void HardwareTimer::setOutputMode(uint8_t channel, uint8_t outputMode)
{
  uint8_t COMbitMask = 0b11;
  uint8_t shiftCount;

  outputMode &= 0b11;  // only 4 modes

  if (channel < _channelCount)
  {
    if ((_timerNumber == 0 || _timerNumber == 2) && _channelCount == 1)
    {
      // 8 bit timers with only 1 OCR
      shiftCount = COMn0;
    }
    else
    {
      // 16 bit timers
      if (channel == CHANNEL_A)
        shiftCount = COMnA0;
      else if (channel == CHANNEL_B)
        shiftCount = COMnB0;
      else if (channel == CHANNEL_C)
        shiftCount = COMnC0;
    }

    COMbitMask <<= shiftCount;
    outputMode <<= shiftCount;

    *_tccrna = (*_tccrna & ~(COMbitMask)) | outputMode;
  }
}

void HardwareTimer::setOCR(uint8_t channel, uint16_t value)
{
  uint8_t highByte = value >> 8;
  uint8_t lowByte = value & 0x00ff;

  if (channel < _channelCount)
  {
    if (channel == CHANNEL_A)
    {
      if (_ocrnah != NULL)
        *_ocrnah = highByte;
      *_ocrnal = lowByte;
    }
    else if (channel == CHANNEL_B)
    {
      if (_ocrnbh != NULL)
        *_ocrnbh = highByte;
      *_ocrnbl = lowByte;
    }
    else if (channel == CHANNEL_C)
    {
      *_ocrnch = highByte;
      *_ocrncl = lowByte;
    }
  }
}


void HardwareTimer::setCounter(uint16_t value)
{
  uint8_t highByte = value >> 8;
  uint8_t lowByte = value & 0x00ff;

  uint8_t oldSREG = SREG;
  cli();
  if (_tcntnh != NULL)  // 16 bit timers
    *_tcntnh = highByte;

  *_tcntnl = lowByte;
  SREG = oldSREG;
}


uint16_t HardwareTimer::getCounter(void)
{
  uint16_t value = 0;
  uint8_t oldSREG = SREG;
  cli();
  if (_tcntnh != NULL)
    value = *_tcntnh << 8;
  value += *_tcntnl;
  SREG = oldSREG;

  return value;
}


// Preinstantiate Objects
HardwareTimer Timer0(0);
HardwareTimer Timer1(1);

#if (NUM_8BIT_TIMERS == 2)
HardwareTimer Timer2(2);
#endif

#if (NUM_16BIT_TIMERS > 1)
HardwareTimer Timer3(3);
#endif
#if (NUM_16BIT_TIMERS > 2)
HardwareTimer Timer4(4);
HardwareTimer Timer5(5);
#endif


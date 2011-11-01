/* $Id: WHardwareTimer.h 1154 2011-06-07 01:25:23Z bhagman $
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
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WHARDWARETIMER_H
#define WHARDWARETIMER_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

#define CLOCK_STOP                      0
#define CLOCK_NO_PRESCALE               1
#define CLOCK_PRESCALE_8                2
#define CLOCK_PRESCALE_32               3
#define CLOCK_PRESCALE_64               4
#define CLOCK_PRESCALE_128              5
#define CLOCK_PRESCALE_256              6
#define CLOCK_PRESCALE_1024             7
#define CLOCK_EXTERNAL_FALLING          8
#define CLOCK_EXTERNAL_RISING           9

#define INTERRUPT_OVERFLOW              0
#define INTERRUPT_COMPARE_MATCH_A       1
#define INTERRUPT_COMPARE_MATCH_B       2
#define INTERRUPT_COMPARE_MATCH_C       3
#define INTERRUPT_CAPTURE_EVENT         4

#define CHANNEL_A                       0
#define CHANNEL_B                       1
#define CHANNEL_C                       2

// devices with Timer 5, have 4 16 bit timers (i.e Timer 1, 3, 4, 5)
#if defined (TCCR5A)
#define NUM_16BIT_TIMERS 4
// some devices have 2 16 bit timers (i.e. Timer 1, 3)
#elif defined (TCCR3A)
#define NUM_16BIT_TIMERS 2
// the remainder only have 1 16 bit timer (i.e. Timer 1)
#else
#define NUM_16BIT_TIMERS 1
#endif

// a majority of the devices have Timer 2 (Asynchronous timer)
#if defined (TCCR2) || defined (TCCR2A)
#define NUM_8BIT_TIMERS 2
#else
#define NUM_8BIT_TIMERS 1
#endif

#if defined (TIMER0_COMP_vect)
// only a single COMP vector
ISR(TIMER0_COMP_vect);
#else
ISR(TIMER0_COMPA_vect);
ISR(TIMER0_COMPB_vect);
#endif
ISR(TIMER0_OVF_vect);

#if (NUM_8BIT_TIMERS == 2)
#if defined (TIMER2_COMP_vect)
// only a single COMP vector
ISR(TIMER2_COMP_vect);
#else
ISR(TIMER2_COMPA_vect);
ISR(TIMER2_COMPB_vect);
#endif
ISR(TIMER2_OVF_vect);
#endif

ISR(TIMER1_COMPA_vect);
ISR(TIMER1_COMPB_vect);
ISR(TIMER1_COMPC_vect);
ISR(TIMER1_OVF_vect);
ISR(TIMER1_CAPT_vect);

#if (NUM_16BIT_TIMERS > 1)
ISR(TIMER3_COMPA_vect);
ISR(TIMER3_COMPB_vect);
ISR(TIMER3_COMPC_vect);
ISR(TIMER3_OVF_vect);
ISR(TIMER3_CAPT_vect);
#endif

#if (NUM_16BIT_TIMERS > 2)
ISR(TIMER4_COMPA_vect);
ISR(TIMER4_COMPB_vect);
ISR(TIMER4_COMPC_vect);
ISR(TIMER4_OVF_vect);
ISR(TIMER4_CAPT_vect);

ISR(TIMER5_COMPA_vect);
ISR(TIMER5_COMPB_vect);
ISR(TIMER5_COMPC_vect);
ISR(TIMER5_OVF_vect);
ISR(TIMER5_CAPT_vect);
#endif

class HardwareTimer
{
#if defined (TIMER0_COMP_vect)
// only a single COMP vector
  friend void TIMER0_COMP_vect();
#else
  friend void TIMER0_COMPA_vect();
  friend void TIMER0_COMPB_vect();
#endif
  friend void TIMER0_OVF_vect();

  #if (NUM_8BIT_TIMERS == 2)
#if defined (TIMER2_COMP_vect)
// only a single COMP vector
  friend void TIMER2_COMP_vect();
#else
  friend void TIMER2_COMPA_vect();
  friend void TIMER2_COMPB_vect();
#endif
  friend void TIMER2_OVF_vect();
  #endif

  friend void TIMER1_COMPA_vect();
  friend void TIMER1_COMPB_vect();
  friend void TIMER1_COMPC_vect();
  friend void TIMER1_OVF_vect();
  friend void TIMER1_CAPT_vect();

  #if (NUM_16BIT_TIMERS > 1)
  friend void TIMER3_COMPA_vect();
  friend void TIMER3_COMPB_vect();
  friend void TIMER3_COMPC_vect();
  friend void TIMER3_OVF_vect();
  friend void TIMER3_CAPT_vect();
  #endif

  #if (NUM_16BIT_TIMERS > 2)
  friend void TIMER4_COMPA_vect();
  friend void TIMER4_COMPB_vect();
  friend void TIMER4_COMPC_vect();
  friend void TIMER4_OVF_vect();
  friend void TIMER4_CAPT_vect();

  friend void TIMER5_COMPA_vect();
  friend void TIMER5_COMPB_vect();
  friend void TIMER5_COMPC_vect();
  friend void TIMER5_OVF_vect();
  friend void TIMER5_CAPT_vect();
  #endif

  private:
    uint8_t _timerNumber;
    uint8_t _channelCount;
    // Control registers
    volatile uint8_t *_tcntnh;
    volatile uint8_t *_tcntnl;
    volatile uint8_t *_timskn;
    volatile uint8_t *_tccrna;
    volatile uint8_t *_tccrnb;
    volatile uint8_t *_ocrnah;
    volatile uint8_t *_ocrnal;
    volatile uint8_t *_ocrnbh;
    volatile uint8_t *_ocrnbl;
    volatile uint8_t *_ocrnch;
    volatile uint8_t *_ocrncl;
    // User function pointers
    void (*overflowFunction)(void);
    void (*compareMatchAFunction)(void);
    void (*compareMatchBFunction)(void);
    void (*compareMatchCFunction)(void);
    void (*captureEventFunction)(void);
  
  public:
    HardwareTimer(uint8_t timerNumber);

    inline void stop(void) { setClockSource(CLOCK_STOP); };
    void setClockSource(uint8_t clockSource);
    void setInterrupt(uint8_t interrupt, uint8_t value);
    inline void enableInterrupt(uint8_t interrupt) { setInterrupt(interrupt, 1); };
    inline void disableInterrupt(uint8_t interrupt) { setInterrupt(interrupt, 0); };
    void attachInterrupt(uint8_t interrupt, void (*userFunc)(void), uint8_t enable = 1);
    inline void detachInterrupt(uint8_t interrupt) { attachInterrupt(interrupt, NULL, 0); };
    void setMode(uint8_t mode);
    // uint16_t getClockSource();
    void setOutputMode(uint8_t channel, uint8_t outputMode);
    void setOCR(uint8_t channel, uint16_t value);
    void setCounter(uint16_t value);
    uint16_t getCounter(void);
};

extern HardwareTimer Timer0;
#if (NUM_8BIT_TIMERS == 2)
extern HardwareTimer Timer2;
#endif

extern HardwareTimer Timer1;

#if (NUM_16BIT_TIMERS > 1)
extern HardwareTimer Timer3;
#endif
#if (NUM_16BIT_TIMERS > 2)
extern HardwareTimer Timer4;
extern HardwareTimer Timer5;
#endif

#endif
// WHARDWARETIMER_H

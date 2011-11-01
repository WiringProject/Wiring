/* $Id: WDelay.c 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Delay and timing control.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>


/*************************************************************
 * Delay & Timer
 *************************************************************/

// Notes
// -----
// Variables: F_CPU (cpu clock), Timer 0 prescalar

// Version to accomodate F_CPU frequencies not multiples of 1E6: 
// (but requires 32 bit operations for the fractional calculation)

#if ((F_CPU % 1000000) != 0)

#define MICROSECONDS_PER_TIMER0_OVERFLOW_X100 \
            ((((TIMER0PRESCALEFACTOR * 256UL) * 100UL) * 1000UL) / (F_CPU / 1000UL))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW_X100 / 100000)
#define FRACT_INC  (MICROSECONDS_PER_TIMER0_OVERFLOW_X100 % 100000)
#define FRACT_MAX  (100000)

volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
volatile uint32_t timer0_fract = 0;

#else

#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(TIMER0PRESCALEFACTOR * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

// These are declared as volatile for external purposes only.
// The overflow routine does not need these to be volatile.
volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
volatile uint8_t timer0_fract = 0;

#endif // F_CPU a multiple of 1E6

//ISR(TIMER0_OVF_vect)
void Wiring_Delay_Timer0_overflow(void)
{
  // copy these to local variables so they can be stored in registers
  // (volatile variables must be read from memory on every access)
  uint32_t m = timer0_millis;
#if ((F_CPU % 1000000) != 0)
  uint32_t f = timer0_fract;
#else
  uint8_t f = timer0_fract;
#endif

  m += MILLIS_INC;
  f += FRACT_INC;
  if (f >= FRACT_MAX)
  {
    f -= FRACT_MAX;
    m += 1;
  }

  timer0_fract = f;
  timer0_millis = m;
  timer0_overflow_count++;
}


uint32_t millis()
{
  uint32_t m;
  uint8_t oldSREG = SREG;

  // disable interrupts while we read timer0_millis or we might get an
  // inconsistent value (e.g. in the middle of a write to timer0_millis)
  cli();
  m = timer0_millis;
  SREG = oldSREG;

  return m;
}


// micros() gets the number of Timer 0 overflows (timer0_overflow_count) x 256
// (which is the the overflow max for Timer 0)
// plus what the current Timer 0 counter holds,
// and returns the number of microseconds calculated from that value.

// BH: ***FAIL*** This fails miserably for CPU clock frequencies which
// are not multiples of 1E6.
// It is NOT recommended to use micros() on systems with clock frequencies
// that are not multiples of 1E6, since the floating point calculation will
// take 120+ !! bytes of code (and obviously a lot of time), not including the
// floating point functions that will need to be linked in.

unsigned long micros()
{
  uint32_t m;
  uint8_t t;
  uint8_t oldSREG = SREG;
        
  cli();  
  // get the number of overflows
  m = timer0_overflow_count;
  // get the current counter value
  t = TCNT0;
  
#ifdef TIFR0
  if ((TIFR0 & _BV(TOV0)) && (t < 255))
    m++;
#else
  if ((TIFR & _BV(TOV0)) && (t < 255))
    m++;
#endif

  SREG = oldSREG;
  
  // (m * 256 + t) * the number of microseconds/timer tick
  // (i.e. each timer tick = 1E6 / (F_CPU/PRESCALAR) microseconds)
#if ((F_CPU % 1000000) == 0)
  return ((m * 256 + t) * (TIMER0PRESCALEFACTOR / (F_CPU / 1000000UL)));
#else
  return (unsigned long) (1.0 * (m * 256 + t) * TIMER0PRESCALEFACTOR / (F_CPU / 1E6));
#endif
}


// Because we use unsigned values here, wrap-around/overflow is not a factor.
// e.g.
//  millis() = 0x00000012
//  start    = 0xfffffff0 -
//             ----------
//             0x00000022 (unsigned, carry dropped)

void delay(uint32_t ms)
{
/* older method using micros()
  uint16_t start = (uint16_t)micros();

  while (ms > 0)
    if (((uint16_t)micros() - start) >= 1000)
    {
      ms--;
      start += 1000;
    }
*/
  unsigned long start = millis();
        
  while (millis() - start < ms);
}



void delayMicroseconds(uint16_t count)
{
  // math: count * (F_CPU/1000000) / 4

  if ((count == 0) || (--count == 0))
    return;
#if F_CPU > 18000000UL
  // This calculation can take upwards of 160 cycles
  // due to the multiply function.
  //count = count * (uint16_t)(F_CPU / 4000000UL);
  count = count * 5;
#elif F_CPU > 14000000UL
  count = count * 4;
#elif F_CPU > 10000000UL
  count = count * 3;
#elif F_CPU > 6000000UL
  if (--count == 0)
    return;
  count = count * 2;
#elif F_CPU > 2666666UL
  if (--count == 0)
    return;
  count = count;
#elif F_CPU > 1600000UL
  if (--count == 0)
    return;
  count = count / 2;
#elif F_CPU > 888888UL
  if (--count == 0)
    return;
  count = count / 4;
#else
# warning "Dude, you have a really slow clock. Do some math and figure it out."
  if (--count == 0)
    return;
  count = count / (uint16_t)(4000000UL / F_CPU);
#endif
  // one loop takes 4 cpu cycles 
   __asm__ volatile (
     "1: sbiw %0,1" "\n\t"
     "brne 1b"
     : "=w" (count)
     : "0" (count) );
}





// Delay for the given number of microseconds.
// If we can, we alias to __builtin_avr_delay_cycles(n) in WDelay.h

#if !( __HAS_DELAY_CYCLES && defined(__OPTIMIZE__))

// BH: Yuck! Would be nice to fix this up for small delays.
// Look into macro expansion for small constant values (and place asm
// inline)
/*
void delayMicroseconds(unsigned long us)
{
  uint32_t _ticks = (((F_CPU / 1000UL) * us) / 3000UL);

  while (_ticks > 256)
  {
    // _delay_loop_1 can only do uint8_t (8 bit)
    // 0 = 256 iterations
    _delay_loop_1(0);
    _ticks -= 256;
  }

  if (_ticks)
    _delay_loop_1(_ticks);
}
*/
#endif




// BH: ***FAIL*** This fails miserably for cpu clock frequencies which
// are not multiples of 1E6.
/*
void delayMicroseconds(unsigned int us)
{
  // calling avrlib's delay_us() function with low values (e.g. 1 or
  // 2 microseconds) gives delays longer than desired.
  //delay_us(us);

#if F_CPU >= 16000000L
  // for a one-microsecond delay, simply return.  the overhead
  // of the function call yields a delay of approximately 1 1/8 us.
  if (--us == 0)
    return;

  // the following loop takes a quarter of a microsecond (4 cycles)
  // per iteration, so execute it four times for each microsecond of
  // delay requested.
  us <<= 2;

  // account for the time taken in the preceeding commands.
  us -= 2;
#else
  if (--us == 0)
    return;
  if (--us == 0)
    return;
  us <<= 1;
  us--;
#endif
  // disable interrupts, otherwise the timer 0 overflow interrupt that
  // tracks milliseconds will make us delay longer than we want.
  //cli();

  // busy wait
  __asm__ __volatile__ (
    "1: sbiw %0,1" "\n\t" // 2 cycles
    "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
  );

  // reenable interrupts.
  //sei();
}
*/

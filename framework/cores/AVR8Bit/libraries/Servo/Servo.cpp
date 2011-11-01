/* $Id: Servo.cpp 1142 2011-05-31 06:49:42Z bhagman $
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://wiring.org.co/
|| @contribution   Michael Margolis
||
|| @description
|| | Interrupt driven Servo library using 16 bit timers.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
|| @notes
|| | A servo is activated by creating an instance of the Servo class passing the
|| | desired pin to the attach() method.
|| | The servos are pulsed in the background using the value most recently
|| | written using the write() method.
|| |
|| | Note that analogWrite of PWM on pins associated with the timer are disabled
|| | when the first servo is attached.
|| | Timers are seized as needed in groups of 12 servos - 24 servos use two
|| | timers, 48 servos will use four.
|| |
|| | The methods are:
|| |
|| | attach(pin) - Attaches a servo motor to an i/o pin.
|| | attach(pin, min, max) - Attaches to a pin setting min and max values in
|| |                         microseconds
|| | default min is 544, max is 2400
|| |
|| | write()     - Sets the servo angle in degrees.
|| |               (invalid angle that is valid as pulse in microseconds is
|| |               treated as microseconds).
|| | writeMicroseconds() - Sets the servo pulse width in microseconds
|| | read()      - Gets the last written servo pulse width as an angle between
|| |               0 and 180.
|| | readMicroseconds()   - Gets the last written servo pulse width in
|| |               microseconds.
|| | attached()  - Returns true if there is a servo attached.
|| | detach()    - Stops an attached servos from pulsing its i/o pin.
|| |
|| | Notes [BH]:
|| |  Michael's method is to sequentially go through the each set of channels
|| |  per timer, pulsing each for the required time (approximately 0.5 ms to 2.5 ms),
|| |  then move to the next.  Once all servos for the timer have been serviced,
|| |  a minimum "refresh" time (20 ms) is allowed to pass before starting the
|| |  process again.
|| |
|| |  Of course, this calculation is greatly affected if you use microsecond
|| |  values for write/writeMicroseconds beyond the "accepted" PWM values for
|| |  servos.
|| |
|| |  12 servos per timer (max) means that if all 12 servos were at MAX pulse
|| |  width (approx. 2.5ms), then it would take 30 ms to service the pulses, then
|| |  another 20 ms for "refresh", totalling 50 ms per cycle, or 20 cycles per
|| |  second (i.e. 20 Hz).
|| #
*/

#include <avr/interrupt.h>
#include <Wiring.h>

#include "Servo.h"

// converts microseconds to tick (assumes prescale of 8)
#define usToTicks(_us)    ((clockCyclesPerMicrosecond()* _us) / 8)
// converts from ticks back to microseconds
#define ticksToUs(_ticks) (((uint16_t)_ticks * 8) / clockCyclesPerMicrosecond())


// compensation ticks to trim adjust for digitalWrite delays
#define TRIM_DURATION       2

// static array of servo structures
static servo_t servos[MAX_SERVOS];
// counter for the servo being pulsed for each timer (or -1 if refresh interval)
static volatile int8_t Channel[_Nbr_16timers];

// the total number of attached servos
uint8_t ServoCount = 0;


// convenience macros

// returns the timer controlling this servo
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER))
// returns the index of the servo on this timer
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)
// macro to access servo index by timer and channel
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)
// macro to access servo class by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])

// minimum value in uS for this servo
#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)
// maximum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)

/************ static functions common to all instances ***********************/

static inline void handle_interrupts(timer16_Sequence_t timer,
                                     volatile uint16_t *TCNTn,
                                     volatile uint16_t *OCRnA)
{
  if (Channel[timer] < 0)
    *TCNTn = 0; // channel set to -1 indicated that refresh interval completed so reset the timer
  else
    if (SERVO_INDEX(timer,Channel[timer]) < ServoCount && SERVO(timer,Channel[timer]).Pin.isActive == true)
      digitalWrite(SERVO(timer,Channel[timer]).Pin.nbr,LOW);  // pulse this channel low if activated

  Channel[timer]++;    // increment to the next channel
  if (SERVO_INDEX(timer,Channel[timer]) < ServoCount && Channel[timer] < SERVOS_PER_TIMER)
  {
    *OCRnA = *TCNTn + SERVO(timer,Channel[timer]).ticks;
    if (SERVO(timer,Channel[timer]).Pin.isActive == true)     // check if activated
      digitalWrite(SERVO(timer,Channel[timer]).Pin.nbr,HIGH); // its an active channel so pulse it high
  }
  else
  {
    // finished all channels so wait for the refresh period
    // to expire before starting over.
    // (allow a few ticks to ensure the next OCR1A not missed)
    if ((uint16_t)*TCNTn < (usToTicks(REFRESH_INTERVAL) + 4))
      *OCRnA = (uint16_t)usToTicks(REFRESH_INTERVAL);
    else
      *OCRnA = *TCNTn + 4;  // at least REFRESH_INTERVAL has elapsed
    Channel[timer] = -1;    // this will get incremented at the end of the
                            // refresh period to start again at the first channel
  }
}


#if defined(_useTimer1)
#if defined(SERVO_NEW_TIMER_CONTROL)
void Timer1Service()
#else
ISR(TIMER1_COMPA_vect)
#endif
{
  handle_interrupts(_timer1, &TCNT1, &OCR1A);
}
#endif

#if defined(_useTimer3)
#if defined(SERVO_NEW_TIMER_CONTROL)
void Timer3Service()
#else
ISR(TIMER3_COMPA_vect)
#endif
{
  handle_interrupts(_timer3, &TCNT3, &OCR3A);
}
#endif

#if defined(_useTimer4)
#if defined(SERVO_NEW_TIMER_CONTROL)
void Timer4Service()
#else
ISR(TIMER4_COMPA_vect)
#endif
{
  handle_interrupts(_timer4, &TCNT4, &OCR4A);
}
#endif

#if defined(_useTimer5)
#if defined(SERVO_NEW_TIMER_CONTROL)
void Timer5Service()
#else
ISR(TIMER5_COMPA_vect)
#endif
{
  handle_interrupts(_timer5, &TCNT5, &OCR5A);
}
#endif


static void initISR(timer16_Sequence_t timer)
{
#if defined (_useTimer1)
  if (timer == _timer1)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer1.setMode(0);        // normal counting mode (0 -> 2^16)
    Timer1.setClockSource(CLOCK_PRESCALE_8);
#else
    TCCR1A = 0;               // normal counting mode
    TCCR1B = _BV(CS11);       // set prescalar to ck/8
#endif
    TCNT1 = 0;                // clear the timer count
#if defined(TIFR)
    TIFR |= (1 << OCF1A);     // clear any pending interrupts
#else
    TIFR1 |= (1 << OCF1A);
#endif

#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer1.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, Timer1Service);
#else
#if defined(TIMSK)
    TIMSK |= (1 << OCIE1A);   // enable the output compare interrupt
#else
    TIMSK1 |= (1 << OCIE1A);
#endif
#endif
  }
#endif


#if defined (_useTimer3)
  if (timer == _timer3)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer3.setMode(0);        // normal counting mode (0 -> 2^16)
    Timer3.setClockSource(CLOCK_PRESCALE_8);
#else
    TCCR3A = 0;               // normal counting mode
    TCCR3B = _BV(CS31);       // set prescalar to ck/8
#endif
    TCNT3 = 0;                // clear the timer count
#if defined(TIFR)
    TIFR |= (1 << OCF3A);     // clear any pending interrupts
#else
    TIFR3 |= (1 << OCF3A);
#endif

#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer3.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, Timer3Service);
#else
#if defined(ETIMSK)
    ETIMSK |= (1 << OCIE3A);   // enable the output compare interrupt
#else
    TIMSK3 |= (1 << OCIE3A);
#endif
#endif
  }
#endif


#if defined (_useTimer4)
  if (timer == _timer4)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer4.setMode(0);        // normal counting mode (0 -> 2^16)
    Timer4.setClockSource(CLOCK_PRESCALE_8);
#else
    TCCR4A = 0;               // normal counting mode
    TCCR4B = _BV(CS41);       // set prescalar to ck/8
#endif
    TCNT4 = 0;                // clear the timer count
#if defined(TIFR)
    TIFR |= (1 << OCF4A);     // clear any pending interrupts
#else
    TIFR4 |= (1 << OCF4A);
#endif

#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer4.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, Timer4Service);
#else
#if defined(ETIMSK)
    ETIMSK |= (1 << OCIE4A);   // enable the output compare interrupt
#else
    TIMSK4 |= (1 << OCIE4A);
#endif
#endif
  }
#endif


#if defined (_useTimer5)
  if (timer == _timer5)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer5.setMode(0);        // normal counting mode (0 -> 2^16)
    Timer5.setClockSource(CLOCK_PRESCALE_8);
#else
    TCCR5A = 0;               // normal counting mode
    TCCR5B = _BV(CS51);       // set prescalar to ck/8
#endif
    TCNT5 = 0;                // clear the timer count
#if defined(TIFR)
    TIFR |= (1 << OCF5A);     // clear any pending interrupts
#else
    TIFR5 |= (1 << OCF5A);
#endif

#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer5.attachInterrupt(INTERRUPT_COMPARE_MATCH_A, Timer5Service);
#else
#if defined(ETIMSK)
    ETIMSK |= (1 << OCIE5A);   // enable the output compare interrupt
#else
    TIMSK5 |= (1 << OCIE5A);
#endif
#endif
  }
#endif

}


static void finISR(timer16_Sequence_t timer)
{
#if defined(_useTimer1)
  if (timer == _timer1)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer1.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
#else
#if defined(TIMSK)
    TIMSK &= ~(1 << OCIE1A);
#else
    TIMSK1 &= ~(1 << OCIE1A);
#endif
#endif
  }
#endif

#if defined(_useTimer3)
  if (timer == _timer3)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer3.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
#else
#if defined(ETIMSK)
    ETIMSK &= ~(1 << OCIE3A);
#else
    TIMSK3 &= ~(1 << OCIE3A);
#endif
#endif
  }
#endif

#if defined(_useTimer4)
  if (timer == _timer4)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer4.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
#else
#if defined(ETIMSK)
    ETIMSK &= ~(1 << OCIE4A);
#else
    TIMSK4 &= ~(1 << OCIE4A);
#endif
#endif
  }
#endif

#if defined(_useTimer5)
  if (timer == _timer5)
  {
#if defined(SERVO_NEW_TIMER_CONTROL)
    Timer5.detachInterrupt(INTERRUPT_COMPARE_MATCH_A);
#else
#if defined(ETIMSK)
    ETIMSK &= ~(1 << OCIE5A);
#else
    TIMSK5 &= ~(1 << OCIE5A);
#endif
#endif
  }
#endif

}

static uint8_t isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
  for (uint8_t channel = 0; channel < SERVOS_PER_TIMER; channel++)
    if (SERVO(timer,channel).Pin.isActive == true)
      return true;

  return false;
}


/****************** end of static functions ******************************/

Servo::Servo()
{
  if (ServoCount < MAX_SERVOS)
  {
    // assign a servo index to this instance
    this->servoIndex = ServoCount++;
    // store default values
    servos[this->servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);
  }
  else
    this->servoIndex = INVALID_SERVO ;  // too many servos
}

uint8_t Servo::attach(uint8_t pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(uint8_t pin, uint16_t min, uint16_t max)
{
  if (this->servoIndex < MAX_SERVOS )
  {
    // set servo pin to output
    pinMode(pin, OUTPUT);
    servos[this->servoIndex].Pin.nbr = pin;

    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    this->min = (MIN_PULSE_WIDTH - min) / 4; //resolution of min/max is 4 uS
    this->max = (MAX_PULSE_WIDTH - max) / 4;

    // initialize the timer if it has not already been initialized
    timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if (isTimerActive(timer) == false)
      initISR(timer);

    // this must be set after the check for isTimerActive
    servos[this->servoIndex].Pin.isActive = true;
  }
  return this->servoIndex;
}

void Servo::detach()
{
  servos[this->servoIndex].Pin.isActive = false;
  timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);

  if (isTimerActive(timer) == false)
    finISR(timer);
}

void Servo::write(uint16_t value)
{
  if (value < MIN_PULSE_WIDTH)
  {
    // treat values less than 544 as angles in degrees
    // (valid values in microseconds are handled as microseconds)
    if (value < 0)
      value = 0;
    if (value > 180)
      value = 180;
    value = map(value, 0, 180, SERVO_MIN(),  SERVO_MAX());
  }
  this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(uint16_t value)
{
  // calculate and store the values for the given channel
  byte channel = this->servoIndex;

  if ((channel >= 0) && (channel < MAX_SERVOS))   // ensure channel is valid
  {
    if (value < SERVO_MIN())          // ensure pulse width is valid
      value = SERVO_MIN();
    else if (value > SERVO_MAX())
      value = SERVO_MAX();

    value = value - TRIM_DURATION;
    // convert to ticks after compensating for interrupt overhead
    value = usToTicks(value);

    uint8_t oldSREG = SREG;
    cli();
    servos[channel].ticks = value;
    SREG = oldSREG;
  }
}

uint8_t Servo::read() // return the value as degrees
{
  return map(this->readMicroseconds() + 1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

uint16_t Servo::readMicroseconds()
{
  uint16_t pulsewidth;

  if (this->servoIndex != INVALID_SERVO)
    pulsewidth = ticksToUs(servos[this->servoIndex].ticks) + TRIM_DURATION;
  else
    pulsewidth  = 0;

  return pulsewidth;
}

uint8_t Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive;
}


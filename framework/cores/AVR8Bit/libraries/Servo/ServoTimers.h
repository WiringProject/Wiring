/* $Id: ServoTimers.h 1142 2011-05-31 06:49:42Z bhagman $
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://wiring.org.co/
|| @contribution   Michael Margolis
||
|| @description
|| | Defines for 16 bit timers used with Servo library.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
|| @notes
|| | If _useTimerX is defined then TimerX is a 16 bit timer on the current board.
|| | timer16_Sequence_t enumerates the sequence that the timers should be allocated.
|| | _Nbr_16timers indicates how many 16 bit timers are available.
|| #
 */

#ifndef SERVO_TIMERS_H
#define SERVO_TIMERS_H


#if defined NUM_16BIT_TIMERS
// We are using latest WHardwareTimer encapsulation
#define SERVO_NEW_TIMER_CONTROL
#endif


//#if NUM_16BIT_TIMERS > 3
#if NUM_16BIT_TIMERS > 3 || defined(__AVR_ATmega640__)||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)
#define _useTimer5
#define _useTimer1
#define _useTimer3
#define _useTimer4
typedef enum { _timer5, _timer1, _timer3, _timer4, _Nbr_16timers } timer16_Sequence_t ;

//#elif NUM_16BIT_TIMERS > 1
#elif NUM_16BIT_TIMERS > 1 || defined(__AVR_ATmega32U4__)||defined(__AVR_AT90USB646__)||defined(__AVR_AT90USB1286__)||defined(__AVR_ATmega128__)||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
#define _useTimer3
#define _useTimer1
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#else
#define _useTimer1
typedef enum { _timer1, _Nbr_16timers } timer16_Sequence_t ;
#endif


#endif
// SERVO_TIMERS_H


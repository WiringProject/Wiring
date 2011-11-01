/* $Id: WInterrupts.h 1154 2011-06-07 01:25:23Z bhagman $
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
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WINTERRUPTS_H
#define WINTERRUPTS_H

#define NUM_EXTERNAL_INTERRUPTS 0

#if !defined(EIMSK)
 #if !defined(GIMSK)
  #if defined(GICR)
   #define EIMSK GICR
  #else
   #error "No EIMSK/GIMSK/GICR for this controller!"
  #endif
 #else
  #define EIMSK GIMSK
 #endif
#endif

#if !defined(EICRA)
 #define EICRA MCUCR
#endif

#if defined(INT0)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 1
#endif

#if defined(INT1)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 2
#endif

#if defined(INT2)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 3
#endif

#if defined(INT3)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 4
#endif

#if defined(INT4)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 5
#endif

#if defined(INT5)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 6
#endif

#if defined(INT6)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 7
#endif

#if defined(INT7)
 #undef NUM_EXTERNAL_INTERRUPTS
 #define NUM_EXTERNAL_INTERRUPTS 8
#endif


#define EXTERNAL_INTERRUPT_0 0
#define EXTERNAL_INTERRUPT_1 1
#define EXTERNAL_INTERRUPT_2 2
#define EXTERNAL_INTERRUPT_3 3
#define EXTERNAL_INTERRUPT_4 4
#define EXTERNAL_INTERRUPT_5 5
#define EXTERNAL_INTERRUPT_6 6
#define EXTERNAL_INTERRUPT_7 7


void attachInterrupt(uint8_t, void (*)(void), uint8_t mode);
void detachInterrupt(uint8_t);
void interruptMode(uint8_t, uint8_t);

void attachInterruptSPI(void (*)(void));
void detachInterruptSPI(void);


#endif


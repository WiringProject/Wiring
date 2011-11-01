/* $Id: Encoder.h 1139 2011-05-30 21:34:41Z bhagman $
||
|| @author         Hernando Barragan
|| @url            http://wiring.org.co/
|| @contribution   Nicholas Zambetti
|| @contribution   Brett Hagman <bhagman@roguerobotics.com>
|| @contribution   Alexander Brevig <alexanderbrevig@gmail.com>
||
|| @description
|| | Encoder Hardware Abstraction Library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef ENCODER_H
#define ENCODER_H

#include <inttypes.h>

class Encoder
{
  public:
    Encoder();

    static uint8_t count;
    static Encoder* encoders[];

    uint8_t attach(uint8_t pinA, uint8_t pinB);
    void    detach();
    void    write(int32_t position);
    int32_t read(void);
    uint8_t attached(void);

#if NUM_EXTERNAL_INTERRUPTS > 0
    static void service0(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 1
    static void service1(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 2
    static void service2(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 3
    static void service3(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 4
    static void service4(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 5
    static void service5(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 6
    static void service6(void);
#endif
#if NUM_EXTERNAL_INTERRUPTS > 7
    static void service7(void);
#endif

  private:
    void service(void);

    uint8_t index;
    volatile uint8_t pinA;
    volatile uint8_t pinB;
    uint8_t interruptNumber;
    volatile int32_t position;
};

#endif
// ENCODER_H

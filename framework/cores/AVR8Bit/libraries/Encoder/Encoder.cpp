/* $Id: Encoder.cpp 1139 2011-05-30 21:34:41Z bhagman $
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

#include <Wiring.h>
#include "Encoder.h"


Encoder* Encoder::encoders[NUM_EXTERNAL_INTERRUPTS];
uint8_t Encoder::count = 0;

/*
|| @constructor
|| | Initialize the Encoder
|| #
*/
Encoder::Encoder()
{
  index = 0;
  for (uint8_t i = 0; i < NUM_EXTERNAL_INTERRUPTS; i++ )
    encoders[i] = NULL;
}

/*
|| @description
|| | Attaches the Encoder to the pins
|| #
||
|| @parameter inPinA first pin of the encoder
|| @parameter inPinB second pin of the encoder
||
|| @return true if the Encoder successfully attached
*/
uint8_t Encoder::attach(uint8_t inPinA, uint8_t inPinB)
{

  // we can only have as many Encoders as we have external interrupts
  if (count >= NUM_EXTERNAL_INTERRUPTS)
    return 0;

  // if pinA isn't an external interrupt, we can't continue
  if (pinToInterrupt(inPinA) < 0)
    return 0;

  pinA = inPinA;
  pinB = inPinB;

  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  interruptNumber = pinToInterrupt(pinA);

  position = 0;

  // if we are just reconfiguring the current Encoder, then we are done
  if (this == encoders[index])
    return 1;

  // otherwise, search for a free Encoder in the list
  for (uint8_t i = 0; i < NUM_EXTERNAL_INTERRUPTS; i++)
  {
    if (encoders[i] == NULL)
    {
      // found one!
      encoders[i] = this;
      index = i;
      count++;
      break;
    }
  }

  noInterrupts();

  switch (interruptNumber)
  {
#if NUM_EXTERNAL_INTERRUPTS > 0
    case 0:
      attachInterrupt(EXTERNAL_INTERRUPT_0, Encoder::service0, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 1
    case 1:
      attachInterrupt(EXTERNAL_INTERRUPT_1, Encoder::service1, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 2
    case 2:
      attachInterrupt(EXTERNAL_INTERRUPT_2, Encoder::service2, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 3
    case 3:
      attachInterrupt(EXTERNAL_INTERRUPT_3, Encoder::service3, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 4
    case 4:
      attachInterrupt(EXTERNAL_INTERRUPT_4, Encoder::service4, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 5
    case 5:
      attachInterrupt(EXTERNAL_INTERRUPT_5, Encoder::service5, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 6
    case 6:
      attachInterrupt(EXTERNAL_INTERRUPT_6, Encoder::service6, CHANGE);
      break;
#endif
#if NUM_EXTERNAL_INTERRUPTS > 7
    case 7:
      attachInterrupt(EXTERNAL_INTERRUPT_7, Encoder::service7, CHANGE);
      break;
#endif
  }

  interrupts();

  return 1;
}

/*
|| @description
|| | Detaches the Encoder from the pins
|| #
*/
void Encoder::detach()
{
  if (attached())
  {
    detachInterrupt(interruptNumber);

    // remove this Encoder from the list
    encoders[index] = NULL;
    if (count > 0)
      count--;
  }
}

/*
|| @description
|| | Check to see if this Encoder is attached
|| #
||
|| @return true if this Encoder is attached
*/
uint8_t Encoder::attached(void)
{
  if (this == encoders[index])
    return 1;
  else
    return 0;
}

/*
|| @description
|| | Write a new position to this Encoder
|| #
||
|| @parameter position the target position of this Encoder
*/
void Encoder::write(int32_t newPosition)
{
  position = newPosition;
}

/*
|| @description
|| | Get the position of this Encoder
|| #
||
|| @return the position of this Encoder
*/
int32_t Encoder::read(void)
{
  return position;
}

#if NUM_EXTERNAL_INTERRUPTS > 0
void Encoder::service0(void) { encoders[0]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 1
void Encoder::service1(void) { encoders[1]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 2
void Encoder::service2(void) { encoders[2]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 3
void Encoder::service3(void) { encoders[3]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 4
void Encoder::service4(void) { encoders[4]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 5
void Encoder::service5(void) { encoders[5]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 6
void Encoder::service6(void) { encoders[6]->service(); }
#endif
#if NUM_EXTERNAL_INTERRUPTS > 7
void Encoder::service7(void) { encoders[7]->service(); }
#endif


void Encoder::service(void)
{
  if ((digitalRead(pinA) == LOW) ^ (digitalRead(pinB) == HIGH))
    position++;
  else
    position--;
}


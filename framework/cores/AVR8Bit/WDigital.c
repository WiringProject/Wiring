/* $Id: WDigital.c 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
||
|| @description
|| | Digital pin/port control for
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
 * Digital I/O
 *************************************************************/
/*
const uint8_t PROGMEM pin_type_PGM[] =
{
  NOT_A_TIMER, // D0 - PD0
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  TIMER1B,      // D4 - PD4
  TIMER1A,      // D5 - PD5
  TIMER2B,      // D6 - PD6
  TIMER2A,      // D7 - PD7
  NOT_A_TIMER, // D8 - PB2
  TIMER0A,      // D9 - PB3
  TIMER0B,      // D10 - PB4
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER, // D14/A0 - PA0
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER, // D22 - PB0
  NOT_A_TIMER,
  NOT_A_TIMER, // D24 - PC0
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER,
  NOT_A_TIMER
};
*/


//const uint8_t pins[8] = {
//  _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
//};


//volatile uint8_t * ports[WIRING_PORTS] = {
//  &PORTD, &PORTC, &PORTA, &PORTB, &PORTE, &PORTF, &PORTG,
//#if defined (__AVR_ATmega640__)||(__AVR_ATmega1280__)||(__AVR_ATmega2560__)
//  &PORTH, &PORTJ, &PORTK, &PORTL
//#endif
//};


//volatile uint8_t * portsddr[WIRING_PORTS] = {
//  &DDRD, &DDRC, &DDRA, &DDRB, &DDRE, &DDRF, &DDRG,
//#if defined (__AVR_ATmega640__)||(__AVR_ATmega1280__)||(__AVR_ATmega2560__)
//  &DDRH, &DDRJ, &DDRK, &DDRL
//#endif
//};


//volatile uint8_t * portspin[WIRING_PORTS] = {
//  &PIND, &PINC, &PINA, &PINB, &PINE, &PINF, &PING,
//#if defined (__AVR_ATmega640__)||(__AVR_ATmega1280__)||(__AVR_ATmega2560__)
//  &PINH, &PINJ, &PINK, &PINL
//#endif
//};

void _pinMode(uint8_t pin, uint8_t mode)
{
  uint8_t bitmask = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *moderegister;

  moderegister = portModeRegister(port);

  if (moderegister == NOT_A_REG) return;

  uint8_t oldSREG = SREG;
  cli();

  if (mode == INPUT)
    *moderegister &= ~bitmask;
  else
    *moderegister |= bitmask;

  SREG = oldSREG;
}


uint8_t _pinRead(uint8_t pin)
{
  uint8_t bitmask = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *inputregister;

  inputregister = portInputRegister(port);

  if (inputregister == NOT_A_REG) return;

  if (*inputregister & bitmask)
    return HIGH;
  else
    return LOW;
}


void _pinWrite(uint8_t pin, uint8_t val)
{
  uint8_t bitmask = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *portregister;

  portregister = portOutputRegister(port);

  if (portregister == NOT_A_REG) return;

  uint8_t oldSREG = SREG;
  cli();

  if (val == LOW)
   *portregister &= ~bitmask;
  else
   *portregister |= bitmask;

  SREG = oldSREG;
}


void _portMode(uint8_t port, uint8_t mode)
{
  volatile uint8_t *moderegister;

  moderegister = portModeRegister(port);

  if (moderegister == NOT_A_REG) return;

  uint8_t oldSREG = SREG;
  cli();

  //*moderegister = mode;
  if (mode == OUTPUT)
    *moderegister = 0xff;
  else
    *moderegister = 0x00;

  SREG = oldSREG;
}


uint8_t _portRead(uint8_t port)
{
  volatile uint8_t *inputregister;

  inputregister = portInputRegister(port);

  if (inputregister == NOT_A_REG) return;

  uint8_t oldSREG = SREG;
  cli();
  uint8_t portValue = *inputregister;
  SREG = oldSREG;
  return portValue;
}


void _portWrite(uint8_t port, uint8_t val)
{
  volatile uint8_t *portregister;

  portregister = portOutputRegister(port);

  if (portregister == NOT_A_REG) return;

  uint8_t oldSREG = SREG;
  cli();
  *portregister = val;
  SREG = oldSREG;
}


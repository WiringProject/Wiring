/* $Id: WHardwareSerial.cpp 1154 2011-06-07 01:25:23Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   gabebear
|| @contribution   Hernando Barragan <b@wiring.org.co>
|| @contribution   Nicholas Zambetti
||
|| @description
|| | Hardware Serial class for
|| | Atmel AVR 8 bit microcontroller series.
|| |
|| | Wiring Core API
|| #
||
|| @notes
|| | Utilizes modified FIFO class by Alexander Brevig (2010).
|| | U2X and frame format code by gabebear (2010).
|| | Interface by Hernando Barragan and Nicholas Zambetti (2006).
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <avr/io.h>
#include <stdlib.h>
#include <FIFO.h>
#include "WHardwareSerial.h"

// Now, provide the class only if the hardware has at least one serial port.
#if SERIALPORTS > 0

#if !defined(RXCIE)
// UCSRnA bits
#define UDRE   5
#define U2X    1
// UCSRnB bits
#define RXCIE  7
#define UDRIE  5
#define RXEN   4
#define TXEN   3
// UCSRnC bits
#define UPM1   5
#define UPM0   4

/*
#define RXCIE RXCIE0
#define UDRIE UDRIE0
#define RXEN  RXEN0
#define TXEN  TXEN0
#define UDRE  UDRE0
#define U2X   U2X0
#define UPM0  UPM00
#define UPM1  UPM01
*/
#endif

#if !defined(SINGLEUSART1)
ISR(Serial_RX_vect)
{
  Serial.rxfifo.enqueue(*Serial._udr);
}

ISR(Serial_TX_vect)
{
  if (Serial.txfifo.count() > 0)
    *Serial._udr = Serial.txfifo.dequeue();

  if (Serial.txfifo.count() == 0)
    *Serial._ucsrb = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}
#endif

#if SERIALPORTS > 1 || defined(SINGLEUSART1)
ISR(Serial1_RX_vect)
{
  Serial1.rxfifo.enqueue(*Serial1._udr);
}

ISR(Serial1_TX_vect)
{
  if (Serial1.txfifo.count() > 0)
    *Serial1._udr = Serial1.txfifo.dequeue();

  if (Serial1.txfifo.count() == 0)
    *Serial1._ucsrb = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}
#endif

#if SERIALPORTS > 2
ISR(Serial2_RX_vect)
{
  Serial2.rxfifo.enqueue(*Serial2._udr);
}

ISR(Serial2_TX_vect)
{
  if (Serial2.txfifo.count() > 0)
    *Serial2._udr = Serial2.txfifo.dequeue();

  if (Serial2.txfifo.count() == 0)
    *Serial2._ucsrb = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}
#endif

#if SERIALPORTS > 3
ISR(Serial3_RX_vect)
{
  Serial3.rxfifo.enqueue(*Serial3._udr);
}

ISR(Serial3_TX_vect)
{
  if (Serial3.txfifo.count() > 0)
    *Serial3._udr = Serial3.txfifo.dequeue();

  if (Serial3.txfifo.count() == 0)
    *Serial3._ucsrb = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}
#endif


// Constructor

HardwareSerial::HardwareSerial(uint8_t serialPortNumber)
{
  switch (serialPortNumber)
  {
    // We do not take into consideration older AVRs with a single UART,
    // such as the m163, m103, etc.  They only have an 8 bit UBRR, and
    // do not have a UCRSC.
#if !defined(SINGLEUSART1)
    case 0:
      #if defined(UBRRL)
      _ubrrh = &UBRRH;
      _ubrrl = &UBRRL;
      _ucsra = &UCSRA;
      _ucsrb = &UCSRB;
      _ucsrc = &UCSRC;
      _udr = &UDR;
      #else
      _ubrrh = &UBRR0H;
      _ubrrl = &UBRR0L;
      _ucsra = &UCSR0A;
      _ucsrb = &UCSR0B;
      _ucsrc = &UCSR0C;
      _udr = &UDR0;
      #endif
      break;
#endif
#if (SERIALPORTS > 1) || defined(SINGLEUSART1)
    case 1:
      _ubrrh = &UBRR1H;
      _ubrrl = &UBRR1L;
      _ucsra = &UCSR1A;
      _ucsrb = &UCSR1B;
      _ucsrc = &UCSR1C;
      _udr = &UDR1;
      break;
#endif
#if (SERIALPORTS > 2)
    case 2:
      _ubrrh = &UBRR2H;
      _ubrrl = &UBRR2L;
      _ucsra = &UCSR2A;
      _ucsrb = &UCSR2B;
      _ucsrc = &UCSR2C;
      _udr = &UDR2;
      break;
#endif
#if (SERIALPORTS > 3)
    case 3:
      _ubrrh = &UBRR3H;
      _ubrrl = &UBRR3L;
      _ucsra = &UCSR3A;
      _ucsrb = &UCSR3B;
      _ucsrc = &UCSR3C;
      _udr = &UDR3;
      break;
#endif
  }
}


// Public Methods

void HardwareSerial::begin(const uint32_t baud,
                           const uint8_t data_bits,
                           const uint8_t stop_bits,
                           const uint8_t parity)
{
  uint16_t ubrrValue;
  uint8_t frame_format;
  uint8_t use_u2x;

  uint16_t calcUBRRU2X;
  uint16_t calcUBRR;
  uint32_t calcBaudU2X;
  uint32_t calcBaud;

  // Calculate for U2X (with rounding)
  calcUBRR = (F_CPU/2/baud + 4) / 8;
  calcUBRRU2X = (F_CPU/baud + 4) / 8;

  calcBaud = F_CPU/16/calcUBRR;
  calcBaudU2X = F_CPU/8/calcUBRRU2X;

  if (abs(calcBaudU2X - baud) < abs(calcBaud - baud))
  {
    *_ucsra = 1 << U2X;
    ubrrValue = calcUBRRU2X - 1;
  }
  else
  {
    *_ucsra = 0;
    ubrrValue = calcUBRR - 1;
  }

  switch (data_bits)
  {
    // UMSZ0, UMSZ1 are in UCSRnC at bits 1 and 2 respectively on
    // all Atmel AVR 8 bit microcontrollers.
    // UMSZ2 is bit 2 found in UCSRnB.
    case 5:
      frame_format = 0b000;
      break;
    case 6:
      frame_format = 0b010;
      break;
    case 7:
      frame_format = 0b100;
      break;
    case 9:
      frame_format = 0b110;
      *_ucsrb |= 0b100;
      break;
    case 8:
    default:
      frame_format = 0b110;
      break;
  }

  // USBSn is found in UCSRnC at bit 3
  if (stop_bits == 2) frame_format |= 0b1000;

  // UPM0 and UPM1 are found in UCSRnC at bits 4 and 5, respectively.
  switch (parity)
  {
    case 1:  // odd parity
      frame_format |= 0b110000;
      break;
    case 2:  // even parity
      frame_format |= 0b100000;
      break;
    default:  // no parity
      break;
  }

  *_ucsrc = frame_format;

  // assign the baud_setting, a.k.a. ubbr (USART Baud Rate Register)
  *_ubrrh = ubrrValue >> 8;
  *_ubrrl = ubrrValue;
  *_ucsrb = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}


void HardwareSerial::end()
{
  *_ucsrb &= ~(1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}


int HardwareSerial::available(void)
{
  return rxfifo.count();
}


int HardwareSerial::read(void)
{
  uint8_t c;

  if (rxfifo.count())
  {
    uint8_t oldSREG = SREG;
    cli();

    c = rxfifo.dequeue();

    SREG = oldSREG;

    return c;
  }
  else
    return -1;
}


int HardwareSerial::peek(void)
{
  if (rxfifo.count())
    return rxfifo.peek();
  else
    return -1;
}


void HardwareSerial::flush()
{
  rxfifo.flush();
}


size_t HardwareSerial::write(uint8_t c)
{
  // We will block here until we have some space free in the FIFO
  while (txfifo.count() >= TX_BUFFER_SIZE);

  uint8_t oldSREG = SREG;
  cli();

  txfifo.enqueue(c);
  *_ucsrb |= (1 << UDRIE);

  SREG = oldSREG;
  
  return 1;
}


// Preinstantiate Objects


#if !defined(SINGLEUSART1)
HardwareSerial Serial(0);
#endif
#if SERIALPORTS > 1 || defined(SINGLEUSART1)
HardwareSerial Serial1(1);
#endif
#if SERIALPORTS > 2
HardwareSerial Serial2(2);
#endif
#if SERIALPORTS > 3
HardwareSerial Serial3(3);
#endif

#endif // SERIALPORTS > 0
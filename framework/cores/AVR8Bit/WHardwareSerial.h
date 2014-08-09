/* $Id: WHardwareSerial.h 1154 2011-06-07 01:25:23Z bhagman $
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
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WHARDWARESERIAL_H
#define WHARDWARESERIAL_H

#include <inttypes.h>
#include <avr/interrupt.h>
#include <Stream.h>
#include <FIFO.h>

#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 16

#define SERIALPORTS 0

#if defined(USART0_RX_vect)
#undef SERIALPORTS
#define SERIALPORTS 1
#define Serial_RX_vect USART0_RX_vect
#define Serial_TX_vect USART0_UDRE_vect
#elif defined(USART_RX_vect)
#undef SERIALPORTS
#define SERIALPORTS 1
#define Serial_RX_vect USART_RX_vect
#define Serial_TX_vect USART_UDRE_vect
#elif defined(USART_RXC_vect)
#undef SERIALPORTS
#define SERIALPORTS 1
#define Serial_RX_vect USART_RXC_vect
#define Serial_TX_vect USART_UDRE_vect
#endif

#if defined(USART1_RX_vect)
#undef SERIALPORTS
// Some AVRs have 1 USB and a single USART - USART1
#if !defined(USART0_RX_vect)
#define SERIALPORTS 1
#define SINGLEUSART1
#else
#define SERIALPORTS 2
#endif
#define Serial1_RX_vect USART1_RX_vect
#define Serial1_TX_vect USART1_UDRE_vect
#endif

#if defined (USART2_RX_vect)
#undef SERIALPORTS
// No Atmel AVR 8 bit microcontrollers have just 3 serial ports.
// This is just here for completeness.
#define SERIALPORTS 3
#define Serial2_RX_vect USART2_RX_vect
#define Serial2_TX_vect USART2_UDRE_vect
#endif

#if defined (USART3_RX_vect)
#undef SERIALPORTS
#define SERIALPORTS 4
#define Serial3_RX_vect USART3_RX_vect
#define Serial3_TX_vect USART3_UDRE_vect
#endif

// Now, provide the class only if the hardware has at least one serial port.
#if SERIALPORTS > 0

#if !defined(SINGLEUSART1)
ISR(Serial_RX_vect);
ISR(Serial_TX_vect);
#endif
#if SERIALPORTS > 1 || defined(SINGLEUSART1)
ISR(Serial1_RX_vect);
ISR(Serial1_TX_vect);
#endif
#if SERIALPORTS > 2
ISR(Serial2_RX_vect);
ISR(Serial2_TX_vect);
#endif
#if SERIALPORTS > 3
ISR(Serial3_RX_vect);
ISR(Serial3_TX_vect);
#endif

class HardwareSerial : public Stream
{
#if !defined(SINGLEUSART1)
  friend void Serial_RX_vect();
  friend void Serial_TX_vect();
#endif
#if SERIALPORTS > 1 || defined(SINGLEUSART1)
  friend void Serial1_RX_vect();
  friend void Serial1_TX_vect();
#endif
#if SERIALPORTS > 2
  friend void Serial2_RX_vect();
  friend void Serial2_TX_vect();
#endif
#if SERIALPORTS > 3
  friend void Serial3_RX_vect();
  friend void Serial3_TX_vect();
#endif

  private:
    FIFO<uint8_t,RX_BUFFER_SIZE> rxfifo;
    FIFO<uint8_t,TX_BUFFER_SIZE> txfifo;
    volatile uint8_t *_ubrrh;
    volatile uint8_t *_ubrrl;
    volatile uint8_t *_ucsra;
    volatile uint8_t *_ucsrb;
    volatile uint8_t *_ucsrc;
    volatile uint8_t *_udr;
  public:
    HardwareSerial(uint8_t SerialPortNumber);
    void begin(const uint32_t baud = 9600,
               const uint8_t data_bits = 8,
               const uint8_t stop_bits = 1,
               const uint8_t parity = 0);
    void end();
    int available(void);
    int read(void);
    int peek(void);
    void flush(void);
    size_t write(uint8_t);
};

#if !defined(SINGLEUSART1)
extern HardwareSerial Serial;
#endif
#if SERIALPORTS > 1 || defined(SINGLEUSART1)
extern HardwareSerial Serial1;
#endif
#if SERIALPORTS > 2
extern HardwareSerial Serial2;
#endif
#if SERIALPORTS > 3
extern HardwareSerial Serial3;
#endif

#endif // SERIALPORTS > 0

#endif
// WHARDWARESERIAL_H

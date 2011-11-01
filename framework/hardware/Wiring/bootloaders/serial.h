/* $Id: serial.h 1153 2011-06-07 00:51:12Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | Atmel AVR serial routines.
|| | Generic, unbuffered serial routines for ATmega controllers.
|| | Includes a software serial implementation from
|| | Atmel Application Note AVR305.
|| #
||
|| @license Please see License.txt for license information.
||
*/

#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>

#define SOFT_PORT -1

#ifdef UBRRL
// Single UART device
  #define USARTInit() UCSRB = (1 << RXEN) + (1 << TXEN)
//  #define USARTSetBitrate(br) UBRRL = (F_CPU/br/16L) - 1
  #define USARTHasData() (UCSRA & (1 << RXC))
  void USARTWaitForByte(void);
  unsigned char USARTGetByte(void);
  void USARTSendByte(unsigned char data);
  void USARTSetBitrate(int32_t bitrate);

#else
  #ifdef UBRR0L
    #define USART0Init() UCSR0B = (1 << RXEN0) + (1 << TXEN0)
//    #define USART0SetBitrate(br) UBRR0L = (F_CPU/br/16L) - 1
    #define USART0HasData() (UCSR0A & (1 << RXC0))
    void USART0WaitForByte(void);
    unsigned char USART0GetByte(void);
    void USART0SendByte(unsigned char data);
    void USART0SetBitrate(int32_t bitrate);
  #else
    #warning "No hardware USART definitions for target MCU"
  #endif

  #ifdef UBRR1L
    #define USART1Init() UCSR1B = (1 << RXEN1) + (1 << TXEN1)
//    #define USART1SetBitrate(br) UBRR1L = (F_CPU/br/16L) - 1
    #define USART1HasData() (UCSR1A & (1 << RXC1))
    void USART1WaitForByte(void);
    unsigned char USART1GetByte(void);
    void USART1SendByte(unsigned char data);
    void USART1SetBitrate(int32_t bitrate);
  #endif

  #ifdef UBRR2L
    #define USART2Init() UCSR2B = (1 << RXEN2) + (1 << TXEN2)
//    #define USART2SetBitrate(br) UBRR2L = (F_CPU/br/16L) - 1
    #define USART2HasData() (UCSR2A & (1 << RXC2))
    void USART2WaitForByte(void);
    unsigned char USART2GetByte(void);
    void USART2SendByte(unsigned char data);
    void USART2SetBitrate(int32_t bitrate);
  #endif

  #ifdef UBRR3L
    #define USART3Init() UCSR3B = (1 << RXEN3) + (1 << TXEN3)
//    #define USART3SetBitrate(br) UBRR3L = (F_CPU/br/16L) - 1
    #define USART3HasData() (UCSR3A & (1 << RXC3))
    void USART3WaitForByte(void);
    unsigned char USART3GetByte(void);
    void USART3SendByte(unsigned char data);
    void USART3SetBitrate(int32_t bitrate);
  #endif

#endif


#if defined(SS_RX_PORT) || defined(SS_TX_PORT)
void softSerialInit(void);
// impossible to set the bitrate at runtime (for now)
#define softSerialSetBitrate()
// the serial port must be set up prior to receiving data, so HasData() is useless
#define softSerialHasData() (1)
// we can't really know when a byte is coming, and if we did, we'd miss receiving it
#define softSerialWaitForByte()
unsigned char softSerialGetByte(void);
void softSerialSendByte(unsigned char data);
#endif


#endif
// SERIAL_H

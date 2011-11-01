/* $Id: serial.c 1183 2011-06-13 02:55:05Z bhagman $
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

#include "serial.h"
#include "avrportreg.h"

#if defined(UBRRL) && (BOOT_USART == 0 || DEBUG_USART == 0)
void USARTWaitForByte()
{
  while (!USARTHasData());
}

unsigned char USARTGetByte()
{
  USARTWaitForByte();
  return UDR;
}

void USARTSendByte(unsigned char data)
{
  while (!(UCSRA & (1 << UDRE)));
  UDR = data;
}

void USARTSetBitrate(int32_t bitrate)
{
  uint32_t fbase = F_CPU;

  if (bitrate < 0)
  {
    UCSRA |= (1 << U2X);
    bitrate = -bitrate;
  }
  else
  {
    UCSRA &= ~(1 << U2X);
    fbase >>= 1;  // F_CPU/16L
  }
  UBRR = (fbase/bitrate + 4) / 8L - 1;
}
#endif

#if defined(UBRR0L) && (BOOT_USART == 0 || DEBUG_USART == 0)
void USART0WaitForByte()
{
  while (!USART0HasData());
}

unsigned char USART0GetByte()
{
  USART0WaitForByte();
  return UDR0;
}

void USART0SendByte(unsigned char data)
{
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void USART0SetBitrate(int32_t bitrate)
{
  uint32_t fbase = F_CPU;

  if (bitrate < 0)
  {
    UCSR0A |= (1 << U2X0);
    bitrate = -bitrate;
  }
  else
  {
    UCSR0A &= ~(1 << U2X0);
    fbase >>= 1;  // F_CPU/16L
  }
#ifdef UBRR0
  UBRR0 = (fbase/bitrate + 4) / 8L - 1;
#else
  UBRR0L = (fbase/bitrate + 4) / 8L - 1;
#endif
}
#endif

#if defined(UBRR1L) && (BOOT_USART == 1 || DEBUG_USART == 1)
void USART1WaitForByte()
{
  while (!USART1HasData());
}

unsigned char USART1GetByte()
{
  USART1WaitForByte();
  return UDR1;
}

void USART1SendByte(unsigned char data)
{
  while (!(UCSR1A & (1 << UDRE1)));
  UDR1 = data;
}

void USART1SetBitrate(int32_t bitrate)
{
  uint32_t fbase = F_CPU;

  if (bitrate < 0)
  {
    UCSR1A |= (1 << U2X1);
    bitrate = -bitrate;
  }
  else
  {
    UCSR1A &= ~(1 << U2X1);
    fbase >>= 1;  // F_CPU/16L
  }
#ifdef UBRR1
  UBRR1 = (fbase/bitrate + 4) / 8L - 1;
#else
  UBRR1L = (fbase/bitrate + 4) / 8L - 1;
#endif
}
#endif

#if defined(UBRR2L) && (BOOT_USART == 2 || DEBUG_USART == 2)
void USART2WaitForByte()
{
  while (!USART2HasData());
}

unsigned char USART2GetByte()
{
  USART2WaitForByte();
  return UDR2;
}

void USART2SendByte(unsigned char data)
{
  while (!(UCSR2A & (1 << UDRE2)));
  UDR2 = data;
}

void USART2SetBitrate(int32_t bitrate)
{
  uint32_t fbase = F_CPU;

  if (bitrate < 0)
  {
    UCSR2A |= (1 << U2X2);
    bitrate = -bitrate;
  }
  else
  {
    UCSR2A &= ~(1 << U2X2);
    fbase >>= 1;  // F_CPU/16L
  }
  UBRR2 = (fbase/bitrate + 4) / 8L - 1;
}
#endif

#if defined(UBRR3L) && (BOOT_USART == 3 || DEBUG_USART == 3)
void USART3WaitForByte()
{
  while (!USART3HasData());
}

unsigned char USART3GetByte()
{
  USART3WaitForByte();
  return UDR3;
}

void USART3SendByte(unsigned char data)
{
  while (!(UCSR3A & (1 << UDRE3)));
  UDR3 = data;
}

void USART3SetBitrate(int32_t bitrate)
{
  uint32_t fbase = F_CPU;

  if (bitrate < 0)
  {
    UCSR3A |= (1 << U2X3);
    bitrate = -bitrate;
  }
  else
  {
    UCSR3A &= ~(1 << U2X3);
    fbase >>= 1;  // F_CPU/16L
  }
  UBRR3 = (fbase/bitrate + 4) / 8L - 1;
}
#endif


#if defined(SS_RX_PORT) || defined(SS_TX_PORT)

void softSerialInit(void)
{
  // set up the pins
#ifdef SS_RX_PORT
  *(PORT_TO_DDR(SS_RX_PORT)) &= ~(1 << SS_RX_PIN);
  SS_RX_PORT |= (1 << SS_RX_PIN);
#endif

#ifdef SS_TX_PORT
  *(PORT_TO_DDR(SS_TX_PORT)) |= (1 << SS_TX_PIN);
  SS_TX_PORT |= (1 << SS_TX_PIN);
#endif
}

//#define SOFT_SERIAL_B_VALUE (((F_CPU/SOFT_SERIAL_BAUD_RATE)-23)/6)
#define SOFT_SERIAL_B_VALUE (((F_CPU/SS_BAUD_RATE)-20)/6)
#if SOFT_SERIAL_B_VALUE > 255
 #error "Baud rate too slow for soft serial."
#endif

__attribute__ ((naked))
void serialDelay()
{
  __asm__ __volatile__ (
    "ldi r25,%[count]\n"
    "1:dec r25\n"
    "brne 1b\n"
    "ret\n"
    ::[count] "M" (SOFT_SERIAL_B_VALUE)
  );
}


#ifdef SS_RX_PORT
unsigned char softSerialGetByte(void)
{
  unsigned char ch;

  __asm__ __volatile__ (
    "1: sbic  %[rxPin],%[rxBit]\n"        // Wait for start edge
    "   rjmp  1b\n"
    "   rcall serialDelay\n"              // Get to middle of start bit (1/2 bit period)
    "2: rcall serialDelay\n"              // Wait 1/2 bit period
    "   rcall serialDelay\n"              // Wait 1/2 bit period
    "   clc\n"
    "   sbic  %[rxPin],%[rxBit]\n"
    "   sec\n"                          
    "   dec   %[bitCnt]\n"
    "   breq  3f\n"
    "   ror   %[ch]\n"
    "   rjmp  2b\n"
    "3:\n"
    :
      [ch] "=r" (ch)
    :
      [bitCnt] "d" (9),
      [rxPin] "I" (_SFR_IO_ADDR(*(PORT_TO_PIN(SS_RX_PORT))),
      [rxBit] "I" (SS_RX_PIN)
    :
      "r25"
  );

  return ch;
}
#endif

#ifdef SS_TX_PORT
void softSerialSendByte(unsigned char ch)
{
  __asm__ __volatile__ (
    "   com %[ch]\n" // ones complement, carry set
    "   sec\n"
    "1: brcc 2f\n"
    "   cbi %[txPort],%[txBit]\n"
    "   rjmp 3f\n"
    "2: sbi %[txPort],%[txBit]\n"
    "   nop\n"
    "3: rcall serialDelay\n"
    "   rcall serialDelay\n"
    "   lsr %[ch]\n"
    "   dec %[bitcnt]\n"
    "   brne 1b\n"
    :
    :
      [bitcnt] "d" (10),
      [ch] "r" (ch),
      [txPort] "I" (_SFR_IO_ADDR(SS_TX_PORT)),
      [txBit] "I" (SS_TX_PIN)
    :
      "r25"
  );
}
#endif

#endif


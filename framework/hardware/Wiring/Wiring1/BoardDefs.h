/* $Id: BoardDefs.h 1160 2011-06-08 02:41:06Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Wiring V1 (ATmega128)
|| |   (Atmel AVR 8 bit microcontroller core)
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WBOARDDEFS_H
#define WBOARDDEFS_H

#include "WConstants.h"

#define TOTAL_PINS              54
#define TOTAL_ANALOG_PINS       8
#define FIRST_ANALOG_PIN        40

#define WLED                    48

// How many ports are on this device
#if defined (PORTK)
#define WIRING_PORTS 11
#else
#define WIRING_PORTS 7
#endif

/*************************************************************
 * Prototypes
 *************************************************************/

void boardInit(void);


/*************************************************************
 * Pin locations - constants
 *************************************************************/

// SPI port
const static uint8_t SS   = 24;
const static uint8_t MOSI = 25;
const static uint8_t MISO = 26;
const static uint8_t SCK  = 27;

// TWI port
const static uint8_t SCL  = 0;
const static uint8_t SDA  = 1;

// Analog pins
const static uint8_t A0 = 0;
const static uint8_t A1 = 1;
const static uint8_t A2 = 2;
const static uint8_t A3 = 3;
const static uint8_t A4 = 4;
const static uint8_t A5 = 5;
const static uint8_t A6 = 6;
const static uint8_t A7 = 7;

// External Interrupts
const static uint8_t EI0 = 2;
const static uint8_t EI1 = 3;
const static uint8_t EI2 = 4;
const static uint8_t EI3 = 5;
const static uint8_t EI4 = 36;
const static uint8_t EI5 = 37;
const static uint8_t EI6 = 38;
const static uint8_t EI7 = 39;

// Hardware Serial port pins
const static uint8_t RX0 = 32;
const static uint8_t TX0 = 33;
const static uint8_t RX1 = 2;
const static uint8_t TX1 = 3;


/*************************************************************
 * Pin to register mapping macros
 *************************************************************/

// If PORTK defined, that means we are using an ATmega1280/2560

#if defined (PORTK)
#define digitalPinToPortReg(P) \
        (((P) >= 0 && (P) <= 7)   ? &PORTD : \
        (((P) >= 8 && (P) <= 15)  ? &PORTC : \
        (((P) >= 16 && (P) <= 23) ? &PORTA : \
        (((P) >= 24 && (P) <= 31) ? &PORTB : \
        (((P) >= 32 && (P) <= 39) ? &PORTE : \
        (((P) >= 40 && (P) <= 47) ? &PORTF : \
        (((P) >= 48 && (P) <= 53) ? &PORTG : \
        (((P) >= 56 && (P) <= 63) ? &PORTH : \
        (((P) >= 64 && (P) <= 71) ? &PORTJ : \
        (((P) >= 72 && (P) <= 79) ? &PORTK : \
        (((P) >= 80 && (P) <= 87) ? &PORTL : NOT_A_REG)))))))))))
#else
#define digitalPinToPortReg(P) \
        (((P) >= 0 && (P) <= 7)   ? &PORTD : \
        (((P) >= 8 && (P) <= 15)  ? &PORTC : \
        (((P) >= 16 && (P) <= 23) ? &PORTA : \
        (((P) >= 24 && (P) <= 31) ? &PORTB : \
        (((P) >= 32 && (P) <= 39) ? &PORTE : \
        (((P) >= 40 && (P) <= 47) ? &PORTF : \
        (((P) >= 48 && (P) <= 53) ? &PORTG : NOT_A_REG)))))))
#endif

#define digitalPinToBit(P)     ((P) & 7)

#define digitalPinToBitMask(P) (1 << (digitalPinToBit(P)))


#define digitalPinToPort(PIN) ((uint8_t)(PIN / 8))

/*
#if defined(PORTK)
#define digitalPinToPort(P) \
        (((P) >= 0 && (P) <= 7)   ? 0 : \
        (((P) >= 8 && (P) <= 15)  ? 1 : \
        (((P) >= 16 && (P) <= 23) ? 2 : \
        (((P) >= 24 && (P) <= 31) ? 3 : \
        (((P) >= 32 && (P) <= 39) ? 4 : \
        (((P) >= 40 && (P) <= 47) ? 5 : \
        (((P) >= 48 && (P) <= 53) ? 6 : \
        (((P) >= 56 && (P) <= 63) ? 7 : \
        (((P) >= 64 && (P) <= 71) ? 8 : \
        (((P) >= 72 && (P) <= 79) ? 9 : \
        (((P) >= 80 && (P) <= 87) ? 10 : NOT_A_PORT)))))))))))
#else
#define digitalPinToPort(P) \
        (((P) >= 0 && (P) <= 7)   ? 0 : \
        (((P) >= 8 && (P) <= 15)  ? 1 : \
        (((P) >= 16 && (P) <= 23) ? 2 : \
        (((P) >= 24 && (P) <= 31) ? 3 : \
        (((P) >= 32 && (P) <= 39) ? 4 : \
        (((P) >= 40 && (P) <= 47) ? 5 : \
        (((P) >= 48 && (P) <= 53) ? 6 : NOT_A_PORT)))))))
#endif
*/

#define digitalPinToTimer(P) \
        ( ((P) == 53) ? TIMER0B : \
        ( ((P) == 29) ? TIMER1A : \
        ( ((P) == 30) ? TIMER1B : \
        ( ((P) == 31) ? TIMER1C : \
        ( ((P) == 35) ? TIMER3A : \
        ( ((P) == 36) ? TIMER3B : \
        ( ((P) == 37) ? TIMER3C : \
        ( ((P) == 34) ? TIMER2B : NOT_A_TIMER))))))))

#if defined (PORTK)
#define portOutputRegister(P) \
        (((P) == 0 ) ? &PORTD : \
        (((P) == 1 ) ? &PORTC : \
        (((P) == 2 ) ? &PORTA : \
        (((P) == 3 ) ? &PORTB : \
        (((P) == 4 ) ? &PORTE : \
        (((P) == 5 ) ? &PORTF : \
        (((P) == 6 ) ? &PORTG : \
        (((P) == 7 ) ? &PORTH : \
        (((P) == 8 ) ? &PORTJ : \
        (((P) == 9 ) ? &PORTK : \
        (((P) == 10 ) ? &PORTL : NOT_A_REG)))))))))))
#else
#define portOutputRegister(P) \
        (((P) == 0 ) ? &PORTD : \
        (((P) == 1 ) ? &PORTC : \
        (((P) == 2 ) ? &PORTA : \
        (((P) == 3 ) ? &PORTB : \
        (((P) == 4 ) ? &PORTE : \
        (((P) == 5 ) ? &PORTF : \
        (((P) == 6 ) ? &PORTG : NOT_A_REG)))))))
#endif

#if defined (PORTK)
#define portInputRegister(P) \
        (((P) == 0 ) ? &PIND : \
        (((P) == 1 ) ? &PINC : \
        (((P) == 2 ) ? &PINA : \
        (((P) == 3 ) ? &PINB : \
        (((P) == 4 ) ? &PINE : \
        (((P) == 5 ) ? &PINF : \
        (((P) == 6 ) ? &PING : \
        (((P) == 7 ) ? &PINH : \
        (((P) == 8 ) ? &PINJ : \
        (((P) == 9 ) ? &PINK : \
        (((P) == 10 ) ? &PINL : NOT_A_REG)))))))))))
#else
#define portInputRegister(P) \
        (((P) == 0 ) ? &PIND : \
        (((P) == 1 ) ? &PINC : \
        (((P) == 2 ) ? &PINA : \
        (((P) == 3 ) ? &PINB : \
        (((P) == 4 ) ? &PINE : \
        (((P) == 5 ) ? &PINF : \
        (((P) == 6 ) ? &PING : NOT_A_REG)))))))
#endif

#if defined (PORTK)
#define portModeRegister(P) \
        (((P) == 0 ) ? &DDRD : \
        (((P) == 1 ) ? &DDRC : \
        (((P) == 2 ) ? &DDRA : \
        (((P) == 3 ) ? &DDRB : \
        (((P) == 4 ) ? &DDRE : \
        (((P) == 5 ) ? &DDRF : \
        (((P) == 6 ) ? &DDRG : \
        (((P) == 7 ) ? &DDRH : \
        (((P) == 8 ) ? &DDRJ : \
        (((P) == 9 ) ? &DDRK : \
        (((P) == 10 ) ? &DDRL : NOT_A_REG)))))))))))
#else
#define portModeRegister(P) \
        (((P) == 0 ) ? &DDRD : \
        (((P) == 1 ) ? &DDRC : \
        (((P) == 2 ) ? &DDRA : \
        (((P) == 3 ) ? &DDRB : \
        (((P) == 4 ) ? &DDRE : \
        (((P) == 5 ) ? &DDRF : \
        (((P) == 6 ) ? &DDRG : NOT_A_REG)))))))
#endif

#define pinToInterrupt(PIN) \
        ( ((PIN) == 2) ? EXTERNAL_INTERRUPT_0 : \
        ( ((PIN) == 3) ? EXTERNAL_INTERRUPT_1 : \
        ( ((PIN) == 4) ? EXTERNAL_INTERRUPT_2 : \
        ( ((PIN) == 5) ? EXTERNAL_INTERRUPT_3 : \
        ( ((PIN) == 36) ? EXTERNAL_INTERRUPT_4 : \
        ( ((PIN) == 37) ? EXTERNAL_INTERRUPT_5 : \
        ( ((PIN) == 38) ? EXTERNAL_INTERRUPT_6 : \
        ( ((PIN) == 39) ? EXTERNAL_INTERRUPT_7 : -1))))))))


/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

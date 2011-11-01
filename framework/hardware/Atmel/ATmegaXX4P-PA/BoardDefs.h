/* $Id: BoardDefs.h 1177 2011-06-11 06:00:01Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Bare Atmel microcontrollers.
|| |   ATmega164P(A), '324P(A), '644P(A), '1284(P).
|| |   (Atmel AVR 8 bit microcontroller core)
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WBOARDDEFS_H
#define WBOARDDEFS_H

#include "WConstants.h"

#define TOTAL_PINS              32
#define TOTAL_ANALOG_PINS       8
#define FIRST_ANALOG_PIN        24

#define WLED                    15

// How many ports are on this device
#define WIRING_PORTS 4

/*************************************************************
 * Prototypes
 *************************************************************/

void boardInit(void);


/*************************************************************
 * Pin locations - constants
 *************************************************************/

// SPI port
const static uint8_t SS   = 20;
const static uint8_t MOSI = 21;
const static uint8_t MISO = 22;
const static uint8_t SCK  = 23;

// TWI port
const static uint8_t SCL  = 8;
const static uint8_t SDA  = 9;

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
const static uint8_t EI2 = 18;

// Hardware Serial port pins
const static uint8_t RX0 = 0;
const static uint8_t TX0 = 1;
const static uint8_t RX1 = 2;
const static uint8_t TX1 = 3;


/*************************************************************
 * Pin to register mapping macros
 *************************************************************/

#define digitalPinToPortReg(PIN) \
        ( ((PIN) >= 0  && (PIN) <= 7)  ? &PORTD : \
        ( ((PIN) >= 8  && (PIN) <= 15) ? &PORTC : \
        ( ((PIN) >= 16 && (PIN) <= 23) ? &PORTB : \
        ( ((PIN) >= 24 && (PIN) <= 31) ? &PORTA : NOT_A_REG))))

#define digitalPinToBit(P)       ((P) & 7)

#define digitalPinToBitMask(PIN) (1 << (digitalPinToBit(PIN)))

#define digitalPinToPort(PIN) ((uint8_t)(PIN / 8))
/*
#define digitalPinToPort(PIN) \
        ( ((PIN) >= 0  && (PIN) <= 7)  ? 0 : \
        ( ((PIN) >= 8  && (PIN) <= 15) ? 1 : \
        ( ((PIN) >= 16 && (PIN) <= 23) ? 2 : \
        ( ((PIN) >= 24 && (PIN) <= 31) ? 3 : NOT_A_PORT))))
*/
#define digitalPinToTimer(PIN) \
        ( ((PIN) == 4) ? TIMER1B : \
        ( ((PIN) == 5) ? TIMER1A : \
        ( ((PIN) == 6) ? TIMER2B : \
        ( ((PIN) == 7) ? TIMER2A : \
        ( ((PIN) == 19) ? TIMER0A : \
        ( ((PIN) == 20) ? TIMER0B : NOT_A_TIMER))))))

#define portOutputRegister(PORT) \
        ( ((PORT) == 0 ) ? &PORTD : \
        ( ((PORT) == 1 ) ? &PORTC : \
        ( ((PORT) == 2 ) ? &PORTB : \
        ( ((PORT) == 3 ) ? &PORTA : NOT_A_REG))))

#define portInputRegister(PORT) \
        ( ((PORT) == 0 ) ? &PIND : \
        ( ((PORT) == 1 ) ? &PINC : \
        ( ((PORT) == 2 ) ? &PINB : \
        ( ((PORT) == 3 ) ? &PINA : NOT_A_REG))))

#define portModeRegister(PORT) \
        ( ((PORT) == 0 ) ? &DDRD : \
        ( ((PORT) == 1 ) ? &DDRC : \
        ( ((PORT) == 2 ) ? &DDRB : \
        ( ((PORT) == 3 ) ? &DDRA : NOT_A_REG))))

#define pinToInterrupt(PIN) \
        ( ((PIN) == 2) ? EXTERNAL_INTERRUPT_0 : \
        ( ((PIN) == 3) ? EXTERNAL_INTERRUPT_1 : \
        ( ((PIN) == 18) ? EXTERNAL_INTERRUPT_2 : -1)))

/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

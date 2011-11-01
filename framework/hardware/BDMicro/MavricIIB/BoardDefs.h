/* $Id: BoardDefs.h 1201 2011-06-16 00:42:47Z bhagman $

  BoardDefs.h - Board Specific Definitions
  Part of the Wiring Project - http://wiring.org.co/

  Copyright (C) 2004-2011 Hernando Barragan
  Copyright (C) 2010-2011 Brett Hagman

  Please see License.txt for license information.
*/

/**************************************************************************
  Wiring Project - Hardware Specific Definitions

  Definitions for:
    BDMicro Mavric IIB
  (Atmel AVR 8 bit microcontroller core)

  Copyright (C) 2011 Brett Hagman
  http://www.roguerobotics.com/
  bhagman@roguerobotics.com

**************************************************************************/

#ifndef WBOARDDEFS_H
#define WBOARDDEFS_H

#include "WConstants.h"

#define TOTAL_PINS              51
#define TOTAL_ANALOG_PINS       8
#define FIRST_ANALOG_PIN        32

#define WLED                    0

// How many ports are on this device
#define WIRING_PORTS 7

/*************************************************************
 * Prototypes
 *************************************************************/

void boardInit(void);


/*************************************************************
 * Pin locations - constants
 *************************************************************/

// SPI port
const static uint8_t SS   = 0;
const static uint8_t MOSI = 2;
const static uint8_t MISO = 3;
const static uint8_t SCK  = 1;

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
const static uint8_t EI0 = 8;
const static uint8_t EI1 = 9;
const static uint8_t EI2 = 10;
const static uint8_t EI3 = 11;
const static uint8_t EI4 = 28;
const static uint8_t EI5 = 29;
const static uint8_t EI6 = 30;
const static uint8_t EI7 = 31;

// Hardware Serial port pins
const static uint8_t RX0 = 24;
const static uint8_t TX0 = 25;
const static uint8_t RX1 = 10;
const static uint8_t TX1 = 11;


/*************************************************************
 * Pin to register mapping macros
 *************************************************************/

// If PORTK defined, that means we are using an ATmega1280/2560

#define digitalPinToPortReg(P) \
        (((P) >= 0 && (P) <= 7)   ? &PORTB : \
        (((P) >= 8 && (P) <= 15)  ? &PORTD : \
        (((P) >= 16 && (P) <= 23) ? &PORTC : \
        (((P) >= 24 && (P) <= 31) ? &PORTE : \
        (((P) >= 32 && (P) <= 39) ? &PORTF : \
        (((P) >= 40 && (P) <= 47) ? &PORTA : \
        (((P) >= 48 && (P) <= 50) ? &PORTG : NOT_A_REG)))))))

#define digitalPinToBit(P)     ((P) & 7)

#define digitalPinToBitMask(P) (1 << (digitalPinToBit(P)))

#define digitalPinToPort(PIN) ((uint8_t)(PIN / 8))

#define digitalPinToTimer(P) \
        ( ((P) == 5)  ? TIMER1A : \
        ( ((P) == 6)  ? TIMER1B : \
        ( ((P) == 7)  ? TIMER1C : \
        ( ((P) == 27) ? TIMER3A : \
        ( ((P) == 28) ? TIMER3B : \
        ( ((P) == 29) ? TIMER3C : NOT_A_TIMER))))))

#define portOutputRegister(P) \
        (((P) == 0 ) ? &PORTB : \
        (((P) == 1 ) ? &PORTD : \
        (((P) == 2 ) ? &PORTC : \
        (((P) == 3 ) ? &PORTE : \
        (((P) == 4 ) ? &PORTF : \
        (((P) == 5 ) ? &PORTA : \
        (((P) == 6 ) ? &PORTG : NOT_A_REG)))))))

#define portInputRegister(P) \
        (((P) == 0 ) ? &PINB : \
        (((P) == 1 ) ? &PIND : \
        (((P) == 2 ) ? &PINC : \
        (((P) == 3 ) ? &PINE : \
        (((P) == 4 ) ? &PINF : \
        (((P) == 5 ) ? &PINA : \
        (((P) == 6 ) ? &PING : NOT_A_REG)))))))

#define portModeRegister(P) \
        (((P) == 0 ) ? &DDRB : \
        (((P) == 1 ) ? &DDRD : \
        (((P) == 2 ) ? &DDRC : \
        (((P) == 3 ) ? &DDRE : \
        (((P) == 4 ) ? &DDRF : \
        (((P) == 5 ) ? &DDRA : \
        (((P) == 6 ) ? &DDRG : NOT_A_REG)))))))

#define pinToInterrupt(PIN) \
        ( ((PIN) == 8) ? EXTERNAL_INTERRUPT_0 : \
        ( ((PIN) == 9) ? EXTERNAL_INTERRUPT_1 : \
        ( ((PIN) == 10) ? EXTERNAL_INTERRUPT_2 : \
        ( ((PIN) == 11) ? EXTERNAL_INTERRUPT_3 : \
        ( ((PIN) == 28) ? EXTERNAL_INTERRUPT_4 : \
        ( ((PIN) == 29) ? EXTERNAL_INTERRUPT_5 : \
        ( ((PIN) == 30) ? EXTERNAL_INTERRUPT_6 : \
        ( ((PIN) == 31) ? EXTERNAL_INTERRUPT_7 : -1))))))))


/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

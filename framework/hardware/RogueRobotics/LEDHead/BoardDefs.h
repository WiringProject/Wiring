/* $Id: BoardDefs.h 1201 2011-06-16 00:42:47Z bhagman $
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://wiring.org.co/
|| @url            http://roguerobotics.com/
||
|| @description
|| | Board Specific Definitions for:
|| |   Rogue Robotics LEDHead (ATmega644P)
|| |     http://www.roguerobotics.com/products/electronics/ledhead
|| |   Rogue Robotics rEDI (ATmega644P)
|| |     http://www.roguerobotics.com/products/electronics/redi
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

#define WLED                    31

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
const static uint8_t SS   = 10;
const static uint8_t MOSI = 11;
const static uint8_t MISO = 12;
const static uint8_t SCK  = 13;

// TWI port
const static uint8_t SCL  = 24;
const static uint8_t SDA  = 25;

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
const static uint8_t EI2 = 8;

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
        ( ((PIN) >= 8  && (PIN) <= 13) ? &PORTB : \
        ( ((PIN) >= 14 && (PIN) <= 21) ? &PORTA : \
        ( ((PIN) >= 22 && (PIN) <= 23) ? &PORTB : \
        ( ((PIN) >= 24 && (PIN) <= 31) ? &PORTC : NOT_A_REG)))))

#define digitalPinToBit(PIN) \
        ( ((PIN) >= 0  && (PIN) <= 7)  ? ((PIN)) : \
        ( ((PIN) >= 8  && (PIN) <= 13) ? ((PIN) - 6) : \
        ( ((PIN) >= 14 && (PIN) <= 21) ? ((PIN) - 14) : \
        ( ((PIN) >= 22 && (PIN) <= 23) ? ((PIN) - 22) : \
        ( ((PIN) >= 24 && (PIN) <= 31) ? ((PIN) - 24) : 0)))))

#define digitalPinToBitMask(PIN) (1 << (digitalPinToBit(PIN)))

#define digitalPinToPort(PIN) \
        ( ((PIN) >= 0  && (PIN) <= 7)  ? 0 : \
        ( ((PIN) >= 8  && (PIN) <= 13) ? 1 : \
        ( ((PIN) >= 14 && (PIN) <= 21) ? 2 : \
        ( ((PIN) >= 22 && (PIN) <= 23) ? 1 : \
        ( ((PIN) >= 24 && (PIN) <= 31) ? 3 : NOT_A_PORT)))))

#define digitalPinToTimer(PIN) \
        ( ((PIN) == 4) ? TIMER1B : \
        ( ((PIN) == 5) ? TIMER1A : \
        ( ((PIN) == 6) ? TIMER2B : \
        ( ((PIN) == 7) ? TIMER2A : \
        ( ((PIN) == 9) ? TIMER0A : \
        ( ((PIN) == 10) ? TIMER0B : NOT_A_TIMER))))))

#define portOutputRegister(PORT) \
        ( ((PORT) == 0 ) ? &PORTD : \
        ( ((PORT) == 1 ) ? &PORTB : \
        ( ((PORT) == 2 ) ? &PORTA : \
        ( ((PORT) == 3 ) ? &PORTC : NOT_A_REG))))

#define portInputRegister(PORT) \
        ( ((PORT) == 0 ) ? &PIND : \
        ( ((PORT) == 1 ) ? &PINB : \
        ( ((PORT) == 2 ) ? &PINA : \
        ( ((PORT) == 3 ) ? &PINC : NOT_A_REG))))

#define portModeRegister(PORT) \
        ( ((PORT) == 0 ) ? &DDRD : \
        ( ((PORT) == 1 ) ? &DDRB : \
        ( ((PORT) == 2 ) ? &DDRA : \
        ( ((PORT) == 3 ) ? &DDRC : NOT_A_REG))))

#define pinToInterrupt(PIN) \
        ( ((PIN) == 2) ? EXTERNAL_INTERRUPT_0 : \
        ( ((PIN) == 3) ? EXTERNAL_INTERRUPT_1 : \
        ( ((PIN) == 8) ? EXTERNAL_INTERRUPT_2 : -1)))

/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

/* $Id: BoardDefs.h 1160 2011-06-08 02:41:06Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Arduino 1280/2560 (ATmega1280/2560)
|| |   (Atmel AVR 8 bit microcontroller core)
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WBOARDDEFS_H
#define WBOARDDEFS_H

#include <avr/pgmspace.h>
#include "WConstants.h"

#define TOTAL_PINS              70
#define TOTAL_ANALOG_PINS       16
#define FIRST_ANALOG_PIN        54

#define WLED                    13

// How many ports are on this device
#define WIRING_PORTS 11

/*************************************************************
 * Prototypes
 *************************************************************/

void boardInit(void);


/*************************************************************
 * Pin locations - constants
 *************************************************************/

// SPI port
const static uint8_t SS   = 53;
const static uint8_t MOSI = 51;
const static uint8_t MISO = 50;
const static uint8_t SCK  = 52;

// TWI port
const static uint8_t SCL  = 21;
const static uint8_t SDA  = 20;

// Analog pins
const static uint8_t A0 = 0;
const static uint8_t A1 = 1;
const static uint8_t A2 = 2;
const static uint8_t A3 = 3;
const static uint8_t A4 = 4;
const static uint8_t A5 = 5;
const static uint8_t A6 = 6;
const static uint8_t A7 = 7;
const static uint8_t A8 = 8;
const static uint8_t A9 = 9;
const static uint8_t A10 = 10;
const static uint8_t A11 = 11;
const static uint8_t A12 = 12;
const static uint8_t A13 = 13;
const static uint8_t A14 = 14;
const static uint8_t A15 = 15;

// External Interrupts
const static uint8_t EI0 = 21;
const static uint8_t EI1 = 20;
const static uint8_t EI2 = 19;
const static uint8_t EI3 = 18;
const static uint8_t EI4 = 2;
const static uint8_t EI5 = 3;
//const static uint8_t EI6 = ;  // no connection
//const static uint8_t EI7 = ;  // no connection

// Hardware Serial port pins
const static uint8_t RX0 = 0;
const static uint8_t TX0 = 1;
const static uint8_t RX1 = 19;
const static uint8_t TX1 = 18;
const static uint8_t RX2 = 17;
const static uint8_t TX2 = 16;
const static uint8_t RX3 = 15;
const static uint8_t TX3 = 14;


/*************************************************************
 * Pin to register mapping macros
 *************************************************************/

extern volatile uint8_t PROGMEM *port_to_mode_PGM[];
extern volatile uint8_t PROGMEM *port_to_input_PGM[];
extern volatile uint8_t PROGMEM *port_to_output_PGM[];
extern const uint8_t PROGMEM digital_pin_to_port_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];


#define digitalPinToPort(P) \
        (pgm_read_byte(digital_pin_to_port_PGM + (P)))

#define digitalPinToPortReg(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_output_PGM + digitalPinToPort(P))))

/*
#define digitalPinToPortReg(P) \
        ((((P) >= 0 && (P) <= 3)   || (P) == 5)                 ? &PORTE : \
        ((((P) >= 39 && (P) <= 41) || (P) == 4)                 ? &PORTG : \
        ((((P) >= 6 && (P) <= 9)   || (P) == 16 || (P) == 17)   ? &PORTH : \
        ((((P) >= 10 && (P) <= 13) || ((P) >= 50 && (P) <= 53)) ? &PORTB : \
        (( (P) >= 14 && (P) <= 15)                              ? &PORTJ : \
        ((((P) >= 18 && (P) <= 21) || (P) == 38)                ? &PORTD : \
        (( (P) >= 22 && (P) <= 29)                              ? &PORTA : \
        (( (P) >= 30 && (P) <= 37)                              ? &PORTC : \
        (( (P) >= 42 && (P) <= 49)                              ? &PORTL : \
        (( (P) >= 54 && (P) <= 61)                              ? &PORTF : \
        (( (P) >= 62 && (P) <= 69)                              ? &PORTK : NOT_A_REG )))))))))))
*/

#define digitalPinToBit(P) \
        (pgm_read_byte(digital_pin_to_bit_PGM + (P)))

#define digitalPinToBitMask(P) (1 << (digitalPinToBit(P)))

#define digitalPinToTimer(P) \
        ( ((P) == 2) ? TIMER3B : \
        ( ((P) == 3) ? TIMER3C : \
        ( ((P) == 4) ? TIMER0B : \
        ( ((P) == 5) ? TIMER3A : \
        ( ((P) == 6) ? TIMER4A : \
        ( ((P) == 7) ? TIMER4B : \
        ( ((P) == 8) ? TIMER4C : \
        ( ((P) == 9) ? TIMER2B : \
        ( ((P) == 10) ? TIMER2A : \
        ( ((P) == 11) ? TIMER1A : \
        ( ((P) == 12) ? TIMER1B : \
        ( ((P) == 13) ? TIMER0A : \
        ( ((P) == 44) ? TIMER5C : \
        ( ((P) == 45) ? TIMER5B : \
        ( ((P) == 46) ? TIMER5A : NOT_A_TIMER)))))))))))))))

#define portOutputRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_output_PGM + (P))))

#define portInputRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_input_PGM + (P))))

#define portModeRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_mode_PGM + (P))))

#define pinToInterrupt(P) \
        ( ((P) == 21) ? EXTERNAL_INTERRUPT_0 : \
        ( ((P) == 20) ? EXTERNAL_INTERRUPT_1 : \
        ( ((P) == 19) ? EXTERNAL_INTERRUPT_2 : \
        ( ((P) == 18) ? EXTERNAL_INTERRUPT_3 : \
        ( ((P) == 2) ? EXTERNAL_INTERRUPT_4 : \
        ( ((P) == 3) ? EXTERNAL_INTERRUPT_5 : -1))))))

/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

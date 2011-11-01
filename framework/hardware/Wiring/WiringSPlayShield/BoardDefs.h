/* $Id: BoardDefs.h 1160 2011-06-08 02:41:06Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Wiring S Play Shield (ATmega644P)
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
#define FIRST_ANALOG_PIN        14

#define WLED                    25

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
const static uint8_t SCL  = 26;
const static uint8_t SDA  = 27;

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
const static uint8_t EI1 = 4;
const static uint8_t EI2 = 8;

// Hardware Serial port pins
const static uint8_t RX0 = 0;
const static uint8_t TX0 = 1;
const static uint8_t RX1 = 2;
const static uint8_t TX1 = 4;


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

#define digitalPinToBit(P) \
        (pgm_read_byte(digital_pin_to_bit_PGM + (P)))

#define digitalPinToBitMask(P) (1 << (digitalPinToBit(P)))

#define digitalPinToTimer(P) \
        ( ((P) == 3) ? TIMER1B : \
        ( ((P) == 5) ? TIMER1A : \
        ( ((P) == 6) ? TIMER2B : \
        ( ((P) == 7) ? TIMER2A : \
        ( ((P) == 9) ? TIMER0A : \
        ( ((P) == 10) ? TIMER0B : NOT_A_TIMER))))))

#define portOutputRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_output_PGM + (P))))

#define portInputRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_input_PGM + (P))))

#define portModeRegister(P) \
        ((volatile uint8_t *)(pgm_read_word(port_to_mode_PGM + (P))))

#define pinToInterrupt(PIN) \
        ( ((PIN) == 2) ? EXTERNAL_INTERRUPT_0 : \
        ( ((PIN) == 4) ? EXTERNAL_INTERRUPT_1 : \
        ( ((PIN) == 8) ? EXTERNAL_INTERRUPT_2 : -1)))

/*************************************************************
 * Timer prescale factors
 *************************************************************/

#define TIMER0PRESCALEFACTOR 64

#endif
// BOARDDEFS_H

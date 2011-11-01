/* $Id: BoardDefs.cpp 1229 2011-08-23 01:49:39Z bhagman $
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

#include <Wiring.h>

#define PA 0
#define PB 1
#define PC 2
#define PD 3


volatile uint8_t PROGMEM *port_to_mode_PGM[] = {
  &DDRA,
  &DDRB,
  &DDRC,
  &DDRD
};

volatile uint8_t PROGMEM *port_to_output_PGM[] = {
  &PORTA,
  &PORTB,
  &PORTC,
  &PORTD
};

volatile uint8_t PROGMEM *port_to_input_PGM[] = {
  &PINA,
  &PINB,
  &PINC,
  &PIND
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
  // PORTLIST
  // -------------------------------------------
  PD  , // PD 0 ** 0 ** USART0_RX
  PD  , // PD 1 ** 1 ** USART0_TX
  PD  , // PD 2 ** 2 ** USART1_RX
  PD  , // PD 4 ** 3 ** PWM
  PD  , // PD 3 ** 4 ** USART1_TX
  PD  , // PD 5 ** 5 ** PWM
  PD  , // PD 6 ** 6 ** PWM
  PD  , // PD 7 ** 7 ** PWM
  PB  , // PB 2 ** 8 ** D8
  PB  , // PB 3 ** 9 ** PWM
  PB  , // PB 4 ** 10 ** SPI_SS
  PB  , // PB 5 ** 11 ** SPI_MOSI
  PB  , // PB 6 ** 12 ** SPI_MISO
  PB  , // PB 7 ** 13 ** SPI_SCK
  PA  , // PA 0 ** 14 ** ADC0
  PA  , // PA 1 ** 15 ** ADC1
  PA  , // PA 2 ** 16 ** ADC2
  PA  , // PA 3 ** 17 ** ADC3
  PA  , // PA 4 ** 18 ** ADC4
  PA  , // PA 5 ** 19 ** ADC5
  PC  , // PC 2 ** 20 ** D20
  PC  , // PC 3 ** 21 ** D21
  PC  , // PC 4 ** 22 ** D22
  PC  , // PC 5 ** 23 ** D23
  PC  , // PC 6 ** 24 ** D24
  PC  , // PC 7 ** 25 ** D25
  PC  , // PC 0 ** 26 ** I2C_SCL
  PC  , // PC 1 ** 27 ** I2C_SDA
  PB  , // PB 0 ** 28 ** D28
  PB  , // PB 1 ** 29 ** D29
  PA  , // PA 6 ** 30 ** D30/ADC6
  PA    // PA 7 ** 31 ** D31/ADC7
};

const uint8_t PROGMEM digital_pin_to_bit_PGM[] = {
  // PIN IN PORT
  // -------------------------------------------
  0  , // PD 0 ** 0 ** USART0_RX
  1  , // PD 1 ** 1 ** USART0_TX
  2  , // PD 2 ** 2 ** USART1_RX
  4  , // PD 4 ** 3 ** PWM
  3  , // PD 3 ** 4 ** USART1_TX
  5  , // PD 5 ** 5 ** PWM
  6  , // PD 6 ** 6 ** PWM
  7  , // PD 7 ** 7 ** PWM
  2  , // PB 2 ** 8 ** D8
  3  , // PB 3 ** 9 ** PWM
  4  , // PB 4 ** 10 ** SPI_SS
  5  , // PB 5 ** 11 ** SPI_MOSI
  6  , // PB 6 ** 12 ** SPI_MISO
  7  , // PB 7 ** 13 ** SPI_SCK
  0  , // PA 0 ** 14 ** ADC0
  1  , // PA 1 ** 15 ** ADC1
  2  , // PA 2 ** 16 ** ADC2
  3  , // PA 3 ** 17 ** ADC3
  4  , // PA 4 ** 18 ** ADC4
  5  , // PA 5 ** 19 ** ADC5
  2  , // PC 2 ** 20 ** D20
  3  , // PC 3 ** 21 ** D21
  4  , // PC 4 ** 22 ** D22
  5  , // PC 5 ** 23 ** D23
  6  , // PC 6 ** 24 ** D24
  7  , // PC 7 ** 25 ** D25
  0  , // PC 0 ** 26 ** I2C_SCL
  1  , // PC 1 ** 27 ** I2C_SDA
  0  , // PB 0 ** 28 ** D28
  1  , // PB 1 ** 29 ** D29
  6  , // PA 6 ** 30 ** D30/ADC6
  7    // PA 7 ** 31 ** D31/ADC7
};


void boardInit(void)
{
  // Initializes main clock used for delay functions, and PWM (fast PWM only)
  Timer0.setMode(0b0011);  // fast PWM
  Timer0.attachInterrupt(INTERRUPT_OVERFLOW, Wiring_Delay_Timer0_overflow);
  Timer0.setClockSource(CLOCK_PRESCALE_64);

  // All other clocks are initialized for PWM use (phase-correct PWM)
  Timer1.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer1.setClockSource(CLOCK_PRESCALE_64);

  Timer2.setMode(0b0001);  // phase-correct PWM
  Timer2.setClockSource(CLOCK_PRESCALE_64);

  // Start interrupts
  sei();
}


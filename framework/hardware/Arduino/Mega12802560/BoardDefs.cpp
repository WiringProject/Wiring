/* $Id: BoardDefs.cpp 1160 2011-06-08 02:41:06Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Board Specific Definitions for:
|| |   Wiring Mega 128/1281/2561
|| |   Wiring 1.1 Sprakfun (ATmega1281/2561)
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
#define PE 4
#define PF 5
#define PG 6
#define PH 7
#define PJ 8
#define PK 9
#define PL 10


volatile uint8_t PROGMEM *port_to_mode_PGM[] = {
  &DDRA,
  &DDRB,
  &DDRC,
  &DDRD,
  &DDRE,
  &DDRF,
  &DDRG,
  &DDRH,
  &DDRJ,
  &DDRK,
  &DDRL,
};

volatile uint8_t PROGMEM *port_to_output_PGM[] = {
  &PORTA,
  &PORTB,
  &PORTC,
  &PORTD,
  &PORTE,
  &PORTF,
  &PORTG,
  &PORTH,
  &PORTJ,
  &PORTK,
  &PORTL,
};

volatile uint8_t PROGMEM *port_to_input_PGM[] = {
  &PINA,
  &PINB,
  &PINC,
  &PIND,
  &PINE,
  &PINF,
  &PING,
  &PINH,
  &PINJ,
  &PINK,
  &PINL,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
  // PORTLIST
  // -------------------------------------------
  PE  , // PE 0 ** 0 ** USART0_RX
  PE  , // PE 1 ** 1 ** USART0_TX
  PE  , // PE 4 ** 2 ** PWM2
  PE  , // PE 5 ** 3 ** PWM3
  PG  , // PG 5 ** 4 ** PWM4
  PE  , // PE 3 ** 5 ** PWM5
  PH  , // PH 3 ** 6 ** PWM6
  PH  , // PH 4 ** 7 ** PWM7
  PH  , // PH 5 ** 8 ** PWM8
  PH  , // PH 6 ** 9 ** PWM9
  PB  , // PB 4 ** 10 ** PWM10
  PB  , // PB 5 ** 11 ** PWM11
  PB  , // PB 6 ** 12 ** PWM12
  PB  , // PB 7 ** 13 ** PWM13
  PJ  , // PJ 1 ** 14 ** USART3_TX
  PJ  , // PJ 0 ** 15 ** USART3_RX
  PH  , // PH 1 ** 16 ** USART2_TX
  PH  , // PH 0 ** 17 ** USART2_RX
  PD  , // PD 3 ** 18 ** USART1_TX
  PD  , // PD 2 ** 19 ** USART1_RX
  PD  , // PD 1 ** 20 ** I2C_SDA
  PD  , // PD 0 ** 21 ** I2C_SCL
  PA  , // PA 0 ** 22 ** D22
  PA  , // PA 1 ** 23 ** D23
  PA  , // PA 2 ** 24 ** D24
  PA  , // PA 3 ** 25 ** D25
  PA  , // PA 4 ** 26 ** D26
  PA  , // PA 5 ** 27 ** D27
  PA  , // PA 6 ** 28 ** D28
  PA  , // PA 7 ** 29 ** D29
  PC  , // PC 7 ** 30 ** D30
  PC  , // PC 6 ** 31 ** D31
  PC  , // PC 5 ** 32 ** D32
  PC  , // PC 4 ** 33 ** D33
  PC  , // PC 3 ** 34 ** D34
  PC  , // PC 2 ** 35 ** D35
  PC  , // PC 1 ** 36 ** D36
  PC  , // PC 0 ** 37 ** D37
  PD  , // PD 7 ** 38 ** D38
  PG  , // PG 2 ** 39 ** D39
  PG  , // PG 1 ** 40 ** D40
  PG  , // PG 0 ** 41 ** D41
  PL  , // PL 7 ** 42 ** D42
  PL  , // PL 6 ** 43 ** D43
  PL  , // PL 5 ** 44 ** D44
  PL  , // PL 4 ** 45 ** D45
  PL  , // PL 3 ** 46 ** D46
  PL  , // PL 2 ** 47 ** D47
  PL  , // PL 1 ** 48 ** D48
  PL  , // PL 0 ** 49 ** D49
  PB  , // PB 3 ** 50 ** SPI_MISO
  PB  , // PB 2 ** 51 ** SPI_MOSI
  PB  , // PB 1 ** 52 ** SPI_SCK
  PB  , // PB 0 ** 53 ** SPI_SS
  PF  , // PF 0 ** 54 ** A0
  PF  , // PF 1 ** 55 ** A1
  PF  , // PF 2 ** 56 ** A2
  PF  , // PF 3 ** 57 ** A3
  PF  , // PF 4 ** 58 ** A4
  PF  , // PF 5 ** 59 ** A5
  PF  , // PF 6 ** 60 ** A6
  PF  , // PF 7 ** 61 ** A7
  PK  , // PK 0 ** 62 ** A8
  PK  , // PK 1 ** 63 ** A9
  PK  , // PK 2 ** 64 ** A10
  PK  , // PK 3 ** 65 ** A11
  PK  , // PK 4 ** 66 ** A12
  PK  , // PK 5 ** 67 ** A13
  PK  , // PK 6 ** 68 ** A14
  PK  , // PK 7 ** 69 ** A15
};

const uint8_t PROGMEM digital_pin_to_bit_PGM[] = {
  // PIN IN PORT
  // -------------------------------------------
  0  , // PE 0 ** 0 ** USART0_RX
  1  , // PE 1 ** 1 ** USART0_TX
  4  , // PE 4 ** 2 ** PWM2
  5  , // PE 5 ** 3 ** PWM3
  5  , // PG 5 ** 4 ** PWM4
  3  , // PE 3 ** 5 ** PWM5
  3  , // PH 3 ** 6 ** PWM6
  4  , // PH 4 ** 7 ** PWM7
  5  , // PH 5 ** 8 ** PWM8
  6  , // PH 6 ** 9 ** PWM9
  4  , // PB 4 ** 10 ** PWM10
  5  , // PB 5 ** 11 ** PWM11
  6  , // PB 6 ** 12 ** PWM12
  7  , // PB 7 ** 13 ** PWM13
  1  , // PJ 1 ** 14 ** USART3_TX
  0  , // PJ 0 ** 15 ** USART3_RX
  1  , // PH 1 ** 16 ** USART2_TX
  0  , // PH 0 ** 17 ** USART2_RX
  3  , // PD 3 ** 18 ** USART1_TX
  2  , // PD 2 ** 19 ** USART1_RX
  1  , // PD 1 ** 20 ** I2C_SDA
  0  , // PD 0 ** 21 ** I2C_SCL
  0  , // PA 0 ** 22 ** D22
  1  , // PA 1 ** 23 ** D23
  2  , // PA 2 ** 24 ** D24
  3  , // PA 3 ** 25 ** D25
  4  , // PA 4 ** 26 ** D26
  5  , // PA 5 ** 27 ** D27
  6  , // PA 6 ** 28 ** D28
  7  , // PA 7 ** 29 ** D29
  7  , // PC 7 ** 30 ** D30
  6  , // PC 6 ** 31 ** D31
  5  , // PC 5 ** 32 ** D32
  4  , // PC 4 ** 33 ** D33
  3  , // PC 3 ** 34 ** D34
  2  , // PC 2 ** 35 ** D35
  1  , // PC 1 ** 36 ** D36
  0  , // PC 0 ** 37 ** D37
  7  , // PD 7 ** 38 ** D38
  2  , // PG 2 ** 39 ** D39
  1  , // PG 1 ** 40 ** D40
  0  , // PG 0 ** 41 ** D41
  7  , // PL 7 ** 42 ** D42
  6  , // PL 6 ** 43 ** D43
  5  , // PL 5 ** 44 ** D44
  4  , // PL 4 ** 45 ** D45
  3  , // PL 3 ** 46 ** D46
  2  , // PL 2 ** 47 ** D47
  1  , // PL 1 ** 48 ** D48
  0  , // PL 0 ** 49 ** D49
  3  , // PB 3 ** 50 ** SPI_MISO
  2  , // PB 2 ** 51 ** SPI_MOSI
  1  , // PB 1 ** 52 ** SPI_SCK
  0  , // PB 0 ** 53 ** SPI_SS
  0  , // PF 0 ** 54 ** A0
  1  , // PF 1 ** 55 ** A1
  2  , // PF 2 ** 56 ** A2
  3  , // PF 3 ** 57 ** A3
  4  , // PF 4 ** 58 ** A4
  5  , // PF 5 ** 59 ** A5
  6  , // PF 6 ** 60 ** A6
  7  , // PF 7 ** 61 ** A7
  0  , // PK 0 ** 62 ** A8
  1  , // PK 1 ** 63 ** A9
  2  , // PK 2 ** 64 ** A10
  3  , // PK 3 ** 65 ** A11
  4  , // PK 4 ** 66 ** A12
  5  , // PK 5 ** 67 ** A13
  6  , // PK 6 ** 68 ** A14
  7  , // PK 7 ** 69 ** A15
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

  Timer3.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer3.setClockSource(CLOCK_PRESCALE_64);

  Timer4.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer4.setClockSource(CLOCK_PRESCALE_64);

  Timer5.setMode(0b0001);  // phase-correct 8 bit PWM
  Timer5.setClockSource(CLOCK_PRESCALE_64);

  // Start interrupts
  sei();
}


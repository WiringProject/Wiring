/* $Id: avrportreg.h 1181 2011-06-13 02:52:42Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://www.roguerobotics.com/
||
|| @description
|| | Simple register look-up macros for Atmel AVR 8 bit controllers.
|| | Provides an easy way to cross reference PORT, DDR, and PIN registers
|| | for any port.
|| #
||
|| @notes
|| |  These are precompiler reduction macros - so if you use a variable with these
|| |  macros, you're going to get a whole lot more than you bargained for.
|| |
|| |  The 8 bit controllers have a maximum of 11 ports (A,B,C,D,E,F,G,H,J,K,L).
|| |
|| |  Warning: If you specify a register which is not available for a given
|| |  controller, you will not be warned (&(_SFR_IO8(0x00)) is returned for the port
|| |  register).
|| #
||
|| @example
|| |  #define LED_PORT PORTB
|| |  #define LED_PIN  PINB3
|| |  ...
|| |  // Set DDR for LED to OUTPUT
|| |  *(PORT_TO_DDR(LED_PORT)) |= (1 << LED_PIN);
|| #
||
|| @license Please see License.txt for license information.
||
*/

#ifndef AVRPORTREG_H
#define AVRPORTREG_H

#ifdef PORTA
 #define PORT_TO_DDR(port)  (((&port) == (&PORTA)) ?  (&DDRA) : PORT_TO_DDRB(port))
 #define PORT_TO_PIN(port)  (((&port) == (&PORTA)) ?  (&PINA) : PORT_TO_PINB(port))
 #define  DDR_TO_PIN(ddr)   (((&ddr)  ==  (&DDRA)) ?  (&PINA) :  DDR_TO_PINB(ddr))
 #define DDR_TO_PORT(ddr)   (((&ddr)  ==  (&DDRA)) ? (&PORTA) : DDR_TO_PORTB(ddr))
 #define  PIN_TO_DDR(pin)   (((&pin)  ==  (&PINA)) ?  (&DDRA) :  PIN_TO_DDRB(pin))
 #define PIN_TO_PORT(pin)   (((&pin)  ==  (&PINA)) ? (&PORTA) : PIN_TO_PORTB(pin))
#else
 #define PORT_TO_DDR(port)  PORT_TO_DDRB(port)
 #define PORT_TO_PIN(port)  PORT_TO_PINB(port)
 #define  DDR_TO_PIN(ddr)    DDR_TO_PINB(ddr)
 #define DDR_TO_PORT(ddr)   DDR_TO_PORTB(ddr)
 #define  PIN_TO_DDR(pin)    PIN_TO_DDRB(pin)
 #define PIN_TO_PORT(pin)   PIN_TO_PORTB(pin)
#endif

#ifdef PORTB
 #define PORT_TO_DDRB(port) (((&port) == (&PORTB)) ?  (&DDRB) : PORT_TO_DDRC(port))
 #define PORT_TO_PINB(port) (((&port) == (&PORTB)) ?  (&PINB) : PORT_TO_PINC(port))
 #define  DDR_TO_PINB(ddr)  (((&ddr)  ==  (&DDRB)) ?  (&PINB) :  DDR_TO_PINC(ddr))
 #define DDR_TO_PORTB(ddr)  (((&ddr)  ==  (&DDRB)) ? (&PORTB) : DDR_TO_PORTC(ddr))
 #define  PIN_TO_DDRB(pin)  (((&pin)  ==  (&PINB)) ?  (&DDRB) :  PIN_TO_DDRC(pin))
 #define PIN_TO_PORTB(pin)  (((&pin)  ==  (&PINB)) ? (&PORTB) : PIN_TO_PORTC(pin))
#else             //B
 #define PORT_TO_DDRB(port) PORT_TO_DDRC(port)
 #define PORT_TO_PINB(port) PORT_TO_PINC(port)
 #define  DDR_TO_PINB(ddr)   DDR_TO_PINC(ddr)
 #define DDR_TO_PORTB(ddr)  DDR_TO_PORTC(ddr)
 #define  PIN_TO_DDRB(pin)   PIN_TO_DDRC(pin)
 #define PIN_TO_PORTB(pin)  PIN_TO_PORTC(pin)
#endif

#ifdef PORTC
 #define PORT_TO_DDRC(port) (((&port) == (&PORTC)) ?  (&DDRC) : PORT_TO_DDRD(port))
 #define PORT_TO_PINC(port) (((&port) == (&PORTC)) ?  (&PINC) : PORT_TO_PIND(port))
 #define  DDR_TO_PINC(ddr)  (((&ddr)  ==  (&DDRC)) ?  (&PINC) :  DDR_TO_PIND(ddr))
 #define DDR_TO_PORTC(ddr)  (((&ddr)  ==  (&DDRC)) ? (&PORTC) : DDR_TO_PORTD(ddr))
 #define  PIN_TO_DDRC(pin)  (((&pin)  ==  (&PINC)) ?  (&DDRC) :  PIN_TO_DDRD(pin))
 #define PIN_TO_PORTC(pin)  (((&pin)  ==  (&PINC)) ? (&PORTC) : PIN_TO_PORTD(pin))
#else             //C
 #define PORT_TO_DDRC(port) PORT_TO_DDRD(port)
 #define PORT_TO_PINC(port) PORT_TO_PIND(port)
 #define  DDR_TO_PINC(ddr)   DDR_TO_PIND(ddr)
 #define DDR_TO_PORTC(ddr)  DDR_TO_PORTD(ddr)
 #define  PIN_TO_DDRC(pin)   PIN_TO_DDRD(pin)
 #define PIN_TO_PORTC(pin)  PIN_TO_PORTD(pin)
#endif

#ifdef PORTD
 #define PORT_TO_DDRD(port) (((&port) == (&PORTD)) ?  (&DDRD) : PORT_TO_DDRE(port))
 #define PORT_TO_PIND(port) (((&port) == (&PORTD)) ?  (&PIND) : PORT_TO_PINE(port))
 #define  DDR_TO_PIND(ddr)  (((&ddr)  ==  (&DDRD)) ?  (&PIND) :  DDR_TO_PINE(ddr))
 #define DDR_TO_PORTD(ddr)  (((&ddr)  ==  (&DDRD)) ? (&PORTD) : DDR_TO_PORTE(ddr))
 #define  PIN_TO_DDRD(pin)  (((&pin)  ==  (&PIND)) ?  (&DDRD) :  PIN_TO_DDRE(pin))
 #define PIN_TO_PORTD(pin)  (((&pin)  ==  (&PIND)) ? (&PORTD) : PIN_TO_PORTE(pin))
#else             //D
 #define PORT_TO_DDRD(port) PORT_TO_DDRE(port)
 #define PORT_TO_PIND(port) PORT_TO_PINE(port)
 #define  DDR_TO_PIND(ddr)   DDR_TO_PINE(ddr)
 #define DDR_TO_PORTD(ddr)  DDR_TO_PORTE(ddr)
 #define  PIN_TO_DDRD(pin)   PIN_TO_DDRE(pin)
 #define PIN_TO_PORTD(pin)  PIN_TO_PORTE(pin)
#endif

#ifdef PORTE
 #define PORT_TO_DDRE(port) (((&port) == (&PORTE)) ?  (&DDRE) : PORT_TO_DDRF(port))
 #define PORT_TO_PINE(port) (((&port) == (&PORTE)) ?  (&PINE) : PORT_TO_PINF(port))
 #define  DDR_TO_PINE(ddr)  (((&ddr)  ==  (&DDRE)) ?  (&PINE) :  DDR_TO_PINF(ddr))
 #define DDR_TO_PORTE(ddr)  (((&ddr)  ==  (&DDRE)) ? (&PORTE) : DDR_TO_PORTF(ddr))
 #define  PIN_TO_DDRE(pin)  (((&pin)  ==  (&PINE)) ?  (&DDRE) :  PIN_TO_DDRF(pin))
 #define PIN_TO_PORTE(pin)  (((&pin)  ==  (&PINE)) ? (&PORTE) : PIN_TO_PORTF(pin))
#else             //E
 #define PORT_TO_DDRE(port) PORT_TO_DDRF(port)
 #define PORT_TO_PINE(port) PORT_TO_PINF(port)
 #define  DDR_TO_PINE(ddr)   DDR_TO_PINF(ddr)
 #define DDR_TO_PORTE(ddr)  DDR_TO_PORTF(ddr)
 #define  PIN_TO_DDRE(pin)   PIN_TO_DDRF(pin)
 #define PIN_TO_PORTE(pin)  PIN_TO_PORTF(pin)
#endif

#ifdef PORTF
 #define PORT_TO_DDRF(port) (((&port) == (&PORTF)) ?  (&DDRF) : PORT_TO_DDRG(port))
 #define PORT_TO_PINF(port) (((&port) == (&PORTF)) ?  (&PINF) : PORT_TO_PING(port))
 #define  DDR_TO_PINF(ddr)  (((&ddr)  ==  (&DDRF)) ?  (&PINF) :  DDR_TO_PING(ddr))
 #define DDR_TO_PORTF(ddr)  (((&ddr)  ==  (&DDRF)) ? (&PORTF) : DDR_TO_PORTG(ddr))
 #define  PIN_TO_DDRF(pin)  (((&pin)  ==  (&PINF)) ?  (&DDRF) :  PIN_TO_DDRG(pin))
 #define PIN_TO_PORTF(pin)  (((&pin)  ==  (&PINF)) ? (&PORTF) : PIN_TO_PORTG(pin))
#else             //F
 #define PORT_TO_DDRF(port) PORT_TO_DDRG(port)
 #define PORT_TO_PINF(port) PORT_TO_PING(port)
 #define  DDR_TO_PINF(ddr)   DDR_TO_PING(ddr)
 #define DDR_TO_PORTF(ddr)  DDR_TO_PORTG(ddr)
 #define  PIN_TO_DDRF(pin)   PIN_TO_DDRG(pin)
 #define PIN_TO_PORTF(pin)  PIN_TO_PORTG(pin)
#endif

#ifdef PORTG
 #define PORT_TO_DDRG(port) (((&port) == (&PORTG)) ?  (&DDRG) : PORT_TO_DDRH(port))
 #define PORT_TO_PING(port) (((&port) == (&PORTG)) ?  (&PING) : PORT_TO_PINH(port))
 #define  DDR_TO_PING(ddr)  (((&ddr)  ==  (&DDRG)) ?  (&PING) :  DDR_TO_PINH(ddr))
 #define DDR_TO_PORTG(ddr)  (((&ddr)  ==  (&DDRG)) ? (&PORTG) : DDR_TO_PORTH(ddr))
 #define  PIN_TO_DDRG(pin)  (((&pin)  ==  (&PING)) ?  (&DDRG) :  PIN_TO_DDRH(pin))
 #define PIN_TO_PORTG(pin)  (((&pin)  ==  (&PING)) ? (&PORTG) : PIN_TO_PORTH(pin))
#else             //G
 #define PORT_TO_DDRG(port) PORT_TO_DDRH(port)
 #define PORT_TO_PING(port) PORT_TO_PINH(port)
 #define  DDR_TO_PING(ddr)   DDR_TO_PINH(ddr)
 #define DDR_TO_PORTG(ddr)  DDR_TO_PORTH(ddr)
 #define  PIN_TO_DDRG(pin)   PIN_TO_DDRH(pin)
 #define PIN_TO_PORTG(pin)  PIN_TO_PORTH(pin)
#endif

#ifdef PORTH
 #define PORT_TO_DDRH(port) (((&port) == (&PORTH)) ?  (&DDRH) : PORT_TO_DDRJ(port))
 #define PORT_TO_PINH(port) (((&port) == (&PORTH)) ?  (&PINH) : PORT_TO_PINJ(port))
 #define  DDR_TO_PINH(ddr)  (((&ddr)  ==  (&DDRH)) ?  (&PINH) :  DDR_TO_PINJ(ddr))
 #define DDR_TO_PORTH(ddr)  (((&ddr)  ==  (&DDRH)) ? (&PORTH) : DDR_TO_PORTJ(ddr))
 #define  PIN_TO_DDRH(pin)  (((&pin)  ==  (&PINH)) ?  (&DDRH) :  PIN_TO_DDRJ(pin))
 #define PIN_TO_PORTH(pin)  (((&pin)  ==  (&PINH)) ? (&PORTH) : PIN_TO_PORTJ(pin))
#else             //H
 #define PORT_TO_DDRH(port) PORT_TO_DDRJ(port)
 #define PORT_TO_PINH(port) PORT_TO_PINJ(port)
 #define  DDR_TO_PINH(ddr)   DDR_TO_PINJ(ddr)
 #define DDR_TO_PORTH(ddr)  DDR_TO_PORTJ(ddr)
 #define  PIN_TO_DDRH(pin)   PIN_TO_DDRJ(pin)
 #define PIN_TO_PORTH(pin)  PIN_TO_PORTJ(pin)
#endif

#ifdef PORTJ
 #define PORT_TO_DDRJ(port) (((&port) == (&PORTJ)) ?  (&DDRJ) : PORT_TO_DDRK(port))
 #define PORT_TO_PINJ(port) (((&port) == (&PORTJ)) ?  (&PINJ) : PORT_TO_PINK(port))
 #define  DDR_TO_PINJ(ddr)  (((&ddr)  ==  (&DDRJ)) ?  (&PINJ) :  DDR_TO_PINK(ddr))
 #define DDR_TO_PORTJ(ddr)  (((&ddr)  ==  (&DDRJ)) ? (&PORTJ) : DDR_TO_PORTK(ddr))
 #define  PIN_TO_DDRJ(pin)  (((&pin)  ==  (&PINJ)) ?  (&DDRJ) :  PIN_TO_DDRK(pin))
 #define PIN_TO_PORTJ(pin)  (((&pin)  ==  (&PINJ)) ? (&PORTJ) : PIN_TO_PORTK(pin))
#else             //J
 #define PORT_TO_DDRJ(port) PORT_TO_DDRK(port)
 #define PORT_TO_PINJ(port) PORT_TO_PINK(port)
 #define  DDR_TO_PINJ(ddr)   DDR_TO_PINK(ddr)
 #define DDR_TO_PORTJ(ddr)  DDR_TO_PORTK(ddr)
 #define  PIN_TO_DDRJ(pin)   PIN_TO_DDRK(pin)
 #define PIN_TO_PORTJ(pin)  PIN_TO_PORTK(pin)
#endif

#ifdef PORTK
 #define PORT_TO_DDRK(port) (((&port) == (&PORTK)) ?  (&DDRK) : PORT_TO_DDRL(port))
 #define PORT_TO_PINK(port) (((&port) == (&PORTK)) ?  (&PINK) : PORT_TO_PINL(port))
 #define  DDR_TO_PINK(ddr)  (((&ddr)  ==  (&DDRK)) ?  (&PINK) :  DDR_TO_PINL(ddr))
 #define DDR_TO_PORTK(ddr)  (((&ddr)  ==  (&DDRK)) ? (&PORTK) : DDR_TO_PORTL(ddr))
 #define  PIN_TO_DDRK(pin)  (((&pin)  ==  (&PINK)) ?  (&DDRK) :  PIN_TO_DDRL(pin))
 #define PIN_TO_PORTK(pin)  (((&pin)  ==  (&PINK)) ? (&PORTK) : PIN_TO_PORTL(pin))
#else             //K
 #define PORT_TO_DDRK(port) PORT_TO_DDRL(port)
 #define PORT_TO_PINK(port) PORT_TO_PINL(port)
 #define  DDR_TO_PINK(ddr)   DDR_TO_PINL(ddr)
 #define DDR_TO_PORTK(ddr)  DDR_TO_PORTL(ddr)
 #define  PIN_TO_DDRK(pin)   PIN_TO_DDRL(pin)
 #define PIN_TO_PORTK(pin)  PIN_TO_PORTL(pin)
#endif

#ifdef PORTL
 #define PORT_TO_DDRL(port) (((&port) == (&PORTL)) ?  (&DDRL) : &(_SFR_IO8(0x00)))
 #define PORT_TO_PINL(port) (((&port) == (&PORTL)) ?  (&PINL) : &(_SFR_IO8(0x00)))
 #define  DDR_TO_PINL(ddr)  (((&ddr)  ==  (&DDRL)) ?  (&PINL) : &(_SFR_IO8(0x00)))
 #define DDR_TO_PORTL(ddr)  (((&ddr)  ==  (&DDRL)) ? (&PORTL) : &(_SFR_IO8(0x00)))
 #define  PIN_TO_DDRL(pin)  (((&pin)  ==  (&PINL)) ?  (&DDRL) : &(_SFR_IO8(0x00)))
 #define PIN_TO_PORTL(pin)  (((&pin)  ==  (&PINL)) ? (&PORTL) : &(_SFR_IO8(0x00)))
#else             //L
 #define PORT_TO_DDRL(port) &(_SFR_IO8(0x00))
 #define PORT_TO_PINL(port) &(_SFR_IO8(0x00))
 #define  DDR_TO_PINL(ddr)  &(_SFR_IO8(0x00))
 #define DDR_TO_PORTL(ddr)  &(_SFR_IO8(0x00))
 #define  PIN_TO_DDRL(pin)  &(_SFR_IO8(0x00))
 #define PIN_TO_PORTL(pin)  &(_SFR_IO8(0x00))
#endif

#endif
// AVRPORTREG_H

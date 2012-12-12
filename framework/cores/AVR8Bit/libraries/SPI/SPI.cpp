/* $Id: SPI.cpp 1163 2011-06-08 03:40:56Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | SPI Library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/


#include "SPI.h"


// default is MASTER
void WSPI::begin() 
{
  begin(SPI_MASTER, MSBFIRST, SPI_MODE3, SPI_CLOCK_DIV4); 
}


void WSPI::begin(uint8_t mode, uint8_t bitOrder, uint8_t dataMode, uint8_t clockRate)
{
  if(mode == SPI_MASTER) {
    pinMode(SS, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(MISO, INPUT);
    setBitOrder(bitOrder);
    setDataMode(dataMode);
    setClockDivider(clockRate); 

    // Enable SPI, Master
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);
  } else { 
    pinMode(SS, INPUT);
    pinMode(SCK, INPUT);
    pinMode(MOSI, INPUT);
    pinMode(MISO, OUTPUT);
    setBitOrder(bitOrder);
    setDataMode(dataMode);
    // clock rate is ignored in slave mode

    // Enable SPI, Slave
    SPCR |= _BV(SPE);
  }
}


void WSPI::end() {
  SPCR &= ~_BV(SPE);
}


// send and receive
uint8_t WSPI::transfer(uint8_t data)
{
  SPDR =  data;
  while(!(SPSR & _BV(SPIF)));
  return SPDR;
}


void WSPI::setBitOrder(uint8_t bitOrder) {
  if(bitOrder == LSBFIRST) {
    SPCR |= _BV(DORD);
  } else {
    SPCR &= ~(_BV(DORD));
  }
}


void WSPI::setClockDivider(uint8_t rate) {
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | ((rate >>2) & SPI_2XCLOCK_MASK);
}


void WSPI::setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}


WSPI SPI;

/* $Id: EEPROM.cpp 1163 2011-06-08 03:40:56Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | EEPROM Hardware Abstraction Library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "EEPROM.h"

/*
|| @description
|| | Read a value from the EEPROM
|| #
|| 
|| @parameter address where to read
|| 
|| @return the value at the address
*/
uint8_t WEEPROM::read(int address)
{
  return eeprom_read_byte((unsigned char *) address);
}

/*
|| @description
|| | Write a value to the EEPROM
|| #
|| 
|| @parameter address  where to write
|| @parameter value    the value to write
*/
void WEEPROM::write(int address, uint8_t value)
{
  eeprom_write_byte((unsigned char *) address, value);
}

/*
uint8_t WEEPROM::read(uint16_t address)
{
#if defined (__AVR_ATmega2561__)||(__AVR_ATmega2560__)||(__AVR_ATmega1281__)||(__AVR_ATmega1280__)
  while( EECR & _BV(EEPE) );
#else
  while( EECR & _BV(EEWE) );
#endif
  EEARH = (uint8_t) ((address & 0xFF00) >> 8);
  EEARL = (uint8_t) (address & 0x00FF);
    
  // set read EERE
  EECR |= _BV(EERE);
    
  // return data byte 
  return EEDR;
}

void WEEPROM::write(uint16_t address, uint8_t value)
{
  // wait until any previous write is done
#if defined (__AVR_ATmega2561__)||(__AVR_ATmega2560__)||(__AVR_ATmega1281__)||(__AVR_ATmega1280__)
  while( EECR & _BV(EEPE) );
#else
  while( EECR & _BV(EEWE) );
#endif
  EEARH = (uint8_t) ((address & 0xFF00) >> 8);
  EEARL = (uint8_t) (address & 0x00FF);

  EEDR = value;

#if defined (__AVR_ATmega2561__)||(__AVR_ATmega2560__)||(__AVR_ATmega1281__)||(__AVR_ATmega1280__)
  // set master write enable EMWEE
  EECR |= _BV(EEMPE);

  // Set write EEPE
  EECR |= _BV( EEPE );

#else
  // set master write enable EMWEE
  EECR |= _BV(EEMWE);

  // Set write EEWE 
  EECR |= _BV( EEWE );
#endif
}
*/

WEEPROM EEPROM;


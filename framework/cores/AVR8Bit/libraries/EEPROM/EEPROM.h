/* $Id: EEPROM.h 1163 2011-06-08 03:40:56Z bhagman $
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

#ifndef EEPROM_h
#define EEPROM_h

#include <avr/eeprom.h>
#include <inttypes.h>
#include <Wiring.h>

class WEEPROM
{
  public:
    uint8_t read(int address);
    void write(int address, uint8_t value);
};

extern WEEPROM EEPROM;

#endif

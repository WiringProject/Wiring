/* $Id: Potentiometer.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Hardware Abstraction Library for Potentiometers.
|| | Provides an easy way of making/using potentiometers.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Wiring.h>

class Potentiometer
{
  public:
    Potentiometer(byte potPin);
    Potentiometer(byte potPin, uint16_t sectors);

    uint16_t getValue();
    uint16_t getSector();

    void setSectors(uint16_t sectors);

  private:
    byte pin;
    uint16_t sectors;
};

#endif
// POTENTIOMETER_H

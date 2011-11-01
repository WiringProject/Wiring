/* $Id: Potentiometer.cpp 1198 2011-06-14 21:08:27Z bhagman $
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

#include "Potentiometer.h"
#include <Wiring.h>

#define POTENTIOMETER_ADC_RESOLUTION 1024

/*
|| @constructor
|| | Initialize the Potentiometer object
|| #
||
|| @parameter potPin  the pin this Potentiometer is connected to
*/
Potentiometer::Potentiometer(byte potPin)
{
  pin = potPin;
  setSectors(6);
}

/*
|| @constructor
|| | Initialize the Potentiometer object and specify the number of sectors of it
|| #
||
|| @parameter potPin  the pin this Potentiometer is connected to
|| @parameter sectors the pin this Potentiometer is connected to
*/
Potentiometer::Potentiometer(byte potPin, uint16_t sectors)
{
  pin = potPin;
  setSectors(sectors);
}

/*
|| @description
|| | Get the current value of the Potentiometer
|| | This is a wrapper around the analogRead core call
|| | Why? To make the code that handles Potentiometers easier to read
|| #
||
|| @return The value of the Potentiometer [0,1023]
*/
uint16_t Potentiometer::getValue()
{
  return analogRead(pin);
}

/*
|| @description
|| | Get the current sector of the Potentiometer
|| #
||
|| @return The current sector of this Potentiometer [0,sectors]
*/
uint16_t Potentiometer::getSector()
{
  return analogRead(pin) / (POTENTIOMETER_ADC_RESOLUTION / sectors);
}

/*
|| @description
|| | Set the number of sectors for this Potentiometer
|| #
||
|| @parameter newSectors the number of sectors of this Potentiometer
*/
void Potentiometer::setSectors(uint16_t newSectors)
{
  //map newSectors within the bounds of the accepted values?
  if (newSectors < POTENTIOMETER_ADC_RESOLUTION && newSectors > 0)
  {
    sectors = newSectors;
  }
  else
  {
    sectors = POTENTIOMETER_ADC_RESOLUTION - 1;
  }
}


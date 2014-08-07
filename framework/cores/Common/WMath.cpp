/* $Id: WMath.cpp 1156 2011-06-07 04:01:16Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Math methods.
|| |
|| | Wiring Common API
|| #
||
|| @notes
|| | These functions have been defined in C++ so that we can utilize
|| | overloading.
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <math.h>
#include <stdlib.h>
#include <stdint.h>


void randomSeed(uint16_t seed)
{
  if (seed != 0)
    srandom(seed);
}


long random(long howbig)
{
  if (howbig == 0)
    return 0;
  return random() % howbig;
}


long random(long howsmall, long howbig)
{
  if (howsmall >= howbig)
    return howsmall;

  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}


long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
}


uint16_t makeWord(uint16_t w)
{
  return w;
}


uint16_t makeWord(uint8_t highByte, uint8_t lowByte)
{
  return (highByte << 8) | lowByte;
}


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


int32_t random(int32_t howbig)
{
  if (howbig == 0)
    return 0;
  return random() % howbig;
}


int32_t random(int32_t howsmall, int32_t howbig)
{
  if (howsmall >= howbig)
    return howsmall;

  int32_t diff = howbig - howsmall;
  return random(diff) + howsmall;
}


int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
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


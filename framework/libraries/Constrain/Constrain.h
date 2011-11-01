/* $Id: Constrain.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Provides an easy way of making constrained variables.
|| |
|| | Wiring Cross-platform Library
|| #
||
*/

#ifndef CONSTRAINED_H
#define CONSTRAINED_H

#include <Wiring.h>

template< typename T >
struct Constrained
{
  /*
  || @constructor
  || | Initializes the Constrained value
  || #
  ||
  || @parameter val The initial value of this Constrained value
  || @parameter min The minimum value of this Constrained value
  || @parameter max The maximum value of this Constrained value
  */
  Constrained(T val , T min , T max) : value(val), minimum(min), maximum(max) {}
  T value; //hold the current value of the constrained variable
  T minimum; //minimum value for this variable
  T maximum; //maximum value for this variable
  T &operator=(T set)
  {
    if (set < minimum)
    {
      value = minimum;
    }
    else if (set > maximum)
    {
      value = maximum;
    }
    else if (set <= maximum && set >= minimum)
    {
      value = set;
    }
    return value;
  }
  void operator=(Constrained& right)
  {
    value = right.value;
    minimum = right.minimum;
    maximum = right.maximum;
  }
  Constrained &operator++()
  {
    if (value + 1 <= maximum)
    {
      value++;
    }
    return *this;
  }
  Constrained operator++(int)
  {
    if (value + 1 <= maximum)
    {
      value++;
    }
  }
  Constrained &operator--()
  {
    if (value - 1 >= minimum)
    {
      value--;
    }
    return *this;
  }
  Constrained operator--(int)
  {
    if (value - 1 >= minimum)
    {
      value--;
    }
  }
  const Constrained &operator+=(T val)
  {
    value += val;
    value = constrain(value, minimum, maximum);
    return *this;
  }
  const Constrained &operator-=(T val)
  {
    value -= val;
    value = constrain(value, minimum, maximum);
    return *this;
  }
  bool operator<(const T i) const
  {
    return value < i;
  }
  bool operator<=(const T i) const
  {
    return !(value > i);
  }
  bool operator>(const T i) const
  {
    return value > i;
  }
  bool operator>=(const T i) const
  {
    return !(value < i);
  }
  bool operator==(const T i) const
  {
    return value == i;
  }

  operator T()
  {
    return value;
  }
  /*operator int() { return (int)value; }
  operator unsigned char() { return (unsigned char)value; }
  operator char() { return (char)value; }
  operator long() { return (long)value; }*/
};

#endif
// CONSTRAINED_H

/* $Id: SmoothInterpolate.h 1225 2011-07-06 05:09:06Z h $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Make it easy to interpolate smoothly
|| | from x to y in z steps (between each value).
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @example
|| | float arr[2] = { 0.0, 1.0}; //from 0.0 to 1.0
|| | SmoothInterpolate< 2 , 21 > smoothInterpolate = arr; //you start with 2 values, and you have 21 steps between each value
|| | smoothInterpolate.calculate(); //smooth interpolate
|| | float smoothed = smoothInterpolate[2]; //acces the third value (index 2)
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef SMOOTHINTERPOLATE_H
#define SMOOTHINTERPOLATE_H

#include "Countable.h"

template<unsigned int start, unsigned int steps>
class  SmoothInterpolate : public Countable<float>
{
  public:
    /*
    || @constructor
    || | Initialize this SmoothInterpolator
    || #
    */
    SmoothInterpolate(void)
    {
      /*default constructor*/
    }
    /*
    || @constructor
    || | Initialize this SmoothInterpolator with a target array for interpolating from
    || #
    ||
    || @parameter arr the array of values we want to interpolate from
    */
    SmoothInterpolate(float* arr)
    {
      for (unsigned int i = 0; i < start; i++)
      {
        raw[i * steps] = arr[i];
      }
    }
    /*
    || @description
    || | Interpolate smoothly
    || | Effectively increasing the presicion from start to (start*steps)-steps+1
    || #
    ||
    || @parameter compare optional function for comparing a key against another (for complex types)
    */
    void calculate()
    {
      for (unsigned int i = 0; i < (start - 1); i++)
      {
        float min = raw[i * steps];
        float max = raw[(i + 1) * steps];
        for (unsigned int j = 1; j < steps; j++)
        {
          float v = (steps - j) / (float)steps;
          v = smooth(v);
          raw[(i * steps) + j] = (min * v) + (max * (1 - v));
        }
      }
    }
    /*
    || @description
    || | Get the number of values in the interpolated array
    || #
    ||
    || @return The number of vales in the interpolated array
    */
    unsigned int count() const
    {
      return size();
    }

    ///DO NOT DOCUMENT
    const unsigned int size() const
    {
      return (start * steps) - steps + 1;
    }

    /*
    || @description
    || | Assign the interpolator to an array
    || #
    ||
    || @parameter arr the array of values we want to interpolate from
    || @return the arr for chaining
    */
    float* operator=(float* arr)
    {
      for (unsigned int i = 0; i < start; i++)
      {
        raw[i * steps] = arr[i];
      }
      return arr;
    }
    /*
    || @description
    || | Access the values of the interpolated array
    || #
    ||
    || @parameter index the index for access
    || @return the const value at the index
    */
    const float &operator[](unsigned int index) const
    {
      return raw[index]; //unsafe indexing
    }
    /*
    || @description
    || | Access the values of the interpolated array
    || #
    ||
    || @parameter index the index for access
    || @return the value at the index
    */
    float &operator[](unsigned int index)
    {
      return raw[index]; //unsafe indexing
    }

    /*
    || @description
    || | The smooth function
    || | This is public in case some other library or sketch want to get the smoothed value of a var
    || #
    ||
    || @parameter var the value to smooth
    || @return the smoothed value
    */
    static float smooth(float var)
    {
      return (var * var * (3 - 2 * var));
    }
  private:
    float raw[(start*steps) - steps + 1 ];
};

#endif
// SMOOTHINTERPOLATE_H

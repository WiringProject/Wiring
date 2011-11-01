/* $Id: Print.h 1156 2011-06-07 04:01:16Z bhagman $
||
|| @author         Hernando Barragan <b@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Nicholas Zambetti
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Print library.
|| |
|| | Wiring Common API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef PRINT_H
#define PRINT_H

#ifdef __cplusplus

#include <stdint.h>
#include <stdio.h>

#include "WConstants.h"
#include "WString.h"
#include "WConstantTypes.h"
#include "Printable.h"

class Print
{
  public:
    // pure virtual - must be implemented by derived class
    virtual void write(uint8_t) = 0;

    // virtual - can be redefined (polymorphic class)
    virtual void write(const char *str);
    virtual void write(const uint8_t *buffer, size_t size);

    // print
    void print(char);
    void print(const char[]);

    void print(unsigned long, int = DEC);
    void print(long, int = DEC);

    void print(unsigned int, int = DEC);
    void print(unsigned char, int = DEC);
    void print(int, int = DEC);
    void print(double, int = 2);

    void print(const Printable &p);
    void print(const __ConstantStringHelper *cs);

    // println
    void println(void);

    void println(const char[]);
    void println(char);

    void println(unsigned char, int = DEC);
    void println(unsigned int, int = DEC);
    void println(unsigned long, int = DEC);
    void println(int, int = DEC);
    void println(long, int = DEC);
    void println(double, int = 2);

    void println(const Printable &p);
    void println(const __ConstantStringHelper *cs);

  private:
    void printNumber(unsigned long, uint8_t);
    void printFloat(double, uint8_t);
};

#endif  // __cplusplus
#endif
// PRINT_H

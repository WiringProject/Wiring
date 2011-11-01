/* $Id: FluentPrint.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | A library that enables a fluent API for printing.
|| |
|| | Wiring Cross-platform Library
|| #
||
*/

#ifndef FLUENTPRINT_H
#define FLUENTPRINT_H

#include <Wiring.h>

class FluentPrint
{
  public:

    FluentPrint(Print *userPrinter)
    {
      printer = userPrinter;
    }

    template<typename T>
    FluentPrint& print(T n)
    {
      printer->print(n);
      return *this;
    }

    template<typename T>
    FluentPrint& print(T n, int base)
    {
      printer->print(n, base);
      return *this;
    }

    template<typename T>
    FluentPrint& println(T n)
    {
      printer->println(n);
      return *this;
    }

    template<typename T>
    FluentPrint& println(T n, int base)
    {
      printer->println(n, base);
      return *this;
    }

  private:
    Print* printer;
};

#endif
// FLUENTPRINT_H

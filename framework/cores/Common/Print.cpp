/* $Id: Print.cpp 1156 2011-06-07 04:01:16Z bhagman $
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

#include <stdint.h>
#include "Print.h"


/*
|| @description
|| | Virtual method - may be redefined in derived class (polymorphic)
|| | write()s a NUL terminated string.
|| #
*/

void Print::write(const char *str)
{
  while (*str)
    write(*str++);
}

/*
|| @description
|| | Virtual method - may be redefined in derived class (polymorphic)
|| | write()s a specific length string.
|| #
*/

void Print::write(const uint8_t *buffer, size_t size)
{
  while (size--)
    write(*buffer++);
}


// Base method (character)
void Print::print(char c)
{
  write(c);
}

// Base method (string)
void Print::print(const char c[])
{
  write(c);
}


// Base method (unsigned)
void Print::print(unsigned long n, int base)
{
  if (base == 0) write(n);
  else printNumber(n, base);
}

// Base method (signed)
void Print::print(long n, int base)
{
  if (base == 0)
  {
    write(n);
  }
  else if (base == 10)
  {
    // why must this only be in base 10?
    if (n < 0)
    {
      print('-');
      n = -n;
    }
    printNumber(n, 10);
  }
  else
  {
    printNumber(n, base);
  }
}


// Overload (unsigned)
void Print::print(unsigned int n, int base)
{
  print((unsigned long)n, base);
}

// Overload (unsigned)
void Print::print(unsigned char n, int base)
{
  print((unsigned long) n, base);
}

// Overload (signed)
void Print::print(int n, int base)
{
  print((long)n, base);
}


void Print::print(double n, int digits)
{
  printFloat(n, digits);
}


void Print::print(const Printable &p)
{
  p.printTo(*this);
}

void Print::print(const __ConstantStringHelper *cs)
{
  const prog_char *p = (const prog_char *)(cs);
  char c = pgm_read_byte(p++);
  while (c)
  {
    print(c);
    c = pgm_read_byte(p++);
  }
}


void Print::println(void)
{
  print('\r');
  print('\n');
}


void Print::println(char c)
{
  print(c);
  println();
}

void Print::println(const char c[])
{
  print(c);
  println();
}


void Print::println(unsigned long n, int base)
{
  print(n, base);
  println();
}

void Print::println(unsigned int n, int base)
{
  print(n, base);
  println();
}

void Print::println(unsigned char b, int base)
{
  print(b, base);
  println();
}

void Print::println(long n, int base)
{
  print(n, base);
  println();
}

void Print::println(int n, int base)
{
  print(n, base);
  println();
}

void Print::println(double n, int digits)
{
  print(n, digits);
  println();
}


void Print::println(const Printable &p)
{
  p.printTo(*this);
  println();
}

void Print::println(const __ConstantStringHelper *cs)
{
  print(cs);
  println();
}


// private methods

void Print::printNumber(unsigned long n, uint8_t base)
{
  /* BH: new version to be implemented
    uint8_t buf[sizeof(char) * sizeof(int32_t)];
    uint32_t i = 0;

    if (n == 0)
    {
      write('0');
      return;
    }

    while (n > 0)
    {
      buf[i++] = n % base;
      n /= base;
    }

    for (; i > 0; i--)
      write((buf[i - 1] < 10 ?
            '0' + buf[i - 1] :
            'A' + buf[i - 1] - 10));
  */

  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long i = 0;

  if (n == 0)
  {
    print('0');
    return;
  }

  while (n > 0)
  {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char)(buf[i - 1] < 10 ?
                 '0' + buf[i - 1] :
                 'A' + buf[i - 1] - 10));
}

void Print::printFloat(double number, uint8_t digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
    print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}


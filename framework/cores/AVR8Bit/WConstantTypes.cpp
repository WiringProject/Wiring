/* $Id: WConstantTypes.cpp 1152 2011-06-06 21:50:10Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Mikal Hart
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Introduces a new ConstantType datatype, to help compilers understand
|| | the difference between ROM/Flash strings and RAM strings.
|| |
|| | Mikal Hart can be found @ http://arduiniana.org/
|| |
|| | Wiring Core API
|| #
||
|| @example
|| | ConstantSting bigString = Constant("A string store in Flash or other non-volatile memory");
|| | Serial.println(bigString);
|| |
|| | Serial.println(Constant("This string is NOT stored in RAM"));
|| |
|| | IntTable ctable = IntTable(1, 2, 3, 4, 5, 6, 7, 8);
|| |
|| | for (int i = 1; i < ctable.count(); ++i)
|| |   Serial.println(ctable[i]);
|| |
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "WConstantTypes.h"
#include <Print.h>

/*
void ConstantString::printTo(Print &stream) const
{
  const prog_char *p = arr;
  char c = pgm_read_byte(p++);
  while (c)
  {
    stream.print(c);
    c = pgm_read_byte(p++);
  }
}
*/

size_t ConstantString::printTo(Print &stream) const
{
  stream.print((const __ConstantStringHelper *)(arr));
}


char ConstantString::operator[](int index) const
{
  return pgm_read_byte(arr + index);
}

/* Specializations for the ConstantTable class */
template<>
byte ConstantTable<byte>::operator[](int index) const
{
  return pgm_read_byte(arr + index);
}

template<>
char ConstantTable<char>::operator[](int index) const
{
  return pgm_read_byte(arr + index);
}

template<>
int ConstantTable<int>::operator[](int index) const
{
  return pgm_read_word(arr + index);
}

template<>
unsigned int ConstantTable<unsigned int>::operator[](int index) const
{
  return pgm_read_word(arr + index);
}

template<>
long ConstantTable<long>::operator[](int index) const
{
  return pgm_read_dword(arr + index);
}

template<>
unsigned long ConstantTable<unsigned long>::operator[](int index) const
{
  return pgm_read_dword(arr + index);
}

template<>
float ConstantTable<float>::operator[](int index) const
{
  return pgm_read_float(arr + index);
}

template<>
double ConstantTable<double>::operator[](int index) const
{
  return pgm_read_float(arr + index);
}

/* $Id: WConstantTypes.h 1152 2011-06-06 21:50:10Z bhagman $
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
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WCONSTANTTYPES_H
#define WCONSTANTTYPES_H

#include <avr/pgmspace.h>
#include <stdint.h>

class __ConstantStringHelper;

#include <Print.h>
#include <Printable.h>
//#include <Wiring.h>

typedef uint8_t byte;

/*
  The ConstantString class represents an in-flash/ROM String object
*/
class ConstantString : public Printable
{
  private:
    const char PROGMEM *arr;

  public:
  ConstantString(const __ConstantStringHelper *p) :
  
  arr(reinterpret_cast<const char PROGMEM *>(const_cast<__ConstantStringHelper *>(p)))
  {
  }
  
  size_t length() const
  {
    return strlen_P(arr);
  }
  
  char operator[](int index) const;
  
  operator const __ConstantStringHelper *() const
  {
    return reinterpret_cast<const __ConstantStringHelper *>(const_cast<char PROGMEM *>(arr));
  }
  
  size_t printTo(Print &stream) const;
};

/* For inline/auto creation of ConstantStrings */
#define Constant(str) reinterpret_cast<__ConstantStringHelper *>(PSTR(str))

/* For global/static creation of ConstantStrings */
#define ConstantString(name, value) \
  static char __##name[] PROGMEM = value; \
  ConstantString name = reinterpret_cast<__ConstantStringHelper *>(__##name);

/*
  The template class ConstantTable represents a read-only array of an underlying type
*/
template <class T>
class ConstantTable
{
  private:
    const PROGMEM T *arr;
    size_t cnt;

  public:
    ConstantTable(const PROGMEM T *_arr, size_t _cnt) :
      arr(_arr), cnt(_cnt) {}
    size_t count() const
    {
      return cnt;
    }
    T operator[](int index) const;
};

/* For inline/auto creation of ConstantTables */
#define _A(type, values...) ConstantTable<type>( \
  (__extension__( \
    { \
      static type __a[] PROGMEM = { values }; \
      ConstantTable<type>(&__a[0], sizeof(__a) / sizeof(__a[0])); \
    } \
  ) \
))

/* For global/static creation of ConstantTables */
#define ConstantTable(name, type, values...) \
  static type __##name[] PROGMEM = { values }; \
  ConstantTable<type> name(__##name, sizeof(__##name) / sizeof(__##name[0]));

// Typedefs designed to hide the template syntax from the faint of heart
typedef ConstantTable<byte> ByteTable;
typedef ConstantTable<char> CharTable;
typedef ConstantTable<unsigned char> UCharTable;
typedef ConstantTable<int> IntTable;
typedef ConstantTable<unsigned int> UIntTable;
typedef ConstantTable<long> LongTable;
typedef ConstantTable<unsigned long> ULongTable;
typedef ConstantTable<float> FloatTable;
typedef ConstantTable<double> DoubleTable;

#define ByteTable(values...) _A(byte, values)
#define CharTable(values...) _A(char, values)
#define UCharTable(values...) _A(unsigned char, values)
#define IntTable(values...) _A(int, values)
#define UIntTable(values...) _A(unsigned int, values)
#define LongTable(values...) _A(long, values)
#define ULongTable(values...) _A(unsigned long, values)
#define FloatTable(values...) _A(float, values)
#define DoubleTable(values...) _A(double, values)

// Specializations for [] for built-in types defined in .cpp
template<> byte ConstantTable<byte>::operator[](int index) const;
template<> char ConstantTable<char>::operator[](int index) const;
template<> unsigned char ConstantTable<unsigned char>::operator[](int index) const;
template<> int ConstantTable<int>::operator[](int index) const;
template<> unsigned int ConstantTable<unsigned int>::operator[](int index) const;
template<> long ConstantTable<long>::operator[](int index) const;
template<> unsigned long ConstantTable<unsigned long>::operator[](int index) const;
template<> float ConstantTable<float>::operator[](int index) const;
template<> double ConstantTable<double>::operator[](int index) const;

// The generic array access operator is defined here
template<class T> T ConstantTable<T>::operator[](int index) const
{
  T val;
  byte *to = reinterpret_cast<byte *>(&val);
  const PROGMEM byte *from = reinterpret_cast<const PROGMEM byte *>(arr + index);
  for (int i = 0; i < sizeof(T); ++i)
    *to++ = pgm_read_byte(from++);
  return val;
}

#endif
// WCONSTANTTYPES_H

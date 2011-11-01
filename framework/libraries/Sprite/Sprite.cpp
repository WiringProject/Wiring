/* $Id: Sprite.cpp 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         David A. Mellis <dam@mellis.org>
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | 2D sprite buffers library.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "Sprite.h"


/*
|| @constructor
|| | Initializes the Sprite buffer
|| #
||
|| @parameter width   The width of the Sprite buffer
|| @parameter height  The height of the Sprite buffer
*/
Sprite::Sprite(uint8_t width, uint8_t height)
{
  init(width, height);
}

/*
|| @constructor
|| | Initializes the Sprite buffer
|| #
||
|| @parameter width   The width of the Sprite buffer
|| @parameter height  The height of the Sprite buffer
|| @parameter row     The first row data
|| @parameter va_arg  The remainder of the row datas for this Sprite buffer
*/
Sprite::Sprite(uint8_t width, uint8_t height, uint8_t row, ...)
{
  init(width, height);

  if (!_buffer) return;

  va_list ap;
  va_start(ap, row);

  int y = 0;

  for (y = 0; ; y++)
  {
    for (int x = 0; x < width && x < 8; x++)
    {
      write(x, y, (row >> (width - x - 1)) & 0x01);
    }

    if (y == height - 1)
    {
      break;
    }

    row = va_arg(ap, int); // using '...' promotes uint8_t to int
  }

  va_end(ap);
}

/*
|| @description
|| | Get the width of this Sprite buffer
|| #
||
|| @return The width of this Sprite buffer
*/
uint8_t Sprite::width() const
{
  return _width;
}

/*
|| @description
|| | Get the height of this Sprite buffer
|| #
||
|| @return The height of this Sprite buffer
*/
uint8_t Sprite::height() const
{
  return _height;
}

/*
|| @description
|| | Write a value to an x,y coordinate of the buffer
|| #
||
|| @parameter x     The x part of the coordinate
|| @parameter y     The y part of the coordinate
|| @parameter value The value to write at the x,y coordinate
*/
void Sprite::write(int8_t x, int8_t y, uint8_t value)
{
  if (!_buffer) return;
  if (x < 0 || x >= _width || y < 0 || y >= _height) return;

  // we need to bitwise-or the value of the other pixels in the byte with
  // the new value, masked and shifted into the proper bits.
  _buffer[y] = (_buffer[y] & ~(0x01 << x)) | ((value & 0x01) << x);
}

/*
|| @description
|| | Get the value at a specific coordinate
|| #
||
|| @parameter x  The x part of the coordinate
|| @parameter y  The y part of the coordinate
||
|| @return The value of x,y coordinate
*/
uint8_t Sprite::read(int8_t x, int8_t y) const
{
  if (!_buffer) return 0;
  if (x < 0 || x >= _width || y < 0 || y >= _height) return 0;

  return (_buffer[y] >> x) & 0x01;
}

/// private methods


void Sprite::init(uint8_t width, uint8_t height)
{
  _width = width >= 8 ? 8 : width;
  _height = height >= 8 ? 8 : height;

  // for now, do nothing if this allocation fails.  methods that require it
  // should silently fail if _buffer is null.
  _buffer = (uint8_t *) calloc(_height, 1);
}


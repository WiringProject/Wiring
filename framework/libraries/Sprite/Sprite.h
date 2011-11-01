/* $Id: Sprite.h 1198 2011-06-14 21:08:27Z bhagman $
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

#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include <Wiring.h>
#include "Binary.h"

class Sprite
{
  public:
    Sprite(uint8_t width, uint8_t height);
    Sprite(uint8_t width, uint8_t height, uint8_t row, ...);

    uint8_t width() const;
    uint8_t height() const;
    void write(int8_t x, int8_t y, uint8_t value);
    uint8_t read(int8_t x, int8_t y) const;

  private:
    void init(uint8_t width, uint8_t height);

    uint8_t _width;
    uint8_t _height;
    uint8_t _depth;
    uint8_t _ppb;
    uint8_t _bpr;
    uint8_t _mask;
    uint8_t *_buffer;

};

#endif
// SPRITE_H

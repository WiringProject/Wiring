/* $Id: Matrix.cpp 1163 2011-06-08 03:40:56Z bhagman $
||
|| @author         Nicholas Zambetti
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Max7219 LED Matrix Library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

// TODO: Support segment displays in api?
// TODO: Support varying vendor layouts?

#include "Matrix.h"

#include "Sprite.h"

// Matrix registers
#define REG_NOOP   0x00
#define REG_DIGIT0 0x01
#define REG_DIGIT1 0x02
#define REG_DIGIT2 0x03
#define REG_DIGIT3 0x04
#define REG_DIGIT4 0x05
#define REG_DIGIT5 0x06
#define REG_DIGIT6 0x07
#define REG_DIGIT7 0x08
#define REG_DECODEMODE  0x09
#define REG_INTENSITY   0x0A
#define REG_SCANLIMIT   0x0B
#define REG_SHUTDOWN    0x0C
#define REG_DISPLAYTEST 0x0F

/*
|| @constructor
|| | Initializes the digital pins and the Max7219
|| #
|| 
|| @parameter data    The data pin connected to the Max7219
|| @parameter clock   The clock pin connected to the Max7219
|| @parameter load    The load pin connected to the Max7219
|| @parameter screens The number of screens
*/
Matrix::Matrix(byte data, byte clock, byte load, byte screens /* = 1 */)
{
  // record pins for sw spi
  dataPin = data;
  clockPin = clock;
  loadPin = load;

  // set ddr for sw spi pins
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(loadPin, OUTPUT);

  // allocate screenbuffers
  numberOfScreens = numberOfScreens;
  buf = (byte*)calloc(numberOfScreens, 64);
  maximumX = (numberOfScreens * 8);

  // initialize registers
  clear();             // clear display
  setScanLimit(0x07);  // use all rows/digits
  setBrightness(0x0F); // maximum brightness
  setRegister(REG_SHUTDOWN, 0x01);    // normal operation
  setRegister(REG_DECODEMODE, 0x00);  // pixels not integers
  setRegister(REG_DISPLAYTEST, 0x00); // not in test mode
}

/*
|| @description
|| | Sets brightness of the display
|| #
*/
void Matrix::setBrightness(byte value)
{
  setRegister(REG_INTENSITY, value & 0x0F);
}

/*
|| @description
|| | Buffers and writes to screen
|| #
*/
void Matrix::write(int x, int y, byte value)
{
  buffer(x, y, value);
  
  // update affected row
  syncRow(y);
}

/*
|| @description
|| | Buffers and writes to screen using the Sprite library
|| #
*/
void Matrix::write(int x, int y, Sprite sprite)
{
  for (byte i = 0; i < sprite.height(); i++)
  {
    for (byte j = 0; j < sprite.width(); j++)
    {
      buffer(x + j, y + i, sprite.read(j, i));
    }
    syncRow(y + i);
  }
}

/*
|| @description
|| | Clears the screens and buffers
|| #
*/
void Matrix::clear(void)
{
  if (!buf) return;

  // clear buffer
  for(byte i = 0; i < 8; ++i)
  {
    for(byte j = 0; j < numberOfScreens; ++j)
    {
      buf[i + (8 * j)] = 0x00;
    }
  }

  // clear registers
  for(byte i = 0; i < 8; ++i)
  {
    syncRow(i);
  }
}

/// private methods

// sends a single byte by sw spi (no latching)
void Matrix::putByte(byte data)
{
  byte i = 8;
  byte mask;
  while(i > 0) 
  {
    mask = 0x01 << (i - 1);         // get bitmask
    digitalWrite(clockPin, LOW);   // tick
    if (data & mask)
    {               // choose bit
      digitalWrite(dataPin, HIGH); // set 1
    }
    else
    {
      digitalWrite(dataPin, LOW);  // set 0
    }
    digitalWrite(clockPin, HIGH);  // tock
    --i;                            // move to lesser bit
  }
}

// sets register to a byte value for all numberOfScreens
void Matrix::setRegister(byte reg, byte data)
{
  digitalWrite(loadPin, HIGH); // begin
  for(byte i = 0; i < numberOfScreens; ++i)
  {
    putByte(reg);  // specify register
    putByte(data); // send data
  }
  digitalWrite(loadPin, LOW);  // latch in data
  digitalWrite(loadPin, HIGH); // end
}

// syncs row of display with buffer
void Matrix::syncRow(int row)
{
  if (!buf) return;
  if (row < 0 || row >= 8) return;
  digitalWrite(loadPin, HIGH); // begin
  for(byte i = 0; i < numberOfScreens; ++i)
  {
    putByte(8 - row);                // specify register
    putByte(buf[row + (8 * i)]); // send data
  }
  digitalWrite(loadPin, LOW);  // latch in data
  digitalWrite(loadPin, HIGH); // end
}

// sets how many digits are displayed
void Matrix::setScanLimit(byte value)
{
  setRegister(REG_SCANLIMIT, value & 0x07);
}

void Matrix::buffer(int x, int y, byte value)
{
  if (!buf) return;
  if (x < 0 || x >= maximumX || y < 0 || y >= 8) return;

  byte offset = x; // record x
  x %= 8;             // make x relative to a single matrix
  offset -= x;        // calculate buffer offset

  // wrap shift relative x for nexus module layout
  if (x == 0)
  {
    x = 8;
  }
  --x;

  // record value in buffer
  if(value)
  {
    buf[y + offset] |= 0x01 << x;
  }
  else
  {
    buf[y + offset] &= ~(0x01 << x);
  }
}

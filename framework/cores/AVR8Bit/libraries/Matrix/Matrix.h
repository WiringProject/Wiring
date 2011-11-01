/* $Id: Matrix.h 1163 2011-06-08 03:40:56Z bhagman $
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

#ifndef Matrix_h
#define Matrix_h

// include types & constants of Wiring core API
#include <Wiring.h>
#include "Sprite.h"

class Sprite; //forward declaration of the Sprite class

class Matrix
{
  public:
    Matrix(byte data, byte clock, byte load, byte screens=1);
    
    void setBrightness(byte);
    void write(int, int, byte);
    void write(int, int, Sprite);
    void clear(void);
    
  private:
    void putByte(byte);
    void setRegister(byte, byte);
    void syncRow(int);

    void setScanLimit(byte);

    void buffer(int, int, byte);
    
    byte dataPin;
    byte clockPin;
    byte loadPin;

    byte* buf;
    byte numberOfScreens;
    byte maximumX;
};

#endif

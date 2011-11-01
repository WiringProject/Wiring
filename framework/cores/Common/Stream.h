/* $Id: Stream.h 1151 2011-06-06 21:13:05Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Base class for streams.
|| |
|| | Wiring Common API
|| #
||
|| @notes
|| | Originally discussed here:
|| |
|| | http://code.google.com/p/arduino/issues/detail?id=60
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef STREAM_H
#define STREAM_H

#include <stdint.h>
#include <Print.h>

class Stream : public Print
{
  public:
    //virtual ~Stream() {}
    virtual int available() = 0;
    virtual int peek() = 0;
    virtual int read() = 0;
    virtual void flush() = 0;
};

#endif
// STREAM_H

/* $Id: SoftwareSerial.h 1163 2011-06-08 03:40:56Z bhagman $
||
|| @author         David A. Mellis <dam@mellis.org>
|| @url            http://wiring.org.co/
|| @contribution   Hernando Barragan <b@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
||
|| @description
|| | Software serial library.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef SoftwareSerial_h
#define SoftwareSerial_h

#include <inttypes.h>
#include "Print.h"

class SoftwareSerial : public Print
{
  public:
    SoftwareSerial(uint8_t receive, uint8_t transmit);
    
    virtual void write(uint8_t b);
    
    void begin(long);
    int read();
    
  private:    
    uint8_t receivePin;
    uint8_t transmitPin;
    long baudRate;
    int bitPeriod;
};

#endif


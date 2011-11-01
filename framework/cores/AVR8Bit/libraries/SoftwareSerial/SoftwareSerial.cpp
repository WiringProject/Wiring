/* $Id: SoftwareSerial.cpp 1163 2011-06-08 03:40:56Z bhagman $
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

#include <Wiring.h>
#include "SoftwareSerial.h"

/*
|| @constructor
|| | Initializes the internal state of the SoftwareSerial object
|| #
|| 
|| @parameter receive   The pin that recieves serial data
|| @parameter transmit  The pin that transmits serial data
*/
SoftwareSerial::SoftwareSerial(uint8_t receive, uint8_t transmit)
{
  receivePin = receivePin;
  transmitPin = transmitPin;
  baudRate = 0;
}

/*
|| @override Print.write 
||
|| @description
|| | Set the cursor at cooridnate x,y of the display
|| #
*/
void SoftwareSerial::write(uint8_t b)
{
  if (baudRate == 0)
    return;
    
  int bitDelay = bitPeriod - clockCyclesToMicroseconds(50); // a digitalWrite is about 50 cycles
  byte mask;

  digitalWrite(transmitPin, LOW);
  delayMicroseconds(bitDelay);

  for (mask = 0x01; mask; mask <<= 1) 
  {
    if (b & mask) // choose bit
    { 
      digitalWrite(transmitPin,HIGH); // send 1
    }
    else
    {
      digitalWrite(transmitPin,LOW); // send 1
    }
    delayMicroseconds(bitDelay);
  }

  digitalWrite(transmitPin, HIGH);
  delayMicroseconds(bitDelay);
}

/*
|| @description
|| | Set the baud rate of the SS object
|| #
*/
void SoftwareSerial::begin(long speed)
{
  baudRate = speed;
  bitPeriod = 1000000 / baudRate;

  digitalWrite(transmitPin, HIGH);
  delayMicroseconds( bitPeriod); // if we were low this establishes the end
}

/*
|| @description
|| | Set the baud rate of the SS object
|| #
*/
int SoftwareSerial::read()
{
  int val = 0;
  int bitDelay = bitPeriod - clockCyclesToMicroseconds(50);
  
  // one byte of serial data (LSB first)
  // ...--\    /--\/--\/--\/--\/--\/--\/--\/--\/--...
  //	 \--/\--/\--/\--/\--/\--/\--/\--/\--/
  //	start  0   1   2   3   4   5   6   7 stop

  while (digitalRead(receivePin));

  // confirm that this is a real start bit, not line noise
  if (digitalRead(receivePin) == LOW) 
  {
    // frame start indicated by a falling edge and low start bit
    // jump to the middle of the low start bit
    delayMicroseconds(bitDelay / 2 - clockCyclesToMicroseconds(50));
	
    // offset of the bit in the byte: from 0 (LSB) to 7 (MSB)
    for (int offset = 0; offset < 8; offset++) 
    {
	  // jump to middle of next bit
	  delayMicroseconds(bitDelay);
	
	  // read bit
	  val |= digitalRead(receivePin) << offset;
    }
	
    delayMicroseconds(bitPeriod);
    
    return val;
  }
  
  return -1;
}

/** 
 * OSC 
 * 
 * Starts the OSC messaging system
 */

#include <OSC.h>

void setup() 
{
  OSC.begin();
}

void loop() 
{
  OSC.transmit();
}



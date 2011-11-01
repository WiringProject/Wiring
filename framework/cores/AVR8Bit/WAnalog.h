/* $Id: WAnalog.h 1152 2011-06-06 21:50:10Z bhagman $
||
|| @author         Brett Hagman <bhagman@wiring.org.co>
|| @url            http://wiring.org.co/
||
|| @description
|| | Analog input and output methods.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core API
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef WANALOG_H
#define WANALOG_H

#include <inttypes.h>

// Constants

// More than likely, there are only two choices for most microcontrollers:
//  External and Default

#define EXTERNAL     0
#define DEFAULT      1
#define INTERNAL1V1  2
#define INTERNAL2V56 3
#define INTERNAL     3

// Prototypes

int analogRead(uint8_t);
void analogReference(uint8_t);


#endif


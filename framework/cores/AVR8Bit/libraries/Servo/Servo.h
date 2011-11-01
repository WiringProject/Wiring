/* $Id: Servo.h 1142 2011-05-31 06:49:42Z bhagman $
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://wiring.org.co/
|| @contribution   Michael Margolis
||
|| @description
|| | Interrupt driven Servo library using 16 bit timers.
|| | Atmel AVR 8 bit microcontroller series core.
|| |
|| | Wiring Core Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>
#include <ServoTimers.h>

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false
} ServoPin_t   ;

typedef struct {
  ServoPin_t Pin;
  uint16_t ticks;
} servo_t;

class Servo
{
  public:
    Servo();
    uint8_t attach(uint8_t pin);       // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
    uint8_t attach(uint8_t pin, uint16_t min, uint16_t max); // as above but also sets min and max values for writes.
    void detach();
    void write(uint16_t value);        // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
    void writeMicroseconds(uint16_t value); // Write pulse width in microseconds
    uint8_t read();                    // returns current pulse width as an angle between 0 and 180 degrees
    uint16_t readMicroseconds();       // returns current pulse width in microseconds for this servo
    uint8_t attached();                // return true if this servo is attached, otherwise false
  private:
    uint8_t servoIndex;                // index into the channel data for this servo
    uint8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
    uint8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
};

#endif
// SERVO_H

/* $Id: LED.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | This is a Hardware Abstraction Library for LEDs.
|| | Provides an easy way of handling LEDs.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef LED_H
#define LED_H

#include <Wiring.h>

class LED
{
  public:
    LED(uint8_t ledPin);

    bool getState();
    void on();
    void off();
    void toggle();
    void blink(unsigned int time, byte times = 1);

    void setValue(byte val);
    void fadeIn(unsigned int time);
    void fadeOut(unsigned int time);

  private:
    bool status;
    uint8_t pin;
};

#endif
// LED_H

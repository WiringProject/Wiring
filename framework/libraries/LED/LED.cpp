/* $Id: LED.cpp 1198 2011-06-14 21:08:27Z bhagman $
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

#include "LED.h"

/*
|| @constructor
|| | Initialize the LED
|| | Set the pinMode of the LED
|| #
||
|| @parameter ledPin the pin connected to this LED
*/
LED::LED(uint8_t ledPin)
{
  pin = ledPin;
  status = LOW;
  pinMode(pin, OUTPUT);
}

/*
|| @description
|| | Get the state of this LED
|| #
||
|| @return The state of this LED [ HIGH | LOW ]
*/
bool LED::getState()
{
  return status;
}

/*
|| @description
|| | Set this LED on
|| #
*/
void LED::on(void)
{
  digitalWrite(pin, HIGH);
  status = true;
}

/*
|| @description
|| | Set this LED off
|| #
*/
void LED::off(void)
{
  digitalWrite(pin, LOW);
  status = false;
}

/*
|| @description
|| | Toggle this LED
|| | It will change state from on to off, or off to on
|| #
*/
void LED::toggle(void)
{
  status ? off() : on();
}

/*
|| @description
|| | Bling this led a number of times, with the duration of time each blink
|| #
||
|| @parameter time  the time each blink will take
|| @parameter times the number of blinks
*/
void LED::blink(unsigned int time, byte times)
{
  for (byte i = 0; i < times; i++)
  {
    toggle();
    delay(time / 2);
    toggle();
    delay(time / 2);
  }
}

/*
|| @description
|| | This method assumes a PWM pin
|| | analogWrites the pin if PWM, else it either turn it on or off
|| #
||
|| @parameter val the value to set the LED to [0,255]
*/
void LED::setValue(byte val)
{
  analogWrite(pin, val);
  status = (val <= 127) ? false : true;
}

/*
|| @description
|| | This method assumes a PWM pin
|| | It will fade the LED from off to on
|| | analogWrites the pin if PWM, else it ends up turning this LED on
|| #
||
|| @parameter time the time that the fade will last
*/
void LED::fadeIn(unsigned int time)
{
  for (byte value = 0 ; value < 255; value += 5)
  {
    analogWrite(pin, value);
    delay(time / (255 / 5));
  }
  on();
}

/*
|| @description
|| | This method assumes a PWM pin
|| | It will fade the LED from on to off
|| | analogWrites the pin if PWM, else it ends up turning this LED on
|| #
||
|| @parameter time the time that the fade will last
*/
void LED::fadeOut(unsigned int time)
{
  for (byte value = 255; value > 0; value -= 5)
  {
    analogWrite(pin, value);
    delay(time / (255 / 5));
  }
  off();
}


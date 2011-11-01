/**
 * Loop
 * by BREVIG http://alexanderbrevig.com
 * inspired by Capt.Tagon
 * 
 * Create an array of LED instances and play Knight Rider with them.
 */

#include <LED.h>

const byte TIMER = 100;        //each LED will stay in for TIMER ms
const byte NUMBER_OF_LEDS = 5;

//create array of LED instances, wire LEDs from pin 8 to 12 (to ground through a resistor).
LED led[NUMBER_OF_LEDS] = { 
  LED(8), LED(9), LED(10), LED(11), LED(12) 
};

void setup(){/*no setup required*/}

void loop()
{
  byte currentLED = 0; //keep track of current LED to blink
  
  for (currentLED = 0; currentLED < NUMBER_OF_LEDS; currentLED++) 
  { //loop up
    led[currentLED].on();
    delay(TIMER);
    led[currentLED].off();
  }
  for (currentLED = NUMBER_OF_LEDS-1; currentLED >= 0; currentLED--) 
  { //loop down
    led[currentLED].on();
    delay(TIMER);
    led[currentLED].off();
  }
}

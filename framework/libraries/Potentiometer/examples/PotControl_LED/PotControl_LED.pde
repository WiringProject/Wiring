/**
 * PotControl_LED
 * by BREVIG http://alexanderbrevig.com
 * 
 * This demonstrates how to control two LEDs using a Potentiometer.
 * The ledBelow lights up when the potentiometer is below middle, and the ledAbove lights up when potentiometer is above middle
 */

#include <Potentiometer.h>
#include <LED.h>

LED ledBelow = LED(12); //object LED below  at digital 12
LED ledAbove = LED(13); //object LED above  at digital 13
Potentiometer potentiometer = Potentiometer(2);       //a Potentiometer at analog in 2

void setup()
{
  potentiometer.setSectors(2); //split the Potentiometer into two sectors
}

void loop()
{
  if(potentiometer.getSector()==0)
  {
    ledBelow.on();
    ledAbove.off();
  }
  else
  {
    ledBelow.off();
    ledAbove.on();
  }
}

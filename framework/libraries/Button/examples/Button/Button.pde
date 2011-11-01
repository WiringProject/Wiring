/**
 * Button
 * by BREVIG http://alexanderbrevig.com
 * 
 * Use a button connected to digital pin 12.
 * Digital pin 12 is used as input and connected to a button
 * When the button is pressed, the Wiring board LED turn ON,
 * the LED turns OFF when the button is released.
 * 
 * This example simulates the switch example
 */
 
#include <Button.h>

/*
  Wire like this:
  GND -----/ button ------ pin 12
*/
Button button = Button(12,BUTTON_PULLUP_INTERNAL);

void setup()
{
  pinMode(48,OUTPUT);
}

void loop()
{
  if(button.isPressed())
  {
    digitalWrite(48,HIGH);
  }
  else
  {
    digitalWrite(48,LOW);
  }
}

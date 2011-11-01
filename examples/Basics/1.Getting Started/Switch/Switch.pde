/**
 * Switch
 * by BARRAGAN http://barraganstudio.com
 * 
 * Use a switch connected to digital pin 8.
 * Digital pin 8 is used as input and connected to a switch
 * When the switch is pressed, the Wiring board LED turn ON,
 * the LED turns OFF when the switch is released.
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 */

int switchPin = 8;  // digital pin to attach the switch

void setup()
{
  pinMode(switchPin, INPUT);  // set digital pin 0 as input
  pinMode(WLED, OUTPUT);  // set digital (Wiring on-board LED) as output
}

void loop()
{
  if (digitalRead(switchPin) == HIGH) // if the switch is pressed
  {
    digitalWrite(WLED, HIGH);         // turns the Wiring LED ON
  }
  else                                // if the switch is not pressed
  {
    digitalWrite(WLED, LOW);          // turns the Wiring LED OFF
  }
}

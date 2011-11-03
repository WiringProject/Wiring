/**
 * Blink an LED
 * by BARRAGAN http://barraganstudio.com
 * 
 * turns on and off an LED connected to digital pin 8, with
 * intervals of 1 second (1000 milliseconds)
 * Note in the circuit the LED it has a positive (long leg) and a ground
 * (short leg), if the LED doesn't turn ON, it might be it is inverted.
 */

int ledPin = 8;  // LED connected to digital pin 8

void setup()
{
  pinMode(ledPin, OUTPUT);  // set ledPin pin as output
}

void loop()
{
  digitalWrite(ledPin, HIGH);  // set the LED on
  delay(1000);                 // wait for a second
  digitalWrite(ledPin, LOW);   // set the LED off
  delay(1000);                 // wait for a second
}

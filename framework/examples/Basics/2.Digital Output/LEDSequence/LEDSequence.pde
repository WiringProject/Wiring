/**
 * Blink an LED in a sequence
 * by BARRAGAN http://barraganstudio.com
 * 
 * turns on and off an LED connected to a digital pin, with different
 * intervals to create a sequence
 * Note in the circuit the LED it has a positive (long leg) and a ground
 * (short leg), if the LED doesn't turn ON, it might be it is inverted.
 */

int ledPin = 8;  // LED connected to the Wiring I/O board pin 8

void setup()
{
  pinMode(ledPin, OUTPUT);  // sets the digital pin as output
}

void loop()
{
  digitalWrite(ledPin, HIGH);  // sets the LED on
  delay(100);                  // waits for 100ms
  digitalWrite(ledPin, LOW);   // sets the LED off
  delay(1000);                 // waits for a second
  digitalWrite(ledPin, HIGH);  // sets the LED on
  delay(100);                  // waits for 100ms
  digitalWrite(ledPin, LOW);   // sets the LED off
  delay(200);                  // waits for 200ms
}

/**
 * Blink the Wiring board LED
 * by BARRAGAN http://barraganstudio.com
 * 
 * turns on and off the Wiring board LED, with
 * intervals of 1 second (1000 milliseconds).
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 * it is also possible to use the WLED constant with the
 * digitalWrite command: digitalWrite(WLED, HIGH). WLED will be the
 * correct pin in the current board selected in the
 * Tools -> Board menu.
 */

// blinks the board LED, use 48 for Wiring 1.0 boards, use pin 15
// for Wiring S

void setup()
{
  pinMode(WLED, OUTPUT);  // set pin as output
}

void loop()
{
  digitalWrite(WLED, HIGH);  // set the LED on
  delay(1000);               // wait for a second
  digitalWrite(WLED, LOW);   // set the LED off
  delay(1000);               // wait for a second
}

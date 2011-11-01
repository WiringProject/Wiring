/**
 * Controlling a DC Motor speed
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates the use a DC Motor motor with the L293D Motor Driver chip.
 * On Wiring v1 boards the PWM capable pins are: 29, 30, 31, 35, 36 and 37
 * On Wiring S board the PWM capable pins are: 4, 5, 6, 7, 19 and 20
 */

int motorPin = 4;  // L293D Pin En1 connected to pin PWM 4

void setup()
{
  pinMode(motorPin, OUTPUT);
}

void loop()
{
  analogWrite(motorPin, 125);  // turn ON the Motor at medium speed
  delay(100);
}



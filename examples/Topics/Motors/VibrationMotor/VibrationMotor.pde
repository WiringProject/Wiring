/**
 * Driving a DC cell phone vibrating motor.
 * by Diana Fernandez
 * 
 * Demonstrates the use of a vibrating DC motor (cell phone motor).
 * On Wiring v1 boards the PWM capable pins are: 29, 30, 31, 35, 36 and 37
 * On Wiring S board the PWM capable pins are: 4, 5, 6, 7, 19 and 20
 */

int motorpin = 4;  // Vibrating motor connected to pin PWM 4

void setup()
{
  pinMode(motorpin, OUTPUT);
}

void loop()
{
  analogWrite(motorpin, 125);  // turn ON the Motor at medium speed
  delay(100);
}


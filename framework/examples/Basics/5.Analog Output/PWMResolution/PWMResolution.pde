/**
 * Use setPWMResolution and fade an LED brightness
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates the use of PWM pin 4 dimming an LED using the analogWrite() command
 * and the setPWMResoultion command. By default 8-bit resolution is set in all PWM pins
 * On Wiring v1 boards the PWM capable pins are: 29, 30, 31, 35, 36 and 37 and all are
 * 8, 9 and 10 bit resolution capable
 * On Wiring S board the PWM capable pins are: 4, 5, 6, 7, 19 and 20 and only 4 and 5 are
 * 8, 9 and 10 bit resolution capable
 */

int brightness = 0;    // LED brightness
int increment = 5;     // brightness increment

void setup()
{
  pinMode(4, OUTPUT);      // set PWM pin as output
  setPWMResolution(4, 10); // set PWM resolution to 10-bit (now values range in 0-1023)
}

void loop()
{
  // increment brightness for next loop iteration
  brightness = brightness + increment;
  // reverse the direction of the fading
  // since 10-bit resolution is active,
  // possible values are in the range 0-1023
  if (brightness <= 0 || brightness >= 1023)
  {

    increment = -increment;
  }

  // keep brightness in the range
  brightness = constrain(brightness, 0, 1023);
  analogWrite(4, brightness); // set the PWM output

  // wait for 20 milliseconds to see the dimming effect
  delay(20);
}


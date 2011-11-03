/**
 * Fade an LED brightness
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates the use of PWM pin 4 dimming an LED using the analogWrite() command
 * On Wiring v1 boards the PWM capable pins are: 29, 30, 31, 35, 36 and 37
 * On Wiring S board the PWM capable pins are: 4, 5, 6, 7, 19 and 20
 */

int brightness = 0;    // LED brightness
int increment = 5;     // brightness increment

void setup()
{
  pinMode(4, OUTPUT);  // set PWM pin as output
}

void loop()
{
  brightness = brightness + increment;  // increment brightness for next loop iteration

  if (brightness <= 0 || brightness >= 255)    // reverse the direction of the fading
  {
    increment = -increment;
  }
  brightness = constrain(brightness, 0, 255);
  analogWrite(4, brightness);

  delay(20);  // wait for 20 milliseconds to see the dimming effect
}


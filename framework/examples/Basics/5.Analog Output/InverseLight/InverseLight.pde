/**
 * Reading a light sensor and set an LED intensity accordingly
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a photoresistor connected to the
 * analog input pin 0. The value read from the sensor is
 * proportional to the ambient light.
 * This value is used to set an LED brightness to more ambient
 * light less LED brightness.
 * The LED is connected to a PWM output pin.
 * On Wiring v1 boards the PWM capable pins are: 29, 30, 31, 35, 36 and 37
 * On Wiring S board the PWM capable pins are: 4, 5, 6, 7, 19 and 20
 */

int sensorValue;

void setup()
{
  pinMode(19, OUTPUT);
}

void loop()
{
  // read analog input pin 0 (value in the range 0-255)
  sensorValue = analogRead(0) / 4;

  // The luminosity of the LED will be proportional to te amount
  // of light in the environment.

  // Write the value to PWM output pin 0 (value in the range 0-255)
  // analogWrite(19, sensorValue);

  // if you want the luminosity of the LED to be inversely
  // proportional to the amount of light in the environment
  // comment the previous line and use the line below instead:

  analogWrite(19, 255 - sensorValue);

  // wait 100ms for next reading
  delay(100);
}


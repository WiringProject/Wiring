/**
 * Potentiometer + LED brightness
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a potentiometer connected to the
 * analog input pin 0. The value read from the sensor is proportional
 * to the knob position.
 * The value read is used to dim an LED connected to the PWM output pin 19
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
  sensorValue = analogRead(0);  // read analog input pin 0 (value in the range 0-1023)

  // The LED brightness will be proportional to knob position.

  analogWrite(19, sensorValue / 4); // write the value to PWM output pin 37 (value in the range 0-255)

  // if you want the sensorValue of the LED to be inversely proportional to the amount of
  // of light in the environment comment the previous line and use the line below instead:

  //analogWrite(37, 1023 - sensorValue);

  delay(100);  // wait 100ms for next reading
}

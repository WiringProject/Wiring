/**
 * Stretch light
 * by Karmen Franinovic
 * 
 * Controls an LED brightness by pulling a stretch sensor (rubbery ruler).
 * The stretch sensor is made of conductive rubber, that changes
 * resistance when it is streteched.
 * The stretch sensor is connected to analog input pin 0
 * The LED is connected to the analog output (PWM) pin 37
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
  // read analog input pin 0
  sensorValue = analogRead(0);
  // min value read from the stretch sensor was 400
  // calibrare yours accordingly
  sensorValue = (sensorValue - 400);
  // constrain value in the range 0-255
  sensorValue = constrain(sensorValue, 0, 255);
  // write value to PWM (analog) output 19
  analogWrite(19, sensorValue);
  // wait 50ms for next reading
  delay(50);
}


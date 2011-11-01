/**
 * Sensor calibration
 * 
 * Get the maximum and minimum value from a sensor to help finding its
 * operation range at current conditions.
 * Any analog sensor, (photoresistor or potentiometer) connected to
 * analog pin 0 will be fine.
 */

int sensorValue = 0;   // The sensor value
int sensorMin = 1023;  // Minimum sensor value
int sensorMax = 0;     // Maximum sensor value


void setup()
{
  Serial.begin(9600);  // Open the serial at 9600
  Serial.println("Starting calibration for 10 seconds");
  // calibrate during the first five seconds
  while (millis() < 10000)
  {
    sensorValue = analogRead(0);    // read sensor connected to analog pin 0

    if (sensorValue > sensorMax)    // save the maximum sensor value found
    {
      sensorMax = sensorValue;
    }

    if (sensorValue < sensorMin)    // save the minimum sensor value found
    {
      sensorMin = sensorValue;
    }
  }
  Serial.println("Finished calibration");
}

void loop()
{
  // read sensor connected to analog pin 0
  sensorValue = analogRead(0);

  // use the calibration to print values between 0 and 100
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 100);

  // keep the value in the desired range
  sensorValue = constrain(sensorValue, 0, 100);

  // fade the LED using the calibrated value:
  Serial.println(sensorValue, DEC);
}

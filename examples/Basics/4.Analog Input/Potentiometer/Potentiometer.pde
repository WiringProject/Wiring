/**
 * Reading a potentiometer
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a potentiometer connected to the
 * analog input pin 0. The value read from the sensor is proportional
 * to the knob position on the potentiomenter.
 * The value read is printed to the serial monitor
 */

int sensorValue;

void setup()
{
  Serial.begin(9600);  // sets the serial port to 9600
}

void loop()
{
  sensorValue = analogRead(0);     // read analog input pin 0
  Serial.println(sensorValue, DEC);  // prints the value read
  delay(100);                      // wait 100ms for next reading
}

/**
 * Reading a SHARP GP2D12/120 Infrared Ranger
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to connect and read values from a SHARP GP2D12 and GP2D120
 * family of infrared Ranger sensors.
 * The ranger is connected to analog input pin 0.
 * The value read from the sensor is proportional to the distance to an object
 * or obstacle
 * The value read is printed to the serial monitor
 */

int sensorValue;

void setup()
{
  Serial.begin(9600);  // sets the serial port to 9600
}

void loop()
{
  sensorValue = analogRead(0);       // read analog input pin 0
  Serial.println(sensorValue, DEC);  // prints the value read
  delay(100);                        // wait 100ms for next reading
}

/**
 * Piezo film sensor http://msiusa.com
 * by BARRAGAN http://barraganstudio.com
 * 
 * A Piezo film sensor can be used to measure a wide variety of
 * phenomena, including pulses, vibration, pressure etc.
 * This example reads values from a piezo film sensor connected to the
 * analog input pin 0. The value read from the sensor is proportional
 * to the amount of vibration that reaches the sensor's surface.
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

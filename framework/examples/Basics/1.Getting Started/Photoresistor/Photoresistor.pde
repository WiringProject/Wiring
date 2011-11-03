/**
 * Photoresistor
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a photoresistor connected to
 * analog input pin 0 (or A0) and prints the result to the serial monitor
 * The value read from the sensor is proportional
 * to the amount of light that hits the sensor's surface.
 */

int sensorValue;

void setup()
{
  Serial.begin(9600);      // starts the serial port at 9600
}

void loop()
{
  sensorValue = analogRead(0);     // read analog input pin 0
  Serial.print(sensorValue, DEC);  // prints the value read
  Serial.print(" ");               // prints a space between the numbers
  delay(100);                      // wait 100ms for next reading
}

/**
 * AnalogReadSerial
 * Reads an analog input pin 0 and prints the result to the serial monitor
 * Click on the serial monitor button to open it.
 */

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(0);
  Serial.println(sensorValue, DEC);
  delay(100);
}

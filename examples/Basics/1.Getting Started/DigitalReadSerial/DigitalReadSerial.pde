/**
 * DigitalReadSerial
 * Reads a digital input pin 8, prints the result to the serial monitor
 * Click on the serial monitor button to open it.
 */

void setup()
{
  Serial.begin(9600);
  pinMode(8, INPUT);
}

void loop()
{
  int sensorValue = digitalRead(8);
  Serial.println(sensorValue, DEC);
  delay(100);
}




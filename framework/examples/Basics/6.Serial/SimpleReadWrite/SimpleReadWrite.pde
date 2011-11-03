/**
 * Simple ReadWrite
 * 
 * Read data from the serial port and echoes it back to the
 * serial monitor
 */

char val;                   // to read the char

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())   // if data available
  {
    val = Serial.read();    // read data
    Serial.print(val);      // print it back
  }
  delay(100);               // wait 100ms for next read
}

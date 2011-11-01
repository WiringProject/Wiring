/**
 * Simple Write.
 * 
 * Write data to the serial port
 */

char data = 'a';
char space = ' ';

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(data);   // sends 'a'
  Serial.print(space);  // sends ' '
  delay(1000);          // wait 1 second for next print
}


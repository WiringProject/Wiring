/**
 * Many Serial Ports
 * 
 * Read data from the multiple Serial Ports
 */

char val;

void setup()
{
  Serial.begin(9600);  // start Serial at 9600bps
  Serial1.begin(9600); // start Serial1 at 9600bps
}

void loop()
{
  if (Serial.available())  // if data avaible fomr Serial
  {
    val = Serial.read();   // read data from Serial
    // print it back to Serial for console monitoring
    Serial.print("received data from Serial: ");
    Serial.println(val);
  }
  if (Serial1.available())  // if data avaible fomr Serial1
  {
    val = Serial1.read();   // read data from Serial1
    // print it back to Serial for console monitoring
    Serial.print("received data from Serial1: ");
    Serial.println(val);
  }
  delay(100); // wait 100ms for next reading
}

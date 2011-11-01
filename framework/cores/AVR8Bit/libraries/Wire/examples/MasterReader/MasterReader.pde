/**
 * Wire Master Reader
 * by Nicholas Zambetti <http://www.zambetti.com>
 * 
 * Demonstrates use of the Wire library
 * Reads data from an I2C/TWI slave device
 * Refer to the "Wire Slave Sender" example for use with this
 * On Wiring v1 boards the SCL and SDA pins are: 0 and 1
 * On Wiring S board the SCL and SDA pins are: 8 and 9 
 */
 
#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.requestFrom(2, 6);     // request 6 bytes from slave device #2

  while(Wire.available())     // slave may send less than requested
  { 
    char c = Wire.read();  // receive a byte as character
    Serial.print(c);          // print the character
  }

  delay(500);
}

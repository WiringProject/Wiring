/**
 * Wire Master Writer
 * by Nicholas Zambetti <http://www.zambetti.com>
 * 
 * Demonstrates use of the Wire library
 * Writes data to an I2C/TWI slave device
 * Refer to the "Wire Slave Receiver" example for use with this
 * On Wiring v1 boards the SCL and SDA pins are: 0 and 1
 * On Wiring S board the SCL and SDA pins are: 8 and 9 
 */

#include <Wire.h>

void setup()
{
  Wire.begin();  // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4);  // transmit to device #4
  Wire.write("x is ");         // sends five bytes
  Wire.write(x);               // sends one byte  
  Wire.endTransmission();     // stop transmitting

  x++;
  delay(500);
}

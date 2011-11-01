/**
 * I2C HMC6343 compass heading (sparkfun breakout)
 * by BARRAGAN (http://barraganstudio.com)
 * 
 * Demonstrates use of the Wire library reading data from the 
 * HMC6343 compass heading
 * On Wiring v1 boards the SCL and SDA pins are: 0 and 1
 * On Wiring S board the SCL and SDA pins are: 8 and 9 
 */

#include <Wire.h> 

int compassAddress = 0x32 >> 1; // From datasheet compass address is 0x32 for write operations, 
                                // or 0x33 for read operations.
                                // shift the address 1 bit right, the Wire library only needs the 7
                                // most significant bits for the address

int heading = 0; // variable to hold the heading angle
int tilt = 0;    // variable to hold the tilt angle
int roll = 0;    // variable to hold the roll angle

byte responseBytes[6];  // for holding the sensor response bytes

void setup() 
{ 
  delay(500);  //Wait at least 500 milli-seconds for device initialization
  Wire.begin();       // join i2c bus (address optional for master) 
  Serial.begin(9600); // start serial communication at 9600bps 
  pinMode(WLED, OUTPUT);  
  digitalWrite(WLED, HIGH); // just turn ON the onboard LED 
} 

void loop() 
{
  readSensor();  // read data from the HMC6343 sensor
  // Note that heading, tilt and roll values are in tenths of a degree, for example
  // if the value of heading is 1234 would mean 123.4 degrees, that's why the result
  // is divided by 10 when printing.
  Serial.print("Heading: ");
  Serial.print(heading / 10, DEC); 
  Serial.print(" Tilt: ");
  Serial.print(tilt / 10, DEC);
  Serial.print(" Roll: ");
  Serial.println(roll / 10, DEC);
  delay(200);                   // wait for half a second 
}
  
void readSensor() 
{ 
  // step 1: instruct sensor to read echoes 
  Wire.beginTransmission(compassAddress); // transmit to device
                          // the address specified in the datasheet is 66 (0x42) 
                          // but i2c adressing uses the high 7 bits so it's 33 
  Wire.write(byte(0x50)); // Send a "Post Heading Data" (0x50) command to the HMC6343  
  Wire.endTransmission(); // stop transmitting 
 
  // step 2: wait for readings to happen 
  delay(2); // datasheet suggests at least 1 ms 
  
  // step 3: request reading from sensor 
  Wire.requestFrom(compassAddress, 6); // request 6 bytes from slave device #33 
 
  // step 4: receive reading from sensor 
  if(6 <= Wire.available()) // if six bytes were received 
  {
    for(int i = 0; i<6; i++) {
      responseBytes[i] = Wire.read();
    }
  }
  
  heading = ((int)responseBytes[0]<<8) | ((int)responseBytes[1]); // heading MSB and LSB
  tilt = (((int)responseBytes[2]<<8) | ((int)responseBytes[3]));  // tilt MSB and LSB
  roll = (((int)responseBytes[4]<<8) | ((int)responseBytes[5]));  // roll MSB and LSB
} 




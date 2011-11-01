/**
 * Port and LEDs
 * by BARRAGAN http://barraganstudio.com
 * 
 * Ports are sets of 8 pins which can be used to send
 * data in parallel to devices like printers or displays.
 * This example demonstrates the use of digital ports to turn on
 * 8 LEDs connected to digital port 1, the LEDs will reflect
 * the bit value of each pin, value 0 will be 00000000 or all
 * LEDs turned OFF, value 255 will be 11111111 or all LEDs
 * turned ON.
 */

int port = 1;               // which port will be used
byte value = 0;             // byte will go from 0 to 255

void setup()
{
  portMode(port, OUTPUT);
  Serial.begin(9600);       // use serial to monitor value
}

void loop()
{
  portWrite(port, value);   // writes the value to port 0
  value = value + 1;        // increment the variable
  Serial.println(value, DEC);  // print value to console for monitoring
  delay(200);               // waits for 200 milli seconds
}



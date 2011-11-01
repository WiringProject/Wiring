/**
 * Acceleromenter ADXL335 Sparkfun breakout
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from an accelerometer with X, Y and Z connected
 * to analog inputs 0, 1 and 2 respectively
 * The values are printed to the serial monitor
 */

int x, y, z;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  x = analogRead(0);       // read analog input pin 0
  y = analogRead(1);       // read analog input pin 1
  z = analogRead(2);       // read analog input pin 1
  Serial.print("accelerations are x, y, z: ");
  Serial.print(x, DEC);    // print the acceleration in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(y, DEC);    // print the acceleration in the Y axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.println(z, DEC);  // print the acceleration in the Z axis
  delay(100);              // wait 100ms for next reading
}

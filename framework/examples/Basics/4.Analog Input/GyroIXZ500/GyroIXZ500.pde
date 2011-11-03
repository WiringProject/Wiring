/**
 * Dual axis gyroscope IXZ500 500 degrees per second, Sparkfun breakout
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a gyroscope with X, Z connected to analog inputs 0 and 1 respectively
 * The values read re printed to the serial monitor
 */

int x, z;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  x = analogRead(0);       // read analog input pin 0
  z = analogRead(1);       // read analog input pin 1
  Serial.print("rotational rates are x, z: ");
  Serial.print(x, DEC);    // print the rotational rate in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.println(z, DEC);  // print the rotational rate in the Z axis
  delay(100);              // wait 100ms for next reading
}

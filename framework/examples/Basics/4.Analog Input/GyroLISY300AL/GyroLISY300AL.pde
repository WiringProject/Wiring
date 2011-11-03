/**
 * Single axis gyroscope LISY300AL 300 degree per second Sparkfun breakout
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a gyroscope with Z connected to analog inputs 0
 * The values read re printed to the serial monitor
 */

int z;
int pinPowerDown = 8;  // digital pin for Power Down mode
// LOW = Normal, HIGH = Power down

void setup()
{
  Serial.begin(9600);           // sets the serial port to 9600
  pinMode(pinPowerDown, OUTPUT);
  digitalWrite(pinPowerDown, LOW);  // set gyroscope to Normal
}

void loop()
{
  z = analogRead(0);       // read analog input pin 0
  Serial.print("rotation rate in z: ");
  Serial.println(z, DEC);  // print the rotation rate in the Z axis
  delay(100);              // wait 100ms for next reading
}

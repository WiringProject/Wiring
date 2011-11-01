/**
 * Dual axis gyroscope IDG500 500 degreees per second, Sparkfun breakout
 * by BARRAGAN http://barraganstudio.com
 * 
 * Reads values from a gyroscope
 * with X, Y connected to analog inputs 0 and 1 respectively
 * The values read re printed to the serial monitor
 */

int x, y;  // X and Y in-plane sensing

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  x = analogRead(0);       // read analog input pin 0
  y = analogRead(1);       // read analog input pin 1
  Serial.print("rotational rates are x, y: ");
  Serial.print(x, DEC);    // print the rotational rate in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.println(y, DEC);  // print the rotational rate in the Y axis
  delay(100);              // wait 100ms for next reading
}

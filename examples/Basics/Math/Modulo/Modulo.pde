/**
 * Modulo.
 * 
 * The modulo operator (%) returns the remainder of a number
 * divided by another. As in this example, it is often used
 * to keep numerical values within a set range.
 */

int num = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  num = (num + 1) % 10;  // num goes from 0 to 9
  Serial.println(num, DEC);
  delay(50);
}



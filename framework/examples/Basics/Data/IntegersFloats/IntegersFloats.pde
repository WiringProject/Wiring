/**
 * Integers Floats.
 * 
 * Integers and floats are two different kinds of numerical data.
 * An integer (more commonly called an int) is a number without
 * a decimal point. A float is a floating-point number, which means
 * it is a number that has a decimal place. Floats are used when
 * more precision is needed.
 */

int a = 0;      // Create a variable "a" of the datatype "int"
float b = 0.0;  // Create a variable "b" of the datatype "float"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  a = a + 1;
  b = b + 0.2;
  Serial.print("a is: ");
  Serial.println(a, DEC);
  Serial.print("b is: ");
  Serial.println(b);

  if (a > 1000)
  {
    a = 0;
  }
  if (b > 1000)
  {
    b = 0;
  }
  delay(100);
}

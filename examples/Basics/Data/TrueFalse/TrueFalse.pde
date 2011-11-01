/**
 * True/False.
 * 
 * Boolean data is one bit of information. True or false.
 * It is common to use booleans with control statements to
 * determine the flow of a program. In this example, when the
 * boolean value "x" is true, the program waits for 10 seconds
 * then set the value "x" to false. After that "x" will be false
 * forever turning ON the Wiring board LED permanently
 */

boolean x = true;

void setup()
{
  pinMode(WLED, OUTPUT);
}

void loop()
{
  if (x == true)
  {
    delay(10000);  // waits for 10 seconds
    x = false;
  }
  else
  {
    digitalWrite(WLED, HIGH);
  }
}



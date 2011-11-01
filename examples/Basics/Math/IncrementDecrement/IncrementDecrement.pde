/**
 * Increment Decrement.
 * by BARRAGAN http://barraganstudio.com
 * 
 * Writing "a++" is equivalent to "a = a + 1".
 * Writing "a--" is equivalent to "a = a - 1".
 */

int current = 8;  // variable the keeps which light must be turn on next

void setup()
{
  for (int i = 8; i < 16; i++)   // set pins 8-15 as outputs
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  turn_all_off();  // turns all LEDs off
  digitalWrite(current, HIGH);  // set the current light ON
  delay(200);  // wait for 200ms
  current++;  // increment current LED
  if (current > 15)   // range check, if last LED goes back to LED 8
  {
    current = 8;
  }
}

void turn_all_off()    // function to turn off all the LEDs
{
  for (int i = 8; i < 16; i++)   // connected to digital pins 8-15
  {
    digitalWrite(i, LOW);
  }
}



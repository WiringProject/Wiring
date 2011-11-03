/**
 * Swing LEDs
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates the use of digital pins to turn on one light (LED) at a time
 * in a row of 8 one after the other.
 */

int which = 8;              // variable the keeps which light must be turn on next

void setup()
{
  for (int i = 8; i < 16; i++) // initializes pins 8 to 15 as outputs
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  turn_all_off();              // turns all lights off
  digitalWrite(which, HIGH);   // sets on the current light on
  delay(200);                  // waits for 200 milli seconds
  which = which + 1;           // increment the variable to turn on the next one next time
  if (which > 15)              // check for the range, if greater then 15 goes back to 8
  {
    which = 8;
  }
}

void turn_all_off()        // function to turn off all the lights
{
  for (int i = 8; i < 16; i++)
  {
    digitalWrite(i, LOW);
  }
}



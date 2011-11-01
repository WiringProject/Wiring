/**
 * 7 segment LED display
 * by Jose Ojeda
 * 
 * Shows how to drive a 7 segment LED display.
 * The display shows the numbers from 0 to 9 over and over.
 * Those displays can be common anode (the segments will be ON by turning the pins LOW) or
 * common cathode (the segments will be ON by turning the pins HIGH).
 */

int number = 0;  // variable to keep the number in the display

void turn_all_off()    // function to turn off all the segments
{
  for (int i = 8; i < 16; i++)
  {
    digitalWrite(i, LOW);
  }
}

void setup()
{
  for (int i = 8; i < 16; i++) // set pins 0-7 as outputs
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  turn_all_off();  // turns off the display segments
  if (number == 0) // set pins ON for drawing number 0
  {
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 1) // set pins ON for drawing number 1
  {
    digitalWrite(10, HIGH);
    digitalWrite(15, HIGH);
  }
  if (number == 2) // set pins ON for drawing number 2
  {
    digitalWrite(15, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
  if (number == 3) // set pins ON for drawing number 3
  {
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 4) // set pins ON for drawing number 4
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 5) // set pins ON for drawing number 5
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 6) // set pins ON for drawing number 6
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 7) // set pins ON for drawing number 7
  {
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 8) // set pins ON for drawing number 8
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  if (number == 9) // set pins ON for drawing number 9
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  delay(1000);  // wait for a second
  number = number + 1;  // increment the number
  if (number > 9)   // range check, if greater then 9 go back to 0
  {
    number = 0;
  }
}

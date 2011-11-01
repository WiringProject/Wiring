/**
 * Iteration over digital inputs.
 * 
 * Iteration with a "for" structure over input pins.
 * button switches are wired from pins 8 to 11
 * depending the number of pressed buttons a variable
 * named "force" will hold different values from 0 to 4
 */

int force;

void setup()
{
  Serial.begin(9600);
  for (int i = 8; i < 12; i++)   // sets pins 0-3 as inputs
  {
    pinMode(i, INPUT);
  }
}

void loop()
{
  force = 0;
  for (int i = 8; i < 12; i++)   // calculates how many buttons are pressed
  {
    if (digitalRead(i) == HIGH)
    {
      force = force + 1;  // add 1 to force if the button is pressed
    }
  }
  Serial.print("force is: ");  // print the force value
  Serial.println(force, DEC);
  delay(200);  // wait 200ms for next reading
}


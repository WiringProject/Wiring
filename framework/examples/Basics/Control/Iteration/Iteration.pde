/**
 * Iteration.
 * 
 * Iteration with a "for" structure constructs repetitive structures.
 */

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 100; i++)   // prints numbers from 0 to 99
  {
    Serial.print(i);
    Serial.print(" ");
  }

  for (char c = 'A'; c <= 'z'; c++)   // prints all characters between 'A' and 'z'
  {
    Serial.print(c);
    Serial.print(" ");
  }
}

void loop()
{
}


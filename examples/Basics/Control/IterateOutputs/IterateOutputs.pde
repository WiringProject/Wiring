/**
 * Iteration over digital outputs.
 * 
 * Iteration with a "for" structure over output pins.
 * LEDs are wired from pins 8 to 15
 */

void setup()
{
  Serial.begin(9600);
  for (int i = 8; i < 16; i++)   // sets pins 8-15 as outputs
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  for (int i = 8; i < 16; i++)   // sets pins 8-15 to HIGH
  {
    digitalWrite(i, HIGH);
    delay(100);  // delay to see the sequence
  }
  for (int i = 8; i < 16; i++)   // sets pins 8-15 to LOW
  {
    digitalWrite(i, LOW);
    delay(100);  // delay to see the sequence
  }
}


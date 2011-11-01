/**
 * Setup and Loop.
 * 
 * The loop() function creates a structure in which
 * to write programs that change with time.
 */

// The statements in the setup() function
// execute once when the program begins
void setup()
{
  pinMode(WLED, OUTPUT); // Set the pin WLED (onboard LED) as OUTPUT
  digitalWrite(WLED, HIGH); // Set the pin WLED as HIGH (turn ON the onboard LED)
}

int y = 100;

// The statements in loop() are executed until the
// board is stopped. Each statement is executed in
// sequence and after the last line is read, the first
// line is executed again.
void loop()
{
  if (y > 0)   // Blink the LED while y > 0
  {
    digitalWrite(WLED, LOW);
    delay(100);
    digitalWrite(WLED, HIGH);
    delay(100);
  }
  y = y - 1;
}


/**
 * Loop.
 * 
 * The loop() function execute continuously.
 * the setup() is only executed once.
 * In this example the onboard LED blinks forever every two seconds
 */

// The statements in the setup() function
// execute once when the program begins
void setup()
{
  pinMode(WLED, OUTPUT); // Set pin WLED (onboard LED) to OUTPUT
}

// The statements in loop() are run until the
// board is stopped. Each statement is run in
// sequence and after the last line is read, the first
// line is run again.
void loop()
{
  digitalWrite(WLED, HIGH);
  delay(2000);
  digitalWrite(WLED, LOW);
  delay(2000);
}


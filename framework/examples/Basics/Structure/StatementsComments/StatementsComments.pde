/**
 * Statements and Comments.
 * 
 * Statements are the elements that make up programs.
 * The ";" (semi-colon) symbol is used to end statements.
 * It is called the "statement terminator."
 * Comments are used for making notes to help people better understand programs.
 * A comment begins with two forward slashes ("//").
 */

// The pinMode function is a statement that tells the Wiring board
// to set a pin as INPUT or OUTPUT.
// Each function statement has zero or more parameters.
// Parameters are data passed into the function
// and used as values for specifying what the hardware will do.

void setup()
{
  pinMode(WLED, OUTPUT);
  digitalWrite(WLED, HIGH);
}

// The digitalWrite function is a statement that tells the hardware
// which value to set a pin, HIGH or LOW

void loop()
{
  // nothing for loop()
}

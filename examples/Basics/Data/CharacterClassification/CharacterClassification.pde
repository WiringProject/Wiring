/**
 * Character Classification.
 * 
 * Characters are typographic symbols such as A, d, and %.
 * The character datatype, abbreviated as char, stores letters and
 * symbols in the ascii format. Characters are distinguished from other
 * symbols by putting them between single quotes ('P').
 * This example demonstrates the use of character classification
 * and conversion commands.
 */

char tab = '\t';    // tab character
char digit = '1';   // digit character
char upperA = 'A';  // upper case 'A'
char lowerA = 'a';  // lower case 'a'
char colon = ',';   // comma
char val;

void setup()
{
  Serial.begin(9600);
  val = toLowerCase(upperA);
  Serial.print(val);                        // prints 'a'
  Serial.print(" ");
  Serial.print(isAlphaNumeric(digit), DEC); // prints 1 (true)
  Serial.print(" ");
  Serial.print(isAlpha(upperA), DEC);       // prints 1 (true)
  Serial.print(" ");
  Serial.print(isAscii(upperA), DEC);       // prints 1 (true)
  Serial.print(" ");
  Serial.print(isWhitespace(tab), DEC);     // prints 1 (true)
  Serial.print(" ");
  Serial.print(isGraph(lowerA), DEC);       // prints 1 (true)
  Serial.print(" ");
  Serial.print(isLowerCase(lowerA), DEC);   // prints 1 (true)
  Serial.print(" ");
  Serial.print(isSpace(val), DEC);          // prints 0 (false)
  Serial.print(" ");
  Serial.print(isUpperCase(upperA), DEC);   // prints 1 (true)
  Serial.print(" ");
  Serial.print(isControl(upperA), DEC);     // prints 0 (false)
  Serial.print(" ");
  Serial.print(isDigit(digit), DEC);        // prints 1 (true)
  Serial.print(" ");
  Serial.print(isGraph(digit), DEC);        // prints 1 (true)
  Serial.print(" ");
  Serial.print(isPunct(colon), DEC);        // prints 1 (true)
  Serial.print(" ");
  Serial.print(isHexadecimalDigit('F'), DEC);  // prints 1 (true)
  Serial.print(" ");
  val = toLowerCase('K');                   // prints 'k'
  Serial.print(val);
  Serial.print(" ");
  val = toAscii(40);
  Serial.println(val);                      // prints '('
}

void loop()
{

}


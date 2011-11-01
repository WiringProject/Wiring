/**
 * Datatype Conversion.
 * 
 * It is sometimes beneficial to convert a value from one type of
 * data to another. Each of the conversion functions converts its parameter
 * to an equivalent representation within its datatype.
 * The conversion functions include int(), float(), char(), byte(), and others.
 */

char c;    // Chars are used for storing typographic symbols
float f;   // Floats are decimal numbers
int i;     // Ints are values between -32,768 and 32.767
byte b;    // Bytes are values between 0 and 255

void setup()
{
  c = 'A';
  f = float(c);     // Sets f = 65.0
  i = int(f * 1.4); // Sets i to 91
  b = (c / 2);  // Sets b to 32
  Serial.begin(9600);
  Serial.println(c);
  Serial.println(f);
  Serial.println(i);
  Serial.println(b, DEC);
}

void loop()
{

}


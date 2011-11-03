/**
 * Characters Strings.
 * 
 * Characters are typographic symbols such as A, d, and %.
 * The character datatype, abbreviated as char, stores letters and
 * symbols in the Unicode format, a coding system developed to support
 * a variety of world languages. Characters are distinguished from other
 * symbols by putting them between single quotes ('P').
 * A string is a sequence of characters. A string is noted by surrounding
 * a group of letters with double quotes ("Wiring").
 * Chars and strings are most often used with the serial methods,
 * to print text to the serial port and visualize it in the Wiring console.
 */

char letter;

void setup()
{
  Serial.begin(9600);
  // The String datatype must be capitalized because it is a complex datatype.
  // A String is actually a class with its own methods, some of which are
  // featured below.
  String name = "rathausFrog";
  String extension = ".jpg";
  int nameLength = name.length();
  Serial.println("The length of " + name + " is " + String(nameLength) + ".");
  name.concat(extension);
  nameLength = name.length();
  Serial.println("The length of " + name + " is " + String(nameLength) + ".");
}

void loop()
{
  for (letter = 'A'; letter < 'Z'; letter++)
  {
    Serial.print(letter);
  }
  Serial.println();
  delay(1000);
}

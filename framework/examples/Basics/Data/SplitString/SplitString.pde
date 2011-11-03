/**
 * Characters Strings.
 * 
 * Splits the given String int a Vector of numbers and print the resulting
 * vector to the serial port.
 * Characters are typographic symbols such as A, d, and %.
 * The character datatype, abbreviated as char, stores letters and
 * symbols in the Unicode format, a coding system developed to support
 * a variety of world languages. Characters are distinguished from other
 * symbols by putting them between single quotes ('W').
 * A string is a sequence of characters. A string is noted by surrounding
 * a group of letters with double quotes ("Wiring").
 * Chars and strings are most often used with the serial methods,
 * to print text to the serial port and visualize it in the serial monitor.
 */

String str = String("1240,87000,10,30,20,1200");  // The string to split
Vector <long> numVector;  // Vector of long numbers

void setup()
{
  Serial.begin(9600);
  pinMode(WLED, OUTPUT);  // turn ON wiring hardware LED
  digitalWrite(WLED, HIGH);

  // split str using ',' as separator and store the resolt on numVector
  splitString(str, ',', numVector);
  for (int i = 0; i < numVector.size(); i++)
  {
    // print the contents of numVector
    Serial.println(numVector.get(i), DEC);
  }
}

void loop()
{

}

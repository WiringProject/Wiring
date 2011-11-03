/**
 * String Case changes
 * by Tom Igoe
 * 
 * Examples of how to change the case of a string
 */

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\nString  case changes:");
}

void loop()
{
  // toUpperCase() changes all letters to upper case:
  String stringOne = "<html><head><body>";
  Serial.println(stringOne);
  stringOne.toUpperCase();
  Serial.println(stringOne);

// toLowerCase() changes all letters to lower case:
  String stringTwo = "</BODY></HTML>";
  Serial.println(stringTwo);
  stringTwo.toLowerCase();
  Serial.println(stringTwo);


  // do nothing while true:
  while (true);
}

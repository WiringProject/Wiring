/**
 * String replace()
 * by Tom Igoe
 * 
 * Examples of how to replace characters or substrings of a string
 */

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\nString  replace:");
}

void loop()
{
  String stringOne = "<html><head><body>";
  Serial.println(stringOne);
  // replace() changes all instances of one substring with another:
  stringOne.replace("<", "</");
  String stringTwo = stringOne;
  Serial.println(stringTwo);

  // you can also use replace() on single characters:
  String normalString = "bookkeeper";
  Serial.println("normal: " + normalString);
  normalString.replace('o', '0');
  String leetString = normalString;
  leetString.replace('e', '3');
  Serial.println("l33tspeak: " + leetString);

  // do nothing while true:
  while (true);
}

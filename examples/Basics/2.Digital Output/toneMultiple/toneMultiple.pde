/**
 * Multiple tone player
 * by Tom Igoe
 * 
 * Plays multiple tones on multiple pins in sequence
 * circuit:
 * 3 8-ohm speaker on digital pins 8, 9, and 10
 * based on a snippet from Greg Borenstein
 */

void setup()
{
}

void loop()
{
  // turn off tone function for pin 10:
  noTone(10);
  // play a note on pin 8 for 200 ms:
  tone(8, 440, 200);
  delay(200);

  // turn off tone function for pin 8:
  noTone(8);
  // play a note on pin 9 for 500 ms:
  tone(9, 494, 500);
  delay(500);

  // turn off tone function for pin 7:
  noTone(9);
  // play a note on pin 10 for 500 ms:
  tone(10, 523, 300);
  delay(300);
}


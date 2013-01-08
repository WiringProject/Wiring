/**
 * Button
 * by Brett Hagman http://roguerobotics.com/
 *    and BREVIG http://alexanderbrevig.com/
 *
 * Use a button connected to digital pin 5.
 * Digital pin 5 is used as input and connected to a button.
 * When the button is pressed, the Wiring board LED will turn ON.
 * The LED turns OFF when the button is released.
 *
 * The button is debounced.
 */

#include <Button.h>

const int buttonPin = 5;
/*
  Wire like this:
  GND -----/ button ------ pin 5
*/

// Instantiate our button, setting the appropriate mode.
// (BUTTON_PULLDOWN, BUTTON_PULLUP, or BUTTON_PULLUP_INTERNAL)
Button button = Button(buttonPin, BUTTON_PULLUP_INTERNAL);

void setup()
{
  pinMode(WLED, OUTPUT);
}

void loop()
{
  if (button.scan())
  {
    digitalWrite(WLED, HIGH);
  }
  else
  {
    digitalWrite(WLED, LOW);
  }
}


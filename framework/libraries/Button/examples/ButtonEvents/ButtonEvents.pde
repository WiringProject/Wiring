/**
 * ButtonEvents
 * by Brett Hagman http://roguerobotics.com/
 *    and BREVIG http://alexanderbrevig.com/
 *
 * Use a button connected to digital pin 5.
 * Digital pin 5 is used as input and connected to a button.
 *
 * This example demonstates the event API for buttons.
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

// Define the event handlers first.
void handleButtonPressEvents(Button &btn)
{
  Serial.print(Constant("press"));
  if (btn.getClickCount() > 1)
  {
    Serial.print(Constant(" <multiClick "));
    Serial.print(btn.getClickCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}

void handleButtonReleaseEvents(Button &btn)
{
  Serial.println(Constant("release"));
}

void handleButtonClickEvents(Button &btn)
{
  Serial.print(Constant("click"));
  if (btn.getClickCount() > 1)
  {
    Serial.print(Constant(" <multiClick "));
    Serial.print(btn.getClickCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}

void handleButtonHoldEvents(Button &btn)
{
  Serial.print(Constant("hold"));
  if (btn.getHoldRepeatCount() > 0)
  {
    Serial.print(Constant(" <holdRepeat "));
    Serial.print(btn.getHoldRepeatCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}

// Do your regular setup stuff here
void setup()
{
  Serial.begin(9600);

  button.pressHandler(handleButtonPressEvents);
  button.releaseHandler(handleButtonReleaseEvents);
  button.clickHandler(handleButtonClickEvents);
  // Hold event handler - first event @ 1000 ms,
  button.holdHandler(handleButtonHoldEvents, 1000);
  // and repeat every 500 ms.
  button.setHoldRepeat(500);
  // Turn on multi click handling with a 350 ms threshold.
  button.setMultiClickThreshold(250);
}

void loop()
{
  button.scan(); // Update internal state
  /*
    Feel free to do your own processing here.
    The buttons will be handled 'automagically' by the handler functions.
  */
}


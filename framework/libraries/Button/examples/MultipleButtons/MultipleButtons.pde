/**
 * MultipleButtons
 * by Brett Hagman http://roguerobotics.com/
 *    and BREVIG http://alexanderbrevig.com/
 *
 * Use two buttons connected to digital pin 4 and 5.
 *
 * This example demonstates how to work with multiple buttons.
 */

#include <Button.h>

const int button1Pin = 4;
const int button2Pin = 5;
/*
  Wire like this:
  GND -----/ button ------ pin 4
  GND -----/ button ------ pin 5
*/

// Instantiate our buttons, setting the appropriate mode for each.
// (BUTTON_PULLDOWN, BUTTON_PULLUP, or BUTTON_PULLUP_INTERNAL)
Button button1 = Button(button1Pin, BUTTON_PULLUP_INTERNAL);
Button button2 = Button(button2Pin, BUTTON_PULLUP_INTERNAL);

// Define the event handlers first.
void handleButtonPressEvents(Button &btn)
{
  Serial.print(Constant("Button on pin "));
  Serial.print(btn.getPin(), DEC);
  Serial.print(Constant(" press"));
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
  Serial.print(Constant("Button on pin "));
  Serial.print(btn.getPin(), DEC);
  Serial.println(Constant(" release"));
}

void handleButtonClickEvents(Button &btn)
{
  Serial.print(Constant("Button on pin "));
  Serial.print(btn.getPin(), DEC);
  Serial.print(Constant(" click"));
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
  Serial.print(Constant("Button on pin "));
  Serial.print(btn.getPin(), DEC);
  Serial.print(Constant(" hold"));
  if (btn.getHoldRepeatCount() > 0)
  {
    Serial.print(Constant(" <holdRepeat "));
    Serial.print(btn.getHoldRepeatCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}

void scanButtons()
{
  button1.scan();
  button2.scan();
}

// Do your regular setup stuff here
void setup()
{
  Serial.begin(9600);

  button1.pressHandler(handleButtonPressEvents);
  button1.releaseHandler(handleButtonReleaseEvents);
  button1.clickHandler(handleButtonClickEvents);
  button1.holdHandler(handleButtonHoldEvents, 1000);
  button1.setHoldRepeat(500);
  button1.setMultiClickThreshold(250);

  button2.pressHandler(handleButtonPressEvents);
  button2.releaseHandler(handleButtonReleaseEvents);
  button2.clickHandler(handleButtonClickEvents);
  button2.holdHandler(handleButtonHoldEvents, 1000);
  button2.setHoldRepeat(500);
  button2.setMultiClickThreshold(250);
}

void loop()
{
  scanButtons(); // Update internal state
  /*
    Feel free to do your own processing here.
    The buttons will be handled 'automagically' by the handler functions.
  */
}


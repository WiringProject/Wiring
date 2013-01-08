/**
 * ButtonPolling
 * by Brett Hagman http://roguerobotics.com/
 *    and BREVIG http://alexanderbrevig.com
 *
 * Use a button connected to digital pin 5.
 * Digital pin 5 is used as input and connected to a button.
 *
 * This is similar to ButtonEvents example, but it uses polling technique.
 */

#include <Button.h>

const int buttonPin = 5;
/*
  Wire like this:
  GND -----/ button ------ pin 5
*/

// Instantiate our button, setting the appropriate mode
// (BUTTON_PULLDOWN, BUTTON_PULLUP, or BUTTON_PULLUP_INTERNAL)
Button button = Button(buttonPin, BUTTON_PULLUP_INTERNAL);


// Do your regular setup stuff here
void setup()
{
  Serial.begin(9600);

  button.setMultiClickThreshold(250);
}

void loop()
{
  button.scan(); // Update internal state.

  // Now see if things have changed.
  if (button.stateChanged())
  {
    if (button.isPressed())
    {
      handleButtonPressEvent();
    }
    else
    {
      handleButtonReleaseEvent();
    }
  }

  // Clicks are separate, since there can be multiple clicks.
  if (button.clicked())
  {
    handleButtonClickEvent();
  }

  // As well as the button being held. Let's check if it's been held for
  // over 1000 ms.
  if (button.held(1000))
  {
    handleButtonHoldEvent();
  }
}


// Event handlers.
void handleButtonPressEvent()
{
  Serial.print(Constant("press"));
  if (button.getClickCount() > 1)
  {
    Serial.print(Constant(" <multiClick "));
    Serial.print(button.getClickCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}

void handleButtonReleaseEvent()
{
  Serial.println(Constant("release"));
}

void handleButtonClickEvent()
{
  unsigned int clicks = button.getClickCount();

  if (clicks > 0)
  {
    Serial.print(Constant("click"));
    if (clicks > 1)
    {
      Serial.print(Constant(" <multiClick "));
      Serial.print(clicks);
      Serial.print(Constant(">"));
    }
    Serial.println();
  }
}

void handleButtonHoldEvent()
{
  Serial.print(Constant("hold"));
  if (button.getHoldRepeatCount() > 0)
  {
    Serial.print(Constant(" <holdRepeat "));
    Serial.print(button.getHoldRepeatCount());
    Serial.print(Constant(">"));
  }
  Serial.println();
}


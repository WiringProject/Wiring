/**
 * MulitClickEventButton
 * by Simon Kirchner
 * 
 * Use a button connected to digital pin 12.
 * Digital pin 12 is used as input and connected to a button
 * 
 * This example demonstates the event API for buttons and the new multiclick event
 * Multi click will not work if delay is used since it needs the button.iPressed to 
 * get read before the multiClickTreshold has passed.
 * Look at this example if you need multiclick with blinking leds
 * http://arduino.cc/en/Tutorial/BlinkWithoutDelay
 */
 
#include <Button.h>

/*
  Wire like this:
  GND -----/ button ------ pin 12
*/
Button button = Button(12,BUTTON_PULLUP_INTERNAL);

/*
  Define the event handler first
*/
void handleButtonPressEvents(Button &btn)
{
  Serial.println("press");
}

void handleButtonReleaseEvents(Button &btn)
{
  Serial.println("release");
}

void handleButtonClickEvents(Button &btn)
{
  Serial.println("click");
}

void handleButtonMultiClickEvents(Button &btn)
{
  Serial.println("multiclick");
}

void handleButtonHoldEvents(Button &btn)
{
  Serial.println("hold");
}

void setup()
{
  Serial.begin(9600);
  
  button.pressHandler(handleButtonPressEvents);
  button.releaseHandler(handleButtonReleaseEvents);
  button.clickHandler(handleButtonClickEvents);
  button.multiClickHandler(handleButtonMultiClickEvents, 300);
  button.holdHandler(handleButtonHoldEvents, 1500);
}

void loop()
{
  button.isPressed(); //update internal state
  /*
    Feel free to do your own processing here. 
    The buttons will be handeled 'automagically' by the handler functions
  */
}
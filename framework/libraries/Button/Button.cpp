/* $Id: Button.cpp 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Hardware Abstraction Library for Buttons.
|| | It provides an easy way of handling buttons.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include <Wiring.h>
#include "Button.h"

#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2

/*
|| @constructor
|| | Set the initial state of this button
|| #
||
|| @parameter buttonPin  sets the pin that this switch is connected to
|| @parameter buttonMode indicates BUTTON_PULLUP or BUTTON_PULLDOWN resistor
*/
Button::Button(uint8_t buttonPin, uint8_t buttonMode)
{
  pin = buttonPin;
  pinMode(pin, INPUT);

  buttonMode == BUTTON_PULLDOWN ? pulldown() : pullup(buttonMode);
  state = 0;
  bitWrite(state, CURRENT, !mode);

  cb_onPress = 0;
  cb_onRelease = 0;
  cb_onClick = 0;
  cb_onHold = 0;

  numberOfPresses = 0;
  triggeredHoldEvent = true;
}

/*
|| @description
|| | Prepare logic for a pullup button.
|| | If mode is internal set pin HIGH as default
|| #
*/
void Button::pullup(uint8_t buttonMode)
{
  mode = BUTTON_PULLUP;
  if (buttonMode == BUTTON_PULLUP_INTERNAL)
  {
    digitalWrite(pin, HIGH);
  }
}

/*
|| @description
|| | Set pin LOW as default
|| #
*/
void Button::pulldown(void)
{
  mode = BUTTON_PULLDOWN;
}

/*
|| @description
|| | Return the bitRead(state,CURRENT) of the switch
|| #
||
|| @return true if button is pressed
*/
bool Button::isPressed(void)
{
  //save the previous value
  bitWrite(state, PREVIOUS, bitRead(state, CURRENT));

  //get the current status of the pin
  if (digitalRead(pin) == mode)
  {
    //currently the button is not pressed
    bitWrite(state, CURRENT, false);
  }
  else
  {
    //currently the button is pressed
    bitWrite(state, CURRENT, true);
  }

  //handle state changes
  if (bitRead(state, CURRENT) != bitRead(state, PREVIOUS))
  {
    //the state changed to PRESSED
    if (bitRead(state, CURRENT) == true)
    {
      numberOfPresses++;
      if (cb_onPress)
      {
        cb_onPress(*this);  //fire the onPress event
      }
      pressedStartTime = millis();             //start timing
      triggeredHoldEvent = false;
    }
    else //the state changed to RELEASED
    {
      if (cb_onRelease)
      {
        cb_onRelease(*this);  //fire the onRelease event
      }
      if (cb_onClick)
      {
        cb_onClick(*this);  //fire the onClick event AFTER the onRelease
      }
      //reset states (for timing and for event triggering)
      pressedStartTime = -1;
    }
    //note that the state changed
    bitWrite(state, CHANGED, true);
  }
  else
  {
    //note that the state did not change
    bitWrite(state, CHANGED, false);
    //should we trigger a onHold event?
    if (pressedStartTime != -1 && !triggeredHoldEvent)
    {
      if (millis() - pressedStartTime > holdEventThreshold)
      {
        if (cb_onHold)
        {
          cb_onHold(*this);
          triggeredHoldEvent = true;
        }
      }
    }
  }
  return bitRead(state, CURRENT);
}

/*
|| @description
|| | Return true if the button has been pressed
|| #
*/
bool Button::wasPressed(void)
{
  return bitRead(state, CURRENT);
}

/*
|| @description
|| | Return true if state has been changed
|| #
*/
bool Button::stateChanged(void)
{
  return bitRead(state, CHANGED);
}

/*
|| @description
|| | Return true if the button is pressed, and was not pressed before
|| #
*/
bool Button::uniquePress(void)
{
  return (isPressed() && stateChanged());
}

/*
|| @description
|| | onHold polling model
|| | Check to see if the button has been pressed for time ms
|| | This will clear the counter for next iteration and thus return true once
|| #
*/
bool Button::held(unsigned int time /*=0*/)
{
  unsigned int threshold = time ? time : holdEventThreshold; //use holdEventThreshold if time == 0
  //should we trigger a onHold event?
  if (pressedStartTime != -1 && !triggeredHoldEvent)
  {
    if (millis() - pressedStartTime > threshold)
    {
      triggeredHoldEvent = true;
      return true;
    }
  }
  return false;
}

/*
|| @description
|| | Polling model for holding, this is true every check after hold time
|| | Check to see if the button has been pressed for time ms
|| #
*/
bool Button::heldFor(unsigned int time)
{
  if (isPressed())
  {
    if (millis() - pressedStartTime > time)
    {
      return true;
    }
  }
  return false;
}

/*
|| @description
|| | Set the hold event time threshold
|| #
*/
void Button::setHoldThreshold(unsigned int holdTime)
{
  holdEventThreshold = holdTime;
}

/*
|| @description
|| | Register a handler for presses on this button
|| #
||
|| @parameter handler The function to call when this button is pressed
*/
void Button::pressHandler(buttonEventHandler handler)
{
  cb_onPress = handler;
}

/*
|| @description
|| | Register a handler for releases on this button
|| #
||
|| @parameter handler The function to call when this button is released
*/
void Button::releaseHandler(buttonEventHandler handler)
{
  cb_onRelease = handler;
}

/*
|| @description
|| | Register a handler for clicks on this button
|| #
||
|| @parameter handler The function to call when this button is clicked
*/
void Button::clickHandler(buttonEventHandler handler)
{
  cb_onClick = handler;
}

/*
|| @description
|| | Register a handler for when this button is held
|| #
||
|| @parameter handler The function to call when this button is held
*/
void Button::holdHandler(buttonEventHandler handler, unsigned int holdTime /*=0*/)
{
  if (holdTime > 0)
  {
    setHoldThreshold(holdTime);
  }
  cb_onHold = handler;
}

/*
|| @description
|| | Get the time this button has been held
|| #
||
|| @return The time this button has been held
*/
unsigned int Button::holdTime() const
{
  if (pressedStartTime != -1)
  {
    return millis() - pressedStartTime;
  }
  else return 0;
}

/*
|| @description
|| | Compare a button object against this
|| #
||
|| @parameter  rhs the Button to compare against this Button
||
|| @return true if they are the same
*/
bool Button::operator==(Button &rhs)
{
  return (this == &rhs);
}


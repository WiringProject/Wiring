/*
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   https://github.com/cyborgsimon
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

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#define BUTTON_PULLUP HIGH
#define BUTTON_PULLUP_INTERNAL 2
#define BUTTON_PULLDOWN LOW

class Button;
typedef void (*buttonEventHandler)(Button&);

class Button
{
  public:

    Button(uint8_t buttonPin, uint8_t buttonMode = BUTTON_PULLUP_INTERNAL);

    void pullup(uint8_t buttonMode);
    void pulldown();

    bool isPressed();
    bool wasPressed();
    bool stateChanged();
    bool uniquePress();

    void setDebounceTime(unsigned int debounce);
    void setHoldThreshold(unsigned int holdTime);
    void setMultiClickThreshold(unsigned int multiClickTime);
    bool held(unsigned int time = 0);
    bool heldFor(unsigned int time);

    void pressHandler(buttonEventHandler handler);
    void releaseHandler(buttonEventHandler handler);
    void clickHandler(buttonEventHandler handler);
    void holdHandler(buttonEventHandler handler, unsigned int holdTime = 0);

    unsigned int holdTime() const;
    // returns the total count of presses
    inline unsigned int presses() const
    {
      return numberOfPresses;
    }
    // returns the count of "multi" clicks
    unsigned int getClickCount();

    bool operator==(Button &rhs);

  private:
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    unsigned long pressedStartTime;
    unsigned long lastPressStartTime;
    unsigned int debounceTime;
    unsigned int holdEventThreshold;
    unsigned int multiClickEventThreshold;
    buttonEventHandler cb_onPress;
    buttonEventHandler cb_onRelease;
    buttonEventHandler cb_onClick;
    buttonEventHandler cb_onHold;
    unsigned int numberOfPresses; // holds the total count of presses
    unsigned int clickCount; // holds the count of clicks
    bool triggeredHoldEvent;
};

#endif
// BUTTON_H

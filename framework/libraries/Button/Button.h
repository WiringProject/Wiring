/*
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
|| @contribution   https://github.com/cyborgsimon
|| @contribution   Chris van Marle (DebounceButton Library)
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

    // Constructor
    Button(uint8_t buttonPin, uint8_t buttonMode = BUTTON_PULLUP_INTERNAL);

    // Public Member
    uint8_t ID;

    // Methods
    void pullup(uint8_t buttonMode);
    void pulldown();
    bool scan();
    bool isPressed() const;
    bool stateChanged() const;
    bool uniquePress() const;
    unsigned int clicked();
    bool held(unsigned long time = 0);
    bool heldFor(unsigned long time) const;

    // Properties
    uint8_t getPin(void) const
    {
      return pin;
    }
    void setDebounceDelay(unsigned int debounceDelay);
    void setHoldThreshold(unsigned int holdTime);
    void setHoldRepeat(unsigned int repeatTime);
    void setMultiClickThreshold(unsigned int multiClickTime);
    void pressHandler(buttonEventHandler handler);
    void releaseHandler(buttonEventHandler handler);
    void clickHandler(buttonEventHandler handler);
    void holdHandler(buttonEventHandler handler, unsigned long holdTime = 0);

    unsigned long holdTime() const;
    unsigned long heldTime() const;
    inline unsigned long presses() const
    {
      return numberOfPresses;
    }

    inline unsigned int getClickCount() const
    {
      return clickCount;
    }

    inline unsigned int getHoldRepeatCount() const
    {
      return holdEventRepeatCount;
    }

    bool operator==(Button &rhs);

  private:
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    unsigned long pressedStartTime;
    unsigned long debounceStartTime;
    unsigned long debounceDelayTime;
    unsigned long holdEventThresholdTime;
    unsigned long holdEventRepeatTime;
    unsigned long holdEventPreviousTime;
    unsigned long lastReleaseTime;
    unsigned long multiClickThresholdTime;
    buttonEventHandler cb_onPress;
    buttonEventHandler cb_onRelease;
    buttonEventHandler cb_onClick;
    buttonEventHandler cb_onHold;
    unsigned long numberOfPresses;
    unsigned int clickCount;
    unsigned int holdEventRepeatCount;
    bool triggeredHoldEvent;
};

#endif
// BUTTON_H

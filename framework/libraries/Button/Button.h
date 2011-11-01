/* $Id: Button.h 1198 2011-06-14 21:08:27Z bhagman $
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

    void setHoldThreshold(unsigned int holdTime);
    bool held(unsigned int time = 0);
    bool heldFor(unsigned int time);

    void pressHandler(buttonEventHandler handler);
    void releaseHandler(buttonEventHandler handler);
    void clickHandler(buttonEventHandler handler);
    void holdHandler(buttonEventHandler handler, unsigned int holdTime = 0);

    unsigned int holdTime() const;
    inline unsigned int presses() const
    {
      return numberOfPresses;
    }

    bool operator==(Button &rhs);

  private:
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    unsigned int pressedStartTime;
    unsigned int holdEventThreshold;
    buttonEventHandler cb_onPress;
    buttonEventHandler cb_onRelease;
    buttonEventHandler cb_onClick;
    buttonEventHandler cb_onHold;
    unsigned int numberOfPresses;
    bool triggeredHoldEvent;
};

#endif
// BUTTON_H

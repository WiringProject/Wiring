/* $Id: Keypad.h 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Alexander Brevig <abrevig@wiring.org.co>
|| @url            http://wiring.org.co/
|| @url            http://alexanderbrevig.com/
|| @contribution   Mark Stanley
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | This is a Hardware Abstraction Library for matrix Keypads.
|| | This library provides a simple interface for using matrix
|| | keypads. It supports the use of multiple keypads with the
|| | same or different sets of keys.  It also supports user
|| | selectable pins and definable keymaps.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef KEYPAD_H
#define KEYPAD_H

#include <Wiring.h>

#define makeKeymap(x) ((char*)x)

typedef char KeypadEvent;

/// enumerate the possible states of this keypad
typedef enum
{
  IDLE = 0,
  PRESSED,
  RELEASED,
  HOLD
} KeypadState;

/// define a structure that holds the size of the keypad
typedef struct
{
  byte rows;
  byte columns;
} KeypadSize;

/// for readability in user code when polling the state
const char NO_KEY = '\0';
/// alias for readability
#define KEY_RELEASED NO_KEY

class Keypad
{
  public:
    Keypad(char *userKeymap, byte *row, byte *col, byte rows, byte cols);

    void begin(char *userKeymap);

    char getKey();
    KeypadState getState();
    unsigned int getPressCount();

    void setMultiPressTime(unsigned int multipress);
    void setDebounceTime(unsigned int debounce);
    void setHoldTime(unsigned int hold);
    
    //@deprecated
    void addEventListener(void (*listener)(char)) {
      setEventListener(listener);
    }
    void setEventListener(void (*listener)(char));

  private:
    void transitionTo(KeypadState newState);
    void initializePins();

    char *keymap;
    byte *rowPins;
    byte *columnPins;
    KeypadSize size;
    KeypadState state;
    char currentKey;
    char lastKey;
    unsigned int pressCount;
    unsigned long lastUpdate;
    unsigned long lastPress;
    unsigned int multiPressTime;
    unsigned int debounceTime;
    unsigned int holdTime;

    void (*keypadEventListener)(char);
};

#endif
// KEYPAD_H

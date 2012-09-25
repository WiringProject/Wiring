/**
 * MultiPressEventKeypad
 * by https://github.com/cyborgsimon
 * 
 * This example demonstates the event API for keypads and the new 
 * Multi press will not work if delay is used since it needs the keypad.getKey to 
 * get read before the multiPressTime has passed.
 * Look at this example if you need multi press with blinking leds
 * http://arduino.cc/en/Tutorial/BlinkWithoutDelay
 */
 
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  Serial.print(key);
  switch (keypad.getState()){
    case PRESSED:
      Serial.println(" PRESSED");
      Serial.print("press count: ");
      Serial.println(keypad.getPressCount());
    break;
    case RELEASED:
      Serial.println(" RELEASED");
    break;
    case HOLD:
      Serial.println(" HOLD");
    break;
  }
}

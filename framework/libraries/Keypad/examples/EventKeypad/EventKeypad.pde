/**
 * EventKeypad
 * by BREVIG http://alexanderbrevig.com
 * 
 * This is a simple demonstration using the KeypadEvent
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
byte ledPin = 13; 

boolean blink = false;

void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    Serial.println(key);
  }
  if (blink){
    digitalWrite(ledPin,!digitalRead(ledPin));
    delay(100);
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){
        case '#': digitalWrite(ledPin,!digitalRead(ledPin)); break;
        case '*': 
          digitalWrite(ledPin,!digitalRead(ledPin));
        break;
      }
    break;
    case RELEASED:
      switch (key){
        case '*': 
          digitalWrite(ledPin,!digitalRead(ledPin));
          blink = false;
        break;
      }
    break;
    case HOLD:
      switch (key){
        case '*': blink = true; break;
      }
    break;
  }
}

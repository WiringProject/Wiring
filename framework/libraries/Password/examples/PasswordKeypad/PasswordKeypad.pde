/**
 * PasswordKeypad
 * by BREVIG http://alexanderbrevig.com
 * 
 * A simple password application that uses a keypad as input source.
 */

#include <Password.h>
#include <Keypad.h> 

Password password = Password( "1234" );

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte ledPin = 13; 

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(ledPin, HIGH);   // sets the LED on
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop()
{
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey)
{
   switch (keypad.getState())
   {
    case PRESSED:
      switch (eKey)
      {
        case '*': guessPassword(); break;
        case '#': password.reset(); break;
        default: 
          password.append(eKey);
      }
    break;
  }
}

void guessPassword()
{
	if (password.evaluate())
  {
		digitalWrite(ledPin,HIGH);
	}
  else
  {
		digitalWrite(ledPin,LOW);
	}
}

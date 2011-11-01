/**
 * SerialMonitor
 * by BREVIG http://alexanderbrevig.com
 * 
 * A simple password application that uses the serial monitor as input source.
 */

#include <Password.h>

Password password = Password( "1234" );

byte currentLength = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Try to guess the password!");
  Serial.println("Reset with ! evaluate with ?");
  Serial.print("Enter password: ");
}

void loop()
{
  if (Serial.available())
  {
    char input = Serial.read();
    switch (input)
    {
      case '!': //reset password
        password.reset();
        currentLength = 0;
        Serial.println("\tPassword is reset!");
      break;
      case '?': //evaluate password
        if (password.evaluate()){
          Serial.println("\tYou guessed the correct password!");
        }else{
          Serial.println("\tYou did not guess the correct password!");
        }
      break;
      default: //append any keypress that is not a '!' nor a '?' to the currently guessed password.
        password << input;
        currentLength++;
        
        //Print some feedback.
        Serial.print("Enter password: ");
        for (byte i=0; i<currentLength; i++)
        {
          Serial.print('*');
        }
        Serial.println();
     }
  }
}

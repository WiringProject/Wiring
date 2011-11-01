/**
 * Basic Communication
 * by Thomas Ouellet Fredericks and Alexandre Quessy
 * 
 * Control the Wiring board functions with the following messages:
 * 
 * r a -> read analog pins
 * r d -> read digital pins
 * w d [pin] [value] -> write digital pin
 * w a [pin] [value] -> write analog pin
 * p m [pin] [value] -> set pin mode
 */


#include <Messenger.h>


// Instantiate Messenger object with the message function and the default separator (the space character)
Messenger message = Messenger(); 

// Define messenger function
void messageCompleted() 
{
  if ( message.checkString("r") ) 
  { // Read pins (analog or digital)
    if ( message.checkString("a") ) 
    {
      Serial.print("a ");
      for (char i=0;i<8;i++) 
      { // Read pins 0 to 8
        Serial.print(analogRead(i),DEC); // Send the pin value
        Serial.print(" "); // Add a space separator
      }
      Serial.println(); // Terminate message
    } 
    else if ( message.checkString("d") ) 
    {
      Serial.print("d ");
      for (char i=0;i<23;i++) 
      { // Read pins 0 to 23
        Serial.print(digitalRead(i),DEC); // Send the pin value
        Serial.print(" "); // Add a space separator
      }
      Serial.println(); // Terminate message
    }
  } 
  else if ( message.checkString("w") ) 
  { // Write pin (analog or digital)
    if ( message.checkString("a") ) 
    {
      int pin = message.readInt();
      int value = message.readInt();
      analogWrite(pin,value); //Sets the PWM of the pin 
    } 
    else if ( message.checkString("d") ) 
    {
      int pin = message.readInt();
      int state = message.readInt();
      digitalWrite(pin,state); //Sets the state of the pin 
    }
  } 
  else if ( message.checkString("p") &&  message.checkString("m") ) 
  { // Pin mode
    int pin = message.readInt();
    int mode = message.readInt();
    pinMode(pin,mode);
  }
}

void setup() 
{
  // Initiate Serial Communication
  Serial.begin(115200); 
  message.attach(messageCompleted);
}

void loop()
{
  // The following line is the most effective way of 
  // feeding the serial data to Messenger
  while (Serial.available()) message.process(Serial.read());
}



/**
 * This example demonstrates Messenger's checkString method
 * It turns on the LED attached to pin 48 if it receives "on"
 * It turns it off if it receives "off"
 */

#include <Messenger.h>


// Instantiate Messenger object with the message function and the default separator 
// (the space character)
Messenger message = Messenger(); 


// Define messenger function
void messageCompleted() {
  // This loop will echo each element of the message separately
  while ( message.available() ) {
    if ( message.checkString("on") ) {
      digitalWrite(48,HIGH);
    } else if ( message.checkString("off") ) {
      digitalWrite(48,LOW);
    }
  }
  
  
}

void setup() {
  // Initiate Serial Communication
  Serial.begin(115200); 
  message.attach(messageCompleted);
  
  pinMode(48,OUTPUT);
  
}

void loop() {
  
  // The following line is the most effective way of 
  // feeding the serial data to Messenger
  while ( Serial.available() ) message.process( Serial.read() );


}


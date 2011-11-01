/** 
 * This example demonstrates Messenger's copy string method
 * It simply echos the string back
 */

#include <Messenger.h>


// Instantiate Messenger object with the message function and the default separator 
// (the space character)
Messenger message = Messenger(); 

// Define the max size of the string
// The size must be big enough to hold the longest string you are expecting
#define MAXSIZE 30 

// Create a char array (string) to hold the received string
char string[MAXSIZE]; 



// Define messenger function
void messageCompleted() {
  // This loop will echo each element of the message separately
  while ( message.available() ) {
    message.copyString(string,MAXSIZE);
    Serial.print(string); // Echo the string
    Serial.println(); // Terminate the message with a carriage return
  }
  
  
}

void setup() {
  // Initiate Serial Communication
  Serial.begin(115200); 
  message.attach(messageCompleted);
}

void loop() {
  
  // The following line is the most effective way of 
  // feeding the serial data to Messenger
  while ( Serial.available() ) message.process( Serial.read() );


}


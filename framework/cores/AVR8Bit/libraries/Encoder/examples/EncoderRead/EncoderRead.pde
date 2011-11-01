/**
 * Encoder read 
 * by BARRAGAN <http://barraganstudio.com> 
 * 
 * Demonstrates the use of an encoder with the Encoder library 
 * Prints the encoder value
 * Encoder's PinA must be attached to External Interrupt pins.
 * On Wiring v1 boards the external interrupts capable pins are: 0, 1, 2, 3, 36, 37, 38 and 39
 * On Wiring S board the external interrupts capable pins are: 2, 3 and 18  
 */

#include <Encoder.h> 
 
int val; 
Encoder myEncoder; 
 
void setup() { 
  // ataches the encoder to pins EI2 and pin 8
  // EI2 is pin 18 on Wiring S
  // EI2 is pin 2 on Wiring v1
  myEncoder.attach(EI2, 8); 
  myEncoder.write(0); // set the encoder position to 0
  Serial.begin(9600);
} 
 
void loop() { 
  // Reads the position or angle of the encoder variable 
  val = myEncoder.read();          // read position
  Serial.print("Encoder is at: "); // print the position
  Serial.println(val);
  delay(100); // wait 100ms for next reading
} 

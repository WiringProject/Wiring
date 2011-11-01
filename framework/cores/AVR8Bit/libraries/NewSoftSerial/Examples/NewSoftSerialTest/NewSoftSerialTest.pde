/** 
 * NewSoftSerial 
 * 
 * Demonstrates the use of software serial ports
 */

#include <NewSoftSerial.h>

NewSoftSerial mySerial(4, 5);

void setup()  
{
  Serial.begin(57600);
  Serial.println("Goodnight moon!");

  // set the data rate for the NewSoftSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void loop()  // run over and over again
{

  if (mySerial.available()) {
    Serial.print((char)mySerial.read());
  }
  if (Serial.available()) {
    mySerial.print((char)Serial.read());
  }
}


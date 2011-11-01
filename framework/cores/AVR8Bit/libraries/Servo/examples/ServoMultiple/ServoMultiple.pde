/**
 * Driving multiple servos
 * by BARRAGAN <http://barraganstudio.com>
 * 
 * Demonstrates the use of the servo library to drive two servo motors. It positions two 
 * generic servo motors at 0, 90 and 180 degrees.
 */

#include <Servo.h>

Servo myservo0;  // create servo object to control a servo
Servo myservo1;  // create another servo object to control another servo

void setup()
{
  myservo0.attach(8);  // attaches the servo on pin 8 to the servo object
  myservo1.attach(9);  // attaches the servo on pin 9 to the other servo object
}


void loop()
{
  myservo0.write(0);    // position first servo at 0 degrees
  myservo1.write(0);    // position second servo at 0 degrees
  delay(1000);          // wait for the servos to reach the desired position
  myservo0.write(90);   // at 90 degrees
  myservo1.write(90);
  delay(500);                     
  myservo0.write(180);  // at 180 degrees
  myservo1.write(180);
  delay(500);                     
}


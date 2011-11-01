/**
 * Controlling a servo position using a slider (variable resistor)
 * by Michal Rinott
 * 
 * Demostrates how to control a servo's position using a slider
 */

#include <Servo.h>

Servo myservo;      // create servo object to control a servo

int sliderpin = 0;  // analog pin used to connect the slider
int sliderValue;    // variable to read the value from the analog pin

void setup()
{
  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
}

void loop()
{
  sliderValue = analogRead(sliderpin);  // reads the value of the slider (value between 0 and 1023)
  sliderValue = sliderValue/5.68;       // scale it to use it with the servo (value between 0 and 180)
  myservo.write(sliderValue);           // sets the servo position according to the scaled value
  delay(15);                            // waits for the servo to get there
}

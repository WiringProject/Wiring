/**
 * HelloTimedAction
 * by BREVIG http://alexanderbrevig.com
 * 
 * This sketch will blink an LED each second
 * A simulation of the well known 'blink' sketch without it blocking execution of loop
 */

#include <TimedAction.h>

//this initializes a TimedAction class that will change the state of an LED every second.
TimedAction timedAction = TimedAction(1000,blink);

//pin / state variables
const byte ledPin = WLED;
boolean ledState = false;

void setup()
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);
}

void loop()
{
  timedAction.check();
  //you can add you code here, it will run 'parallel' to the blink
}

void blink()
{
  ledState ? ledState=false : ledState=true;
  digitalWrite(ledPin,ledState);
}


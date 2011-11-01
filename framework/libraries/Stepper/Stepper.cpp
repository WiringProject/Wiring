/* $Id: Stepper.cpp 1198 2011-06-14 21:08:27Z bhagman $
||
|| @author         Tom Igoe
|| @url            http://wiring.org.co/
|| @contribution   Sebastian Gassner
|| @contribution   David A. Mellis <dam@mellis.org>
|| @contribution   Noah Shibley
|| @contribution   Alexander Brevig <abrevig@wiring.org.co>
|| @contribution   Brett Hagman <bhagman@wiring.org.co>
||
|| @description
|| | Stepper library.
|| | This is a Hardware Abstraction Library for Stepper motors.
|| | Drives a unipolar or bipolar stepper motor using  2 wires or 4 wires.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#include "Stepper.h"

/*
|| @constructor
|| | Initializes the Stepper with two wires
|| #
||
|| @parameter numberOfSteps  The number of steps for this stepper
|| @parameter motorPin1      A pin connected to the stepper
|| @parameter motorPin2      A pin connected to the stepper
*/
Stepper::Stepper(int numberOfSteps, int motorPin1, int motorPin2)
{
  this->stepNumber = 0;     // which step the motor is on
  this->speed = 0;          // the motor speed, in revolutions per minute
  this->direction = 0;      // motor direction
  this->lastStepTime = 0;   // time stamp in ms of the last step taken
  this->numberOfSteps = numberOfSteps;  // total number of steps for this motor

  // Arduino pins for the motor control connection:
  this->motorPin1 = motorPin1;
  this->motorPin2 = motorPin2;

  // setup the pins on the microcontroller:
  pinMode(this->motorPin1, OUTPUT);
  pinMode(this->motorPin2, OUTPUT);

  // When there are only 2 pins, set the other two to 0:
  this->motorPin3 = 0;
  this->motorPin4 = 0;

  // pinCount is used by the stepMotor() method:
  this->pinCount = 2;
}


/*
|| @constructor
|| | Initializes the Stepper with four wires
|| #
||
|| @parameter numberOfSteps  The number of steps for this stepper
|| @parameter motorPin1      A pin connected to the stepper
|| @parameter motorPin2      A pin connected to the stepper
|| @parameter motorPin3      A pin connected to the stepper
|| @parameter motorPin4      A pin connected to the stepper
*/
Stepper::Stepper(int numberOfSteps, int motorPin1, int motorPin2, int motorPin3, int motorPin4)
{
  this->stepNumber = 0;     // which step the motor is on
  this->speed = 0;          // the motor speed, in revolutions per minute
  this->direction = 0;      // motor direction
  this->lastStepTime = 0;   // time stamp in ms of the last step taken
  this->numberOfSteps = numberOfSteps;  // total number of steps for this motor

  // Arduino pins for the motor control connection:
  this->motorPin1 = motorPin1;
  this->motorPin2 = motorPin2;
  this->motorPin3 = motorPin3;
  this->motorPin4 = motorPin4;

  // setup the pins on the microcontroller:
  pinMode(this->motorPin1, OUTPUT);
  pinMode(this->motorPin2, OUTPUT);
  pinMode(this->motorPin3, OUTPUT);
  pinMode(this->motorPin4, OUTPUT);

  // pinCount is used by the stepMotor() method:
  this->pinCount = 4;
}

/*
|| @description
|| | Sets the speed in revs per minute
|| #
||
|| @parameter whatSpeed The value that dictates the revolutions per minute (RPM)
*/
void Stepper::setSpeed(long whatSpeed)
{
  this->stopDelay = 60L * 1000L / this->numberOfSteps / whatSpeed;
}

/*
|| @description
|| | Moves the motor numberOfSteps steps.
|| | If the number is negative, the motor moves in the reverse direction.
|| #
||
|| @parameter numberOfSteps The number of steps to step the stepper
*/
void Stepper::step(int numberOfSteps)
{
  int stepsLeft = abs(numberOfSteps);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (numberOfSteps > 0)
  {
    this->direction = 1;
  }
  if (numberOfSteps < 0)
  {
    this->direction = 0;
  }


  // decrement the number of steps, moving one step each time:
  while (stepsLeft > 0)
  {
    // move only if the appropriate delay has passed:
    if (millis() - this->lastStepTime >= this->stopDelay)
    {
      // step the motor to step number 0, 1, 2, or 3:
      stepMotor(this->stepNumber % 4);
      // get the timeStamp of when you stepped:
      this->lastStepTime = millis();
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1)
      {
        this->stepNumber++;
        if (this->stepNumber == this->numberOfSteps)
        {
          this->stepNumber = 0;
        }
      }
      else
      {
        if (this->stepNumber == 0)
        {
          this->stepNumber = this->numberOfSteps;
        }
        this->stepNumber--;
      }
      // decrement the steps left:
      stepsLeft--;
    }
  }
}

/*
|| @description
|| | Get the version of the library
|| #
||
|| @return The version of this library
*/
int Stepper::version(void) const
{
  return 4;
}

void Stepper::stepMotor(int thisStep)
{
  if (this->pinCount == 2)
  {
    switch (thisStep)
    {
    case 0: /* 01 */
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      break;
    case 1: /* 11 */
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, HIGH);
      break;
    case 2: /* 10 */
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      break;
    case 3: /* 00 */
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      break;
    }
  }
  if (this->pinCount == 4)
  {
    switch (thisStep)
    {
    case 0:    // 1010
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      break;
    case 1:    // 0110
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      break;
    case 2:    //0101
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      break;
    case 3:    //1001
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, HIGH);
      break;
    }
  }
}


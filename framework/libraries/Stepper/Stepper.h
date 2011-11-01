/* $Id: Stepper.h 1198 2011-06-14 21:08:27Z bhagman $
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
|| @notes
|| | When wiring multiple stepper motors to a microcontroller,
|| | you quickly run out of output pins, with each motor requiring 4 connections.
|| |
|| | By making use of the fact that at any time two of the four motor
|| | coils are the inverse  of the other two, the number of
|| | control connections can be reduced from 4 to 2.
|| |
|| | A slightly modified circuit around a Darlington transistor array or an L293 H-bridge
|| | connects to only 2 microcontroller pins, inverts the signals received,
|| | and delivers the 4 (2 plus 2 inverted ones) output signals required
|| | for driving a stepper motor.
|| |
|| | The sequence of control signals for 4 control wires is as follows:
|| |
|| | Step C0 C1 C2 C3
|| |    1  1  0  1  0
|| |    2  0  1  1  0
|| |    3  0  1  0  1
|| |    4  1  0  0  1
|| |
|| | The sequence of controls signals for 2 control wires is as follows
|| | (columns C1 and C2 from above):
|| |
|| | Step C0 C1
|| |    1  0  1
|| |    2  1  1
|| |    3  1  0
|| |    4  0  0
|| |
|| | The circuits can be found at
|| | http://www.arduino.cc/en/Tutorial/Stepper
|| |
|| #
||
|| @license Please see cores/Common/License.txt.
||
*/

#ifndef STEPPER_H
#define STEPPER_H

#include <Wiring.h>

class Stepper
{
  public:
    Stepper(int numberOfSteps, int motorPin1, int motorPin2);
    Stepper(int numberOfSteps, int motorPin1, int motorPin2, int motorPin3, int motorPin4);

    void setSpeed(long whatSpeed);

    void step(int numberOfSteps);

    int version(void) const;

  private:
    void stepMotor(int thisStep);

    int direction;          // Direction of rotation
    int speed;              // Speed in RPMs
    unsigned long stopDelay;  // delay between steps, in ms, based on speed
    int numberOfSteps;      // total number of steps this motor can take
    int pinCount;           // whether you're driving the motor with 2 or 4 pins
    int stepNumber;         // which step the motor is on

    // motor pin numbers:
    int motorPin1;
    int motorPin2;
    int motorPin3;
    int motorPin4;

    unsigned long lastStepTime;  // time stamp in ms of when the last step was taken
};

#endif
// STEPPER_H

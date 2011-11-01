/** 
 * Stepper motor move
 * by BARRAGAN <http://barraganstudio.com>
 * 
 * Demonstrates the use of the Stepper library
 */

#include <Stepper.h> 
 
// change the steps variable to the number of steps on your motor 
int steps = 100; 
 
// create and attaches a stepper motor 
// with 100 steps to pins 8, 9, 10 and 11 
 
Stepper stepper(steps, 8, 9, 10, 11); 
 
void setup() 
{ 
  // set the speed of the motor to 20 rpms 
  stepper.setSpeed(20); 
} 
 
void loop() 
{ 
  // move 20 steps forward 
  stepper.step(20); 
 
  // move 20 steps backwards 
  stepper.step(-20); 
} 

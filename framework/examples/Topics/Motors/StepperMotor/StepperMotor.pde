/**
 * Stepper Motor Sequences
 * by Juan Manuel Gonzalez V.
 * 
 * Demonstrates the use of a TEAC stepper motor using pin commands.
 * TEAC motors rotate 360 degrees in 50 cycles (steps).
 * For the Wiring boards v1 the on-board LED is on pin 48,
 * on Wiring S the on-board LED is on pin 15.
 */

void setup()
{
  int i;
  for (i = 8; i < 12; i++)  // Analog pins for yellow, red,
  {
    pinMode(i, OUTPUT);    // blue and white wires of the motor.
  }

  pinMode(WLED, OUTPUT);     // Wiring board LED
  digitalWrite(WLED, HIGH);
}


void stepforward()         //Drive sequence for one cycle going
{
  //forward.
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(30);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(30);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(30);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(30);
}

void stepbackward()            //Drive sequence for one cycle going
{
  //backward.
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(30);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(30);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(30);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(30);
}

void loop()
{
  stepforward();      //Repeats the required sequence over &
  //over to make the motor turn continuously FW.
  //stepbackward();     //Repeats the required sequence over &
  //over to make the motor turn continuously BW.
}

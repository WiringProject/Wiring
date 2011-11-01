/**
 * External interrupts
 * by BARRAGAN http://barraganstudio.com
 * 
 * Demonstrates how to attend an external interrupts generated on a digital
 * pin. It is possible to generate and attend external interrupts on the Wiring
 * board.
 * WARNING: you should avoid doing long procedures in interrupt routines
 * On Wiring v1 boards the external interrupts capable pins are: 0, 1, 2, 3, 36, 37, 38 and 39
 * On Wiring S board the external interrupts capable pins are: 2, 3 and 18
 */

void setup()
{
  // set myFunction to be called everytime
  // interrupt 2 is generated (everytime the pin gets from LOW to HIGH)
  pinMode(EI2, INPUT); // set External interrupt pin as INPUT
  // On Wiring S pin 18
  // On Wiring v1 pin 2
  pinMode(8, OUTPUT);  // pin to be used as trigger in this example

  attachInterrupt(EXTERNAL_INTERRUPT_2, myFunction, RISING);
  Serial.begin(9600);  // Starts serial to print data
}

void loop()
{
  // pin 8 will be directly attached to the External interrupt 2
  // pin 18 on Wiring S or pin 2 on Wiring v1 boards
  // just to test the interruption generation
  digitalWrite(8, LOW);
  delay(500);
  digitalWrite(8, HIGH);
  delay(500);
}

void myFunction()
{
  // WARNING: you should avoid doing long procedures in interrupt routines
  // Since this is an interrupt routine
  // and Serial is an interrupt driven output
  // interrupts must be enabled before printing
  interrupts();
  Serial.println("Interrupt generated");
}

